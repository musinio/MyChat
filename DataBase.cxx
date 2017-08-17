#include "DataBase.h"
DataBase::DataBase(const QString& servername, const QString& dbname)
{
  QSqlDatabase Db = QSqlDatabase::addDatabase("QPSQL");
  Db.setHostName(servername);
  Db.setDatabaseName(dbname);

  if(!Db.open())
    qDebug() << "Error: connection with database fail" << Db.lastError().text() << endl;
  else
    qDebug() << "DataBase: connection ok" << endl;
}

DataBase::~DataBase()
{
  if(Db.isOpen())
    Db.close();
}

bool DataBase::ExistsUser(const QString &nickname)
{
    bool exists = false;
    QSqlQuery Query;
    Query.prepare("SELECT nickname FROM users WHERE nickname = (:nickname)");
    Query.bindValue(":nickname", nickname);

    if (Query.exec())
    {
      if (Query.next())
        exists = true;
    }
    else
      qDebug() << "user exists failed: " << Query.lastError();

    return exists;
}

bool DataBase::AddUser(const QString &nickname, const QString &login, const QString &paswd)
{
  bool success = false;

  if(!DataBase::ExistsUser(nickname))
  {
    if(!nickname.isEmpty() && !login.isEmpty() && !paswd.isEmpty())
    {
      QSqlQuery query;
      query.prepare("INSERT INTO users (nickname, login, paswd) VALUES (:nickname, :login, :paswd)");
      query.bindValue(":nickname", nickname);
      query.bindValue(":login", login);
      query.bindValue(":paswd", paswd);

      if(query.exec())
        success = true;
      else
        qDebug() << "add user failed: " << query.lastError();
    }
    else
      qDebug() << "nickname, login and password cannot be empty";
  }
  return success;
}

