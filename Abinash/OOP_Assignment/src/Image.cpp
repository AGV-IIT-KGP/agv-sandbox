#include "Image.h"

cv::Mat Image::image_transform_binary(cv::Mat img0)
{
	cv::Mat bin(img0.rows,img0.cols,CV_8UC1,cvScalarAll(0));
	for (int i=0;i<img0.rows;i++)
	{
		for (int j=0;j<img0.cols;j++)
		{
			if (img0.at<cv::Vec3b>(i,j)[0]==255 && img0.at<cv::Vec3b>(i,j)[1]==0 && img0.at<cv::Vec3b>(i,j)[2]==0) bin.at<uchar>(i,j)=255;
			if (img0.at<cv::Vec3b>(i,j)[1]==255 && img0.at<cv::Vec3b>(i,j)[0]==0 && img0.at<cv::Vec3b>(i,j)[2]==0) bin.at<uchar>(i,j)=255;
			if (img0.at<cv::Vec3b>(i,j)[2]==255 && img0.at<cv::Vec3b>(i,j)[1]==0 && img0.at<cv::Vec3b>(i,j)[0]==0) bin.at<uchar>(i,j)=255;
		}
	}
	return bin;
}

void find_pass_center(cv::Mat bin,Board* bd)
{
	Position* Ctmp = new Position[blob_count];
	int *Cn = new int[blob_count];
	Position tmp;

	for (int m=0;m<blob_count;m++)
	{
		Ctmp[m].x=0;
		Ctmp[m].y=0;
		Cn[m]=0;
	}

	for (int i=0;i<bin.rows;i++)
	{
		for (int j=0;j<bin.cols;j++)
		{
			int k=VISITED[i]][j];
			if (k!=-1)
				{
					Ctmp[k].x+=j;
					Ctmp[k].y+=i;
					Cn[k]++;
				}
		}
	}

	for (int z=0;z<blob_count;z++)
	{
		tmp.x=Ctmp[z].x/Cn[z];
		tmp.y=Ctmp[z].y/Cn[z];
		if (img.at<cv::Vec3b>(tmp.y,tmp.x)[0]==255)
		{
			bd->A.b[bd->A.bn]=tmp;
			(bd->A.bn)++;
		}
		if (img.at<cv::Vec3b>(tmp.y,tmp.x)[1]==255)
		{
			bd->A.g[bd->A.gn]=tmp;
			(bd->A.gn)++;
		}
		if (img.at<cv::Vec3b>(tmp.y,tmp.x)[2]==255)
		{
			bd->A.r[bd->A.rn]=tmp;
			(bd->A.rn)++;
		}
	}
}

void blob_detect(cv::Mat bin,Board *bd)
{
	int height=bin.rows, width=bin.cols;
	VISITED=new int*[height];
	 	
	for(int i=0;i<height;i++)
		VISITED[i]=new int[width];
	 	
	for(i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			A[i][j]=-1;
		}
	}

	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			if(bin.at<uchar>(i,j)==255)
			{
				if(VISITED[i][j]==-1)
				{
					Position tmp;
					tmp.y=i;
					tmp.x=j;
				 	track.push(tmp);
					while(!track.empty())
					{
				 		Position v=track.front();
				 		int k,l;
				 		track.pop();
				 		for(k=v.x-1;k<=v.x+1;k++)
				 		{
							 for(l=v.y-1;l<=v.y+1;l++)
							 {
								if(k<height && l<width && k>=0 && l>=0 && VISITED[k][l]==-1 && bin.at<uchar>(k,l)==255)
								{
									Position kl;
									kl.y=l;
									kl.x=k;
									track.push(kl);
							 		VISITED[k][l]=blob_count;
							 	}
					 		}
						}
						A[v.x][v.y]=blob_count;
					}
					blob_count++;
				 }
			 }
		 }
	}

	Image::find_pass_center(bin,bd);
}

Image::Image(std::string file,Board *bd)
{
	cv::Mat bin;
	img=imread(file);
	blob_count=0;
	bin=Image::image_transform_binary(img);
	cv::namedWindow("OImage",CV_WINDOW_AUTOSIZE);
	cv::imshow("OImage",img);
	cv::waitKey(0);
	cv::namedWindow("Image",CV_WINDOW_AUTOSIZE);
	cv::imshow("Image",bin);
	cv::waitKey(0);
	Image::blob_detect(bin,bd);
}

