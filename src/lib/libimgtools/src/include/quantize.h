/*******************************************************************************
 * Name            : quantize.h
 * Project         : FlashPhoto
 * Module          : utils
 * Description     : Header file for Quantize class.
 * Copyright       : 2016 CSCI3081W - Group C07. All rights reserved.
 * Creation Date   : 11/15/2016
 * Original Author : James Stanley
 *
 ******************************************************************************/

#ifndef INCLUDE_QUANTIZE_H_
#define INCLUDE_QUANTIZE_H_
/*******************************************************************************
 * Includes
 *******************************************************************************/
#include "pixel_buffer.h"
#include "filter.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This abstract base class from which all Quantizes inherit defines the  
 *        default implementation for ApplyQuantize() and declares the interface for ModifyPixel().
 */

class Quantize : public Filter {
 public:
      explicit Quantize(PixelBuffer *canvas);
      virtual ~Quantize(void);

      /*
       * @brief Setter method quantize value
       */
      void bins(int bins) { bins_ = bins; }

      /* 
       * @brief Adjust each color channel based on number of bins
       */
      void ModifyPixel(int x, int y);

 private:
      int bins_;
};
}  // namespace image_tools

#endif    // INCLUDE_QUANTIZE_H_
