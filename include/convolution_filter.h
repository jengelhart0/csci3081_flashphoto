/*******************************************************************************
 * Name            : convolution_filter.h
 * Project         : FlashPhoto
 * Module          : utils
 * Description     : Header file for ConvolutionFilter class.
 * Copyright       : 2016 CSCI3081W - Group C07. All rights reserved.
 * Creation Date   : 11/07/2016
 * Original Author : Joey Engelhart
 *
 ******************************************************************************/

#ifndef INCLUDE_CONVOLUTION_FILTER_H_
#define INCLUDE_CONVOLUTION_FILTER_H_
/*******************************************************************************
 * Includes
 *******************************************************************************/
#include "include/filter.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This extension of Filter overrides the base ApplyFilter() to allow to 
 * CreateKernel(). It also implements ModifyPixel() for all ConvolutionFilters.
 */

class ConvolutionFilter : public Filter {
  public:
      ConvolutionFilter(PixelBuffer *canvas);
      virtual ~ConvolutionFilter(void);

      virtual void ApplyFilter(void);
      virtual void ModifyPixel(int x, int y, PixelBuffer *canvas_copy);
      /* CreateKernel() differentiates ConvolutionFilters and must be implemented
       * by each one.
       */ 
      virtual void CreateKernel(void) = 0;

  private:
      Kernel kernel_;

