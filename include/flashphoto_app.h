/*******************************************************************************
 * Name            : flashphoto_app.h
 * Project         : FlashPhoto
 * Module          : App
 * Description     : Header file for FlashPhotoApp class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef INCLUDE_FLASHPHOTO_APP_H_
#define INCLUDE_FLASHPHOTO_APP_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "include/base_gfx_app.h"
#include "include/color_data.h"
#include "include/pixel_buffer.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
class FlashPhotoApp : public BaseGfxApp {
 public:
  FlashPhotoApp(int width,int height);
  virtual ~FlashPhotoApp(void);

  void MouseDragged(int x, int y);
  void MouseMoved(int x, int y);
  void LeftMouseDown(int x, int y);
  void LeftMouseUp(int x, int y);
  void Display(void);
  void GluiControl(int controlID);
  void Init(
      int argc,
      char* argv[],
      int x,
      int y,
      ColorData background_color);

 private:
  void set_image_file(const std::string & filepath);
  bool is_valid_image_file_name(const std::string & name);
  bool is_valid_image_file(const std::string & name);
  bool has_suffix(const std::string & str, const std::string & suffix);
  void button_enabled(GLUI_Button * button, bool enabled);
  void undo_enabled(bool enabled);
  void redo_enabled(bool enabled);
  void save_canvas_enabled(bool enabled);
  void load_canvas_enabled(bool enabled);
  void load_stamp_enabled(bool enabled);
  void update_colors(void);

  void LoadImageToCanvas(void);
  void LoadImageToStamp(void);
  void SaveCanvasToFile(void);

  void ApplyFilterBlur(void);
  void ApplyFilterSharpen(void);
  void ApplyFilterMotionBlur(void);
  void ApplyFilterEdgeDetect(void);
  void ApplyFilterThreshold(void);
  void ApplyFilterChannel(void);
  void ApplyFilterSaturate(void);
  void ApplyFilterQuantize(void);
  void ApplyFilterSpecial(void);

  void UndoOperation(void);
  void RedoOperation(void);
  void InitGlui(void);
  void InitGraphics(void);
  /**
   * @brief Initialize the buffers for the main window
   */
  void InitializeBuffers(ColorData initialColor,
                         int width, int height);

  /* Copy/move assignment/construction disallowed */
  FlashPhotoApp(const FlashPhotoApp &rhs) = delete;
  FlashPhotoApp& operator=(const FlashPhotoApp &rhs) = delete;

  // GLUI INTERFACE ELEMENTS
  enum UIControlType {
    UI_TOOLTYPE,
    UI_COLOR_R,
    UI_COLOR_G,
    UI_COLOR_B,
    UI_PRESET_RED,
    UI_PRESET_ORANGE,
    UI_PRESET_YELLOW,
    UI_PRESET_GREEN,
    UI_PRESET_BLUE,
    UI_PRESET_PURPLE,
    UI_PRESET_WHITE,
    UI_PRESET_BLACK,
    UI_FILE_BROWSER,
    UI_LOAD_CANVAS_BUTTON,
    UI_LOAD_STAMP_BUTTON,
    UI_SAVE_CANVAS_BUTTON,
    UI_FILE_NAME,
    UI_APPLY_BLUR,
    UI_APPLY_SHARP,
    UI_APPLY_EDGE,
    UI_APPLY_THRESHOLD,
    UI_APPLY_DITHER,
    UI_APPLY_SATURATE,
    UI_APPLY_CHANNEL,
    UI_APPLY_QUANTIZE,
    UI_APPLY_MOTION_BLUR,
    UI_APPLY_SPECIAL_FILTER,
    UI_UNDO,
    UI_REDO,
    UI_QUIT
  };

  enum UIMotionBlurDirections {
    DIR_N_S,
    DIR_E_W,
    DIR_NE_SW,
    DIR_NW_SE
  };

  struct {
    float channel_color_red;
    float channel_color_green;
    float channel_color_blue;
    float saturation_amount;
    float threshold_amount;
    float blur_amount;
    float sharpen_amount;
    float motion_blur_amount;
    int motion_blur_direction;
    int quantize_bins;
  } filter_parameters_;

  struct {
    GLUI_FileBrowser* file_browser;
    GLUI_Button *load_canvas_button;
    GLUI_Button *load_stamp_button;
    GLUI_Button *save_canvas_button;
    GLUI_Button *redo_button;
    GLUI_Button *undo_button;
    GLUI_StaticText * current_file_label;
    GLUI_EditText* file_name_box;
    GLUI_StaticText * save_file_label;

    GLUI_Spinner *spinner_red;
    GLUI_Spinner *spinner_green;
    GLUI_Spinner *spinner_blue;
  } glui_control_hooks_;

  // This is the pointer to the buffer where the display PixelBuffer is stored
  PixelBuffer* display_buffer_;

  // These are used to store the selections from the GLUI user interface
  int cur_tool_;
  float cur_color_red_, cur_color_green_, cur_color_blue_;
  std::string file_name_;
};
}  // namespace image_tools

#endif  // INCLUDE_FLASHPHOTO_APP_H_
