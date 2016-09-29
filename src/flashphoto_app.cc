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
FlashPhotoApp::FlashPhotoApp(int width, int height) : BaseGfxApp(width, height),
                                                      filter_handler_(),
                                                      io_handler_(),
                                                      glui_ctrl_hooks_(),
                                                      display_buffer_(nullptr),
                                                      cur_tool_(0),
                                                      cur_color_red_(0.0),
                                                      cur_color_green_(0.0),
                                                      cur_color_blue_(0.0) {}

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

  GLUI_Panel *color_panel = new GLUI_Panel(glui(), "Tool Color");
  {
    cur_color_red_ = 0;
    glui_ctrl_hooks_.spinner_red  = new GLUI_Spinner(color_panel, "Red:",
                                                     &cur_color_red_,
                                                     UICtrl::UI_COLOR_R,
                                                     s_gluicallback);
    glui_ctrl_hooks_.spinner_red->set_float_limits(0, 1.0);

    cur_color_green_ = 0;
    glui_ctrl_hooks_.spinner_green = new GLUI_Spinner(color_panel, "Green:",
                                                      &cur_color_green_,
                                                      UICtrl::UI_COLOR_G,
                                                      s_gluicallback);
    glui_ctrl_hooks_.spinner_green->set_float_limits(0, 1.0);

    cur_color_blue_ = 0;
    glui_ctrl_hooks_.spinner_blue  = new GLUI_Spinner(color_panel, "Blue:",
                                                      &cur_color_blue_,
                                                      UICtrl::UI_COLOR_B,
                                                      s_gluicallback);
    glui_ctrl_hooks_.spinner_blue->set_float_limits(0, 1.0);

    new GLUI_Button(color_panel, "Red", UICtrl::UI_PRESET_RED,
                    s_gluicallback);
    new GLUI_Button(color_panel, "Orange", UICtrl::UI_PRESET_ORANGE,
                    s_gluicallback);
    new GLUI_Button(color_panel, "Yellow", UICtrl::UI_PRESET_YELLOW,
                    s_gluicallback);
    new GLUI_Button(color_panel, "Green", UICtrl::UI_PRESET_GREEN,
                    s_gluicallback);
    new GLUI_Button(color_panel, "Blue", UICtrl::UI_PRESET_BLUE,
                    s_gluicallback);
    new GLUI_Button(color_panel, "Purple", UICtrl::UI_PRESET_PURPLE,
                    s_gluicallback);
    new GLUI_Button(color_panel, "White", UICtrl::UI_PRESET_WHITE,
                    s_gluicallback);
    new GLUI_Button(color_panel, "Black", UICtrl::UI_PRESET_BLACK,
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
  filter_handler_.InitGlui(glui(), s_gluicallback);

  /* Initialize image I/O */
  io_handler_.InitGlui(glui(), s_gluicallback);
  return;
}

void FlashPhotoApp::GluiControl(int control_id) {
  switch (control_id) {
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
      io_handler_.set_image_file(io_handler_.file_browser()->get_file());
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
      io_handler_.file_browser()->fbreaddir(".");
      break;
    case UICtrl::UI_FILE_NAME:
      io_handler_.set_image_file(io_handler_.file_name());
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
  std::cout << "Load Canvas has been clicked for file " <<
      io_handler_.file_name() << std::endl;
}

void FlashPhotoApp::LoadImageToStamp(void) {
  std::cout << "Load Stamp has been clicked for file " <<
      io_handler_.file_name() << std::endl;
}

void FlashPhotoApp::SaveCanvasToFile(void) {
  std::cout << "Save Canvas been clicked for file " <<
      io_handler_.file_name() << std::endl;
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
void FlashPhotoApp::redo_enabled(bool enabled) {
  UICtrl::button_toggle(glui_ctrl_hooks_.redo_btn, enabled);
}

void FlashPhotoApp::undo_enabled(bool enabled) {
  UICtrl::button_toggle(glui_ctrl_hooks_.undo_btn, enabled);
}

void FlashPhotoApp::update_colors(void) {
  glui_ctrl_hooks_.spinner_blue->set_float_val(cur_color_blue_);
  glui_ctrl_hooks_.spinner_green->set_float_val(cur_color_green_);
  glui_ctrl_hooks_.spinner_red->set_float_val(cur_color_red_);
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
