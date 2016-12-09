/*******************************************************************************
 * Name            : mia_app.cc
 * Project         : MIA
 * Module          : App
 * Description     : Implementation of MIA
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 5/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "app/MIA/src/include/mia_app.h"
#include "lib/libimgtools/src/include/base_gfx_app.h"
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"
#include "lib/libimgtools/src/include/pen.h"
#include "lib/libimgtools/src/include/stamp.h"
#include <string>
#include <iostream>
#include <math.h>

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
MIAApp::MIAApp(int width, int height,
               const std::string& marker_fname) : BaseGfxApp(width, height),
                                                  filter_manager_(),
                                                  io_manager_(),
                                                  state_manager_(),
                                                  display_buffer_(nullptr),
                                                  marker_fname_(marker_fname),
                                                  cur_tool_(0) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void MIAApp::Init(
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
  set_caption("MIA");

  // Initialize Interface
  InitializeBuffers(background_color, width(), height());

  InitGlui();
  InitGraphics();

  // Initiailize tools
  tools_.push_back(new Pen());
  io_manager_.set_image_file("./resources/marker.png");
  PixelBuffer* marker = io_manager_.LoadImageToStamp();
  tools_.push_back(new Stamp(marker));
  tool_ = tools_[0];
}

void MIAApp::Display(void) {
  DrawPixels(0, 0, width(), height(), display_buffer_->data());
}

MIAApp::~MIAApp(void) {
  if (display_buffer_) {
    delete display_buffer_;
  }
}

void MIAApp::LeftMouseDown(int x, int y) {
    std::cout << "mousePressed " << x << " " << y << std::endl;
    y = display_buffer_->height() - y;
	tool_->Draw(x, y, 1.0, 0.0, 0.0, display_buffer_);
} 

void MIAApp::InitializeBuffers(ColorData background_color,
                               int width, int height) {
  display_buffer_ = new PixelBuffer(width, height, background_color);
}

void MIAApp::InitGlui(void) {
  // Select first tool (this activates the first radio button in glui)
  cur_tool_ = 0;

  new GLUI_Column(glui(), false);
  GLUI_Panel *tool_panel = new GLUI_Panel(glui(), "Tool Type");
  {
    GLUI_RadioGroup *radio = new GLUI_RadioGroup(tool_panel, &cur_tool_,
                                                 UICtrl::UI_TOOLTYPE,
                                                 s_gluicallback);
    // Create interface buttons for different tools:
    new GLUI_RadioButton(radio, "Pen");
    new GLUI_RadioButton(radio, "Marker");
  }

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

void MIAApp::GluiControl(int control_id) {
  switch (control_id) {
    case UICtrl::UI_TOOLTYPE:
      tool_ = tools_[cur_tool_];
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
    case UICtrl::UI_FILE_BROWSER:
      io_manager_.set_image_file(io_manager_.file_browser()->get_file());
      break;
    case UICtrl::UI_LOAD_CANVAS_BUTTON:
      io_manager_.LoadImageToCanvas();
      break;
    case UICtrl::UI_LOAD_STAMP_BUTTON:
      io_manager_.LoadImageToStamp();
      break;
    case UICtrl::UI_SAVE_CANVAS_BUTTON:
      io_manager_.SaveCanvasToFile(*display_buffer_);
      // Reload the current directory:
      io_manager_.file_browser()->fbreaddir(".");
      break;
    case UICtrl::UI_NEXT_IMAGE_BUTTON:
      io_manager_.LoadNextImage();
      break;
    case UICtrl::UI_PREV_IMAGE_BUTTON:
      io_manager_.LoadPreviousImage();
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
void MIAApp::InitGraphics(void) {
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
void MIAApp::MouseDragged(int new_x, int new_y) {
    /* Don't draw for stamp */
    if (cur_tool_ == 1) { return; }
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
                adjusted_y = display_buffer_->height() - y;
                tool_->Draw(x, adjusted_y, 1.0, 0.0, 0.0, display_buffer_);
                last_x_applied = x;
                last_y_applied = y;
            }
        }

    } else {
        adjusted_y = display_buffer_->height() - y;
        tool_->Draw(x, adjusted_y, 1.0, 0.0, 0.0, display_buffer_);
    }
    // For efficiency, only update relevant portion of canvas
    DrawPixels(x, y, x_gap, y_gap, display_buffer_->data());
    prev_x_ = new_x;
    prev_y_ = new_y;
}
void MIAApp::MouseMoved(int x, int y) {
    // Keep track of latest x-y coordinates so
    // MouseDragged() has current data to use
    prev_x_ = x;
    prev_y_ = y;
}
}  /* namespace image_tools */
