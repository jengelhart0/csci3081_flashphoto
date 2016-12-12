/*******************************************************************************
 * Name            : kernel.h
 * Project         : FlashPhoto
 * Module          : utils
 * Description     : Header file for Kernel class.
 * Copyright       : 2016 CSCI3081W - Group C07. All rights reserved.
 * Creation Date   : 11/10/2016
 * Original Author : Joey Engelhart
 *
 ******************************************************************************/

#ifndef INCLUDE_KERNEL_H_
#define INCLUDE_KERNEL_H_
/*******************************************************************************
 * Includes
 *******************************************************************************/
#include <cmath>
#include "pixel_buffer.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This abstract class is a base for the different types of kernels for ConvolutionFilters.        
 */

class Kernel {
 public:
     Kernel(float filter_amount, int dimension);
     explicit Kernel(int dimension);
     virtual ~Kernel(void);
     /**
      * @brief Gets value of kernel at (x, y)
      * @return Float representing weight value
      */ 
     float weight(int x, int y);
     /**
      * @return Integer dimension of kernel
      */
     int dimension(void);
     /**
      * @return Float representing filter magnitude.
      */
     float filter_amount(void);

 protected:
     /**
      * @brief Initializes float values according to
      * the required characteristics of specific kernel subclass.
      */
     virtual void InitKernel(void) = 0;
     /**
      * @brief Sets value of one float in kernel
      */
     void weight(int x, int y, float value);

 private:
     /**
      * @brief Allocates data to hold kernel in memory
      * according to dimension.
      */
     void init_data(void);
     float filter_amount_; 
     int dimension_;
     float *data_; /**< Maintains individual values in kernel */
};
}  // namespace image_tools

#endif  // INCLUDE_KERNEL_H_
