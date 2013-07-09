#include "lightdata.h"

const double light_frequency = 4;
const double dit_length = (1/light_frequency)/2;

std::string dit;
std::string dah;
std::string p;
std::string ch_p;

std::deque<std::string> letters;

void morse_code_init(){
	dit = std::string("1");
	dah = std::string("111");
	p = std::string("0");
	ch_p = std::string("0");
}

void morse_letters_init(){
	morse_code_init();
	
	letters.push_back(dit+ p+ dah);//A
	letters.push_back(dah+ p+ dit+ p+ dit+ p+ dit);//B
	letters.push_back(dah+ p+ dit+ p+ dah+ p+ dit);//C
	letters.push_back(dah+ p+ dit+ p+ dit);//D
	letters.push_back(dit);//E
	letters.push_back(dit+ p+ dit+ p+ dah+ p+ dit);//F
	letters.push_back(dah+ p+ dah+ p+ dit);//G
	letters.push_back(dit+ p+ dit+ p+ dit+ p+ dit);//H
	letters.push_back(dit+ p+ dit);//I
	letters.push_back(dit+ p+ dah+ p+ dah+ p+ dah);//J
	letters.push_back(dah+ p+ dit+ p+ dah);//K
	letters.push_back(dit+ p+ dah+ p+ dit+ p+ dit);//L
	letters.push_back(dah+ p+ dah);//M
	letters.push_back(dah+ p+ dit);//N
	letters.push_back(dah+ p+ dah+ p+ dah);//O
	letters.push_back(dit+ p+ dah+ p+ dah+ p+ dit);//P
	letters.push_back(dah+ p+ dah+ p+ dit+ p+ dah);//Q
	letters.push_back(dit+ p+ dah+ p+ dit);//R
	letters.push_back(dit+ p+ dit+ p+ dit);//S
	letters.push_back(dah);//T
	letters.push_back(dit+ p+ dit+ p+ dah);//U
	letters.push_back(dit+ p+ dit+ p+ dit+ p+ dah);//V
	letters.push_back(dit+ p+ dah+ p+ dah);//W
	letters.push_back(dah+ p+ dit+ p+ dit+ p+ dah);//X
	letters.push_back(dah+ p+ dit+ p+ dah+ p+ dah);//Y
	letters.push_back(dah+ p+ dah+ p+ dit+ p+ dit);//Z
	return;
}

//finds the start of a ditlength
 int findSignalChange(std::deque<Data> data){
	for(UINT i = 1; i < data.size(); ++i){
		if(data[i].value() > 1 && data[i-1].value() < 1){
			return i;
		}else if(data[i].value() < 1 && data[i-1].value() > 1){
			return i;
		}
	}
	return -1;
 }

int midPoint(int start, std::deque<Data> data){

	if(start == -1){
		return -1;
	}
	
	double nextVal = data[start].time() + dit_length/2;
	for(int i = start; i < data.size(); ++i){
		if((data[i].time() - nextVal) > 0){
			if(fabs(data[i].time() - nextVal) < fabs(data[i-1].time() - nextVal))
				return i;
			else
				return i-1;
		}
	}
		
	return -1;
}

int nextPoint(int start, std::deque<Data> data){

	if(start == -1){
		return -1;
	}
	
	double nextVal = data[start].time() + dit_length;
	for(int i = start; i < data.size(); ++i){
		if((data[i].time() - nextVal) > 0){
			if(fabs(data[i].time() - nextVal) < fabs(data[i-1].time() - nextVal))
				return i;
			else
				return i-1;
		}
	}
		
	return -1;
}

int findStartPoint(std::deque<Data> data){
	int zerosInRow = 0;
	int j = findSignalChange(data);
	
	if(j == -1)
		return -1;
	
	int start = midPoint(j, data);
	for( int i = start; i < data.size();i = nextPoint(i, data)){
		if(i == -1){
			return -1;
		}
		if(data[i].value() < 1){	
			++zerosInRow;
			if(zerosInRow == ch_p.size()){
				return i;
			}
		}else{
			zerosInRow = 0;
		}
	}
	return -1;
}

std::string recordSignal(std::deque<Data> data){
	std::string toReturn = std::string("");
	
	int zerosInRow = 0;
	int start = findStartPoint(data);
	start = nextPoint(start, data);
	
	if(start == -1){
		return std::string("ERROR");
	}
	
	for(int i = start; i < data.size(); i = nextPoint(i, data)){
		if(i==-1){
			return std::string("ERROR");
		}
		if(data[i].value() > 1){
			toReturn += "1";
			zerosInRow = 0;
		}else{
			
			toReturn += "0";
			++zerosInRow;
			if(zerosInRow == ch_p.size()){
				toReturn.erase(toReturn.end()-ch_p.size(),toReturn.end());
				if(toReturn.empty()){
					return std::string("ERROR");
				}
				return toReturn;
			}
		}
	}
	return std::string("ERROR");
}

std::string compareSignal(std::string str){
	for(int i = 0; i < letters.size(); ++i){
		if(str.compare(letters[i]) == 0){
			return std::string() += (char)(i+65);
		}
	}
	return std::string("ERROR");
}

std::deque<std::string> analyseData(std::deque<std::deque<Data>> data){
	morse_letters_init();
	
	std::deque<std::string> light_IDs;
	for(UINT i = 0; i < data.size(); ++i){
		std::string signal = recordSignal(data[i]);
		
		signal = compareSignal(signal);
		light_IDs.push_back(signal);
	}
	return light_IDs;
}

void seeLightIDs(std::deque<std::string> light_IDs){
	for(UINT i = 0; i < light_IDs.size(); ++i){
		std::cout << light_IDs[i] << std::endl;
	}
	return;
}