#ifndef IMAGE_H
#define IMAGE_H
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <queue>
#include <cstdlib>
#include <string>
#include "Position.h"
#include "Board.h"

class Image
{
   public:
     Image(cv::Mat,Board*);

   protected:
   private:
   	cv::Mat img;
   	int blob_count;
	int **VISITED;
   	queue<position> track;
};

#endif // IMAGE_H

