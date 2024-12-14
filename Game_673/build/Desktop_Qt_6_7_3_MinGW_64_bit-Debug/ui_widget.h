/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLabel *label;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton_4;
    QLineEdit *lineEdit;
    QPushButton *pushButton_3;
    QLabel *label_2;
    QPushButton *pushButton_5;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->setEnabled(true);
        Widget->resize(300, 200);
        label = new QLabel(Widget);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 40, 40, 20));
        pushButton_2 = new QPushButton(Widget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(190, 110, 60, 20));
        pushButton = new QPushButton(Widget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(30, 110, 60, 60));
        lineEdit_2 = new QLineEdit(Widget);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(90, 80, 150, 20));
        pushButton_4 = new QPushButton(Widget);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(110, 150, 60, 20));
        lineEdit = new QLineEdit(Widget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(90, 40, 150, 20));
        pushButton_3 = new QPushButton(Widget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(110, 110, 60, 20));
        label_2 = new QLabel(Widget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, 80, 40, 20));
        pushButton_5 = new QPushButton(Widget);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(190, 150, 60, 20));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        label->setText(QCoreApplication::translate("Widget", "\350\264\246\345\217\267\357\274\232", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Widget", "\351\200\200\345\207\272", nullptr));
        pushButton->setText(QCoreApplication::translate("Widget", "\347\231\273\345\275\225", nullptr));
        pushButton_4->setText(QCoreApplication::translate("Widget", "\346\233\264\346\224\271\345\257\206\347\240\201", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Widget", "\346\263\250\345\206\214\350\264\246\345\217\267", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "\345\257\206\347\240\201\357\274\232", nullptr));
        pushButton_5->setText(QCoreApplication::translate("Widget", "\346\263\250\351\224\200\350\264\246\345\217\267", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
