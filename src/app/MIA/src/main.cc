/*******************************************************************************
 * Name              : main.cc
 * Project           : MIA
 * Module            : main
 * Description       : Entry point for MIA application
 * Copyright         : 2016 CSCI3081W TAs. All rights reserved.
 * Creation Date     : 1/15/15
 * Original Author   : Seth Johnson
 *
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "include/mia_app.h"
#include <iostream>
#include "lib/libimgtools/src/include/color_data.h"

/*******************************************************************************
 * Non-Member Functions
 ******************************************************************************/
/* Definitions for the command line arguments */
const char* kHelp = "-h";
const char* kSharpen = "-sharpen";
const char* kEdge = "-edge";
const char* kThreshold = "-threshold";
const char* kQuantize = "-quantize";
const char* kBlur = "-blur";
const char* kSaturate = "-saturate";
const char* kChannel = "-channel";
const char* kCompare = "-compare";
const std::string kMessage = "usage: MIA"
    " [-h] [-edge] [-sharpen <val>] [-threshold <val>] [-quantize <val>]\n"
    "      [-blur <val>] [-saturate <val>] [-channel <red> <green> <blue>]\n"
    "      [-compare <file1> <file2>]\n"
    "\t -h\t\t\t\t\tDisplays this message\n"
    "\t -sharpen <float>\t\t\tSharpen image by value passed in\n"
    "\t -edge\t\t\t\t\tDisplays on the edges of the image\n"
    "\t -threshold <float>\t\t\tRounds color channels to 0/1 if below/above value\n"
    "\t -quantize <int>\t\t\tReduces possible color values to value passed in\n"
    "\t -blur <float>\t\t\t\tBlur image by value passed in\n"
    "\t -saturate <float>\t\t\tSaturate image by value passed in\n"
    "\t -channel <float> <float> <float>\tMultiply color channel by value\n"
    "\t -compare <file1> <file2>\t\tCheck to see if two images are equivalent";

int main(int argc, char** argv) {
    if (argc == 1) {
      image_tools::MIAApp *app = new image_tools::MIAApp(
          400,
          400,
          "resources/marker.png");
      app->Init(argc, argv, 50, 50,
                image_tools::ColorData(1, 1, static_cast<float>(0.95)));
      app->RunMainLoop();
      delete app;
    } else {
        for (int i = 1; i < argc; i++) {
            try {
                /* Check for possible commands */
                if (strcmp(argv[i], kHelp) == 0) {
                    std::cout << kMessage << std::endl;

                } else if (strcmp(argv[i], kSharpen) == 0) {
                    float sharpen = std::stof(argv[++i]);
                    std::cout << "Sharpen by value " << sharpen << std::endl;

                } else if (strcmp(argv[i], kEdge) == 0) {
                    std::cout << "Edge detect" << std::endl;

                } else if (strcmp(argv[i], kThreshold) == 0) {
                    float threshold = std::stof(argv[++i]);
                    std::cout << "Threshold by value " << threshold << std::endl;

                } else if (strcmp(argv[i], kQuantize) == 0) {
                    float quantize = std::stof(argv[++i]);
                    std::cout << "Quantize by value " << quantize << std::endl;

                } else if (strcmp(argv[i], kBlur) == 0) {
                    float blur = std::stof(argv[++i]);
                    std::cout << "Blur by value " << blur << std::endl;

                } else if (strcmp(argv[i], kSaturate) == 0) {
                    float saturate = std::stof(argv[++i]);
                    std::cout << "Saturate by value " << saturate << std::endl;

                } else if (strcmp(argv[i], kChannel) == 0) {
                    float red = std::stof(argv[++i]);
                    float green = std::stof(argv[++i]);
                    float blue = std::stof(argv[++i]);
                    std::cout << "Color channels by values " << red << ", " <<
                        green << ", " << blue << std::endl;

                } else if (strcmp(argv[i], kCompare) == 0) {
                    char* file1 = argv[++i];
                    char* file2 = argv[++i];
                    std::cout << "Comparing files: " << file1 <<
                        " and " <<file2 << std::endl;
                }
                else {
                    std::cout << kMessage << std::endl;
                    return 1;
                }
            } catch (...) {
                std::cout << kMessage << std::endl;
                return 1;
            }
        }
    }
        return 0;
} /* main() */
