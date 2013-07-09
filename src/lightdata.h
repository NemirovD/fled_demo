#ifndef FLED_LIGHT_DATA_H
#define FLED_LIGHT_DATA_H

#include <iostream>
#include <cstdio>
#include <opencv2/opencv.hpp>
#include "classes.h"

void morse_letters_init();

std::deque<std::string> analyseData(std::deque<std::deque<Data>> data);

void seeLightIDs(std::deque<std::string>);

#endif