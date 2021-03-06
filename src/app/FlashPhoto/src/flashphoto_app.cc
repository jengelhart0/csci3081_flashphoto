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
#include <iostream>
#include <cmath>
#include "lib/libimgtools/src/include/pen.h"
#include "include/caligraphy_pen.h"
#include "include/eraser.h"
#include "include/spray_can.h"
#include "include/wire_brush.h"
#include "include/highlighter.h"
#include "lib/libimgtools/src/include/stamp.h"
#include "lib/libimgtools/src/include/blur.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
FlashPhotoApp::FlashPhotoApp(int width, int height) : BaseGfxApp(width, height),
                                                      filter_manager_(),
                                                      io_manager_(),
                                                      state_manager_(),
                                                      glui_ctrl_hooks_(),
                                                      display_buffer_(nullptr),
                                                      cur_tool_(0),
                                                      tool_(nullptr),
                                                      prev_x_(0),
                                                      prev_y_(0),
                                                      cur_color_red_(0.0),
                                                      cur_color_green_(0.0),
                                                      cur_color_blue_(0.0) {}

FlashPhotoApp::~FlashPhotoApp(void) {
    if (display_buffer_) {
        delete display_buffer_;
    }
}


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
  // Create tools
  InitTools();

  // Set the name of the window
  set_caption("FlashPhoto");

  // Set tool
  ChangeTool(cur_tool_);

  // Initialize Interface
  InitializeBuffers(background_color, width(), height());

  InitGlui();
  InitGraphics();
}

void FlashPhotoApp::Display(void) {
  DrawPixels(0, 0, width(), height(), display_buffer_->data());
}

/* i2 - Overrides BaseGfxApp so users can resize image */
void FlashPhotoApp::Reshape(int width, int height) {
    glutReshapeWindow(width, height);
    canvas_height_ = height;
    canvas_width_ = width;
}

void FlashPhotoApp::MouseDragged(int new_x, int new_y) {
    /* Don't draw for stamp */
    if (cur_tool_ == 6) { return; }
    int x = new_x;
    int y = new_y;
    int x_gap = std::abs(x - prev_x_);
    int y_gap = std::abs(y - prev_y_);
    int half_mask_length = tool_->length() / 2;
    int half_mask_height = tool_->height() / 2;
    int adjusted_y = y;

    // Only applies gap fill logic if gaps between
    // MouseDragged() calls are large enough
    if ((x_gap > half_mask_length) ||
        (y_gap > half_mask_height)) {
        int last_x_applied = prev_x_;
        int last_y_applied = prev_y_;

        // For each hundredth of the gap distance,
        // apply the tool across the gap slope...
        for (float p = 0.0; p < 1.0; p += 0.01) {
            x = static_cast<int>(floor(prev_x_ + p * (new_x - prev_x_) + 0.5));
            y = static_cast<int>(floor(prev_y_ + p * (new_y - prev_y_) + 0.5));

            // Don't 'overfill' if that hundredth distance is less
            // than quarter mask size. This prevents unnatural density
            // for semi-transparent tools like highlighter and spray can
            if ((abs(x - last_x_applied) >= half_mask_length / 2) ||
                (abs(y - last_y_applied) >= half_mask_height / 2)) {
                adjusted_y = canvas_height_ - y;
                tool_->Draw(x, adjusted_y, cur_color_red_, cur_color_green_,
                    cur_color_blue_, display_buffer_);
                last_x_applied = x;
                last_y_applied = y;
            }
        }

    } else {
        adjusted_y = canvas_height_ - y;
        tool_->Draw(x, adjusted_y, cur_color_red_, cur_color_green_,
            cur_color_blue_, display_buffer_);
    }
    // For efficiency, only update relevant portion of canvas
    DrawPixels(x, y, x_gap, y_gap, display_buffer_->data());
    prev_x_ = new_x;
    prev_y_ = new_y;
}
void FlashPhotoApp::MouseMoved(int x, int y) {
    // Keep track of latest x-y coordinates so
    // MouseDragged() has current data to use
    prev_x_ = x;
    prev_y_ = y;
}

void FlashPhotoApp::LeftMouseDown(int x, int y) {
  std::cout << "mousePressed " << x << " " << y << std::endl;
  y = canvas_height_ - y;
  // Only happens in case of uninitialized stamp
  if (tool_ != nullptr)
      tool_->Draw(x, y, cur_color_red_, cur_color_green_,
        cur_color_blue_, display_buffer_);
}

void FlashPhotoApp::LeftMouseUp(int x, int y) {
  std::cout << "mouseReleased " << x << " " << y << std::endl;
}

void FlashPhotoApp::ChangeTool(int current_tool) {
    std::cout << "current tool int is" << current_tool << std::endl;

    tool_ = tools_[current_tool];
}

