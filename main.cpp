#include <iostream>
#include <opencv2/opencv.hpp>
#include "grab_info.hpp"

using namespace std;
int main(int argc,char ** argv){
	if (argc < 2){
		cout << "usage error" << endl;
		return 0;
	}
	std::vector<Marker> possible_markers;
	std::vector<Marker> final_markers;
	

	cv::Mat image = cv::imread(argv[1]);
	Grab_Rect GRect(image,100,40);	
	GRect.markerDetect(possible_markers);
	GRect.markerRecognize(image,possible_markers,final_markers);

return 0;
}
