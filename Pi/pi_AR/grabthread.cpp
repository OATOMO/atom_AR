/*
			  DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
					Version 2, December 2004

 Copyright (C) 2017 Romain Lespinasse <romain.lespinasse@gmail.com>

 Everyone is permitted to copy and distribute verbatim or modified
 copies of this license document, and changing it is allowed as long
 as the name is changed.

			DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

  0. You just DO WHAT THE FUCK YOU WANT TO.
*/
#include <unistd.h>
#include <stdlib.h>
#include "grabthread.h"
#include <opencv2/opencv.hpp>
#include <QDebug>

grabThread::grabThread(QObject * parent):QThread(parent){
	qDebug() << "grab Thread" << QThread::currentThreadId();
}

void grabThread::run(){
	cv::Mat image;
	cv::VideoCapture capture(0);
	capture >> image;
	int x = image.cols;
	qDebug() << x;
	x =  image.rows;
	qDebug() << x;
	cv::imshow("1",image);
	cv::waitKey();
}
