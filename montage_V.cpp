#include <iostream>
#include <fstream>
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <math.h>
#include <sstream>
#include <string.h>
using namespace std;
using namespace cv;
float variance(float sum , float mean)
{
	float var;
	var = ((sum)/9)-pow(mean,2);
	
	return var;
}
Mat montage(Mat img1, Mat img2)
{
	int i,j,k,x,y,p,q,c=0,d=0;
	float sumb1,sumb2,sumr1,sumr2,sumg1,sumg2,sumbx1,sumbx2,sumrx1,sumrx2,sumgx1,sumgx2,sum1,sum2,sumx1,sumx2,mean1,mean2;
	// read the images
	Mat img3(852, 1136, CV_8UC3, Scalar(0,0,0));
	
        
        
    
	// create a 3*3 kernel
	float kernel[3][3] = {{1,1,1},{1,1,1},{1,1,1}};
	
    

	// finding mean and intensity of every pixel;
	for(i=1;i<img1.rows-1;i++)
	{

		for(j=1;j<img1.cols-1;j++)
		{


			sumb1=0;
			sumr1=0;
			sumg1=0;
			sumb2=0;
			sumr2=0;
			sumg2=0;
			sumbx1=0;
			sumrx1=0;
			sumgx1=0;
			sumbx2=0;
			sumrx2=0;
			sumgx2=0;

			for(x=-1;x<2;x++)
			{

				for(y=-1;y<2;y++)
				{
					sumb1 += (float)(img1.at<Vec3b>(i + x, j + y))[0] ;
                    sumg1 += (float)(img1.at<Vec3b>(i + x, j + y))[1] ;
                    sumr1 += (float)(img1.at<Vec3b>(i + x, j + y))[2] ;
                    sumb2 += (float)(img2.at<Vec3b>(i + x, j + y))[0] ;
                    sumg2 += (float)(img2.at<Vec3b>(i + x, j + y))[1] ;
                    sumr2 += (float)(img2.at<Vec3b>(i + x, j + y))[2] ;
                    sumbx1 += pow((float)(img1.at<Vec3b>(i + x, j + y))[0],2);
                    sumgx1 += pow((float)(img1.at<Vec3b>(i + x, j + y))[1],2);
                    sumrx1 += pow((float)(img1.at<Vec3b>(i + x, j + y))[2],2);
                    sumbx2 += pow((float)(img2.at<Vec3b>(i + x, j + y))[0],2);
                    sumgx2 += pow((float)(img2.at<Vec3b>(i + x, j + y))[1],2);
                    sumrx2 += pow((float)(img2.at<Vec3b>(i + x, j + y))[2],2);
                    
                }
			}
            sum1 = sumb1+sumr1+sumg1;
            sum2 = sumb2+sumr2+sumg2;
            sumx1= sumbx1+sumgx1+sumrx1;
            sumx2= sumbx2+sumgx2+sumrx2;
            mean1 = sum1/9;
            mean2 = sum2/9;
            
            //comparing variance
            if(variance(sumx1, mean1)>=variance(sumx2, mean2))
            {
              

               	  
               	  	

               	  	 img3.at<Vec3b>(i,j) =  (img1.at<Vec3b>(i,j));
               	  	 
           
               d++;
            }
            else
            {

            	           	
               	  	 img3.at<Vec3b>(i,j) =  img2.at<Vec3b>(i,j);
                
            	c++;
            }
        }
	}
	cout << d << endl << c << endl;
	return img3;
}

int main()
{
	int a;
	Mat image1,image3;
	image1 = imread("1.jpg");
	for(a=2;a<=20;a++)
	{
      Mat image2;
      stringstream ss;
      ss<<a;
      string path = ss.str() +".jpg";
      image2=imread(path);
      image1=montage(image1,image2);
  	}
  	imwrite("result1.jpg",image1);
	return (0) ;
}
