/*******************************************************************************
 * Name            : threshold.h
 * Project         : FlashPhoto
 * Module          : utils
 * Description     : Header file for Threshold class.
 * Copyright       : 2016 CSCI3081W - Group C07. All rights reserved.
 * Creation Date   : 11/07/2016
 * Original Author : James Stanley
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_THRESHOLD_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_THRESHOLD_H_
/*******************************************************************************
 * Includes
 *******************************************************************************/
#include "./pixel_buffer.h"
#include "./filter.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This class holds the implementation of the threshold filter
 */

class Threshold : public Filter {
 public:
      explicit Threshold(PixelBuffer *canvas);
      virtual ~Threshold(void);

      /**
       * @brief Setter method threshold value
       */
      void threshold(float new_threshold) { threshold_ = new_threshold; }

      /**
       * @brief Rounds each color channel to 1 or 0 depending on
       * threshold values
       */
      void ModifyPixel(int x, int y);

 private:
      float threshold_;
};
}  // namespace image_tools

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_THRESHOLD_H_
