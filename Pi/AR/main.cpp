#include "ar.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	AR w;
	w.show();

	return a.exec();
}