void FlashPhotoApp::InitTools(void) {
    tools_.push_back(new Pen());
    tools_.push_back(new Eraser());
    tools_.push_back(new SprayCan());
    tools_.push_back(new CaligraphyPen());
    tools_.push_back(new Highlighter());
    tools_.push_back(new WireBrush());
    tools_.push_back(nullptr);  // Placeholder for stamp
    tools_.push_back(new Blur());
}

void FlashPhotoApp::InitializeBuffers(ColorData background_color,
  int width,
  int height) {
  display_buffer_ = new PixelBuffer(width, height, background_color);
  canvas_height_ = 800;
  canvas_width_ = 800;
}

void FlashPhotoApp::InitGlui(void) {
    // Select first tool (this activates the first radio button in glui)
    cur_tool_ = 0;

    GLUI_Panel *toolPanel = new GLUI_Panel(glui(), "Tool Type");
    GLUI_RadioGroup *radio = new GLUI_RadioGroup(toolPanel, &cur_tool_,
                                                 UICtrl::UI_TOOLTYPE,
                                                 s_gluicallback);
    // Create interface buttons for different tools:
    new GLUI_RadioButton(radio, "Pen");
    new GLUI_RadioButton(radio, "Eraser");
    new GLUI_RadioButton(radio, "Spray Can");
    new GLUI_RadioButton(radio, "Caligraphy Pen");
    new GLUI_RadioButton(radio, "Highlighter");
    new GLUI_RadioButton(radio, "Wire Brush");
    new GLUI_RadioButton(radio, "Stamp");
    new GLUI_RadioButton(radio, "Blur");

    GLUI_Panel *color_panel = new GLUI_Panel(glui(), "Tool Color");
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

  /* Initialize state management (undo, redo, quit) */
  state_manager_.InitGlui(glui(), s_gluicallback);

  new GLUI_Button(const_cast<GLUI*>(glui()),
                "Quit", UICtrl::UI_QUIT,
                static_cast<GLUI_Update_CB>(exit));

  /* Initialize Filtering */
  filter_manager_.InitGlui(glui(), s_gluicallback);

  /* Initialize image I/O */
  io_manager_.InitGlui(glui(), s_gluicallback);
  return;
}

void FlashPhotoApp::GluiControl(int control_id) {
  switch (control_id) {
    case UI_TOOLTYPE:
      ChangeTool(cur_tool_);
      break;
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
      filter_manager_.ApplyBlur(display_buffer_);
      break;
    case UICtrl::UI_APPLY_SHARP:
      filter_manager_.ApplySharpen(display_buffer_);
      break;
    case UICtrl::UI_APPLY_MOTION_BLUR:
      filter_manager_.ApplyMotionBlur(display_buffer_);
      break;
    case UICtrl::UI_APPLY_EDGE:
      filter_manager_.ApplyEdgeDetect(display_buffer_);
      break;
    case UICtrl::UI_APPLY_THRESHOLD:
      filter_manager_.ApplyThreshold(display_buffer_);
      break;
    case UICtrl::UI_APPLY_SATURATE:
      filter_manager_.ApplySaturate(display_buffer_);
      break;
    case UICtrl::UI_APPLY_CHANNEL:
      filter_manager_.ApplyChannel(display_buffer_);
      break;
    case UICtrl::UI_APPLY_QUANTIZE:
      filter_manager_.ApplyQuantize(display_buffer_);
      break;
    case UICtrl::UI_APPLY_SPECIAL_FILTER:
      filter_manager_.ApplySpecial(display_buffer_);
      break;
    case UICtrl::UI_FILE_BROWSER:
      io_manager_.set_image_file(io_manager_.file_browser()->get_file());
      break;
    case UICtrl::UI_LOAD_CANVAS_BUTTON:
      PixelBuffer* new_buffer;
      new_buffer = io_manager_.LoadImageToCanvas();
      delete(display_buffer_);
      display_buffer_ = new_buffer;
      SetWindowDimensions(new_buffer->width(), new_buffer->height());
      break;
    case UICtrl::UI_LOAD_STAMP_BUTTON:
      PixelBuffer* image;
      image = io_manager_.LoadImageToStamp();
      Stamp* stamp;
      stamp = new Stamp(image);
      tools_[6] = stamp;
      if (cur_tool_ == 6) { tool_ = stamp; }
      break;
    case UICtrl::UI_SAVE_CANVAS_BUTTON:
      io_manager_.SaveCanvasToFile(*display_buffer_);
      // Reload the current directory:
      io_manager_.file_browser()->fbreaddir(".");
      break;
    case UICtrl::UI_FILE_NAME:
      io_manager_.set_image_file(io_manager_.file_name());
      break;
    case UICtrl::UI_UNDO:
      state_manager_.UndoOperation();
      break;
    case UICtrl::UI_REDO:
      state_manager_.RedoOperation();
      break;
    default:
      break;
  }

  // Forces canvas to update changes made in this function
  glui()->post_update_main_gfx();
}

/*******************************************************************************
 * Member Functions For Managing GLUI Interface
 ******************************************************************************/
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

}  /* namespace image_tools */
