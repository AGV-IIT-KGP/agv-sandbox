#ifndef IMAGE_H
#define IMAGE_H
#include <cstdio>
#include <opencv2/highgui/highgui.hpp>
#include <cmath>
#include <cv.h>
#include <cxcore.h>
#include <queue>
#include <cstdlib>
#include <string>
#include "Position.h"
#include "Board.h"

class Image
{
   public:
     Image(std::string ,Board*);
     void blob_detect(cv::Mat,Board*);

   protected:
   private:
   	cv::Mat img;
   	int blob_count;
	int **VISITED;

   	void find_pass_center(cv::Mat,Board*);
   	cv::Mat image_transform_binary(cv::Mat);
};

#endif // IMAGE_H

