/********************************************************************************
** Form generated from reading UI file 'game_ui.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAME_UI_H
#define UI_GAME_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Game_Ui
{
public:
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *Game_Ui)
    {
        if (Game_Ui->objectName().isEmpty())
            Game_Ui->setObjectName("Game_Ui");
        Game_Ui->resize(800, 600);
        lineEdit = new QLineEdit(Game_Ui);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(140, 150, 113, 20));
        pushButton = new QPushButton(Game_Ui);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(670, 120, 80, 20));
        pushButton_2 = new QPushButton(Game_Ui);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(670, 160, 80, 20));

        retranslateUi(Game_Ui);

        QMetaObject::connectSlotsByName(Game_Ui);
    } // setupUi

    void retranslateUi(QWidget *Game_Ui)
    {
        Game_Ui->setWindowTitle(QCoreApplication::translate("Game_Ui", "Form", nullptr));
        lineEdit->setText(QCoreApplication::translate("Game_Ui", "\346\210\220\345\212\237\346\265\213\350\257\225", nullptr));
        pushButton->setText(QCoreApplication::translate("Game_Ui", "\345\261\225\347\244\272\345\217\257\350\277\236\346\216\245\350\267\257\347\272\277", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Game_Ui", "\345\261\225\347\244\272\346\216\222\350\241\214\346\246\234", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Game_Ui: public Ui_Game_Ui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAME_UI_H
