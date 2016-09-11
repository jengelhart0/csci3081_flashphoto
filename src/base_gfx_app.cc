/*******************************************************************************
 * Name            : base_gfx_app.cc
 * Project         : BrushWork
 * Module          : ??
 * Description     : Implementation of things common to all graphics
 *                   applications built on top of GLUI/GLUT toolkits
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : 2/15/15
 * Original Author : Seth Johnson
 *
******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "BaseGfxApp.h"
#include <assert.h>
#include <iostream>
#include <string>

/*******************************************************************************
 * Namespace Definitions
 ******************************************************************************/

/*******************************************************************************
 * Global Variables
 ******************************************************************************/
csci3081::BaseGfxApp* csci3081::BaseGfxApp::s_current_app_ = NULL;
bool csci3081::BaseGfxApp::s_glut_initialized_ = false;

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
csci3081::BaseGfxApp::BaseGfxApp(int width,
                                 int height)
    : glut_window_handle_(0),
      glui_(nullptr),
      drag_(false),
      width_(width),
      height_(height),
      milliseconds_(0) {
    s_current_app_ = this;
}

csci3081::BaseGfxApp::~BaseGfxApp(void) {
    s_current_app_ = NULL;
    glutDestroyWindow(glut_window_handle_);
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void csci3081::BaseGfxApp::Init(int argc,
                      char* argv[],
                      int x,
                      int y,
                      unsigned glutFlags,
                      bool createGLUIWin,
                      int gluiWinX,
                      int gluiWinY) {
    // Set window size and position
    glutInitWindowSize(width_,height_);
    glutInitWindowPosition(x,y);
    glutInitDisplayMode(glutFlags);

    if (!s_glut_initialized_) {
        glutInit(&argc, argv);
        s_glut_initialized_ = true;
    }

    glut_window_handle_ = glutCreateWindow("Graphics Window");

    glutReshapeFunc(s_reshape);
    glutKeyboardFunc(s_keyboard);
    glutKeyboardUpFunc(s_keyboardup);
    glutSpecialFunc(s_keyboardspecial);
    glutSpecialUpFunc(s_keyboardspecialup);
    glutMotionFunc(s_mousemotion);
    glutPassiveMotionFunc(s_mousemotion);
    glutMouseFunc(s_mousebtn);
    glutDisplayFunc(s_draw);
    glutIdleFunc(s_idle);

    if (createGLUIWin) {
        glui_ = GLUI_Master.create_glui("Controls", 0,
                                         gluiWinX, gluiWinY);
        glui_->set_main_gfx_window(glut_window_handle_);
        // Note: if using a glut idle func, it may need to be registered
        // with glui rather than glut.
        GLUI_Master.set_glutIdleFunc(NULL);
    }
}
void csci3081::BaseGfxApp::set_caption(const std::string& caption) {
    glutSetWindowTitle(caption.c_str());
    glutSetIconTitle(caption.c_str());
}

void csci3081::BaseGfxApp::RunMainLoop(void) {
    glutMainLoop();
}

void csci3081::BaseGfxApp::Reshape(int width, int height) {
    // This code essentially disables the ability to interactively resize
    // the graphics window. csci3081::BaseGfxApp defaults to a window that cannot be
    // resized by dragging the corner with the mouse.
    if (s_current_app_->width() != width ||
        s_current_app_->height() != height) {
        glutReshapeWindow(s_current_app_->width(), s_current_app_->height());
    }
}

void csci3081::BaseGfxApp::RenderOneFrame(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Display();
    glutSwapBuffers();
}

void csci3081::BaseGfxApp::DrawPixels(int start_x, int start_y, int width,
                            int height, void const * const pixels) {
    glRasterPos2i(start_x, start_y);
    glDrawPixels(width, height, GL_RGBA, GL_FLOAT, pixels);

    unsigned err = glGetError();
    if (err != GL_NO_ERROR) {
        std::cerr << "GL is in an error state after call to glDrawPixels()\n";
        std::cerr << "(GL error code " << err << ")\n";
        assert(0);
    }
}

void csci3081::BaseGfxApp::s_reshape(int width, int height) {
    s_current_app_->Reshape(width, height);
}

void csci3081::BaseGfxApp::s_keyboard(unsigned char c, int x, int y) {
    s_current_app_->Keyboard(c, x, y);
    glutPostRedisplay();
}

void csci3081::BaseGfxApp::s_keyboardspecial(int key, int x, int y) {
    s_current_app_->KeyboardSpecial(key, x, y);
    glutPostRedisplay();
}

void csci3081::BaseGfxApp::s_keyboardup(unsigned char c, int x, int y) {
    s_current_app_->KeyboardUp(c, x, y);
    glutPostRedisplay();
}

void csci3081::BaseGfxApp::s_keyboardspecialup(int key, int x, int y) {
    s_current_app_->KeyboardSpecialUp(key, x, y);
    glutPostRedisplay();
}

void csci3081::BaseGfxApp::s_mousemotion(int x, int y) {
    if (s_current_app_->drag_ == true) {
        s_current_app_->MouseDragged(x, y);
    } else {
        s_current_app_->MouseMoved(x, y);
    }
    glutPostRedisplay();
}

void csci3081::BaseGfxApp::s_mousebtn(int b, int s, int x, int y) {
    if ((b == GLUT_LEFT_BUTTON) && (s == GLUT_UP)) {
        s_current_app_->LeftMouseUp(x, y);
        s_current_app_->drag_ = false;
    } else if ((b == GLUT_LEFT_BUTTON) && (s == GLUT_DOWN)) {
        s_current_app_->LeftMouseDown(x, y);
        s_current_app_->drag_ = true;
    } else if ((b == GLUT_RIGHT_BUTTON) && (s == GLUT_UP)) {
        s_current_app_->RightMouseUp(x, y);
    } else if ((b == GLUT_RIGHT_BUTTON) && (s == GLUT_DOWN)) {
        s_current_app_->RightMouseDown(x, y);
    } else if ((b == GLUT_MIDDLE_BUTTON) && (s == GLUT_UP)) {
        s_current_app_->MiddleMouseUp(x, y);
    } else if ((b == GLUT_MIDDLE_BUTTON) && (s == GLUT_DOWN)) {
        s_current_app_->MiddleMouseDown(x, y);
    }
    glutPostRedisplay();
}

void csci3081::BaseGfxApp::s_draw(void) {
    s_current_app_->RenderOneFrame();
}

void csci3081::BaseGfxApp::s_gluicallback(int controlID) {
    s_current_app_->GluiControl(controlID);
}

void csci3081::BaseGfxApp::s_idle(void) {
    int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
    int delta = timeSinceStart - s_current_app_->milliseconds_;
    if (delta > 0) {
        s_current_app_->milliseconds_ = timeSinceStart;
        s_current_app_->Update(delta);
    }
}

void csci3081::BaseGfxApp::SetWindowDimensions(int width, int height) {
    height_ = height;
    width_ = width;
    glutReshapeWindow(width_, height_);
}
