#include "mainscreen.h"
#include "Trie.h"
#include <vector>
#include <string>
#include "QStringListModel"
#include "./ui_mainscreen.h"
#include "QString"
#include "QList"
#include "QVector"
#include "QListWidgetItem"
#include <iostream>
#include <stack>
#include <QMessageBox>
#include <iostream>
#include <fstream>
#include <vector>
#include <istream>
#include <string>
#include <QFont>
#include<QFontDatabase>
#include<QPixmap>
#include<QPropertyAnimation>
#include <QSqlDatabase>
#include <QtSql>
#include <QDebug>
#include <QVariant>
#include "mydatabase.h"
#include <QTimer>
#include <QWindowStateChangeEvent>

using namespace std;
  //Trie t1;
mainscreen::mainscreen(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainscreen)
{


    ui->setupUi(this);
    ui->NotFoundLabel->hide();
    ui->Save_Button->hide();
    ui->Cancel_Button->hide();
    ui->Email_Box->hide();
    ui->Email_Label->hide();
    ui->Email_LineEdit->hide();
    ui->Name_Box->hide();
    ui->Name_Label->hide();
    ui->Name_LineEdit->hide();
    ui->Phone_Box->hide();
    ui->Phone_Label->hide();
    ui->Phone_LineEdit->hide();
    ui->Edit_Button->hide();
    ui->Delete_Button->hide();
    ui->Icon->hide();
    ui->Icon_2->hide();
    ui->delete_message->hide();
    ui->listWidget->setSortingEnabled(true);
    ui->listWidget->setSpacing(5);
    ui->Cancel_Button_add_2->hide();
    ui->Save_Button_add->hide();
    ui->AddContact_Label->hide();
    ui->Phone_LineEdit->setMaxLength(25);
    ui->Name_LineEdit->setMaxLength(50);
    ui->Email_LineEdit->setMaxLength(50);




    addButtonIsClicked =false;
    MyDataBase db;
    db.readData(t1);
    lblTransitionDelta = 7000;

    vector<QString> v1 = t1.list();

    for(int i = 0;i<v1.size();i++){

        ui->listWidget->addItem(v1[i]);
    }
}

mainscreen::~mainscreen()
{
    delete ui;
}


/*void mainscreen::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{

    ui->Add_Button->setDisabled(false);
    ui->delete_message->hide();
    ui->Main_Label->hide();
    ui->Email_LineEdit->hide();
    ui->Name_LineEdit->hide();
    ui->Save_Button->hide();
    ui->Cancel_Button->hide();
    ui->Phone_LineEdit->hide();


    QString str = item->text();

    ui->Name_Box->setText(str);
    ui->Email_Box->setText(t1.GetDetails(str)->email);
    ui->Phone_Box->setText(t1.GetDetails(str)->phoneNo);

   // ui->listWidget->findItems("ahmed",Qt::MatchExactly);

    ui->Email_Box->show();
    ui->Email_Label->show();
    ui->Name_Box->show();
    ui->Name_Label->show();
    ui->Phone_Box->show();
    ui->Phone_Label->show();
    ui->Edit_Button->show();
    ui->Delete_Button->show();
    QChar x = ui->Name_Box->text()[0].toUpper(); //convert it to upper

    if(((x>='A')&&(x<='Z'))||((x>='a')&&(x<='z'))){
        ui->Icon->setText(x);
        ui->Icon->show();
        ui->Icon_2->hide();
    }
    else {
        ui->Icon_2->show();
        ui->Icon->hide();
    }



}
*/

void mainscreen::on_Edit_Button_clicked()
{
    ui->Search_lineEdit->clear();
    ui->Name_Box->hide();
    ui->Email_Box->hide();
    ui->Phone_Box->hide();
    ui->Name_LineEdit->show();
    ui->Email_LineEdit->show();
    ui->Phone_LineEdit->show();
    ui->Edit_Button->hide();
    ui->Delete_Button->hide();
    ui->Save_Button->show();
    ui->Cancel_Button->show();
    ui->Name_LineEdit->setText(ui->Name_Box->text());
    ui->Phone_LineEdit->setText(ui->Phone_Box->text());
    ui->Email_LineEdit->setText(ui->Email_Box->text());
    //ui->Icon->hide();
    //ui->Icon_2->hide();
    ui->Add_Button->setDisabled(true);
    addButtonIsClicked = false;
}


