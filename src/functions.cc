#include "functions.h"

//need to edit
bool checkArgs(int argc, TCHAR * args[]){
	if(argc != 7){
		std::cout << "Usage: fled <duration> <resolution_x> <resolution_y>";
		std::cout << " <patch_height> <patch_width> <channel>" << std::endl;
		std::cout << std::endl;
		return false;
	}else{
		return true;
	}
}

std::string makeString(TCHAR * str){
	
	std::string toReturn;
	#ifdef _UNICODE
	toReturn = narrow(std::wstring(str));
	#else
	toReturn = std::string(str);
	#endif
	
	return toReturn;
}

int tchar2int(TCHAR * string){
	int value;
	sscanf(makeString(string).c_str(), "%d", &value);
	return value;
}

std::string float2string(float value){
	std::string out;
	std::stringstream sstrm;
	
	sstrm << value;
	sstrm >> out;
	
	return out;
}


std::deque<Image> record(int duration, int res_x, int res_y){

	bool resize = true;
	cv::Size img_size(res_y,res_x);
	if(res_x==-1 || res_y==-1){
		resize = false;
	}
	
	cv::Mat frame, temp_frame;
	cv::VideoCapture cap(0);
	std::string window_name("Webcam");
	
	cv::namedWindow(window_name);
	
	//Storage and temp variables
	std::deque<Image> images;
	Image temp;
	
	bool recording = false;
	clock_t start, beginning = clock();
	char wait_key_value = -1; // -1 is the value of no key pressed
	while(wait_key_value!=27){//while the escape key has not been pressed
		cap >> frame;
		
		if(recording){
			if(resize){
				cv::resize(frame, temp_frame, img_size);
			}else{
				temp_frame = frame;
			}
			
			cv::cvtColor(temp_frame,temp_frame, CV_BGR2GRAY);
			temp = Image(temp_frame.clone(), (double)(clock()-start)/CLOCKS_PER_SEC);
			images.push_back(temp);
			if(((float)(clock()-start)/CLOCKS_PER_SEC) >= duration){
				recording = false;
				break;
			}
			cv::putText(frame, 
						"recording", 
						cv::Point(0,frame.rows-10),
						cv::FONT_HERSHEY_SIMPLEX,1, 
						cv::Scalar(0,0,255));
			
		}
		
		cv::putText(frame,
					float2string(((float)(clock()-beginning)/CLOCKS_PER_SEC)), 
					cv::Point(frame.cols-100, frame.rows-10),
					cv::FONT_HERSHEY_SIMPLEX,1,cv::Scalar(255,0,0));
					
		cv::imshow(window_name, frame);
		wait_key_value = cv::waitKey(1);
		if(wait_key_value == 13){
			recording = true;
			start = clock();
		}
		
	}
	
	cv::destroyWindow(window_name);
	frame.release();
	cap.release();
	return images;
}

cv::Mat integrateImage(cv::Mat mat, int height, int width){
	cv::Size patchSize(height,width);
	cv::Point anchor(0,0);
	cv::Mat kernel = cv::Mat::ones(height, width, CV_32F)/(height*width);
	
	cv::filter2D(mat, mat, -1, kernel, anchor, 0, cv::BORDER_CONSTANT);
	
	return mat;
}

std::deque<IntImage> integrate(std::deque<Image> images,int height ,int width){
	cv::Mat int_temp;
	IntImage int_img_temp;
	std::deque<IntImage> int_images;
	for(UINT i = 0; i < images.size(); ++i){
		int_temp = integrateImage(images[i].image().clone(),height,width);
		int_img_temp = IntImage(int_temp, images[i].time());
		int_images.push_back(int_img_temp);
	}
	
	return int_images;
}

cv::Mat getVariance(std::deque<IntImage> images, cv::Mat& retMeans){
	
	cv::Mat means = cv::Mat::zeros(images[0].image().size(), CV_64F);
	cv::Mat variance = cv::Mat::zeros(images[0].image().size(), CV_64F);
	
	for(UINT k = 0; k < images.size();++k){
		for(UINT i = 0; i < images[k].image().rows; ++i){
			for(UINT j = 0; j < images[k].image().cols; ++j){
				means.at<double>(i,j) += static_cast<double>(images[k].image().at<UCHAR>(i,j));
			}
		}
	}means/=images.size();
	
	for(UINT k = 0; k < images.size();++k){
		for(UINT i = 0; i < images[k].image().rows; ++i){
			for(UINT j = 0; j < images[k].image().cols; ++j){
				double x = static_cast<double>(images[k].image().at<UCHAR>(i,j));
				double mean = means.at<double>(i,j);
				variance.at<double>(i,j) += (x-mean)*(x-mean);
			}
		}
	}variance/=images.size();
	
	retMeans = means.clone();
	return variance;
}

