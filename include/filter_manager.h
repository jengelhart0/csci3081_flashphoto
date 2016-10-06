/*******************************************************************************
 * Name            : filter_manager.h
 * Project         : FlashPhoto
 * Module          : filter_manager
 * Description     : Header for FilterManager class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : Wed Sep 21 18:40:20 2016
 * Original Author : jharwell
 *
 ******************************************************************************/

#ifndef INCLUDE_FILTER_MANAGER_H_
#define INCLUDE_FILTER_MANAGER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "GL/glui.h"
#include "include/pixel_buffer.h"
#include "include/k_motion_blur.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Handles all aspects of filters in the project. Contains the
 * FilterFactory().
 * TODO: Add more detail
 */
class FilterManager {
 public:
  FilterManager();
  ~FilterManager() {}

  /**
   * @brief Apply a blur filter to the buffer, blurring sharply defined edges
   *
   * @param buffer The buffer. Updated to point to a new filtered buffer.
   */
  void ApplyBlur(PixelBuffer **buffer);

  /**
   * @brief Apply a sharpening filter to the buffer, sharpening blurry/undefined
   * edges
   *
   * @param buffer The buffer. Updated to point to a new filtered buffer.
   */
  void ApplySharpen(PixelBuffer **buffer);

  /**
   * @brief Apply a motion blurring filter to the buffer
   *
   * @param buffer The buffer. Updated to point to a new filtered buffer.
   */
  void ApplyMotionBlur(PixelBuffer **buffer);

  /**
   * @brief Apply an edge detection filter to the buffer
   *
   * @param buffer The buffer. Updated to point to a new filtered buffer.
   */
  void ApplyEdgeDetect(PixelBuffer **buffer);

  /**
   * @brief Apply a threshold detection filter to the buffer
   *
   * @param buffer The buffer. Updated to point to a new filtered buffer.
   */
  void ApplyThreshold(PixelBuffer **buffer);

  /**
   * @brief Apply a channel filter to the buffer
   *
   * @param buffer The buffer. Updated to point to a new filtered buffer.
   */
  void ApplyChannel(PixelBuffer **buffer);

  /**
   * @brief Apply a channel filter to the buffer
   *
   * @param buffer The buffer. Updated to point to a new filtered buffer.
   */
  void ApplySaturate(PixelBuffer **buffer);


  /**
   * @brief Apply a quantization filter to the buffer
   *
   * @param buffer The buffer. Updated to point to a new filtered buffer.
   */
  void ApplyQuantize(PixelBuffer **buffer);

  /**
   * @brief Apply a special filter to the buffer
   *
   * @param buffer The buffer. Updated to point to a new filtered buffer.
   */
  void ApplySpecial(PixelBuffer **buffer);

  /**
   * @brief Initialize the elements of the GLUI interface required by the
   * FilterManager
   *
   * @param glui GLUI handle
   * @param s_gluicallback Callback to install
   */
  void InitGlui(const GLUI *const glui,
                void (*s_gluicallback)(int));

 private:
  float channel_color_red_;
  float channel_color_green_;
  float channel_color_blue_;
  float saturation_amount_;
  float threshold_amount_;
  float blur_amount_;
  float sharpen_amount_;
  float motion_blur_amount_;
  enum KMotionBlur::Direction motion_blur_direction_;
  int quantize_bins_;
};

}  // namespace image_tools
#endif  // INCLUDE_FILTER_MANAGER_H_
