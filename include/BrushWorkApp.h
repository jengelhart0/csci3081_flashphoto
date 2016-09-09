/*******************************************************************************
 * Name            : BrushWorkApp.h
 * Project         : BrushWork
 * Module          : ??
 * Description     : Main class for BrushWork
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

#ifndef INCLUDE_BRUSHWORKAPP_H_
#define INCLUDE_BRUSHWORKAPP_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "BaseGfxApp.h"

/*******************************************************************************
 * Forward Declarations
 ******************************************************************************/
class ColorData;
class PixelBuffer;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * This is the main class for BrushWork. It is a graphics app that derives
 * from BaseGfxApp. It creates two graphics windows, one for 2D painting and
 * one for the buttons and other UI widgets to control the brushes.
 **/
class BrushWorkApp : public BaseGfxApp {
 public:
    BrushWorkApp(
        int argc,
        char* argv[],
        int width,
        int height,
        ColorData backgroundColor);
    virtual ~BrushWorkApp(void);

    // Glut overrided function
    void mouseDragged(int x, int y);
    void mouseMoved(int x, int y);
    void leftMouseDown(int x, int y);
    void leftMouseUp(int x, int y);
    void display(void);
    void gluiControl(int controlID);

 private:
    // BrushWork-specific functions
    void initGlui(void);
    void initGraphics(void);
    void initializeBuffers(ColorData initialColor, int width, int height);

    // GLUI INTERFACE ELEMENTS
    enum UIControlType {
        UI_TOOLTYPE,
        UI_COLOR_R,
        UI_COLOR_G,
        UI_COLOR_B,
        UI_PRESET_RED,
        UI_PRESET_ORANGE,
        UI_PRESET_YELLOW,
        UI_PRESET_GREEN,
        UI_PRESET_BLUE,
        UI_PRESET_PURPLE,
        UI_PRESET_WHITE,
        UI_PRESET_BLACK,
        UI_QUIT
    };


    // This is the pointer to the buffer where the display PixelBuffer is stored
    PixelBuffer *display_buffer_;

    // These are used to store the selections from the GLUI user interface
    int cur_tool_;
    float cur_color_red_, cur_color_green_, cur_color_blue_;
    GLUI_Spinner *spinner_r_;
    GLUI_Spinner *spinner_g_;
    GLUI_Spinner *spinner_b_;

    BrushWorkApp(const BrushWorkApp &rhs) = delete;
    BrushWorkApp& operator=(const BrushWorkApp &rhs) = delete;
};

#endif  // INCLUDE_BRUSHWORKAPP_H_
