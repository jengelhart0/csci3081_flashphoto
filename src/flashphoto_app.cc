/*******************************************************************************
 * Name            : flashphoto_app.cc
 * Project         : FlashPhoto
 * Module          : App
 * Description     : Implementation of FlashPhoto
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/flashphoto_app.h"
#include <cmath>
#include <iostream>
#include "include/color_data.h"
#include "include/pixel_buffer.h"
#include "include/ui_ctrl.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
FlashPhotoApp::FlashPhotoApp(int width,int height) : BaseGfxApp(width, height),
                                                     filter_handler_(),
                                                     glui_ctrl_hooks_(),
                                                     display_buffer_(nullptr),
                                                     cur_tool_(0),
                                                     cur_color_red_(0.0),
                                                     cur_color_green_(0.0),
                                                     cur_color_blue_(0.0),
                                                     file_name_() {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void FlashPhotoApp::Init(
    int argc,
    char* argv[],
    int x,
    int y,
    ColorData background_color) {
  BaseGfxApp::Init(argc, argv,
                   x, y,
                   GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH,
                   true,
                   width()+51,
                   50);

  // Set the name of the window
  set_caption("FlashPhoto");

  // Initialize Interface
  InitializeBuffers(background_color, width(), height());

  InitGlui();
  InitGraphics();
}

void FlashPhotoApp::Display(void) {
  DrawPixels(0, 0, width(), height(), display_buffer_->data());
}

FlashPhotoApp::~FlashPhotoApp(void) {
  if (display_buffer_) {
    delete display_buffer_;
  }
}


void FlashPhotoApp::MouseDragged(int x, int y) {}
void FlashPhotoApp::MouseMoved(int x, int y) {}

void FlashPhotoApp::LeftMouseDown(int x, int y) {
  std::cout << "mousePressed " << x << " " << y << std::endl;
}

void FlashPhotoApp::LeftMouseUp(int x, int y) {
  std::cout << "mouseReleased " << x << " " << y << std::endl;
}

void FlashPhotoApp::InitializeBuffers(ColorData background_color,
                                      int width, int height) {
  display_buffer_ = new PixelBuffer(width, height, background_color);
}

void FlashPhotoApp::InitGlui(void) {
  // Select first tool (this activates the first radio button in glui)
  cur_tool_ = 0;

  GLUI_Panel *toolPanel = new GLUI_Panel(glui(), "Tool Type");
  {
    GLUI_RadioGroup *radio = new GLUI_RadioGroup(toolPanel, &cur_tool_,
                                                 UICtrl::UI_TOOLTYPE,
                                                 s_gluicallback);
    // Create interface buttons for different tools:
    new GLUI_RadioButton(radio, "Pen");
    new GLUI_RadioButton(radio, "Eraser");
    new GLUI_RadioButton(radio, "Spray Can");
    new GLUI_RadioButton(radio, "Caligraphy Pen");
    new GLUI_RadioButton(radio, "Highlighter");
    new GLUI_RadioButton(radio, "Stamp");
    new GLUI_RadioButton(radio, "Blur");
  }

  GLUI_Panel *colorPanel = new GLUI_Panel(glui(), "Tool Color");
  {
    cur_color_red_ = 0;
    glui_ctrl_hooks_.spinner_red  = new GLUI_Spinner(colorPanel, "Red:",
                                                     &cur_color_red_,
                                                     UICtrl::UI_COLOR_R,
                                                     s_gluicallback);
    glui_ctrl_hooks_.spinner_red->set_float_limits(0, 1.0);

    cur_color_green_ = 0;
    glui_ctrl_hooks_.spinner_green = new GLUI_Spinner(colorPanel, "Green_:",
                                                      &cur_color_green_,
                                                      UICtrl::UI_COLOR_G,
                                                      s_gluicallback);
    glui_ctrl_hooks_.spinner_green->set_float_limits(0, 1.0);

    cur_color_blue_ = 0;
    glui_ctrl_hooks_.spinner_blue  = new GLUI_Spinner(colorPanel, "Blue:",
                                                      cur_color_blue_,
                                                      UICtrl::UI_COLOR_B,
                                                      s_gluicallback);
    glui_ctrl_hooks_.spinner_blue->set_float_limits(0, 1.0);

    new GLUI_Button(colorPanel, "Red", UICtrl::UI_PRESET_RED,
                    s_gluicallback);
    new GLUI_Button(colorPanel, "Orange", UICtrl::UI_PRESET_ORANGE,
                    s_gluicallback);
    new GLUI_Button(colorPanel, "Yellow", UICtrl::UI_PRESET_YELLOW,
                    s_gluicallback);
    new GLUI_Button(colorPanel, "Green", UICtrl::UI_PRESET_GREEN,
                    s_gluicallback);
    new GLUI_Button(colorPanel, "Blue", UICtrl::UI_PRESET_BLUE,
                    s_gluicallback);
    new GLUI_Button(colorPanel, "Purple", UICtrl::UI_PRESET_PURPLE,
                    s_gluicallback);
    new GLUI_Button(colorPanel, "White", UICtrl::UI_PRESET_WHITE,
                    s_gluicallback);
    new GLUI_Button(colorPanel, "Black", UICtrl::UI_PRESET_BLACK,
                    s_gluicallback);
  }

  /* Initialize undo, redo, quit */
  {
    glui_ctrl_hooks_.undo_btn = new GLUI_Button(glui(), "Undo", UICtrl::UI_UNDO,
                                                   s_gluicallback);
    undo_enabled(false);
    glui_ctrl_hooks_.redo_btn  = new GLUI_Button(glui(), "Redo", UICtrl::UI_REDO,
                                                    s_gluicallback);
    redo_enabled(false);

    new GLUI_Separator(glui());
    new GLUI_Button(glui(), "Quit", UICtrl::UI_QUIT, (GLUI_Update_CB)exit);
  }

  /* Initialize Filtering */
  filter_handler_.InitGlui(glui(),s_gluicallback);

  /* Initialize image I/O */
  new GLUI_Column(glui(), true);

  GLUI_Panel *imagePanel = new GLUI_Panel(glui(), "Image I/O");
  {
    glui_ctrl_hooks_.file_browser = new GLUI_FileBrowser(imagePanel,
                                                         "Choose Image",
                                                         false,
                                                         UICtrl::UI_FILE_BROWSER,
                                                         s_gluicallback);

    glui_ctrl_hooks_.file_browser->set_h(400);

    glui_ctrl_hooks_.file_name_box = new GLUI_EditText(imagePanel ,
                                                       "Image:",
                                                       file_name_,
                                                       UICtrl::UI_FILE_NAME,
                                                       s_gluicallback);
    glui_ctrl_hooks_.file_name_box->set_w(200);

    new GLUI_Separator(imagePanel);

    glui_ctrl_hooks_.current_file_label = new GLUI_StaticText(imagePanel,
                                                              "Will load image: none");
    glui_ctrl_hooks_.load_canvas_btn = new GLUI_Button(imagePanel,
                                                          "Load Canvas",
                                                          UICtrl::UI_LOAD_CANVAS_BUTTON,
                                                          s_gluicallback);
    glui_ctrl_hooks_.load_stamp_btn = new GLUI_Button(imagePanel,
                                                         "Load Stamp",
                                                         UICtrl::UI_LOAD_STAMP_BUTTON,
                                                         s_gluicallback);

    new GLUI_Separator(imagePanel);

    glui_ctrl_hooks_.save_file_label = new GLUI_StaticText(imagePanel,
                                                           "Will save image: none");

    glui_ctrl_hooks_.save_canvas_btn = new GLUI_Button(imagePanel,
                                                          "Save Canvas",
                                                          UICtrl::UI_SAVE_CANVAS_BUTTON,
                                                          s_gluicallback);

    load_canvas_enabled(false);
    load_stamp_enabled(false);
    save_canvas_enabled(false);
  }
  return;
}

