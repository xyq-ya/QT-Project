#include "database.h"
#include <QtAlgorithms>
DataBase::DataBase()
{
    qDebug()<<QSqlDatabase::drivers();
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("cynosdbmysql8-grp-1735115927.xmjar.cn");
    db.setUserName("n1735115927");
    db.setPassword("p_697ade4c12");
    db.setDatabaseName("f4860a669f7f");

    if(db.open() == false)
    {
        printf("Wrong");
    }
    QSqlQuery query;
    QString sql1 = "create table user(username varchar(255),password varchar(255));";
    query.exec(sql1);
    QString sql2 = "create table scores(username varchar(255),score varchar(255));";
    query.exec(sql2);
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
bool DataBase::Register(QString name ,int score)
{
    QSqlQuery query;
    query.exec("insert into scores(username, score) values(?, ?)");
    query.addBindValue(name);
    query.addBindValue(score);
    if(!query.exec())
        return false;
    query.exec("select * from scores order by score ASC");
    if(!query.exec())
        return false;
    return true;
}
QList<QPair<QString,int>>* DataBase::showscore()
{
    std::vector<QPair<QString, int>> vec;
    auto sort = [](const QPair<QString, int> &a, const QPair<QString, int> &b)
    {
        return a.second > b.second;
    };
    QSqlQuery query;
    query.exec("select * from scores");
    while(query.next())
    {
        QString username = query.value(0).toString();
        int score = query.value(1).toInt();
        vec.push_back(QPair(username, score));
    }
    std::sort(vec.begin(), vec.end(), sort);
    QList<QPair<QString, int>>* list = new QList<QPair<QString, int>>();
    for(auto pair : vec)
    {
        list->append(pair);
    }
    return list;
}
