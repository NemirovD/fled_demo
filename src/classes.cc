#include "classes.h"

_Image::_Image(){
	this->image_ = cv::Mat();
	this->time_ = NULL;
}

_Image::_Image(cv::Mat mat,double time){
	this->image_ = mat;
	this->time_ = time;
}

_Image::~_Image(){
	this->image_.release();
	this->time_ = NULL;
}

cv::Mat _Image::image(){
	return (this->image_);
}

double _Image::time(){
	return (this->time_);
}

void _Image::time(double time){
	this->time_ = time;
}

_Data::_Data(){
	this->time_ = NULL;
	this->value_ = NULL;
}

_Data::_Data(double time, double value){
	this->time_ = time;
	this->value_ = value;
}

_Data::~_Data(){
	this->time_ = NULL;
	this->value_ = NULL;
}

double _Data::time(){
	return this->time_;
}

double _Data::value(){
	return this->value_;
}

void _Data::time(double time){
	this->time_ = time;
}

void _Data::value(double value){
	this->value_ = value;
}
std::ostream& operator<<(std::ostream& os, const _Data& obj){
	os << obj.time_;
	os << " ";
	os  << obj.value_;
	return os;
}