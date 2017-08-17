#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#pragma hdrstop

class DataBase
{
public:
  DataBase(const QString& servername, const QString& dbname);

  bool ExistsUser(const QString& nickname);

  bool AddUser(const QString& nickname, const QString& login, const QString& paswd);

  size_t hash(const QString& str);

  ~DataBase();
private:
  QSqlDatabase Db;
};

#endif // DATABASE_H
