#include <opencv/cv.h>
#include <opencv/highgui.h>
class SeperateLanes
{
private :
int distance;
cv::Mat image,formedImage;

public:
SeperateLanes();
void findDistance();
void formImage();
void showImage(cv::Mat img);
};



