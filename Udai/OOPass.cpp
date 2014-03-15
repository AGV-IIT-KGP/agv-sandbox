#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/opencv.hpp>

#include "blobdetection.cpp"


class game
{
public:
cv::Mat img;
int *selected;
int **visited;
int *colour;
int *cenx;
int *ceny;
int dice;
int currx;
int curry;
int score;
int shape;
int rows;
int cols;


game()
{ currx = curry = 0; 
score = 0;
}
void processmap(char []);
void start();
void colouredarray();
void inputdice();
void calculateposition();
int finish();
};



int main()
{
	game g;
	int i;
	g.processmap("/home/udai/Documents/circles.jpeg");
	g.start();
	for(i = 1; i<g.shape; ++i)
	{
		std::cout<<"Shape "<<i<<" has centroid ("<<g.cenx[i]<<", "<<g.ceny[i]<<") and colour "<<g.colour[i]<<std::endl;
	}
	int players;
	std::cout<<"Enter number of players in the game:\n";
	std::cin>>players;
	g.selected = new int[g.shape];
	int* finalscore = new int[players];
	for(i=0; i<players; ++i)
	{
		if(i>0)
			std::cout<<"Next player now!\n";
		g.currx = g.curry = g.score = 0;
		for(int j=1; j<g.shape; ++j)
			g.selected[j] = 0;
		while(1)
		{
			g.inputdice();
			g.calculateposition();
			std::cout<<"score is(player "<<i<<") "<<g.score<<std::endl;
			if(g.finish() == 1)
				break;
		}
		finalscore[i] = g.score;
		std::cout<<"The player's final score is "<<finalscore[i]<<std::endl;
	}
	int max = finalscore[0];
	int winner = 0;
	for(i=0; i<players; ++i)
	{
		if(finalscore[i]>max)
		{
			max = finalscore[i];
			winner = i;
		}
	}
	std::cout<<"Winner of the game is Player "<<winner<<" with a score of "<<max<<std::endl;
	return 0;
}

void game::inputdice()
{
std::cout<<"Roll the dice ";
std::cin>>dice;

while((dice<1)||(dice>6))
{
	std::cout<<"Roll the dice";
	std::cin>>dice;
}
}

void game::calculateposition()
{
int i, j, temp;
float dist;
float min = sqrt( pow(rows, 2) + pow(cols, 2) );
if(dice%2==0)
	{
	for(i=1; i<shape; ++i)
		if(colour[i] == 2) //assuming red to be 2
		{
			dist = sqrt( pow(cenx[i] - currx , 2) + pow(ceny[i] - curry, 2) );
			if(dist<min)
				{min = dist; temp =i; }
		}
	currx = cenx[temp];
	curry = ceny[temp];
	score += 2*dice;
	selected[temp] = 1;
	}
else if (dice == 1)
	{
	for(i=1; i<shape; ++i)
		if(colour[i] == 0) //assuming blue to be 0
		{
			dist = sqrt( pow(cenx[i] - currx , 2) + pow(ceny[i] - curry, 2) );
			if(dist<min)
				{min = dist; temp =i; }
		}
	currx = cenx[temp];
	curry = ceny[temp];
	score += 10;
	selected[temp] = 1;
	}
else
	{
	for(i=1; i<shape; ++i)
		if(colour[i] == 1) //assuming green to be 1
		{
			dist = sqrt( pow(cenx[i] - currx , 2) + pow(ceny[i] - curry, 2) );
			if(dist<min)
				{min = dist; temp =i; }
		}
	currx = cenx[temp];
	curry = ceny[temp];
	score += dice;
	selected[temp] = 1;
	}
std::cout<<"X co-ordinate is "<<currx<<", Y co-ordinate is "<<curry<<std::endl;
}

int game::finish()
{
	int flag = 1;
	for(int i =1; i<shape; ++i)
		if(selected[i] == 0)
			{
				flag = 0;
				break;
			}
	return flag;
}

