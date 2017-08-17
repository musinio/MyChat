#include "DataBase.h"
#define PRECISION 2

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
      QSqlQuery query;
      query.prepare("INSERT INTO users (nickname, login, paswd) VALUES (:nickname, :login, :paswd)");
      query.bindValue(":nickname", nickname);
      query.bindValue(":login", login);
      query.bindValue(":paswd", this->hash(paswd));

      if(query.exec())
      {
        qDebug() << "User Added to Data Base" << endl;
        success = true;
      }
      else
        qDebug() << "add user failed: " << query.lastError();
    }
    else
      qDebug() << "nickname, login and password cannot be empty";
  }
  return success;
}

QString DataBase::hash(const QString& str)
{
  return QString::fromStdString(std::to_string((*(size_t*)str.toUtf8().constData().c_str()) >> PRECISION)); // i got no idea what i'm doing here:)
}
