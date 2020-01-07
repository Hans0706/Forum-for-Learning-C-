#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<stdio.h>
#include<iostream>
#include<QMdiArea>
#include<mainboard.h>
#include<QListWidget>
#include<QString>
#include<QListWidgetItem>
#include<QWidget>
#include<QLayout>
#include<QMenu>
#include<QMenuBar>
#include<iostream>
#include<fstream>
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //Log in
    creatAction();
    creatMenu();
    this->setUser();

   QTextBrowser* text=new QTextBrowser;

    //ACCOUNT
    //Initial
    for(int i=0;i<this->users.size();i++)
      {
        this->account.push_back(ACCOUNT(users[i].account,users[i].password,USER,users[i].id,users[i].sex));
        if(users[i].isBoss==1) account[i].is_Boss=1;
        else account[i].is_Boss=0;
    }
    for(int i=0;i<this->admin.size();i++)
        this->account.push_back(ACCOUNT(admin[i].account,admin[i].password,ADMINE,admin[i].id,admin[i].sex));

    this->server=new QTcpServer(this);
        this->server->listen(QHostAddress::Any,1111);

        connect(server,SIGNAL(newConnection()),this,SLOT(acceptConnection()));


}

void MainWindow::acceptConnection()
{
    client_connection=server->nextPendingConnection();


    connect(client_connection,SIGNAL(readyRead()),this,SLOT(readClient()));
    this->socket_client.push_back(client_connection);
    QMessageBox::warning(NULL,"attention","有新的连接");
    text->append("有新的连接");
}

void MainWindow::readClient()
{

}
MainWindow::~MainWindow()
{
    delete ui;


}
void MainWindow::setUser()
{
    normalUser a(2016211001,"111","111",0,1); //female=0 male=1 secret=2
    normalUser b(2016211002,"222","222",1,0); //male
    normalUser c(2016211003,"333","333",1,0); //secret

    administrator d(000,"admin","admin",1);
    administrator e(001,"admin2","admin3",0);
    administrator f(002,"admin2","admin",0);
    users.push_back(a);
    users.push_back(b);
    users.push_back(c);

    admin.push_back(d);
    admin.push_back(e);
    admin.push_back(f);

}

//  to be continue
void MainWindow::creatAction()
{

}
//  to be continue
void MainWindow::creatMenu()
{

}

void MainWindow::logIn1()
{



     QString acc=ui->lineEdit->text();
     QString pass=ui->lineEdit_2->text();

     std::vector<ACCOUNT>::iterator it = std::find(account.begin(),account.end(),ACCOUNT(acc,pass,0,0,0));
     if(it!=account.end()&&it->kind==0)
     {
         mainBoard* a=new mainBoard;
         a->Users.assign(users.begin(),users.end());
         a->currentUser=new normalUser;
         //successfully log in
             //复制当前的用户到mainboard里面



         //根据查找结果得到用户信息
         //存到当前用户中
        int cur_id=it->id;
        int cur_sex=it->sex;
        a->currentUser->log(cur_id,acc,pass,cur_sex,0,it->is_Boss); //account里面存是否版主

         QMessageBox::about(NULL,"Tips","User Log in suceessfully.");
         a->search();
         if(a->currentUser->isBoss==0)
         a->type=0;
         else
             a->type=2;
a->top->hide();
          a->setB->hide();
          a->show();
          a->show_user();

     }
     else
     {
         //Fail
         QMessageBox::warning(NULL,"Warning","Account or password is wrong!");
     }
}

void MainWindow::logIn2()
{

    mainBoard* a=new mainBoard;
 a->currentUser=new normalUser;
     QString acc=ui->lineEdit->text();
     QString pass=ui->lineEdit_2->text();

     std::vector<ACCOUNT>::iterator it=std::find(account.begin(),account.end(),ACCOUNT(acc,pass,0,0,0));
     if(it!=account.end()&&it->kind==1)
     {
            a->Users.assign(users.begin(),users.end());
         a->currentAdmin=new administrator;
         //successfully log in
         QMessageBox::about(NULL,"Tips","Administrator Log in Successfully");

         //根据查找结果得到管理员信息
         //存到当前管理员中
         int cur_id=it->id;
         int cur_sex=it->sex;
         a->currentAdmin->log(cur_id,acc,pass,cur_sex,0,0);

        a->type=1;
         a->show();
         a->show_user();
     }
     else
     {
         //Fail
         QString a=users[0].account;
         QString b=users[0].password;
         QMessageBox::warning(NULL,"Warning","Account or password is wrong!");
     }
}
void MainWindow::logIn3()
{
    try{ mainBoard* a=new mainBoard; a->currentUser=new Anonym;
        QMessageBox::about(NULL,"Tips","Anonym Logs in Successfully");
            a->type=3;
            a->show();
            a->show_user();}
    catch(...)
    {

    }




}

void MainWindow::signIn()
{

    a=new vicewindow;
    a->setMinimumHeight(300);
    a->setMinimumWidth(400);
    a->show();
    connect(a->pb,SIGNAL(clicked()),this,SLOT(signIn2()));
}

void MainWindow::signIn2()
{

    QString qacc=this->a->acc->text();
    QString qid=this->a->id_number->text();
    QString qpass=this->a->pass->text();
    connect(this,SIGNAL(signIn3(QString,QString,QString)),this->a,SLOT(signIn3(QString,QString,QString)));
            emit signIn3(qacc,qid,qpass);

}

void MainWindow::signIn3(QString acc, QString id, QString pass)
{
    int flag=0;
    for(int i=0;i<this->users.size();i++)
    {


        if(id!=users[i].id)
        {
            //新建的账户是可用的 即id是唯一的
            flag=1;
            int sex=0; //默认sex为0   还没设一个按钮选性别
            int num=users.size();
            normalUser x(id.toInt(),acc,pass,sex,0);
            this->users.push_back(x);

            this->account.push_back(ACCOUNT(users[num].account,users[num].password,0,users[num].id,users[num].sex));
            QMessageBox::warning(NULL,"注册成功!","欢迎使用");
            break;
        }
        else
        {
            QMessageBox::warning(NULL,"注册失败！","ID已被使用，请重新输入");
            break;
        }
    }


}
void MainWindow::inputFile()
{
    //加载系统数据
    QString systemName=QFileDialog::getOpenFileName(this,tr("加载系统文件"),"");
}

