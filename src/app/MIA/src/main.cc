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
const std::string kMessage = "usage: MIA"
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

/**
 * @brief Checks if input string is number
 */
float convertStringToFloat(const char* string) {
    std::string input = string;
    std::string chars = "0123456789.-";
    if (input.find_first_not_of(chars) != std::string::npos) {
        throw std::invalid_argument("The filter you used requires a float");
    }
    return (std::stof(string));
}


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
        std::vector<std::string> inFiles;
        std::vector<std::string> outFiles;

        int in_first = inFile.find("#");
        int out_first = outFile.find("#");
        int in_last = inFile.rfind("#");
        int out_last = outFile.rfind("#");
        /*
         * Detects "###.png" pattern and constructs list of possible
         * files
         */
        if ((in_last - in_first == 2) && (out_last - out_first ==2 )) {
            std::string temp1;
            std::string temp2;
            std::string prefix;
            for (int i = 0; i < 1000; i++) {
                if (i < 10)
                    prefix = "00";
                else if (i < 100)
                    prefix = "0";
                else
                    prefix = "";
                temp1 = inFile;
                temp2 = outFile;
                inFiles.push_back(temp1.replace(in_first, 3,
                                                prefix + std::to_string(i)));
                outFiles.push_back(temp2.replace(out_first, 3,
                                                 prefix + std::to_string(i)));
            }
        }
        /* Single file case */
        else if (io_manager.is_valid_image_file(inFile)) {
            inFiles.push_back(inFile);
            outFiles.push_back(outFile);
        }
        /*
         * Invalid filenames. One of two cases:
         * 1) Uses "#" but not in form "###.png"
         * 2) Doesn't use "#" and file does not exist
         */
        else {
            std::cout << kMessage << std::endl;
            return 1;
        }
        std::string file;
        std::string out;
        bool is_comparison = false;
        for (int j = 0; j < inFiles.size(); j++) {
            file = inFiles[j];
            out = outFiles[j];
            /*
             * Ensure that file exists. Only applicable if "###.png" is used
             * because file "000.png" and "100.png - 999.png" don't exist
             */
            if (!(io_manager.is_valid_image_file(file)))
                continue;
            io_manager.set_image_file(file);
            image_tools::PixelBuffer* image = nullptr;
            image = io_manager.LoadImageToCanvas();

            for (int i = 2; i < argc - 1; i++) {
                /*
                 * Check for possible commands. If only C++ supported
                 * switches on a string...
                 */
                try {
                    if (strcmp(argv[i], kHelp) == 0) {
                        std::cout << kMessage << std::endl;

                    } else if (strcmp(argv[i], kSharpen) == 0) {
                        float sharpen = convertStringToFloat(argv[++i]);
                        filter_manager.sharpen_amount(sharpen);
                        filter_manager.ApplySharpen(image);

                    } else if (strcmp(argv[i], kEdge) == 0) {
                        filter_manager.ApplyEdgeDetect(image);

                    } else if (strcmp(argv[i], kThreshold) == 0) {
                        float threshold = convertStringToFloat(argv[++i]);
                        filter_manager.threshold_amount(threshold);
                        filter_manager.ApplyThreshold(image);

                    } else if (strcmp(argv[i], kQuantize) == 0) {
                        float quantize = convertStringToFloat(argv[++i]);
                        filter_manager.quantize_bins(quantize);
                        filter_manager.ApplyQuantize(image);

                    } else if (strcmp(argv[i], kBlur) == 0) {
                        float blur = convertStringToFloat(argv[++i]);
                        filter_manager.blur_amount(blur);
                        filter_manager.ApplyBlur(image);

                    } else if (strcmp(argv[i], kSaturate) == 0) {
                        float saturate = convertStringToFloat(argv[++i]);
                        filter_manager.saturation_amount(saturate);
                        filter_manager.ApplySaturate(image);

                    } else if (strcmp(argv[i], kChannel) == 0) {
                        float red = convertStringToFloat(argv[++i]);
                        float green = convertStringToFloat(argv[++i]);
                        float blue = convertStringToFloat(argv[++i]);
                        filter_manager.channel_color_red(red);
                        filter_manager.channel_color_green(green);
                        filter_manager.channel_color_blue(blue);
                        filter_manager.ApplyChannel(image);

                    } else if (strcmp(argv[i], kCompare) == 0) {
                        if (++i != argc - 1) {
                            std::cout << i << " " << argc << std::endl;
                            std::cout << kMessage << std::endl;
                            return 1;
                        }
                        is_comparison = true;
                        image_tools::PixelBuffer* comparison = nullptr;
                        io_manager.set_image_file(out);
                        comparison = io_manager.LoadImageToCanvas();
                        if (*image == *comparison)
                            std::cout << "1" << std::endl;
                        else
                            std::cout << "0" << std::endl;
                    }
                    /* Unknown, misspelled option */
                    else {
                        std::cout << kMessage << std::endl;
                        return 1;
                    }
                /*
                 * Reaches this when parameters are malformed
                 * e.g. -saturate one
                 */
                } catch (...) {
                    std::cout << kMessage << std::endl;
                    return 1;
                }
            }
            if (!(is_comparison)) {
                io_manager.set_image_file(out);
                io_manager.SaveCanvasToFile(*image);
            }
        }
    }
        return 0;
} /* main() */
