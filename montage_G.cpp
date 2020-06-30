#include <iostream>
#include <fstream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <math.h>
#include <sstream>
#include <string.h>
using namespace std;
using namespace cv;
Mat montage(Mat img1, Mat img2)
{
  Mat img1_gray;
  cvtColor( img1, img1_gray, CV_BGR2GRAY );
  Mat img2_gray;
	cvtColor( img2, img2_gray, CV_BGR2GRAY );
  float sum1,sum2,sumx1,sumx2;
  float mean1,mean2;
	
	Mat img3(852, 1136, CV_8UC3, Scalar(0,0,0));
    	int gx1, gy1, gx2,gy2,g1,g2;
    	gx1 = gy1 = g1 = 0;
    	gx2= gy2 = g2 =0;
    	int i, j, x, y;
    	int kernel1[5][5]=
    	{{1,  2, 0,  -2, -1},
    	{4,  8, 0,  -8, -4},
    	{6, 12, 0, -12, -6},
    	{4,  8, 0,  -8, -4},
    	{1,  2, 0,  -2, -1}};
    	int kernel2[3][3]=
	{{1, 2, 1},
 	{0, 0, 0},
       	{-1, -2, -1}};

	for(i = 2; i < img1.rows-2; i++){
        for(j = 2; j < img1.cols-2; j++){
            gx1 = gy1 = g1 = 0;
            gx2= gy2= g2 =0;
            
    	for(x = -2; x < 3; x++){
        for(y = -2; y < 3; y++){
                    gx1 += img1_gray.at<uchar>(i + x, j + y) * kernel1[2+x][y+2];
                    gy1 += img1_gray.at<uchar>(i + x, j + y) * kernel1[2+y][x+2];
                    gx2 += img2_gray.at<uchar>(i + x, j + y) * kernel1[2+x][y+2];
                    gy2 += img2_gray.at<uchar>(i + x, j + y) * kernel1[2+y][x+2];
                }
            }
            g1 = sqrt(gx1*gx1 + gy1*gy1);
            g2 = sqrt(gx2*gx2 + gy2*gy2);
            if(g1>=g2)
            {
                img3.at<Vec3b>(i,j) =  img1.at<Vec3b>(i,j);
               	  	 
            }
               
            else
            {
           	
                img3.at<Vec3b>(i,j) =  img2.at<Vec3b>(i,j);
             
            
            }
        }
	}
	return img3;
}

int main()
{
	int a;
	Mat image1,image3,result;
	image1 = imread("1.jpg",1);
	if (image1.empty())
		cout<<"image not found";
	for(a=2;a<=2;a++)
	{
      Mat image2;
      stringstream ss;
      ss<<a;
      string path = ss.str() +".bmp";
      image2=imread(path,1);
     	
      image1=montage(image1,image2);
  	}
    imwrite("output.jpg",image1);
    waitKey(0);
	return (0) ;
}
