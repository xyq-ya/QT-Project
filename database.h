#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QString>
class DataBase
{
public:
    DataBase();
    bool Add(QString, QString);
    bool Change(QString, QString);
    bool Delete(QString);
    bool Login(QString, QString);
private:
    QSqlDatabase db;
};

#endif // DATABASE_H
