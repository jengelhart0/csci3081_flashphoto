/*******************************************************************************
 * Name            : sepia.h
 * Project         : FlashPhoto
 * Module          : utils
 * Description     : Header file for Sepia class.
 * Copyright       : 2016 CSCI3081W - Group C07. All rights reserved.
 * Creation Date   : 11/07/2016
 * Original Author : James Stanley
 *
 ******************************************************************************/

#ifndef SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_SEPIA_H_
#define SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_SEPIA_H_
/*******************************************************************************
 * Includes
 *******************************************************************************/
#include "lib/libimgtools/src/include/pixel_buffer.h"
#include "lib/libimgtools/src/include/filter.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This abstract base class from which all Sepias inherit defines the  
 * default implementation for ApplySepia() and declares the interface for ModifyPixel().
 */

class Sepia : public Filter {
 public:
      explicit Sepia(PixelBuffer *canvas);
      virtual ~Sepia(void);

      /** 
       * @brief Interpolate between grayscale image and original based on 
       */
      void ModifyPixel(int x, int y);

 private:
};
}  // namespace image_tools

#endif  // SRC_LIB_LIBIMGTOOLS_SRC_INCLUDE_SEPIA_H_
