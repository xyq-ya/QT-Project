#include "widget.h"
#include "victory.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Game_673_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

     Widget w;
     w.show();
     return a.exec();

     //测试胜利界面，测试前把上方widget三行都注释掉
    // victory *vic = new victory();
    // vic->show();
    // return a.exec();
}
