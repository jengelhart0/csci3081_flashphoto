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
#include <iostream>
#include "include/mia_app.h"
#include "lib/libimgtools/src/include/color_data.h"
#include "lib/libimgtools/src/include/pixel_buffer.h"
#include "include/mia_io_manager.h"
#include "include/mia_filter_manager.h"

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
const char kMessage[]  = "usage: MIA"
" [-h] [-edge] [-sharpen <val>] [-threshold <val>] [-quantize <val>]\n"
"      [-blur <val>] [-saturate <val>] [-channel <red> <green> <blue>]\n"
"      [-compare <file1> <file2>]\n"
"\t -h\t\t\t\t\tDisplay this message\n"
"\t -sharpen <float>\t\t\tSharpen image by value passed in\n"
"\t -edge\t\t\t\t\tDisplay the edges of the image\n"
"\t -threshold <float>\t\t\tRound color channels to 0/1 if below/above value\n"
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
        image_tools::MIAIOManager io_manager;
        image_tools::MIAFilterManager filter_manager;
        std::string inFile = argv[1];
        std::string outFile = argv[argc-1];

        if (!(io_manager.is_valid_image_file(inFile))) {
            std::cout << kMessage << std::endl;
            return 1;
        }
        io_manager.set_image_file(inFile);
        image_tools::PixelBuffer* image = nullptr;
        image = io_manager.LoadImageToCanvas();

        for (int i = 2; i < argc - 1; i++) {
            try {
                /* Check for possible commands */
                if (strcmp(argv[i], kHelp) == 0) {
                    std::cout << kMessage << std::endl;

                } else if (strcmp(argv[i], kSharpen) == 0) {
                    float sharpen = std::stof(argv[++i]);
                    filter_manager.sharpen_amount(sharpen);
                    filter_manager.ApplySharpen(image);

                } else if (strcmp(argv[i], kEdge) == 0) {
                    filter_manager.ApplyEdgeDetect(image);

                } else if (strcmp(argv[i], kThreshold) == 0) {
                    float threshold = std::stof(argv[++i]);
                    filter_manager.threshold_amount(threshold);
                    filter_manager.ApplyThreshold(image);

                } else if (strcmp(argv[i], kQuantize) == 0) {
                    float quantize = std::stof(argv[++i]);
                    filter_manager.quantize_bins(quantize);
                    filter_manager.ApplyQuantize(image);

                } else if (strcmp(argv[i], kBlur) == 0) {
                    float blur = std::stof(argv[++i]);
                    filter_manager.blur_amount(blur);
                    filter_manager.ApplyBlur(image);

                } else if (strcmp(argv[i], kSaturate) == 0) {
                    float saturate = std::stof(argv[++i]);
                    filter_manager.saturation_amount(saturate);
                    filter_manager.ApplySaturate(image);

                } else if (strcmp(argv[i], kChannel) == 0) {
                    float red = std::stof(argv[++i]);
                    float green = std::stof(argv[++i]);
                    float blue = std::stof(argv[++i]);
                    filter_manager.channel_color_red(red);
                    filter_manager.channel_color_green(green);
                    filter_manager.channel_color_blue(blue);
                    filter_manager.ApplyChannel(image);

                } else if (strcmp(argv[i], kCompare) == 0) {
                    if (strcmp(argv[++i], outFile.c_str())) {
                        std::cout << kMessage << std::endl;
                        return 1;
                    }
                    image_tools::PixelBuffer* comparison = nullptr;
                    io_manager.set_image_file(outFile);
                    comparison = io_manager.LoadImageToCanvas();
                    if (*image == *comparison) {
                        std::cout << "1" << std::endl;
                    } else {
                        std::cout << "0" << std::endl;
                    }
                } else {
                    std::cout << kMessage << std::endl;
                    return 1;
                }
            } catch (...) {
                std::cout << kMessage << std::endl;
                return 1;
            }
        }
        io_manager.set_image_file(outFile);
        io_manager.SaveCanvasToFile(*image);
    }
    return 0;
} /* main() */
