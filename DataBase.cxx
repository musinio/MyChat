#include "DataBase.h"
DataBase::DataBase(const QString& servername, const QString& dbname)
{
  Db = QSqlDatabase::addDatabase("QPSQL");
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
      QString tmp = (char*)this->hash(paswd);
      QSqlQuery query;
      query.prepare("INSERT INTO users (nickname, login, paswd) VALUES (:nickname, :login, :paswd)");
      query.bindValue(":nickname", nickname);
      query.bindValue(":login", login);
      query.bindValue(":paswd", tmp);

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

size_t DataBase::hash(const QString& str)
{
  std::string tmp1 = str.toUtf8().constData(); // qstring to std::string
  const char* tmp2 = tmp1.c_str(); // std::string to char*
  size_t precision = 2;
  return (*(size_t*)tmp2) >> precision; // i got no idea what i'm doing here:)
}
