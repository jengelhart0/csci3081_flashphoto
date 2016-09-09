/*******************************************************************************
 * Name            : PixelBuffer.h
 * Project         : BrushWork
 * Module          : ??
 * Description     : Class definition for Pixel buffers, which stores an array
 *                   of ColorData
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
    virtual ~PixelBuffer();

    // Sets the color of a specific pixel
    void setPixel(int x, int y, const ColorData& color);

    // Fills the enitre pixel buffer with the specified color
    void fillPixelBufferWithColor(ColorData color);


    // Returns the color of a specific pixel
    ColorData getPixel(int x, int y) const;

    // Returns a pointer to the raw ColorData array for fast access to ColorData
    ColorData const * getData() const;

    // Returns the background color that was used to initialize the PixelBuffer
    ColorData getBackgroundColor();

    int getHeight() const;
    int getWidth() const;

    // A static method to copy one pixel buffer to another
    static void copyPixelBuffer(
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