void FlashPhotoApp::GluiControl(int controlID) {
  switch (controlID) {
    case UICtrl::UI_PRESET_RED:
      cur_color_red_ = 1;
      cur_color_green_ = 0;
      cur_color_blue_ = 0;
      update_colors();
      break;
    case UICtrl::UI_PRESET_ORANGE:
      cur_color_red_ = 1;
      cur_color_green_ = 0.5;
      cur_color_blue_ = 0;
      update_colors();
      break;
    case UICtrl::UI_PRESET_YELLOW:
      cur_color_red_ = 1;
      cur_color_green_ = 1;
      cur_color_blue_ = 0;
      update_colors();
      break;
    case UICtrl::UI_PRESET_GREEN:
      cur_color_red_ = 0;
      cur_color_green_ = 1;
      cur_color_blue_ = 0;
      update_colors();
      break;
    case UICtrl::UI_PRESET_BLUE:
      cur_color_red_ = 0;
      cur_color_green_ = 0;
      cur_color_blue_ = 1;
      update_colors();
      break;
    case UICtrl::UI_PRESET_PURPLE:
      cur_color_red_ = 0.5;
      cur_color_green_ = 0;
      cur_color_blue_ = 1;
      update_colors();
      break;
    case UICtrl::UI_PRESET_WHITE:
      cur_color_red_ = 1;
      cur_color_green_ = 1;
      cur_color_blue_ = 1;
      update_colors();
      break;
    case UICtrl::UI_PRESET_BLACK:
      cur_color_red_ = 0;
      cur_color_green_ = 0;
      cur_color_blue_ = 0;
      update_colors();
      break;
    case UICtrl::UI_APPLY_BLUR:
      filter_handler_.ApplyBlur();
      break;
    case UICtrl::UI_APPLY_SHARP:
      filter_handler_.ApplySharpen();
      break;
    case UICtrl::UI_APPLY_MOTION_BLUR:
      filter_handler_.ApplyMotionBlur();
      break;
    case UICtrl::UI_APPLY_EDGE:
      filter_handler_.ApplyEdgeDetect();
      break;
    case UICtrl::UI_APPLY_THRESHOLD:
      filter_handler_.ApplyThreshold();
      break;
    case UICtrl::UI_APPLY_DITHER:
      filter_handler_.ApplyThreshold();
      break;
    case UICtrl::UI_APPLY_SATURATE:
      filter_handler_.ApplySaturate();
      break;
    case UICtrl::UI_APPLY_CHANNEL:
      filter_handler_.ApplyChannel();
      break;
    case UICtrl::UI_APPLY_QUANTIZE:
      filter_handler_.ApplyQuantize();
      break;
    case UICtrl::UI_APPLY_SPECIAL_FILTER:
      filter_handler_.ApplySpecial();
      break;
    case UICtrl::UI_FILE_BROWSER:
      set_image_file(glui_ctrl_hooks_.file_browser->get_file());
      break;
    case UICtrl::UI_LOAD_CANVAS_BUTTON:
      LoadImageToCanvas();
      break;
    case UICtrl::UI_LOAD_STAMP_BUTTON:
      LoadImageToStamp();
      break;
    case UICtrl::UI_SAVE_CANVAS_BUTTON:
      SaveCanvasToFile();
      // Reload the current directory:
      glui_ctrl_hooks_.file_browser->fbreaddir(".");
      break;
    case UICtrl::UI_FILE_NAME:
      set_image_file(file_name_);
      break;
    case UICtrl::UI_UNDO:
      UndoOperation();
      break;
    case UICtrl::UI_REDO:
      RedoOperation();
      break;
    default:
      break;
  }

  // Forces canvas to update changes made in this function
  glui()->post_update_main_gfx();
}

