/*******************************************************************************
 * Name            : ui_ctrl.h
 * Project         : image_tools
 * Module          : utils
 * Description     : General UI constant definitions
 * Creation Date   : Wed Sep 21 19:04:44 2016
 * Original Author : jharwell
 *
 ******************************************************************************/

#ifndef INCLUDE_UI_CTRL_H_
#define INCLUDE_UI_CTRL_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {
class UICtrl {
 public:
  /**
   * @brief GLUI interface elements
   */
  enum Type {
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
};

}  // namespace image_tools

#endif  // INCLUDE_UI_CTRL_H_
