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

void IOManager::LoadImageToCanvas(void) {
    std::cout << "Load Canvas has been clicked for file " 
        << file_name_ << std::endl;
    /* Open file and initialize data structures, useful variables */
    FILE *fp = fopen(file_name_.c_str(), "rb");
    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_init_io(png, fp);
    png_infop info = png_create_info_struct(png);
    int width = png_get_image_width(png, info);
    int height = png_get_image_height(png, info);
    png_byte color_type = png_get_color_type(png, info);
    png_byte bit_depth = png_get_bit_depth(png, info);
    /* Need 8-bit */
    if(bit_depth == 16) {
        png_set_strip_16(png);
    }
    png_read_update_info(png, info);
    /* Allocate space for image */
    png_bytep* rows = static_cast<png_bytep*>(malloc(sizeof(png_bytep) * height));
    for (int i = 0; i < height; i++) {
        rows[i] = static_cast<png_byte*>(malloc(png_get_rowbytes(png, info)));
    }
    /* Read image */
    png_read_image(png, rows);
    fclose(fp);
    /* Iterate over rows, set pixels on canvas */
    png_bytep row;
    png_bytep px;
    printf("Image of height %d and width %d\n", height, width);
    for (int i = 0; i < height; i++) {
        row = rows[i];
        for (int j = 0; j < width; j++) {
            px = &(row[j*4]);
            printf("%4d, %4d = RGBA(%3d, %3d, %3d, %3d)\n", j, i, px[0], px[1], px[2], px[3]);
        }
    }
    return;
    /* Set image properties *
    png_image image;
    image.version = PNG_IMAGE_VERSION;
    image.format = PNG_FORMAT_RGBA;
    // Begin reading file *
    if (png_image_begin_read_from_file(&image, file) != 0) {
        png_bytep buffer = static_cast<png_bytep>(malloc(PNG_IMAGE_SIZE(image)));
        
        if (buffer != NULL &&
          png_image_finish_read(&image, NULL, buffer, 0, NULL) != 0) {
            // Image is fully loaded, set to canvas *
            Reshape(image.width, image.height);
            for (int i = 0; i < canvas_height_; i++) {
                for (int j = 0; j < canvas_width_; j++) {
                    // Somehow do something with bytes *
                }
            }
        }
    } */

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
