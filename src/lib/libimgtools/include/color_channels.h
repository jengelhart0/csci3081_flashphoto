/*******************************************************************************
 * Name            : color_channels.h
 * Project         : FlashPhoto
 * Module          : utils
 * Description     : Header file for ColorChannels class.
 * Copyright       : 2016 CSCI3081W - Group C07. All rights reserved.
 * Creation Date   : 11/07/2016
 * Original Author : James Stanley
 *
 ******************************************************************************/

#ifndef INCLUDE_COLOR_CHANNELS_H_
#define INCLUDE_COLOR_CHANNELS_H_
/*******************************************************************************
 * Includes
 *******************************************************************************/
#include "include/pixel_buffer.h"
#include "include/filter.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This abstract base class from which all ColorChannelss inherit defines the  
 *        default implementation for ApplyColorChannels() and declares the interface for ModifyPixel().
 */

class ColorChannels : public Filter {
 public:
    explicit ColorChannels(PixelBuffer *canvas);
    virtual ~ColorChannels(void);

    /*
    * @brief Setter methods for color channel values
    */
    void red(float r) { red_ = r; }
    void green(float g) { green_ = g; }
    void blue(float b) { blue_ = b; }

    /*
     * @brief Getter methods for color channel values
     */
    float red(void) const { return red_; }
    float green(void) const { return green_; }
    float blue(void) const { return blue_; }

    /* 
    * @brief Multiply each color channel by specified value
    */
    void ModifyPixel(int x, int y);

 private:
    float red_;
    float blue_;
    float green_;
};
}  // namespace image_tools

#endif  // INCLUDE_COLOR_CHANNELS_H_