void mainscreen::on_Save_Button_clicked(){

    //must update listwidget here
    ui->Add_Button->setDisabled(false);
    string name = (ui->Name_Box->text()).toStdString();
    QString email = (ui->Email_Box->text());
    QString phone = (ui->Phone_Box->text());
    QString emailnew = ui->Email_LineEdit->text();
    QString phonenew = ui->Phone_LineEdit->text();
    QString namenew = ui->Name_LineEdit->text();

    ui->Name_Box->hide();
    ui->Email_Box->hide();
    ui->Phone_Box->hide();
    if(phonenew!="")
    {
        for(int i=0;i<phonenew.size();i++)
        {
            if(!((phonenew[i]>='0' && phonenew[i]<='9') || phonenew[i] == '+' || phonenew[i] == '*'
                    || phonenew[i] == '#' || phonenew[i] == '-' || phonenew[i] == '('  || phonenew[i] == ')' ||phonenew[i] == ' ' ))
            {
                 QMessageBox::information(this,"Invalid Phone Number","Invalid Phone Number, Phone Number can include only Numbers,'+','-','#' and '*'"
                                                                        );
                 return;
            }


        }
    }
    if(emailnew!="")
    {
        bool found = false;
        for(int i=0;i<emailnew.size();i++)
        {
            if(emailnew[i]=='@')
            {
                 found = true;
            }


        }
        if(!found)
        {
            QMessageBox::information(this,"Invalid Email Address","Invalid Email Address Entered.");
            return;
        }
    }

    ui->Name_Box->setText(namenew);
    t1.erase(name);
    t1.addContact(namenew,emailnew,phonenew);
    db.updateData(QString::fromStdString(name),email,phone,namenew,emailnew,phonenew);






    ui->listWidget->addItem(namenew);


    QListWidgetItem *it = ui->listWidget->takeItem(ui->listWidget->currentRow());
    delete it;


    // should be changed that when adding contact we update
    // we can use helper function that updates the list when adding new name
    ui->Name_LineEdit->hide();
    ui->Email_LineEdit->hide();
    ui->Phone_LineEdit->hide();
    ui->Save_Button->hide();
    ui->Cancel_Button->hide();


    QChar x = ui->Name_Box->text()[0].toUpper(); //convert it to upper

    if(((x>='A')&&(x<='Z'))||((x>='a')&&(x<='z'))){
        ui->Icon->setText(x);
        ui->Icon->show();
        ui->Icon_2->hide();
    }
    else {
        ui->Icon_2->show();
        ui->Icon->hide();
    }

    ui->delete_message->setText("Contact Edited Successfully!");
    ui->delete_message->show();
    QTimer::singleShot(lblTransitionDelta,ui->delete_message, &QLabel::hide);
    QTimer::singleShot(lblTransitionDelta, [&]() {
           if (addButtonIsClicked == false) {
              ui->Main_Label->showFullScreen();
           }
       });

       // QTimer::singleShot(7000,ui->Main_Label, &QLabel::show);

    ui->Name_LineEdit->clear();
    ui->Email_LineEdit->clear();
    ui->Phone_LineEdit->clear();
    ui->Name_Label->hide();
    ui->Phone_Label->hide();
    ui->Email_Label->hide();
    ui->Icon_2->hide();


}


void mainscreen::on_Cancel_Button_clicked()
{

    ui->Add_Button->setDisabled(false);
    ui->Name_Box->show();
    ui->Email_Box->show();
    ui->Phone_Box->show();
    ui->Name_LineEdit->hide();
    ui->Email_LineEdit->hide();
    ui->Phone_LineEdit->hide();
    ui->Edit_Button->show();
    ui->Delete_Button->show();
    ui->Save_Button->hide();
    ui->Cancel_Button->hide();

    ui->Name_LineEdit->clear();
    ui->Email_LineEdit->clear();
    ui->Phone_LineEdit->clear();


    QChar x = ui->Name_Box->text()[0].toUpper(); //convert it to upper

    if(((x>='A')&&(x<='Z'))||((x>='a')&&(x<='z'))){
        ui->Icon->setText(x);
        ui->Icon->show();
        ui->Icon_2->hide();
    }
    else {
        ui->Icon_2->show();
        ui->Icon->hide();
    }
}



void mainscreen::on_Delete_Button_clicked()
{
    ui->Add_Button->setDisabled(false);
    
   QMessageBox::StandardButton reply = QMessageBox::question(this,"Delete Contact","Are you sure you want to delete this contact?",
                                                             QMessageBox::Yes | QMessageBox::No);




   if(reply ==QMessageBox::Yes ){
    string name = (ui->Name_Box->text()).toStdString();
    QString email = (ui->Email_Box->text());
    QString phone = (ui->Phone_Box->text());
    t1.erase(name);
    db.deleteData(QString::fromStdString(name),email,phone);
    ui->delete_message->setText("Contact Deleted Successfully!");
    ui->delete_message->show();
    QListWidgetItem *it = ui->listWidget->takeItem(ui->listWidget->currentRow());
    delete it;
    QTimer::singleShot(lblTransitionDelta, ui->delete_message, &QLabel::hide);
    QTimer::singleShot(lblTransitionDelta, [&]() {
           if (addButtonIsClicked == false) {
              ui->Main_Label->showFullScreen();
           }
       });
    addButtonIsClicked = false;
    ui->Name_Box->hide();
    ui->Email_Box->hide();
    ui->Phone_Box->hide();
    ui->Edit_Button->hide();
    ui->Delete_Button->hide();
    ui->Icon->hide();
    ui->Icon_2->hide();
    ui->Name_LineEdit->clear();
    ui->Email_LineEdit->clear();
    ui->Phone_LineEdit->clear();
    ui->Name_Label->hide();
    ui->Phone_Label->hide();
    ui->Email_Label->hide();


   }


}


