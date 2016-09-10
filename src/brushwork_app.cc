/*******************************************************************************
 * Name            : brushwork_app.cc
 * Project         : BrushWork
 * Module          : ??
 * Description     : Implementation of BrushWrok
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "BrushWorkApp.h"
#include "ColorData.h"
#include "PixelBuffer.h"

#include <cmath>
#include <iostream>

/*******************************************************************************
 * Namespace Definitions
 ******************************************************************************/
using std::cout;
using std::endl;

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
BrushWorkApp::BrushWorkApp(int argc,
                           char* argv[],
                           int width,
                           int height,
                           ColorData backgroundColor)
    : BaseGfxApp(argc,
                 argv,
                 width,
                 height,
                 50,
                 50,
                 GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH,
                 true,
                 width+51,
                 50),
      display_buffer_(nullptr),
      cur_tool_(0.0),
      cur_color_red_(0.0),
      cur_color_green_(0.0),
      cur_color_blue_(0.0),
      spinner_r_(nullptr),
      spinner_g_(nullptr),
      spinner_b_(nullptr)

{
    // Set the name of the window
    set_caption("BrushWork");

    // Initialize Interface
    InitializeBuffers(backgroundColor, width, height);

    InitGlui();
    InitGraphics();
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
BrushWorkApp::~BrushWorkApp(void) {
    if (display_buffer_) {
        delete display_buffer_;
    }
}

void BrushWorkApp::Display(void) {
    DrawPixels(0, 0, width(), height(), display_buffer_->get_data());
}


void BrushWorkApp::MouseDragged(int x, int y) {}

void BrushWorkApp::MouseMoved(int x, int y) {}


void BrushWorkApp::LeftMouseDown(int x, int y) {
    std::cout << "mousePressed " << x << " " << y << std::endl;
}

void BrushWorkApp::LeftMouseUp(int x, int y) {
    std::cout << "mouseReleased " << x << " " << y << std::endl;
}

void BrushWorkApp::InitializeBuffers(
    ColorData backgroundColor,
    int width,
    int height) {
    display_buffer_ = new PixelBuffer(width, height, backgroundColor);
}

void BrushWorkApp::InitGlui(void) {
    // Select first tool (this activates the first radio button in glui)
    cur_tool_ = 0;

    GLUI_Panel *toolPanel = new GLUI_Panel(glui(), "Tool Type");
    GLUI_RadioGroup *radio = new GLUI_RadioGroup(toolPanel,
                                                 &cur_tool_,
                                                 UI_TOOLTYPE,
                                                 s_gluicallback);

    // Create interface buttons for different tools:
    new GLUI_RadioButton(radio, "Pen");
    new GLUI_RadioButton(radio, "Eraser");
    new GLUI_RadioButton(radio, "Spray Can");
    new GLUI_RadioButton(radio, "Caligraphy Pen");
    new GLUI_RadioButton(radio, "Highlighter");

    GLUI_Panel *colPanel = new GLUI_Panel(glui(), "Tool Color");

    cur_color_red_ = 0;
    spinner_r_  = new GLUI_Spinner(colPanel, "Red:", &cur_color_red_,
                                   UI_COLOR_R, s_gluicallback);
    spinner_r_->set_float_limits(0, 1.0);

    cur_color_green_ = 0;
    spinner_g_ = new GLUI_Spinner(colPanel, "Green:", &cur_color_green_,
                                   UI_COLOR_G, s_gluicallback);
    spinner_g_->set_float_limits(0, 1.0);

    cur_color_blue_ = 0;
    spinner_b_  = new GLUI_Spinner(colPanel, "Blue:", &cur_color_blue_,
                                   UI_COLOR_B, s_gluicallback);
    spinner_b_->set_float_limits(0, 1.0);
    new GLUI_Button(colPanel, "Red", UI_PRESET_RED, s_gluicallback);
    new GLUI_Button(colPanel, "Orange", UI_PRESET_ORANGE, s_gluicallback);
    new GLUI_Button(colPanel, "Yellow", UI_PRESET_YELLOW, s_gluicallback);
    new GLUI_Button(colPanel, "Green", UI_PRESET_GREEN, s_gluicallback);
    new GLUI_Button(colPanel, "Blue", UI_PRESET_BLUE, s_gluicallback);
    new GLUI_Button(colPanel, "Purple", UI_PRESET_PURPLE, s_gluicallback);
    new GLUI_Button(colPanel, "White", UI_PRESET_WHITE, s_gluicallback);
    new GLUI_Button(colPanel, "Black", UI_PRESET_BLACK, s_gluicallback);


    new GLUI_Button(glui(), "Quit", UI_QUIT, static_cast<GLUI_Update_CB>(exit));
}


void BrushWorkApp::InitGraphics(void) {
    // Initialize OpenGL for 2D graphics as used in the BrushWork app
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluOrtho2D(0, width(), 0, height());
    glViewport(0, 0, width(), height());
}



void BrushWorkApp::GluiControl(int controlID) {
    switch (controlID) {
    case UI_PRESET_RED:
        cur_color_red_ = 1;
        cur_color_green_ = 0;
        cur_color_blue_ = 0;
        break;
    case UI_PRESET_ORANGE:
        cur_color_red_ = 1;
        cur_color_green_ = 0.5;
        cur_color_blue_ = 0;
        break;
    case UI_PRESET_YELLOW:
        cur_color_red_ = 1;
        cur_color_green_ = 1;
        cur_color_blue_ = 0;
        break;
    case UI_PRESET_GREEN:
        cur_color_red_ = 0;
        cur_color_green_ = 1;
        cur_color_blue_ = 0;
        break;
    case UI_PRESET_BLUE:
        cur_color_red_ = 0;
        cur_color_green_ = 0;
        cur_color_blue_ = 1;
        break;
    case UI_PRESET_PURPLE:
        cur_color_red_ = 0.5;
        cur_color_green_ = 0;
        cur_color_blue_ = 1;
        break;
    case UI_PRESET_WHITE:
        cur_color_red_ = 1;
        cur_color_green_ = 1;
        cur_color_blue_ = 1;
        break;
    case UI_PRESET_BLACK:
        cur_color_red_ = 0;
        cur_color_green_ = 0;
        cur_color_blue_ = 0;
        break;
    default:
        break;
    }

    spinner_b_->set_float_val(cur_color_blue_);
    spinner_g_->set_float_val(cur_color_green_);
    spinner_r_->set_float_val(cur_color_red_);
}
