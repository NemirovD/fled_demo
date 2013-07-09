#ifndef FLED_FUNCTIONS_H
#define FLED_FUNCTIONS_H
#include <ctime>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <tchar.h>
#include <strsafe.h>
#include <sstream>
#include "classes.h"
#include "lightdata.h"

bool checkArgs(int argc, TCHAR * args[]);

std::string makeString(TCHAR * str);

int tchar2int(TCHAR * string);

std::string float2string(float value);

std::deque<Image> record(int duration, int resolution_x, int resolution_y);

cv::Mat integrateImage(cv::Mat mat, int height, int width);

std::deque<IntImage> integrate(std::deque<Image>,int,int);

cv::Mat getVariance(std::deque<IntImage> images, cv::Mat& retMeans);

double findLargestElement(cv::Mat image);

std::deque<cv::Rect> getRectangles(std::deque<IntImage>, double, double,cv::Mat&);

std::deque<std::deque<Data>> getLightData(std::deque<IntImage>);

void analyse(std::deque<IntImage> images, double height, double width);

void showRects(cv::Mat img, std::deque<cv::Rect> rects, std::deque<std::string>);

void seeData(std::deque<std::deque<Data>> data);

void showDeque(std::deque<Image> images);

#endif