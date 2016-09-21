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

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
using std::cout;
using std::endl;
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
FlashPhotoApp::FlashPhotoApp(int width,int height) : BaseGfxApp(width, height),
                                                     filter_params_(),
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
                                                 UI_TOOLTYPE, s_gluicallback);
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
                                                     UI_COLOR_R,
                                                     s_gluicallback);
    glui_ctrl_hooks_.spinner_red->set_float_limits(0, 1.0);

    cur_color_green_ = 0;
    glui_ctrl_hooks_.spinner_green = new GLUI_Spinner(colorPanel, "Green_:",
                                                      &cur_color_green_,
                                                      UI_COLOR_G,
                                                      s_gluicallback);
    glui_ctrl_hooks_.spinner_green->set_float_limits(0, 1.0);

    cur_color_blue_ = 0;
    glui_ctrl_hooks_.spinner_blue  = new GLUI_Spinner(colorPanel, "Blue:",
                                                      cur_color_blue_,
                                                      UI_COLOR_B,
                                                      s_gluicallback);
    glui_ctrl_hooks_.spinner_blue->set_float_limits(0, 1.0);

    new GLUI_Button(colorPanel, "Red", UI_PRESET_RED, s_gluicallback);
    new GLUI_Button(colorPanel, "Orange", UI_PRESET_ORANGE, s_gluicallback);
    new GLUI_Button(colorPanel, "Yellow", UI_PRESET_YELLOW, s_gluicallback);
    new GLUI_Button(colorPanel, "Green", UI_PRESET_GREEN, s_gluicallback);
    new GLUI_Button(colorPanel, "Blue", UI_PRESET_BLUE, s_gluicallback);
    new GLUI_Button(colorPanel, "Purple", UI_PRESET_PURPLE, s_gluicallback);
    new GLUI_Button(colorPanel, "White", UI_PRESET_WHITE, s_gluicallback);
    new GLUI_Button(colorPanel, "Black", UI_PRESET_BLACK, s_gluicallback);
  }

  // UNDO,REDO,QUIT
  {
    glui_ctrl_hooks_.undo_btn = new GLUI_Button(glui(), "Undo", UI_UNDO,
                                                   s_gluicallback);
    undo_enabled(false);
    glui_ctrl_hooks_.redo_btn  = new GLUI_Button(glui(), "Redo", UI_REDO,
                                                    s_gluicallback);
    redo_enabled(false);

    new GLUI_Separator(glui());
    new GLUI_Button(glui(), "Quit", UI_QUIT, (GLUI_Update_CB)exit);
  }

  new GLUI_Column(glui(), true);
  GLUI_Panel *filterPanel = new GLUI_Panel(glui(), "Filters");
  {
    GLUI_Panel *blurPanel = new GLUI_Panel(filterPanel, "Blur");
    {
      GLUI_Spinner * filterBlurAmount = new GLUI_Spinner(blurPanel, "Amount:",
                                                         &filter_params_.blur_amount);
      filterBlurAmount->set_int_limits(0, 20);

      filterBlurAmount->set_int_val(5);

      new GLUI_Button(blurPanel, "Apply", UI_APPLY_BLUR, s_gluicallback);
    }

    GLUI_Panel *motionBlurPanel = new GLUI_Panel(filterPanel, "MotionBlur");
    {
      GLUI_Spinner * filterMotionBlurAmount = new GLUI_Spinner(motionBlurPanel,
                                                               "Amount:",
                                                               &filter_params_.motion_blur_amount);
      filterMotionBlurAmount->set_int_limits(0, 100);

      filterMotionBlurAmount->set_int_val(5);

      filter_params_.motion_blur_direction = 0;
      GLUI_RadioGroup *dirBlur = new GLUI_RadioGroup(motionBlurPanel,
                                                     &filter_params_.motion_blur_direction);
      new GLUI_RadioButton(dirBlur, "North/South");
      new GLUI_RadioButton(dirBlur, "East/West");
      new GLUI_RadioButton(dirBlur, "NorthEast/SouthWest");
      new GLUI_RadioButton(dirBlur, "NorthWest/SouthEast");

      new GLUI_Button(motionBlurPanel, "Apply", UI_APPLY_MOTION_BLUR, s_gluicallback);
    }
    GLUI_Panel *sharpenPanel = new GLUI_Panel(filterPanel, "Sharpen");
    {
      GLUI_Spinner * filterSharpAmount = new GLUI_Spinner(sharpenPanel, "Amount:",
                                                          &filter_params_.sharpen_amount);
      filterSharpAmount->set_int_limits(0, 100);

      filterSharpAmount->set_int_val(5);

      new GLUI_Button(sharpenPanel, "Apply", UI_APPLY_SHARP, s_gluicallback);
    }
    GLUI_Panel *edgeDetPanel = new GLUI_Panel(filterPanel, "Edge Detect");

    {
      new GLUI_Button(edgeDetPanel, "Apply", UI_APPLY_EDGE, s_gluicallback);
    }
    GLUI_Panel *thresPanel = new GLUI_Panel(filterPanel, "Threshold");
    {
      GLUI_Spinner * filterThresholdAmount = new GLUI_Spinner(thresPanel, "Level:",
                                                              &filter_params_.threshold_amount);
      filterThresholdAmount->set_float_limits(0, 1);
      filterThresholdAmount->set_float_val(0.5);

      new GLUI_Button(thresPanel, "Apply", UI_APPLY_THRESHOLD, s_gluicallback);
    }

    new GLUI_Column(filterPanel, true);

    GLUI_Panel *saturPanel = new GLUI_Panel(filterPanel, "Saturation");
    {
      GLUI_Spinner * filterSaturationAmount = new GLUI_Spinner(saturPanel,
                                                               "Amount:",
                                                               &filter_params_.saturation_amount);
      filterSaturationAmount->set_float_limits(-10, 10);
      filterSaturationAmount->set_float_val(1);

      new GLUI_Button(saturPanel, "Apply", UI_APPLY_SATURATE, s_gluicallback);
    }

    GLUI_Panel *channelPanel = new GLUI_Panel(filterPanel, "Channels");
    {
      GLUI_Spinner * filterChannel_red_ = new GLUI_Spinner(channelPanel, "_red_:",
                                                           &filter_params_.channel_color_red);
      GLUI_Spinner * filterChannel_green_ = new GLUI_Spinner(channelPanel,
                                                             "_green_:",
                                                             &filter_params_.channel_color_green);
      GLUI_Spinner * filterChannel_blue_ = new GLUI_Spinner(channelPanel,
                                                            "_blue_:",
                                                            &filter_params_.channel_color_blue);

      filterChannel_red_->set_float_limits(0, 10);
      filterChannel_red_->set_float_val(1);
      filterChannel_green_->set_float_limits(0, 10);
      filterChannel_green_->set_float_val(1);
      filterChannel_blue_->set_float_limits(0, 10);
      filterChannel_blue_->set_float_val(1);

      new GLUI_Button(channelPanel, "Apply", UI_APPLY_CHANNEL, s_gluicallback);
    }

    GLUI_Panel *quantPanel = new GLUI_Panel(filterPanel, "Quantize");
    {
      GLUI_Spinner * filterQuantizeBins = new GLUI_Spinner(quantPanel, "Bins:",
                                                           &filter_params_.quantize_bins);
      filterQuantizeBins->set_int_limits(2, 256);
      filterQuantizeBins->set_int_val(8);
      filterQuantizeBins->set_speed(0.1);

      new GLUI_Button(quantPanel, "Apply", UI_APPLY_QUANTIZE, s_gluicallback);
    }

    // YOUR SPECIAL FILTER PANEL
    GLUI_Panel *specialFilterPanel = new GLUI_Panel(filterPanel,
                                                    "Special Filter");
    {
      new GLUI_Button(specialFilterPanel, "Apply", UI_APPLY_SPECIAL_FILTER,
                      s_gluicallback);
    }
  }

  new GLUI_Column(glui(), true);

  GLUI_Panel *imagePanel = new GLUI_Panel(glui(), "Image I/O");
  {
    glui_ctrl_hooks_.file_browser = new GLUI_FileBrowser(imagePanel,
                                                         "Choose Image",
                                                         false,
                                                         UI_FILE_BROWSER,
                                                         s_gluicallback);

    glui_ctrl_hooks_.file_browser->set_h(400);

    glui_ctrl_hooks_.file_name_box = new GLUI_EditText(imagePanel ,
                                                       "Image:",
                                                       file_name_,
                                                       UI_FILE_NAME,
                                                       s_gluicallback);
    glui_ctrl_hooks_.file_name_box->set_w(200);

    new GLUI_Separator(imagePanel);

    glui_ctrl_hooks_.current_file_label = new GLUI_StaticText(imagePanel,
                                                              "Will load image: none");
    glui_ctrl_hooks_.load_canvas_btn = new GLUI_Button(imagePanel,
                                                          "Load Canvas",
                                                          UI_LOAD_CANVAS_BUTTON,
                                                          s_gluicallback);
    glui_ctrl_hooks_.load_stamp_btn = new GLUI_Button(imagePanel,
                                                         "Load Stamp",
                                                         UI_LOAD_STAMP_BUTTON,
                                                         s_gluicallback);

    new GLUI_Separator(imagePanel);

    glui_ctrl_hooks_.save_file_label = new GLUI_StaticText(imagePanel,
                                                           "Will save image: none");

    glui_ctrl_hooks_.save_canvas_btn = new GLUI_Button(imagePanel,
                                                          "Save Canvas",
                                                          UI_SAVE_CANVAS_BUTTON,
                                                          s_gluicallback);

    load_canvas_enabled(false);
    load_stamp_enabled(false);
    save_canvas_enabled(false);
  }
  return;
}

