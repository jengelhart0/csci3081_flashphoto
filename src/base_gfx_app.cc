/*******************************************************************************
 * Name            : base_gfx_app.cc
 * Project         : BrushWork
 * Module          : ??
 * Description     : Implementation of common behaviors for all apps built on
 *                   GLUI/GLUT toolkits
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
 * Global Variables
 ******************************************************************************/
BaseGfxApp* BaseGfxApp::s_current_app_ = nullptr;
bool BaseGfxApp::s_glut_initialized_ = false;

/*******************************************************************************
 * Constructors/Destructors
 ******************************************************************************/
BaseGfxApp::BaseGfxApp(int argc,
                       char* argv[],
                       int width,
                       int height,
                       int x,
                       int y,
                       unsigned glutFlags,
                       bool createGLUIWin,
                       int gluiWinX,
                       int gluiWinY)
    : glut_window_handle_(0),
      glui_(nullptr),
      drag_(false),
      width_(width),
      height_(height),
      milliseconds_(0) {
    s_current_app_ = this;

    // Set window size and position
    glutInitWindowSize(width, height);
    glutInitWindowPosition(x, y);
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
        GLUI_Master.set_glutIdleFunc(nullptr);
    }
}

BaseGfxApp::~BaseGfxApp() {
    s_current_app_ = nullptr;
    glutDestroyWindow(glut_window_handle_);
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void BaseGfxApp::set_caption(const std::string& caption) {
    glutSetWindowTitle(caption.c_str());
    glutSetIconTitle(caption.c_str());
}

void BaseGfxApp::RunMainLoop() {
    glutMainLoop();
}

void BaseGfxApp::Reshape(int width, int height) {
    // This code essentially disables the ability to interactively resize
    // the graphics window. BaseGfxApp defaults to a window that cannot be
    // resized by dragging the corner with the mouse.
    if (s_current_app_->width() != width ||
        s_current_app_->height() != height) {
        glutReshapeWindow(s_current_app_->width(), s_current_app_->height());
    }
}

void BaseGfxApp::RenderOneFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Display();
    glutSwapBuffers();
}



void BaseGfxApp::DrawPixels(int start_x, int start_y, int width,
                            int height, void const * const pixels) {
    glRasterPos2i(start_x, start_y);
    glDrawPixels(width, height, GL_RGBA, GL_FLOAT, pixels);

    unsigned err;
    if ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "GL is in an error state after call to glDrawPixels()\n";
        std::cerr << "(GL error code " << err << ")\n";
        assert(0);
    }
}

int BaseGfxApp::width() const { return width_; }
int BaseGfxApp::height() const { return height_; }

void BaseGfxApp::SetWindowDimensions(int width, int height) {
    height_ = height;
    width_ = width;
    glutReshapeWindow(width_, height_);
}

/*******************************************************************************
 * Static Member Functions
 ******************************************************************************/
void BaseGfxApp::s_reshape(int width, int height) {
    s_current_app_->Reshape(width, height);
}

void BaseGfxApp::s_keyboard(unsigned char c, int x, int y) {
    s_current_app_->keyboard(c, x, y);
    glutPostRedisplay();
}

void BaseGfxApp::s_keyboardspecial(int key, int x, int y) {
    s_current_app_->keyboardSpecial(key, x, y);
    glutPostRedisplay();
}

void BaseGfxApp::s_keyboardup(unsigned char c, int x, int y) {
    s_current_app_->keyboardUp(c, x, y);
    glutPostRedisplay();
}

void BaseGfxApp::s_keyboardspecialup(int key, int x, int y) {
    s_current_app_->keyboardSpecialUp(key, x, y);
    glutPostRedisplay();
}

void BaseGfxApp::s_mousemotion(int x, int y) {
    if (s_current_app_->drag_ == true) {
        s_current_app_->mouseDragged(x, y);
    } else {
        s_current_app_->mouseMoved(x, y);
    }
    glutPostRedisplay();
}

void BaseGfxApp::s_mousebtn(int b, int s, int x, int y) {
    if ((b == GLUT_LEFT_BUTTON) && (s == GLUT_UP)) {
        s_current_app_->leftMouseUp(x, y);
        s_current_app_->drag_ = false;
    } else if ((b == GLUT_LEFT_BUTTON) && (s == GLUT_DOWN)) {
        s_current_app_->leftMouseDown(x, y);
        s_current_app_->drag_ = true;
    } else if ((b == GLUT_RIGHT_BUTTON) && (s == GLUT_UP)) {
        s_current_app_->rightMouseUp(x, y);
    } else if ((b == GLUT_RIGHT_BUTTON) && (s == GLUT_DOWN)) {
        s_current_app_->rightMouseDown(x, y);
    } else if ((b == GLUT_MIDDLE_BUTTON) && (s == GLUT_UP)) {
        s_current_app_->middleMouseUp(x, y);
    } else if ((b == GLUT_MIDDLE_BUTTON) && (s == GLUT_DOWN)) {
        s_current_app_->middleMouseDown(x, y);
    }
    glutPostRedisplay();
}

void BaseGfxApp::s_draw() {
    s_current_app_->RenderOneFrame();
}

void BaseGfxApp::s_gluicallback(int controlID) {
    s_current_app_->gluiControl(controlID);
}

void BaseGfxApp::s_idle() {
    int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
    int delta = timeSinceStart - s_current_app_->milliseconds_;
    if (delta > 0) {
        s_current_app_->milliseconds_ = timeSinceStart;
        s_current_app_->update(delta);
    }
}