/*******************************************************************************
 * Member Functions For Handling Button Presses (GLUI callbacks)
 ******************************************************************************/
void FlashPhotoApp::LoadImageToCanvas(void) {
  std::cout << "Load Canvas has been clicked for file " << file_name_ << std::endl;
}

void FlashPhotoApp::LoadImageToStamp(void) {
  std::cout << "Load Stamp has been clicked for file " << file_name_ << std::endl;
}

void FlashPhotoApp::SaveCanvasToFile(void) {
  std::cout << "Save Canvas been clicked for file " << file_name_ << std::endl;
}

void FlashPhotoApp::UndoOperation(void) {
  std::cout << "Undoing..." << std::endl;
}

void FlashPhotoApp::RedoOperation(void) {
  std::cout << "Redoing..." << std::endl;
}

/*******************************************************************************
 * Member Functions For Managing GLUI Interface
 ******************************************************************************/
void FlashPhotoApp::button_enabled(GLUI_Button * button, bool enabled) {
  if (enabled) {
    button->enable();
  } else {
    button->disable();
  }
  button->redraw();
}

void FlashPhotoApp::redo_enabled(bool enabled) {
  button_enabled(glui_ctrl_hooks_.redo_btn, enabled);
}

void FlashPhotoApp::undo_enabled(bool enabled) {
  button_enabled(glui_ctrl_hooks_.undo_btn, enabled);
}

