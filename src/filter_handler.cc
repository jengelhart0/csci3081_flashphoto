/*******************************************************************************
 * Name            : filter_handler.cc
 * Project         : FlashPhoto
 * Module          : filter_handler
 * Description     : Implementation of FilterHandler class
 * Copyright       : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date   : Wed Sep 21 18:47:02 2016
 * Original Author : jharwell
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/filter_handler.h"
#include <iostream>
#include "include/ui_ctrl.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
namespace image_tools {

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
FilterHandler::FilterHandler(void) :
    channel_color_red_(0.0),
    channel_color_green_(0.0),
    channel_color_blue_(0.0),
    saturation_amount_(0.0),
    threshold_amount_(0.0),
    blur_amount_(0.0),
    sharpen_amount_(0.0),
    motion_blur_amount_(0.0),
    motion_blur_direction_(0),
    quantize_bins_(0) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void FilterHandler::ApplyChannel(void) {
  std::cout << "Apply has been clicked for Channels with red = "
       << channel_color_red_
       << ", green = " << channel_color_green_
       << ", blue = " << channel_color_blue_ << std::endl;
}

void FilterHandler::ApplySaturate(void) {
  std::cout << "Apply has been clicked for Saturate with amount = "
       << saturation_amount_ << std::endl;
}

void FilterHandler::ApplyBlur(void) {
  std::cout << "Apply has been clicked for Blur with amount = "
       << blur_amount_ << std::endl;
}

void FilterHandler::ApplySharpen(void) {
  std::cout << "Apply has been clicked for Sharpen with amount = "
       << sharpen_amount_ << std::endl;
}

void FilterHandler::ApplyMotionBlur(void) {
  std::cout << "Apply has been clicked for Sharpen with amount = "
       << motion_blur_amount_
       << " and direction " << motion_blur_direction_ << std::endl;
}

void FilterHandler::ApplyEdgeDetect(void) {
  std::cout << "Apply has been clicked for Edge Detect" << std::endl;
}

void FilterHandler::ApplyQuantize(void) {
  std::cout << "Apply has been clicked for Quantize with bins = "
       << quantize_bins_ << std::endl;
}
void FilterHandler::ApplyThreshold(void) {
  std::cout << "Apply Threshold has been clicked with amount ="
            << threshold_amount_ << std::endl;
}
void FilterHandler::ApplySpecial(void) {
  std::cout << "Apply has been clicked for Special" << std::endl;
}

void FilterHandler::InitGlui(const GLUI *const glui,
                             void (*s_gluicallback)(int)) {
  new GLUI_Column(const_cast<GLUI*>(glui), true);
  GLUI_Panel *filterPanel = new GLUI_Panel(const_cast<GLUI*>(glui), "Filters");
  {
    GLUI_Panel *blurPanel = new GLUI_Panel(filterPanel, "Blur");
    {
      GLUI_Spinner * filterBlurAmount = new GLUI_Spinner(blurPanel, "Amount:",
                                                         &blur_amount_);
      filterBlurAmount->set_int_limits(0, 20);

      filterBlurAmount->set_int_val(5);

      new GLUI_Button(blurPanel, "Apply",
                      UICtrl::UI_APPLY_BLUR, s_gluicallback);
    }

    GLUI_Panel *motionBlurPanel = new GLUI_Panel(filterPanel, "MotionBlur");
    {
      GLUI_Spinner*filterMotionBlurAmount = new GLUI_Spinner(motionBlurPanel,
                                                             "Amount:",
                                                             &motion_blur_amount_);
      filterMotionBlurAmount->set_int_limits(0, 100);
      filterMotionBlurAmount->set_int_val(5);

      motion_blur_direction_ = 0;
      GLUI_RadioGroup *dirBlur = new GLUI_RadioGroup(motionBlurPanel,
                                                     &motion_blur_direction_);
      new GLUI_RadioButton(dirBlur, "North/South");
      new GLUI_RadioButton(dirBlur, "East/West");
      new GLUI_RadioButton(dirBlur, "NorthEast/SouthWest");
      new GLUI_RadioButton(dirBlur, "NorthWest/SouthEast");

      new GLUI_Button(motionBlurPanel, "Apply",
                      UICtrl::UI_APPLY_MOTION_BLUR, s_gluicallback);
    }
    GLUI_Panel *sharpenPanel = new GLUI_Panel(filterPanel, "Sharpen");
    {
      GLUI_Spinner * filterSharpAmount = new GLUI_Spinner(sharpenPanel,
                                                          "Amount:",
                                                          &sharpen_amount_);
      filterSharpAmount->set_int_limits(0, 100);

      filterSharpAmount->set_int_val(5);

      new GLUI_Button(sharpenPanel, "Apply",
                      UICtrl::UI_APPLY_SHARP, s_gluicallback);
    }
    GLUI_Panel *edgeDetPanel = new GLUI_Panel(filterPanel, "Edge Detect");

    {
      new GLUI_Button(edgeDetPanel, "Apply",
                      UICtrl::UI_APPLY_EDGE, s_gluicallback);
    }
    GLUI_Panel *thresPanel = new GLUI_Panel(filterPanel, "Threshold");
    {
      GLUI_Spinner * filterThresholdAmount = new GLUI_Spinner(thresPanel,
                                                              "Level:",
                                                              &threshold_amount_);
      filterThresholdAmount->set_float_limits(0, 1);
      filterThresholdAmount->set_float_val(0.5);

      new GLUI_Button(thresPanel, "Apply",
                      UICtrl::UI_APPLY_THRESHOLD, s_gluicallback);
    }

    new GLUI_Column(filterPanel, true);

    GLUI_Panel *saturPanel = new GLUI_Panel(filterPanel, "Saturation");
    {
      GLUI_Spinner * filterSaturationAmount = new GLUI_Spinner(saturPanel,
                                                               "Amount:",
                                                               &saturation_amount_);
      filterSaturationAmount->set_float_limits(-10, 10);
      filterSaturationAmount->set_float_val(1);

      new GLUI_Button(saturPanel, "Apply",
                      UICtrl::UI_APPLY_SATURATE,
                      s_gluicallback);
    }

    GLUI_Panel *channelPanel = new GLUI_Panel(filterPanel, "Channels");
    {
      GLUI_Spinner *filterChannel_red_ = new GLUI_Spinner(channelPanel, "_red_:",
                                                           &channel_color_red_);
      GLUI_Spinner *filterChannel_green_ = new GLUI_Spinner(channelPanel,
                                                             "_green_:",
                                                             &channel_color_green_);
      GLUI_Spinner *filterChannel_blue_ = new GLUI_Spinner(channelPanel,
                                                            "_blue_:",
                                                            &channel_color_blue_);

      filterChannel_red_->set_float_limits(0, 10);
      filterChannel_red_->set_float_val(1);
      filterChannel_green_->set_float_limits(0, 10);
      filterChannel_green_->set_float_val(1);
      filterChannel_blue_->set_float_limits(0, 10);
      filterChannel_blue_->set_float_val(1);

      new GLUI_Button(channelPanel, "Apply",
                      UICtrl::UI_APPLY_CHANNEL,
                      s_gluicallback);
    }

    GLUI_Panel *quantPanel = new GLUI_Panel(filterPanel, "Quantize");
    {
      GLUI_Spinner * filterQuantizeBins = new GLUI_Spinner(quantPanel, "Bins:",
                                                           &quantize_bins_);
      filterQuantizeBins->set_int_limits(2, 256);
      filterQuantizeBins->set_int_val(8);
      filterQuantizeBins->set_speed(0.1);

      new GLUI_Button(quantPanel, "Apply",
                      UICtrl::UI_APPLY_QUANTIZE,
                      s_gluicallback);
    }

    // YOUR SPECIAL FILTER PANEL
    GLUI_Panel *specialFilterPanel = new GLUI_Panel(filterPanel,
                                                    "Special Filter");
    {
      new GLUI_Button(specialFilterPanel,
                      "Apply",
                      UICtrl::UI_APPLY_SPECIAL_FILTER,
                      s_gluicallback);
    }
  }
} /* FilterHandler::InitGlui() */

}  // namespace image_tools
