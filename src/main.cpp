
#include <cuda_runtime.h> 
#include <cuda.h>
#include "disparity_method.h"
#include <iostream>
#include <numeric>
#include <sys/time.h>
#include <vector>
#include <stdlib.h>
#include <typeinfo>
#include <opencv2/opencv.hpp>

#include <numeric>
#include <stdlib.h>
#include <ctime>
#include <sys/types.h>
#include <stdint.h>
#include <linux/limits.h>
#include <dirent.h>
#include <iostream>
#include <fstream>
#include <string>
const cv::String keys =
    "{@image_left    | ../inputs/left.png      | left image     }"
    "{@image_right   | ../inputs/right.png     | right image    }"
    "{@output_path   | ../outputs/disp.png     | path to output }"
    ;

int main (int argc, char** argv) {
  cv::Mat left, rght;
  cv::CommandLineParser parser(argc, argv, keys);
  cv::String fname_s = parser.get<cv::String>("@output_path");
  const char* fname = fname_s.c_str();
  left = cv::imread(parser.get<cv::String>("@image_left"),cv::IMREAD_GRAYSCALE);
	if(!left.data) {
			std::cerr << "Couldn't read the file " << std::endl;
			return EXIT_FAILURE;
		}
  rght = cv::imread(parser.get<cv::String>("@image_right"),cv::IMREAD_GRAYSCALE);
	if(!rght.data) {
			std::cerr << "Couldn't read the file " << std::endl;
			return EXIT_FAILURE;
		}
  float *elapsed_time_ms ;
  init_disparity_method(10, 200);
  cv::Mat disparity_im = compute_disparity_method(left, rght, elapsed_time_ms, fname);

  cv::imwrite(fname, disparity_im);
  
  finish_disparity_method();
  return 0;
}
