
class PlotCurve
{
private:
Node points[5];
int height,width;
cv::Mat image,formedImage;

public:
PlotCurve(cv::Mat image);
void findPoints();
int findY(int x, Node p);
void drawCurve();
}

