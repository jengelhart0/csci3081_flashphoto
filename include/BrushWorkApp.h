/*******************************************************************************
 * Name            : BrushWorkApp.h
 * Project         : BrushWork
 * Module          : ??
 * Description     : Header file for BrushWork application.
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
#include "ColorData.h"
#include "PixelBuffer.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace csci3081 {
namespace brushwork {

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for BrushWork.
 * It is a graphics app that derives from BaseGfxApp. It creates two graphics
 * windows, one for 2D painting and one for the buttons and other UI widgets to
 * control the brushes.
 **/
class BrushWorkApp : public csci3081::BaseGfxApp {
 public:
    BrushWorkApp(
        int width,
        int height);

    virtual ~BrushWorkApp(void);

    void MouseDragged(int x, int y);
    void MouseMoved(int x, int y);
    void LeftMouseDown(int x, int y);
    void LeftMouseUp(int x, int y);
    void Display(void);
    void GluiControl(int controlID);

    virtual void Init(
        int argc,
        char* argv[],
        int x,
        int y,
        csci3081::ColorData backgroundColor);

 private:
    void InitGlui(void);
    void InitGraphics(void);

    /**
     * @brief Initialize the buffers for the main window
     */
    void InitializeBuffers(::csci3081::ColorData initialColor, int width, int height);

    /**
     * @brief Set of values used to differentiate between what radio buttons is
     * pressed by the user.
     */
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

    csci3081::PixelBuffer *display_buffer_; /** Array of pixel data for the screen  */

    int cur_tool_; /** Currently selected tool from UI  */
    float cur_color_red_;
    float cur_color_green_;
    float cur_color_blue_;

    GLUI_Spinner *spinner_r_; /** SETH FILL THIS IN  */
    GLUI_Spinner *spinner_g_;
    GLUI_Spinner *spinner_b_;

    /* Copy/move assignment/construction disallowed */
    BrushWorkApp(const BrushWorkApp &rhs) = delete;
    BrushWorkApp& operator=(const BrushWorkApp &rhs) = delete;
};
}  // namespace brushwork
}  // namespace csci3081

#endif  // INCLUDE_BRUSHWORKAPP_H_