void FlashPhotoApp::GluiControl(int controlID) {
  switch (controlID) {
    case UI_PRESET_RED:
      cur_color_red_ = 1;
      cur_color_green_ = 0;
      cur_color_blue_ = 0;
      update_colors();
      break;
    case UI_PRESET_ORANGE:
      cur_color_red_ = 1;
      cur_color_green_ = 0.5;
      cur_color_blue_ = 0;
      update_colors();
      break;
    case UI_PRESET_YELLOW:
      cur_color_red_ = 1;
      cur_color_green_ = 1;
      cur_color_blue_ = 0;
      update_colors();
      break;
    case UI_PRESET_GREEN:
      cur_color_red_ = 0;
      cur_color_green_ = 1;
      cur_color_blue_ = 0;
      update_colors();
      break;
    case UI_PRESET_BLUE:
      cur_color_red_ = 0;
      cur_color_green_ = 0;
      cur_color_blue_ = 1;
      update_colors();
      break;
    case UI_PRESET_PURPLE:
      cur_color_red_ = 0.5;
      cur_color_green_ = 0;
      cur_color_blue_ = 1;
      update_colors();
      break;
    case UI_PRESET_WHITE:
      cur_color_red_ = 1;
      cur_color_green_ = 1;
      cur_color_blue_ = 1;
      update_colors();
      break;
    case UI_PRESET_BLACK:
      cur_color_red_ = 0;
      cur_color_green_ = 0;
      cur_color_blue_ = 0;
      update_colors();
      break;
    case UI_APPLY_BLUR:
      ApplyFilterBlur();
      break;
    case UI_APPLY_SHARP:
      ApplyFilterSharpen();
      break;
    case UI_APPLY_MOTION_BLUR:
      ApplyFilterMotionBlur();
      break;
    case UI_APPLY_EDGE:
      ApplyFilterEdgeDetect();
      break;
    case UI_APPLY_THRESHOLD:
      ApplyFilterThreshold();
      break;
    case UI_APPLY_DITHER:
      ApplyFilterThreshold();
      break;
    case UI_APPLY_SATURATE:
      ApplyFilterSaturate();
      break;
    case UI_APPLY_CHANNEL:
      ApplyFilterChannel();
      break;
    case UI_APPLY_QUANTIZE:
      ApplyFilterQuantize();
      break;
    case UI_APPLY_SPECIAL_FILTER:
      ApplyFilterSpecial();
      break;
    case UI_FILE_BROWSER:
      set_image_file(glui_ctrl_hooks_.file_browser->get_file());
      break;
    case UI_LOAD_CANVAS_BUTTON:
      LoadImageToCanvas();
      break;
    case UI_LOAD_STAMP_BUTTON:
      LoadImageToStamp();
      break;
    case UI_SAVE_CANVAS_BUTTON:
      SaveCanvasToFile();
      // Reload the current directory:
      glui_ctrl_hooks_.file_browser->fbreaddir(".");
      break;
    case UI_FILE_NAME:
      set_image_file(file_name_);
      break;
    case UI_UNDO:
      UndoOperation();
      break;
    case UI_REDO:
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
  cout << "Load Canvas has been clicked for file " << file_name_ << endl;
}

void FlashPhotoApp::LoadImageToStamp(void) {
  cout << "Load Stamp has been clicked for file " << file_name_ << endl;
}

void FlashPhotoApp::SaveCanvasToFile(void) {
  cout << "Save Canvas been clicked for file " << file_name_ << endl;
}

void FlashPhotoApp::ApplyFilterThreshold(void) {
  cout << "Apply has been clicked for Threshold has been clicked with amount ="
       << filter_params_.threshold_amount << endl;
}

void FlashPhotoApp::ApplyFilterChannel(void) {
  cout << "Apply has been clicked for Channels with red = "
       << filter_params_.channel_color_red
       << ", green = " << filter_params_.channel_color_green
       << ", blue = " << filter_params_.channel_color_blue << endl;
}

void FlashPhotoApp::ApplyFilterSaturate(void) {
  cout << "Apply has been clicked for Saturate with amount = "
       << filter_params_.saturation_amount << endl;
}

void FlashPhotoApp::ApplyFilterBlur(void) {
  cout << "Apply has been clicked for Blur with amount = "
       << filter_params_.blur_amount << endl;
}

void FlashPhotoApp::ApplyFilterSharpen(void) {
  cout << "Apply has been clicked for Sharpen with amount = "
       << filter_params_.sharpen_amount << endl;
}

void FlashPhotoApp::ApplyFilterMotionBlur(void) {
  cout << "Apply has been clicked for Sharpen with amount = "
       << filter_params_.motion_blur_amount
       << " and direction " << filter_params_.motion_blur_direction << endl;
}

void FlashPhotoApp::ApplyFilterEdgeDetect(void) {
  cout << "Apply has been clicked for Edge Detect" << endl;
}

void FlashPhotoApp::ApplyFilterQuantize(void) {
  cout << "Apply has been clicked for Quantize with bins = "
       << filter_params_.quantize_bins << endl;
}

void FlashPhotoApp::ApplyFilterSpecial(void) {
  cout << "Apply has been clicked for Special" << endl;
}

void FlashPhotoApp::UndoOperation(void) {
  cout << "Undoing..." << endl;
}

void FlashPhotoApp::RedoOperation(void) {
  cout << "Redoing..." << endl;
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
