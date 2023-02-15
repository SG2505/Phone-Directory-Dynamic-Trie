#include "mydatabase.h"
#include <QSqlDatabase>
#include <QtSql>
#include <QDebug>
#include <QVariant>
#include "Trie.h"
MyDataBase::MyDataBase()
{
     createDB();
}


  void MyDataBase::createDB()
  {
      QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
      db.setDatabaseName("ContactsDB.db");
      if (!db.open()) {
          qDebug() << "Error opening database: " << db.lastError().text();
          return;
      }

      QString createSQL = "CREATE TABLE IF NOT EXISTS contacts ("
                              "NAME VARCHAR(50), "
                              "EMAIL VARCHAR(50), "
                              "PHONE VARCHAR(50));";
      QSqlQuery createQuery;
      if (!createQuery.exec(createSQL)) {
          qDebug() << "Error creating table: " << createQuery.lastError().text();
          return;
      }
      qDebug() << "Database and table created successfully";
  }

  void MyDataBase::insertData(QString name, QString email, QString phone)
  {
      QSqlDatabase db = QSqlDatabase::database();
      QSqlQuery insertQuery;
      insertQuery.prepare("INSERT INTO contacts (NAME, EMAIL, PHONE) "
                          "VALUES (?, ?, ?);");
      insertQuery.addBindValue(name);
      insertQuery.addBindValue(email);
      insertQuery.addBindValue(phone);

      if (!insertQuery.exec()) {
          qDebug() << "Error inserting data: " << insertQuery.lastError().text();
          return;
      }
      qDebug() << "Data inserted successfully";
      db.close();
  }

  void MyDataBase::readData(Trie&t1)
  {
      QSqlDatabase db = QSqlDatabase::database();
      QSqlQuery selectQuery("SELECT * FROM contacts;");

      while (selectQuery.next()) {
           QString name = selectQuery.value("NAME").toString();
           QString email = selectQuery.value("EMAIL").toString();
           QString phone = selectQuery.value("PHONE").toString();
           t1.addContact(name,email,phone);
          qDebug() << "Name: " << name << " Email: " << email << " Phone: " << phone;
      }
       db.close();
  }

  void MyDataBase::deleteData(QString name, QString email, QString phone)
  {
      QSqlDatabase db = QSqlDatabase::database();
      QSqlQuery deleteQuery;
      deleteQuery.prepare("DELETE FROM contacts WHERE Name = :name AND Email = :email AND Phone = :phone");
      deleteQuery.bindValue(":name", name);
      deleteQuery.bindValue(":email", email);
      deleteQuery.bindValue(":phone", phone);
      if (!deleteQuery.exec()) {
          qDebug() << "Error deleting data: " << deleteQuery.lastError().text();
      } else {
          qDebug() << "Data deleted successfully";
      }
      db.close();
  }


  void MyDataBase::updateData(QString oldName, QString oldEmail, QString oldPhone, QString newName, QString newEmail, QString newPhone)
  {
      QSqlDatabase db = QSqlDatabase::database();
      QSqlQuery query;
      query.prepare("UPDATE contacts SET Name = :newName, Email = :newEmail, Phone = :newPhone WHERE Name = :oldName AND Email = :oldEmail AND Phone = :oldPhone");
      query.bindValue(":oldName", oldName);
      query.bindValue(":oldEmail", oldEmail);
      query.bindValue(":oldPhone", oldPhone);
      query.bindValue(":newName", newName);
      query.bindValue(":newEmail", newEmail);
      query.bindValue(":newPhone", newPhone);
      if (!query.exec()) {
          qDebug() << "Error updating data: " << query.lastError().text();
      } else {
          qDebug() << "Data updated successfully";
      }
      db.close();
  }


