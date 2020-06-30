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
float calcBlurriness( const Mat &src )
{
	
  Mat Gx, Gy;
  Sobel( src, Gx, CV_32F, 1, 0 );
  Sobel( src, Gy, CV_32F, 0, 1 );
  double normGx = norm( Gx );
  double normGy = norm( Gy );
  double sumSq = normGx * normGx + normGy * normGy;
  float x= 1. / ( sumSq / src.size().area() + 1e-6 );
  return x;
}
Mat montage(Mat image1, Mat image2)
{
  Mat image(480, 480, CV_8UC3, Scalar(0,0,0));
  // Resize the image and Inter change the rows and coloumns
  resize(image,image,Size(480,480));
	
	
  float B1,B2;
  int i,j;
  int count = 1;

  for(i=0;i<image.rows;i+=(image.rows/10))// enter how much increment needed in rows
    
    {
      for(j=0;j<image.cols;j+=(image.cols/8))// enter how much increment needed in coloumns
	
	{
	 // X here is for satisfying the conditions for rows
     // Y here is for satisfying the condiitons for coloumns	
	 int x=min((image.rows/10),image.rows-i),y=min((image.cols/8),image.cols-j);
	 
	  // RECT( i, j, Coloumn length of rectangle, Row length of Rectangle )
	  Rect rec1(j,i,(image.cols/8),(image.rows/10));
	  Rect rec2(j,i,(image.cols/8),(image.rows/10));
	  Rect rect(j,i,(image.cols/8),(image.rows/10));
	  
	  Mat roi1 = image1(rec1);
	  Mat roi2 = image2(rec2);
	  if(calcBlurriness(roi1)>calcBlurriness(roi2))
	    {	
	      roi2.copyTo(image(rect));
	    }
	  else
	    {
	      roi1.copyTo(image(rect));
	    }	
	}
    }
	
	return image;
}

int main()
{
	int a;
	Mat img1,img3,result;
	img1 = imread("1.jpg",1);
	for(a=2;a<=4;a++)
	{
	  cout<<a<<endl;	
      Mat img2;
      stringstream ss;
      ss<<a;
      string path = ss.str() +".jpg";
      img2=imread(path,1);
     	
      img1=montage(img1,img2);
  	}
    imwrite("output.jpg",img1);
    waitKey(0);
	return (0) ;
}
