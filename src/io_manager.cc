/*******************************************************************************
 * Name            : io_manager.cc
 * Project         : FlashPhoto
 * Module          : io_manager
 * Description     : Implementation of IOManager class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : Wed Sep 21 20:47:05 2016
 * Original Author : jharwell
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/io_manager.h"
#include <iostream>
#include "include/color_data.h"
#include "include/ui_ctrl.h"
#include "png.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
IOManager::IOManager(void) :
    file_browser_(nullptr),
    load_canvas_btn_(nullptr),
    load_stamp_btn_(nullptr),
    save_canvas_btn_(nullptr),
    current_file_label_(nullptr),
    file_name_box_(nullptr),
    save_file_label_(nullptr),
    file_name_() {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void IOManager::InitGlui(const GLUI *const glui,
                         void (*s_gluicallback)(int)) {
  new GLUI_Column(const_cast<GLUI*>(glui), true);
  GLUI_Panel *image_panel = new GLUI_Panel(const_cast<GLUI*>(glui),
                                           "Image I/O");
  file_browser_ = new GLUI_FileBrowser(image_panel,
                                      "Choose Image",
                                      false,
                                      UICtrl::UI_FILE_BROWSER,
                                      s_gluicallback);

  file_browser_->set_h(400);

  file_name_box_ = new GLUI_EditText(image_panel ,
                                    "Image:",
                                    file_name_,
                                    UICtrl::UI_FILE_NAME,
                                    s_gluicallback);
  file_name_box_->set_w(200);

  new GLUI_Separator(image_panel);

  current_file_label_ = new GLUI_StaticText(image_panel,
                                           "Will load image: none");
  load_canvas_btn_ = new GLUI_Button(image_panel,
                                    "Load Canvas",
                                    UICtrl::UI_LOAD_CANVAS_BUTTON,
                                    s_gluicallback);
  load_stamp_btn_ = new GLUI_Button(image_panel,
                                   "Load Stamp",
                                   UICtrl::UI_LOAD_STAMP_BUTTON,
                                   s_gluicallback);

  new GLUI_Separator(image_panel);

  save_file_label_ = new GLUI_StaticText(image_panel,
                                        "Will save image: none");

  save_canvas_btn_ = new GLUI_Button(image_panel,
                                    "Save Canvas",
                                    UICtrl::UI_SAVE_CANVAS_BUTTON,
                                    s_gluicallback);

  load_canvas_toggle(false);
  load_stamp_toggle(false);
  save_canvas_toggle(false);
}


bool IOManager::is_valid_image_file(const std::string & name) {
  FILE *f;
  bool is_valid = false;
  if (is_valid_image_file_name(name)) {
    if ((f = fopen(name.c_str(), "r"))) {
      is_valid = true;
      fclose(f);
    }
  }
  return is_valid;
}

void IOManager::set_image_file(const std::string & file_name) {
  // If a directory was selected
  // instead of a file, use the
  // latest file typed or selected.
  std::string image_file = file_name;
  if (!is_valid_image_file_name(image_file)) {
    image_file = file_name_;
  }

  // TOGGLE SAVE FEATURE
  // If no file is selected or typed,
  // don't allow file to be saved. If
  // there is a file name, then allow
  // file to be saved to that name.

  if (!is_valid_image_file_name(image_file)) {
    save_file_label_->set_text("Will save image: none");
    save_canvas_toggle(false);
  } else {
    save_file_label_->set_text((std::string("Will save image: ") +
                                image_file).c_str());
    save_canvas_toggle(true);
  }

  // TOGGLE LOAD FEATURE

  // If the file specified cannot be opened,
  // then disable stamp and canvas loading.
  if (is_valid_image_file(image_file)) {
    load_stamp_toggle(true);
    load_canvas_toggle(true);

    current_file_label_->set_text((std::string("Will load: ") +
                                   image_file).c_str());
    file_name_box_->set_text(image_file);
  } else {
    load_stamp_toggle(false);
    load_canvas_toggle(false);
    current_file_label_->set_text("Will load: none");
  }
}

PixelBuffer* IOManager::LoadImageToCanvas() {
    std::cout << "Load Canvas has been clicked for file "
        << file_name_ << std::endl;
    /* Set image properties */
    png_image image;
    memset(&image, 0, (sizeof image));
    image.version = PNG_IMAGE_VERSION;
    /* Begin reading file */
    if (png_image_begin_read_from_file(&image, file_name_.c_str()) != 0) {
        png_bytep buffer; 
        image.format = PNG_FORMAT_RGBA;
        buffer = static_cast<png_bytep>(malloc(PNG_IMAGE_SIZE(image)));
        if (buffer != NULL &&
          png_image_finish_read(&image, NULL, buffer, 0, NULL) != 0) {
            /* Image is fully loaded, set to canvas */
            int width = image.width;
    		int height = image.height;
            int row = 0;
            int offset = 0;
            ColorData background (0.0, 0.0, 0.0);
            PixelBuffer* new_buffer = new PixelBuffer(width, height, background);
            /* Each pixel is 4 indices wide; this must be considered
             * when calculating row and column offsets */
			# pragma omp for
            for (int y = 0; y < height; y++) {
                row = 4*y*width;
                for (int x = 0; x < width; x++) {
                    offset = row + (4*x);
                    ColorData color(static_cast<float>(buffer[offset]/255.0),
                                    static_cast<float>(buffer[1+offset]/255.0),
                                    static_cast<float>(buffer[2+offset]/255.0),
                                    static_cast<float>(buffer[3+offset]/255.0));
                    new_buffer->set_pixel(x, (height-y-1), color);
                }
            }
            return new_buffer;
        }
    }
    return nullptr;
}

void IOManager::LoadImageToStamp(void) {
  std::cout << "Load Stamp has been clicked for file " <<
      file_name_ << std::endl;
}

void IOManager::SaveCanvasToFile(void) {
  std::cout << "Save Canvas been clicked for file " <<
      file_name_ << std::endl;
}

}  /* namespace image_tools */
