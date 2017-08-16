#include "ar.h"
#include "ui_ar.h"

AR::AR(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::AR)
{
	ui->setupUi(this);
}

AR::~AR()
{
	delete ui;
}
