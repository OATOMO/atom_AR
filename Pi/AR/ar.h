#ifndef AR_H
#define AR_H

#include <QMainWindow>

namespace Ui {
	class AR;
}

class AR : public QMainWindow
{
	Q_OBJECT

public:
	explicit AR(QWidget *parent = 0);
	~AR();

private:
	Ui::AR *ui;
};

#endif // AR_H
