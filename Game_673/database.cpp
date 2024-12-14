#include "database.h"

DataBase::DataBase()
{
    qDebug()<<QSqlDatabase::drivers();
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("cynosdbmysql8-grp-1734073958.xmjar.cn");
    db.setUserName("n1734073958");
    db.setPassword("9d75834a8");
    db.setDatabaseName("0acdba77062b");

    if(db.open() == false)
    {
        printf("Wrong");
    }
}
bool DataBase::Add(QString name, QString pass)
{
    if(name.isEmpty() || pass.isEmpty())
        return false;
    QSqlQuery query;
    query.exec("insert into test(username, password) values(?, ?)");
    query.addBindValue(name);
    query.addBindValue(pass);
    if(!query.exec())
        return false;
    return true;
}
bool DataBase::Delete(QString name)
{
    if(name.isEmpty())
        return false;
    QSqlQuery query;
    query.exec("delete from test where username = ?");
    query.addBindValue(name);
    if(!query.exec())
        return false;
    return true;
}
bool DataBase::Change(QString name, QString pass)
{
    if(name.isEmpty() || pass.isEmpty())
        return false;
    QSqlQuery query;
    query.exec("update test set password = ? WHERE username = ?");
    query.addBindValue(pass);
    query.addBindValue(name);
    if(!query.exec())
        return false;
    return true;
}
bool DataBase::Login(QString name, QString pass)
{
    QSqlQuery query;
    query.exec("select * from test");
    while(query.next())
    {
        QString username = query.value(0).toString();
        QString password = query.value(1).toString();
        if(username == name && password == pass)
            return true;
    }
    return false;
}