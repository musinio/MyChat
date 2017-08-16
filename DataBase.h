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

  /**
   * @brief DataBase = открывает бд
   * @param path = абсолютный путь к бд файлу
   */
  DataBase(const QString& path);

  /**
   *@breif DataBase
   * деструктор
   */
  ~DataBase();

  /**
   * @brief ExistsUser = проверка существования юзера
   * @param nickname = никнейм
   */
  bool ExistsUser(const QString& nickname);

  /**
   * @brief AddUser = добавить нового пользователя
   * @param nickname = никнейм
   * @param login = логин
   * @param paswd = пароль
   */
  bool AddUser(const QString& nickname, const QString& login, const QString& paswd);
private:
  QSqlDatabase Db;
};

#endif // DATABASE_H