void FlashPhotoApp::save_canvas_enabled(bool enabled) {
  button_enabled(glui_ctrl_hooks_.save_canvas_btn, enabled);
}

void FlashPhotoApp::load_stamp_enabled(bool enabled) {
  button_enabled(glui_ctrl_hooks_.load_stamp_btn, enabled);
}

void FlashPhotoApp::load_canvas_enabled(bool enabled) {
  button_enabled(glui_ctrl_hooks_.load_canvas_btn, enabled);
}

void FlashPhotoApp::update_colors(void) {
  glui_ctrl_hooks_.spinner_blue->set_float_val(cur_color_blue_);
  glui_ctrl_hooks_.spinner_green->set_float_val(cur_color_green_);
  glui_ctrl_hooks_.spinner_red->set_float_val(cur_color_red_);
}

bool FlashPhotoApp::has_suffix(const std::string & str,
                               const std::string & suffix) {
  return str.find(suffix, str.length()-suffix.length()) != std::string::npos;
}


bool FlashPhotoApp::is_valid_image_file_name(const std::string & name) {
  if (has_suffix(name, ".png") || has_suffix(name, ".jpg")
      || has_suffix(name, ".jpeg")) {
    return true;
  }
  return false;
}

bool FlashPhotoApp::is_valid_image_file(const std::string & name) {
  FILE *f;
  bool isValid = false;
  if (is_valid_image_file_name(name)) {
    if ((f = fopen(name.c_str(), "r"))) {
      isValid = true;
      fclose(f);
    }
  }
  return isValid;
}

void FlashPhotoApp::set_image_file(const std::string & fileName) {
  // If a directory was selected
  // instead of a file, use the
  // latest file typed or selected.
  std::string imageFile = fileName;
  if (!is_valid_image_file_name(imageFile)) {
    imageFile = file_name_;
  }


  // TOGGLE SAVE FEATURE
  // If no file is selected or typed,
  // don't allow file to be saved. If
  // there is a file name, then allow
  // file to be saved to that name.

  if (!is_valid_image_file_name(imageFile)) {
    glui_ctrl_hooks_.save_file_label->set_text("Will save image: none");
    save_canvas_enabled(false);
  } else {
    glui_ctrl_hooks_.save_file_label->set_text((std::string("Will save image: ") + imageFile).c_str());
    save_canvas_enabled(true);
  }

  // TOGGLE LOAD FEATURE

  // If the file specified cannot be opened,
  // then disable stamp and canvas loading.
  if (is_valid_image_file(imageFile)) {
    load_stamp_enabled(true);
    load_canvas_enabled(true);

    glui_ctrl_hooks_.current_file_label->set_text((std::string("Will load: ") + imageFile).c_str());
    glui_ctrl_hooks_.file_name_box->set_text(imageFile);
  } else {
    load_stamp_enabled(false);
    load_canvas_enabled(false);
    glui_ctrl_hooks_.current_file_label->set_text("Will load: none");
  }
}

void FlashPhotoApp::InitGraphics(void) {
  // Initialize OpenGL for 2D graphics as used in the BrushWork app
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluOrtho2D(0, width(), 0, height());
  glViewport(0, 0, width(), height());
}
}  // namespace image_tools