void mainscreen::on_Search_lineEdit_textChanged(const QString &arg1)
{
    ui->Add_Button->setDisabled(false);
//    QChar x = arg1[0].toUpper(); //convert it to upper
//    ui->search_icon->setText(x);
    if(arg1 != "")
    {
        ui->listWidget->clear();

        string argstr1 = arg1.toStdString(),argstr2= arg1.toStdString();
        QString q1, q2;

        q1 = arg1[0].toUpper();
        argstr1 = q1.toStdString() + &argstr1[1];
        q2 = arg1[0].toLower();
        argstr2 = q2.toStdString() + &argstr2[1];

        vector<QString> v1 = t1.prefix(QString::fromStdString(argstr1));
       vector<QString> v2 = t1.prefix(QString::fromStdString(argstr2));
        QString concat = '"'+arg1+'"';
        //string str;


        if(v1.empty()&&v2.empty())
                {
                    ui->NotFoundLabel->setText("No Search Results For "+concat);
                    ui->NotFoundLabel->show();
                }
                else
                {
                    ui->NotFoundLabel->hide();
                    if(q1==q2){
                        for(int i = 0;i<v1.size();i++)
                        {

                            ui->listWidget->addItem(v1[i]);

                        }
                    }
                    else{
                        for(int i = 0;i<v1.size();i++)
                        {

                            ui->listWidget->addItem(v1[i]);

                        }
                        for(int i = 0;i<v2.size();i++)
                        {

                            ui->listWidget->addItem(v2[i]);

                        }
                    }

               }
  }
    else{
        ui->NotFoundLabel->hide();
        ui->listWidget->clear();
        vector<QString> v1 = t1.list();



        for(int i = 0;i<v1.size();i++){


            ui->listWidget->addItem(v1[i]);

        }
    }
}



void mainscreen::on_Add_Button_clicked()
{
    addButtonIsClicked = true;
    ui->Add_Button->setDisabled(false);
    ui->Search_lineEdit->clear();
    ui->Name_Box->hide();
    ui->Email_Box->hide();
    ui->Phone_Box->hide();
    ui->Name_LineEdit->show();
    ui->Email_LineEdit->show();
    ui->Phone_LineEdit->show();
    ui->Edit_Button->hide();
    ui->Delete_Button->hide();
    ui->Save_Button->hide();
    ui->Cancel_Button->hide();
    ui->Icon->hide();
    ui->Icon_2->show();
    ui->delete_message->hide();
    ui->frame->hide();
    ui->Main_Label->hide();
    ui->Name_Label->show();
    ui->Email_Label->show();
    ui->Phone_Label->show();
    ui->Cancel_Button_add_2->show();
    ui->Save_Button_add->show();
    ui->centralwidget->setStyleSheet("background:rgb(213, 226, 241)");
    ui->AddContact_Label->show();
    ui->Save_Button_add->setDisabled(true);
}


void mainscreen::on_Cancel_Button_add_2_clicked()
{
    ui->Icon_2->hide();
    ui->Icon->hide();
    ui->Add_Button->setDisabled(false);
    ui->frame->show();
    ui->Main_Label->show();
    ui->AddContact_Label->hide();
    ui->centralwidget->setStyleSheet("background:rgb(255, 255, 255)");
    ui->Cancel_Button_add_2->hide();
    ui->Save_Button_add->hide();
    ui->Name_Label->hide();
    ui->Email_Label->hide();
    ui->Phone_Label->hide();
    ui->Name_LineEdit->hide();
    ui->Email_LineEdit->hide();
    ui->Phone_LineEdit->hide();
    ui->Name_LineEdit->clear();
    ui->Email_LineEdit->clear();
    ui->Phone_LineEdit->clear();
    ui->Icon_2->hide();
}


