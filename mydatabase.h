#ifndef MYDATABASE_H
#define MYDATABASE_H

#include <QString>
#include "Trie.h"
class MyDataBase
{
public:
    Trie t1;
    MyDataBase();
    void createDB();
    void insertData(QString name, QString email, QString phone);
    void deleteData(QString name, QString email, QString phone);
    void readData(Trie&t1);
    void updateData(QString oldName, QString oldEmail, QString oldPhone, QString newName, QString newEmail, QString newPhone);


};



#endif // MYDATABASE_H