void game::processmap(char a[])
{
	std::cout<<"Hello world\n";
	img = cv::imread(a, CV_LOAD_IMAGE_COLOR);
	cv::namedWindow("mywin", CV_WINDOW_AUTOSIZE);
	cv::imshow("mywin", img);
	cv::waitKey(0);

cv::Mat newimg(img.rows, img.cols, CV_8UC1, cvScalarAll(0));

	int i, j;
	for(i=0; i<img.rows; ++i)
		for(j=0; j<img.cols; ++j)
			{
				if( ( (img.at<cv::Vec3b>(i,j)[0] >=240) && (img.at<cv::Vec3b>(i,j)[1] <=15) && (img.at<cv::Vec3b>(i,j)[2] <= 15) ) ||
					( (img.at<cv::Vec3b>(i,j)[0] <=15) && (img.at<cv::Vec3b>(i,j)[1] >=240) && (img.at<cv::Vec3b>(i,j)[2] <= 15) ) ||
				( (img.at<cv::Vec3b>(i,j)[0] <=15) && (img.at<cv::Vec3b>(i,j)[1] <=15) && (img.at<cv::Vec3b>(i,j)[2] >= 240) ) )

					newimg.at<uchar>(i,j) = 255;
				else 
					newimg.at<uchar>(i,j) = 0;
			} 

	cv::imshow("mywin", newimg);
	cv::waitKey(0);

//int **visited;
visited = new int*[newimg.rows];
for(i=0; i<img.cols; ++i)
visited[i] = new int[newimg.cols];

if(visited)
	std::cout<<"Visited allocated\n";

for(i=0; i<newimg.rows; ++i)
for(j=0; j<newimg.cols; ++j)
	visited[i][j] = -1;

//int shape = 1;
shape = 1;
	for(i=0; i<newimg.rows; ++i)
		for(j=0; j<newimg.cols; ++j)
			if((newimg.at<uchar>(i,j)==255)&&(visited[i][j]==-1))
				{BFS(newimg, visited, shape, i, j);
					shape++;}
for(i=0; i<newimg.rows; ++i)
	for(j=0; j<newimg.cols; ++j)
		if(visited[i][j]!=-1)
			newimg.at<uchar>(i,j) = 255*sin(visited[i][j]);
	std::cout<<"Number of blobs are "<<shape-1<<std::endl;
	cv::waitKey(0);
	cv::imshow("mywin", newimg);

	cv::waitKey(0);
	rows = newimg.rows;
	cols = newimg.cols;
}
//img.at<cv::Vec3b>(i,j)[0] = 
//cv::Mat bin(img.rows, img.cols, CV_8UC1, cvScalarAll(0));

void game::start()
{
	int i, j;
	int *count = new int[shape];
	cenx = new int[shape];
	ceny = new int[shape];
	colour = new int[shape];
	for(i=1; i<shape; ++i)
		{count[i] = 0;
			cenx[i] = 0;
			ceny[i] = 0;
		}
	for(i = 0; i<rows; ++i)
		for(j=0; j<cols; ++j)
			if(visited[i][j] != -1)
			{
				cenx[visited[i][j]] += j;
				ceny[visited[i][j]] += i;
				count[visited[i][j]] ++;
			}
	for(i =1; i<shape; ++i)
		{
			cenx[i] /= count[i];
			ceny[i] /= count[i];
			if((img.at<cv::Vec3b>(ceny[i],cenx[i])[0] >= 230) && (img.at<cv::Vec3b>(ceny[i],cenx[i])[1] <= 25) && (img.at<cv::Vec3b>(ceny[i],cenx[i])[2] <=25 ))
				colour[i] = 0;
			else if ((img.at<cv::Vec3b>(ceny[i],cenx[i])[0] <=25) && (img.at<cv::Vec3b>(ceny[i],cenx[i])[1] >=230) && (img.at<cv::Vec3b>(ceny[i],cenx[i])[2] <= 25))
				colour[i] = 1;
			else if ((img.at<cv::Vec3b>(ceny[i],cenx[i])[0] <=25) && (img.at<cv::Vec3b>(ceny[i],cenx[i])[1] <=25) && (img.at<cv::Vec3b>(ceny[i],cenx[i])[2] >= 230))
				colour[i] = 2;
			else colour[i] = -1;
		}

}