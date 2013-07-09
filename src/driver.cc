#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <tchar.h>
#include <fstream>
#include "functions.h"
#include "classes.h"



int main(int argc, TCHAR * args[]){

	if(!checkArgs(argc,args)){
		return -1;
	}

	int duration = tchar2int(args[1]);
	int res_x = tchar2int(args[2]);
	int res_y = tchar2int(args[3]);
	int patch_height = tchar2int(args[4]);
	int patch_width = tchar2int(args[5]);
	
	while(1){
		std::deque<Image> images = record(duration, res_x, res_y);
	
		if(!images.empty()){
			analyse(images, patch_height, patch_width);
		}else{
			break;
		}
	}
	
	return 0;

}