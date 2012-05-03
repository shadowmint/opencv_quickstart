#include <stdlib.h>
#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
  Mat img;

  img = imread("sample.png", CV_LOAD_IMAGE_COLOR);
  if (!img.data) {
    cout << "Unable to open image" << std::endl;
  }

  return 0;
}
