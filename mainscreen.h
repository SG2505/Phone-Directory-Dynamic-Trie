#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QMainWindow>
#include "QListWidgetItem"
#include "Trie.h"
#include "mydatabase.h"
#include <QElapsedTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class mainscreen; }
QT_END_NAMESPACE

class mainscreen : public QMainWindow
{
    Q_OBJECT

public:
    mainscreen(QWidget *parent = nullptr);
    ~mainscreen();



private slots:
  //  void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_Edit_Button_clicked();

    void on_Save_Button_clicked();

    void on_Cancel_Button_clicked();

    void on_Delete_Button_clicked();

    void on_Search_lineEdit_textChanged(const QString &arg1);




    void on_Add_Button_clicked();

    void on_Cancel_Button_add_2_clicked();

    void on_Save_Button_add_clicked();

    void on_Name_LineEdit_textChanged(const QString &arg1);

    void on_Phone_LineEdit_textChanged(const QString &arg1);

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void changeEvent( QEvent* e );

private:
    Ui::mainscreen *ui;
    Trie t1;
    MyDataBase db;
    bool addButtonIsClicked; //this variable is used in the handling of the transtion between labels
    int lblTransitionDelta; //label trasition time between main label and operation messages (measured in ms)



};
#endif // MAINSCREEN_H
