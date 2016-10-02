/*******************************************************************************
 * Name            : filter_manager.h
 * Project         : FlashPhoto
 * Module          : filter_handle
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

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A collection of filter parameters for manipulating photos
 * TODO: Add more detail, and add comments/doc for the members below
 */
class FilterManager {
 public:
  FilterManager();
  ~FilterManager() {}

  void ApplyBlur(void);
  void ApplySharpen(void);
  void ApplyMotionBlur(void);
  void ApplyEdgeDetect(void);
  void ApplyThreshold(void);
  void ApplyChannel(void);
  void ApplySaturate(void);
  void ApplyQuantize(void);

  void ApplySpecial(void);
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
  int motion_blur_direction_;
  int quantize_bins_;
};

}  // namespace image_tools
#endif  // INCLUDE_FILTER_MANAGER_H_
