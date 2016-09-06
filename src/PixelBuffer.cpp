//
//  PixelBuffer.cpp
//  Copyright 2016 CSci-3081W TAs.
//
#include "PixelBuffer.h"
#include "ColorData.h"

#include <iostream>
#include <cstring>

using std::cerr;
using std::endl;
using std::fill;

PixelBuffer::PixelBuffer(int w,
                         int h,
                         ColorData backgroundColor) : m_width(w),
                                                      m_height(h) {
    m_backgroundColor = new ColorData(backgroundColor);
    m_pixels = new ColorData[w*h];
    fillPixelBufferWithColor(backgroundColor);
}

PixelBuffer::~PixelBuffer() {
    delete [] m_pixels;
    delete m_backgroundColor;
}

ColorData PixelBuffer::getPixel(int x, int y) const {
    ColorData pixelData;

    if ((x < 0) || (x >= m_width) || (y < 0) || (y >= m_height)) {
        cerr << "getPixel: x,y out of range: " << x << " " << y << endl;
    } else {
        int index = x + m_width*(y);
        pixelData = m_pixels[index];
    }
    return pixelData;
}

void PixelBuffer::setPixel(int x, int y, const ColorData& newPixel) {
    if ((x < 0) || (x >= m_width) || (y < 0) || (y >= m_height)) {
        cerr << "setPixel: x,y out of range: " << x << " " << y << endl;
    } else {
        int index = x + m_width*(y);  // x + m_width*(m_height-(y+1));
        m_pixels[index] = newPixel;
    }
}

ColorData const * PixelBuffer::getData() const {
    return m_pixels;
}

int PixelBuffer::getHeight() const {
    return m_height;
}

int PixelBuffer::getWidth() const {
    return m_width;
}

ColorData PixelBuffer::getBackgroundColor() {
    return *m_backgroundColor;
}

void PixelBuffer::fillPixelBufferWithColor(ColorData color) {
    fill(m_pixels, m_pixels+m_width*m_height, color);
}

void PixelBuffer::copyPixelBuffer(
    PixelBuffer *sourceBuffer,
    PixelBuffer *destBuffer) {
    if (destBuffer->getWidth() != sourceBuffer->getWidth() ||
        destBuffer->getHeight() != sourceBuffer->getHeight()) {
        cerr << "copyPixelBuffer: " << "dimension mismatch" << endl;
    } else {
        memcpy(reinterpret_cast<void*>destBuffer->m_pixels,
               reinterpret_cast<void*>sourceBuffer->m_pixels,
               sizeof(ColorData)*destBuffer->m_height*destBuffer->m_width);
    }
}