void mainscreen::on_Save_Button_add_clicked()
{
    ui->Add_Button->setDisabled(false);

    QString emailnew = ui->Email_LineEdit->text();
    QString phonenew = ui->Phone_LineEdit->text();
    QString namenew = ui->Name_LineEdit->text();
    if(phonenew!="")
    {
        for(int i=0;i<phonenew.size();i++)
        {
            if(!((phonenew[i]>='0' && phonenew[i]<='9') || phonenew[i] == '+' || phonenew[i] == '*'
                    || phonenew[i] == '#' || phonenew[i] == '-'))
            {
                 QMessageBox::information(this,"Invalid Phone Number","Invalid Phone Number, Phone Number can include only Numbers,'+','-','#' and '*'"
                                                                        );
                 return;
            }


        }
    }
    if(emailnew!="")
    {
        bool found = false;
        for(int i=0;i<emailnew.size();i++)
        {
            if(emailnew[i]=='@')
            {
                 found = true;
            }


        }
        if(!found)
        {
            QMessageBox::information(this,"Invalid Email Address","Invalid Email Address Entered.");
            return;
        }

    }
    t1.addContact(namenew,emailnew,phonenew);
    db.insertData(namenew,emailnew,phonenew);


    ui->listWidget->addItem(namenew);
    ui->frame->show();
    ui->delete_message->setText("Contact Added Successfully!");
    ui->delete_message->show();
    QTimer::singleShot(lblTransitionDelta,ui->delete_message, &QLabel::hide);
    QTimer::singleShot(lblTransitionDelta, [&]() {
           if (addButtonIsClicked == false) {
              ui->Main_Label->showFullScreen();
           }
       });
    addButtonIsClicked = false;
    ui->AddContact_Label->hide();
    ui->centralwidget->setStyleSheet("background:rgb(255, 255, 255)");
    ui->Cancel_Button_add_2->hide();
    ui->Save_Button_add->hide();
    ui->Name_Label->hide();
    ui->Email_Label->hide();
    ui->Phone_Label->hide();
    ui->Name_LineEdit->hide();
    ui->Email_LineEdit->hide();
    ui->Phone_LineEdit->hide();
    ui->Name_LineEdit->clear();
    ui->Email_LineEdit->clear();
    ui->Phone_LineEdit->clear();
    ui->Icon_2->hide();
    ui->Icon->hide();

}



void mainscreen::on_Name_LineEdit_textChanged(const QString &arg1)
{

    ui->Icon_2->hide();

    if(arg1 != "") {
        QChar x = arg1[0].toUpper();

        if(((x>='A')&&(x<='Z'))||((x>='a')&&(x<='z'))){
            ui->Icon->setText(x);
            ui->Icon->show();
            ui->Icon_2->hide();
        }
        else {
            ui->Icon_2->show();
            ui->Icon->hide();
        }
        ui->Save_Button_add->setDisabled(false);
        ui->Save_Button->setDisabled(false);

    }
    else {
        ui->Icon->hide();
        ui->Icon_2->show();
        ui->Save_Button_add->setDisabled(true);
        ui->Save_Button->setDisabled(true);
    }


}


void mainscreen::on_Phone_LineEdit_textChanged(const QString &arg1)
{

}

void mainscreen::changeEvent( QEvent* e )
{
    if( e->type() == QEvent::WindowStateChange )
    {
        QWindowStateChangeEvent* event = static_cast< QWindowStateChangeEvent* >( e );

       if( event->oldState() == Qt::WindowMaximized && this->windowState() == Qt::WindowNoState ) // windowNoState is when you hit the restore down button
        {

            mainscreen::resize(1201,700);

        }
    }
}


void mainscreen::on_listWidget_itemClicked(QListWidgetItem *item)
{
    ui->Add_Button->setDisabled(false);
    ui->delete_message->hide();
    ui->Main_Label->hide();
    ui->Email_LineEdit->hide();
    ui->Name_LineEdit->hide();
    ui->Save_Button->hide();
    ui->Cancel_Button->hide();
    ui->Phone_LineEdit->hide();


    QString str = item->text();

    ui->Name_Box->setText(str);
    ui->Email_Box->setText(t1.GetDetails(str)->email);
    ui->Phone_Box->setText(t1.GetDetails(str)->phoneNo);

   // ui->listWidget->findItems("ahmed",Qt::MatchExactly);

    ui->Email_Box->show();
    ui->Email_Label->show();
    ui->Name_Box->show();
    ui->Name_Label->show();
    ui->Phone_Box->show();
    ui->Phone_Label->show();
    ui->Edit_Button->show();
    ui->Delete_Button->show();
    QChar x = ui->Name_Box->text()[0].toUpper(); //convert it to upper

    if(((x>='A')&&(x<='Z'))||((x>='a')&&(x<='z'))){
        ui->Icon->setText(x);
        ui->Icon->show();
        ui->Icon_2->hide();
    }
    else {
        ui->Icon_2->show();
        ui->Icon->hide();
    }


}

