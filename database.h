#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QString>
#include <QList>
class DataBase
{
public:
    DataBase();
    bool Add(QString, QString);
    bool Change(QString, QString);
    bool Delete(QString);
    bool Login(QString, QString);
    bool Register(QString, int);
    QList<QPair<QString,int>>* showscore();
private:
    QSqlDatabase db;
};

#endif // DATABASE_H
