#include <iostream>
#include <opencv2/opencv.hpp>
#include "grab_info.hpp"

using namespace std;
int main(int argc,char ** argv){
	if (argc < 2){
		cout << "usage error" << endl;
		return 0;
	}
	cv::Mat image = cv::imread(argv[1]);
	Grab_Rect GRect(image);	
	GRect.proc();

return 0;
}
