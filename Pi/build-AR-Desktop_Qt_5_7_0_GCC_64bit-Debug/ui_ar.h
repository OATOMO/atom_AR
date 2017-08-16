/********************************************************************************
** Form generated from reading UI file 'ar.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AR_H
#define UI_AR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "drawgl.h"

QT_BEGIN_NAMESPACE

class Ui_AR
{
public:
    QWidget *centralWidget;
    drawGL *widget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *AR)
    {
        if (AR->objectName().isEmpty())
            AR->setObjectName(QStringLiteral("AR"));
        AR->resize(400, 300);
        centralWidget = new QWidget(AR);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        widget = new drawGL(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(90, 30, 191, 141));
        AR->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(AR);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 23));
        AR->setMenuBar(menuBar);
        mainToolBar = new QToolBar(AR);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        AR->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(AR);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        AR->setStatusBar(statusBar);

        retranslateUi(AR);

        QMetaObject::connectSlotsByName(AR);
    } // setupUi

    void retranslateUi(QMainWindow *AR)
    {
        AR->setWindowTitle(QApplication::translate("AR", "AR", 0));
    } // retranslateUi

};

namespace Ui {
    class AR: public Ui_AR {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AR_H
