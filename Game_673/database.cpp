#include "database.h"

DataBase::DataBase()
{
    qDebug()<<QSqlDatabase::drivers();
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("cynosdbmysql8-grp-1734523762.xmjar.cn");
    db.setUserName("n1734523762");
    db.setPassword("p_2937e1455b");
    db.setDatabaseName("c6f568b30294");

    if(db.open() == false)
    {
        printf("Wrong");
    }
    QSqlQuery query;
    QString sql = "create table user(username varchar(255),password varchar(255));";
    query.exec(sql);
}
bool DataBase::Add(QString name, QString pass)
{
    if(name.isEmpty() || pass.isEmpty())
        return false;
    QSqlQuery query;
    query.exec("insert into user(username, password) values(?, ?)");
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
    query.exec("delete from user where username = ?");
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
    query.exec("update user set password = ? WHERE username = ?");
    query.addBindValue(pass);
    query.addBindValue(name);
    if(!query.exec())
        return false;
    return true;
}
bool DataBase::Login(QString name, QString pass)
{
    QSqlQuery query;
    query.exec("select * from user");
    while(query.next())
    {
        QString username = query.value(0).toString();
        QString password = query.value(1).toString();
        if(username == name && password == pass)
            return true;
    }
    return false;
}