double findLargestElement(cv::Mat image){
	double max= 0;
	
	for(UINT i = 0; i < image.rows; ++i){
		double * ptr = image.ptr<double>(i);
		for(UINT j =  0; j < image.cols; ++j){
			if(*ptr > max){
				max = *ptr;
			}
			++ptr;
		}
	
	}
	return max;
}

std::deque<cv::Rect> getRectangles(std::deque<IntImage> images, double height, double width,cv::Mat& means){
	cv::Mat variance = getVariance(images, means);
	double max = findLargestElement(variance);
	int no_collision;
	std::deque<cv::Rect> rects;
	
	for(UINT i = 0; i < variance.rows; ++i){
		
		double *ptr = variance.ptr<double>(i);
		for(UINT j = 0; j < variance.cols; ++j){

			if(*ptr > 0.8 * max){
			
				no_collision = 1;
				cv::Rect rec(j,i,height, width);
				for(UINT k = 0; k < rects.size(); ++k){
				
					if(rec.x+rec.width < rects[k].x){
						;
					}else if(rects[k].x+rects[k].width < rec.x){
						;
					}else if(rec.y+rec.height < rects[k].y){
						;
					}else if(rects[k].y+rects[k].height < rec.y){
						;
					}else{
						no_collision = 0;
						break;
					}
				}
				if(no_collision){
					rects.push_back(rec);
				}
			}
			++ptr;
		}
	}
	return rects;
}


std::deque<std::deque<Data>> getLightData(std::deque<IntImage> images, std::deque<cv::Rect> rects, cv::Mat means){

	std::deque<std::deque<Data>> to_return;
	for(UINT i = 0; i < rects.size(); ++i){
		std::deque<Data> info;
		for(UINT j = 0; j < images.size(); ++j){
			double t_time = images[j].time();
			double t_value = (double)images[j].image().at<UCHAR>(rects[i].y,rects[i].x);
			
			t_value/= means.at<double>(rects[i].y,rects[i].x);
			
			Data t_data(t_time,t_value);
			info.push_back(t_data);
		}
		to_return.push_back(info);
	}
	return to_return;
}

void analyse(std::deque<Image> images, double height, double width){
	
	cv::Mat means;
	
	showDeque(images);
	std::deque<IntImage> int_images = integrate(images,height,width);
	std::deque<cv::Rect> rects = getRectangles(int_images,height,width,means);
	std::deque<std::deque<Data>> data = getLightData(int_images,rects,means);
	std::deque<std::string> light_IDs = analyseData(data);
	seeLightIDs(light_IDs);
	showRects(images[0].image(), rects, light_IDs);
}

void showRects(cv::Mat img, std::deque<cv::Rect> rects, std::deque<std::string> light_IDs){
	cv::cvtColor(img,img,CV_GRAY2BGR);
	for(UINT i = 0; i < rects.size(); ++i){
		cv::Point text_pnt(rects[i].x-10,rects[i].y-2);
		
		cv::putText(img,light_IDs[i],text_pnt, cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0,0,255));
		
		cv::rectangle(img, rects[i], cv::Scalar(0,0,255));
	}
	cv::imshow("rects", img);
	cv::waitKey(0);
	cv::destroyWindow("rects");
}

void seeData(std::deque<std::deque<Data>> data){
	for(UINT i = 0; i < data.size(); ++i){
		for(UINT k = 0; k < data[i].size(); ++k){
			if(data[i][k].value() < 1){
				std::cout << data[i][k].time() << ' ' << 0 << std::endl;
			}else{
				std::cout << data[i][k].time() << ' ' << 1 << std::endl;
			}
		}
	}

}

void showDeque(std::deque<Image> images){
	for(UINT i = 0; i < images.size(); ++i){
		cv::imshow("frame", images[i].image());
		cv::waitKey(1);
	}
	cv::destroyWindow("frame");
	return;
}