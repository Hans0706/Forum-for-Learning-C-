#ifndef USER_H
#define USER_H
#include<QString>
#include<vector>
#include<QMessageBox>
#include<string.h>
#include<QDataStream>
#include<iostream>
#include<fstream>
using namespace std;
class user
{

 public:
   //function
    user();
    int id;
    int sex; //female=0 male=1 secret=2
    int po_num;
    int isBoss=0;//isBoss=1 BOSS
    void viewInfo();


    void viewPost();    //查看：查看所有帖子
    void set_acc(QString acc);
    void set_pass(QString pass);
    void set_id(int id);
    void set_sex(int sex);
    void set_boss(int boss);
    virtual log(int id, QString acc, QString pass, int sex, int po_num, int isBoss);
    virtual show_info(QString &acc,QString &pass,int &id,int &sex);
    QString account;
    QString password;
    QString get_account();
    QString get_pass();

    int get_boss();
    int get_id();
    int get_sex();
    friend ofstream &operator<<(ofstream &, user&);
       friend ifstream &operator>>(ifstream &,user &);

 private:
    //characters


    // and so on



};
class administrator:public user
{

public:

    administrator(int id,QString account,QString password,int sex);
    administrator(){}
     void set_acc(QString acc);
      void set_pass(QString pass);
      void set_id(int id);
      void set_sex(int sex);
    QString get_account();
    int get_id();
    QString get_pass();
    int get_sex();
    log(int id, QString acc, QString pass, int sex, int po_num, int isBoss);
    show_info(QString &acc, QString &pass, int &id, int &sex);
    void setBoss();
    void cancleBoss();
    friend ofstream &operator<<(ofstream &, administrator &);
       friend ifstream &operator>>(ifstream &,administrator &);

};

class normalUser:public user
{
public:
    normalUser(int id,QString name,QString password,int sex,int isBoss);
    normalUser(){}
     log(int id, QString acc,QString pass,int sex,int po_num,int isBoss);
    show_info(QString &acc, int isBoss, int &id, int &sex);
    int isBoss;         //是否是版主 版主=1 不是=0 初始为0

    void writePost();   //发帖 ：用户可以选择在某一板块下发帖
    void comment();     //评论：某一帖子下面评论

    void DeletPost();   //删帖：只能删除自己发布的没有评论的帖子

};

class Boss:public normalUser
{
  public:
    int board;  //1--C++ 2--JAVA  3--Python
    Boss(int id,QString name,QString password,int sex,int board);

    Boss(){}
    bool operator==(const Boss& ele)
    {
        return account==ele.account&&password==ele.password;
    }

    QString get_account();
    int get_id();
    QString get_pass();
    int get_sex();
    int get_board();

    void set_acc(QString acc);
    void set_pass(QString pass);
    void set_id(int id);
    void set_sex(int sex);
    void set_board(int board);
    void deletePosts();  //删帖：分管版块下的任意帖子
    friend ofstream &operator<<(ofstream &, Boss &);
       friend ifstream &operator>>(ifstream &,Boss &);
};

class Anonym:public normalUser
{
  public:

    Anonym(int id,QString name,QString password,int sex,int board);
    Anonym(){}

    QString get_pass();
    QString get_account();
    int get_id();
    int get_sex();
    int get_board();
    void set_acc(QString acc);
    void set_pass(QString pass);
    void set_id(int id);
    void set_sex(int sex);
};

#endif // USER_H
