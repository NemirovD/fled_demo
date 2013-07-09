#ifndef FLED_CLASSES_H
#define FLED_CLASSES_H

#include <iostream>
#include <cstdlib>
#include <opencv2/opencv.hpp>

typedef class _Image{
public:
	//constructors and deconstructor
	_Image();
	_Image(cv::Mat, double);
	~_Image();
	//mutators
	cv::Mat image();
	double time();
	void time(double);
private:
	cv::Mat image_;
	double time_;
} Image, IntImage;

typedef class _Data{
public:
	//constructors and deconstructors
	_Data();
	_Data(double,double);
	~_Data();
	//accessors and mutators
	double time();
	double value();
	void time(double);
	void value(double);
	friend std::ostream& operator<<(std::ostream& os, const _Data& obj);
private:
	double time_;
	double value_;
} Data;


#endif