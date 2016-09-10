/*******************************************************************************
 * Name            : PixelBuffer.h
 * Project         : BrushWork
 * Module          : ??
 * Description     : Header file for PixelBuffer class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
******************************************************************************/

#ifndef INCLUDE_PIXELBUFFER_H_
#define INCLUDE_PIXELBUFFER_H_

/*******************************************************************************
 * Forward Declarations
 ******************************************************************************/
class ColorData;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * The PixelBuffer class stores an array of ColorData, such as an image that
 * can be drawn to the screen.
 **/
class PixelBuffer {
 public:
    PixelBuffer(int w, int h, ColorData background_color);
    virtual ~PixelBuffer(void);

    // Sets the color of a specific pixel
    void set_pixel(int x, int y, const ColorData& color);

    // Fills the enitre pixel buffer with the specified color
    void FillPixelBufferWithColor(ColorData color);


    // Returns the color of a specific pixel
    ColorData get_pixel(int x, int y) const;

    // Returns a pointer to the raw ColorData array for fast access to ColorData
    ColorData const * get_data(void) const;

    // Returns the background color that was used to initialize the PixelBuffer
    ColorData get_background_color(void);

    int get_height(void) const;
    int get_width(void) const;

    // A static method to copy one pixel buffer to another
    static void CopyPixelBuffer(
        PixelBuffer *sourceBuffer,
        PixelBuffer *destinationBuffer);

 private:
    // Dimensions
    const int width_;
    const int height_;

    // Array of pixel colors
    ColorData * pixels_;

    // Pointer to the single color used as the "background color" to initialize
    // the PixelBuffer
    ColorData * background_color_;


    PixelBuffer(const PixelBuffer&rhs) = delete;
    PixelBuffer& operator=(const PixelBuffer&rhs) = delete;
};

#endif  // INCLUDE_PIXELBUFFER_H_
