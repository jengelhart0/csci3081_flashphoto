/*******************************************************************************
 * Name            : io_handler.h
 * Project         : FlashPhoto
 * Module          : io_handler
 * Description     : Header for IoHandler class
 * Creation Date   : Wed Sep 21 20:40:20 2016
 * Original Author : jharwell
 *
 ******************************************************************************/

#ifndef INCLUDE_IO_HANDLER_H_
#define INCLUDE_IO_HANDLER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "GL/glui.h"
#include "ui_ctrl.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A collection of io parameters for manipulating photos
 * TODO: Add more detail, and add comments/doc for the members below
 */
class IOHandler {
 public:
  IOHandler();
  ~IOHandler() {}

  void InitGlui(const GLUI *const glui,
                void (*s_gluicallback)(int));
  void save_canvas_toggle(bool enabled) {
    UICtrl::button_toggle(save_canvas_btn_, enabled);
  }

  void load_stamp_toggle(bool enabled) {
    UICtrl::button_toggle(load_stamp_btn_, enabled);
  }

  void load_canvas_toggle(bool enabled) {
    UICtrl::button_toggle(load_canvas_btn_, enabled);
  }
  void set_image_file(const std::string & filepath);
  const std::string& file_name(void) { return file_name_;}
  GLUI_FileBrowser* file_browser(void) { return file_browser_;}

 private:
  /* Copy/move assignment/construction disallowed */
  IOHandler(const IOHandler &rhs) = delete;
  IOHandler& operator=(const IOHandler &rhs) = delete;

  bool is_valid_image_file_name(const std::string & name);
  bool is_valid_image_file(const std::string & name);
  bool has_suffix(const std::string & str, const std::string & suffix);

  /* data members */
  GLUI_FileBrowser *file_browser_;
  GLUI_Button *load_canvas_btn_;
  GLUI_Button *load_stamp_btn_;
  GLUI_Button *save_canvas_btn_;
  GLUI_StaticText *current_file_label_;
  GLUI_EditText *file_name_box_;
  GLUI_StaticText *save_file_label_;
  std::string file_name_;
};

}  // namespace image_tools
#endif  // INCLUDE_IO_HANDLER_H_
