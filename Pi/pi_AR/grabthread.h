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
#ifndef GRABTHREAD_H
#define GRABTHREAD_H

#include <QThread>
#include <QDebug>
#include <QObject>
#include <opencv2/opencv.hpp>

class grabThread:public QThread
{
	Q_OBJECT
public:
	grabThread(QObject * parent  = 0);

protected:
	virtual void run();

private slots:
	void hello(){qDebug() << "hello";};


};

#endif // GRABTHREAD_H