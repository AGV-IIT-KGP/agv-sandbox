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
     Image(std::string ,Board*);

   protected:
   private:
   	cv::Mat img;
   	int blob_count;
	int **VISITED;
   	queue<position> track;
};

#endif // IMAGE_H

