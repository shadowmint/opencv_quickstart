#include <stdlib.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
  Mat img(Mat::zeros(100, 100, CV_8U));

  imshow("window", img);

  waitKey();

  return 0;
}
