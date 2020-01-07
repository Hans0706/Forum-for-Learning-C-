#include "user.h"
#include<fstream>
user::user()
{

}
Boss::Boss(int id, QString name, QString password, int sex, int board)
{
    this->id=id;
    this->account=name;
    this->password=password;
    this->sex=sex;
    this->board=board;
}
normalUser::normalUser(int id, QString name, QString password, int sex, int board)
{
    this->id=id;
    this->account=name;
    this->password=password;
    this->sex=sex;
    this->isBoss=isBoss;
}
administrator::administrator(int id,QString account,QString password,int sex)
{
    this->id=id;
           this->account=account;
           this->password=password;
           this->sex=sex;
}

QString administrator:: get_account()
{
    return this->account;
}
QString administrator:: get_pass()
{
    return this->account;
}
int administrator::get_id()
{
    return this->id;
}
int administrator::get_sex()
{
    return this->sex;
}
QString Boss:: get_account()
{
    return this->account;
}
QString Boss:: get_pass()
{
    return this->account;
}
int Boss::get_id()
{
    return this->id;
}
int Boss::get_sex()
{
    return this->sex;
}
int Boss::get_board()
{
    return this->board;
}
QString user:: get_account()
{
    return this->account;
}
QString user:: get_pass()
{
    return this->account;
}
int user::get_id()
{
    return this->id;
}
int user::get_sex()
{
    return this->sex;
}
int user::get_boss()
{
    return this->isBoss;
}
user::show_info(QString &acc,QString &pass,int &id,int &sex)
{
    acc=this->account;
    pass=this->password;
    id=this->id;
    sex=this->sex;
}
normalUser::show_info(QString &acc, int isBoss, int &id, int &sex)
{
    acc=this->account;
    isBoss=this->isBoss;
    id=this->id;
    sex=this->sex;
}


administrator::show_info(QString &acc, QString &pass, int &id, int &sex)
{
    acc=this->account;
    pass=this->password;
    id=this->id;
    sex=this->sex;
}
user::log(int id, QString acc, QString pass, int sex, int po_num, int isBoss)
{
    this->account=acc;
    this->password=pass;
}
normalUser::log(int id, QString acc, QString pass, int sex, int po_num, int isBoss)
{
    this->id=id;
    this->account=acc;
    this->password=pass;
    this->sex=sex;
    this->po_num=po_num;
    this->isBoss=isBoss;
}
administrator::log(int id, QString acc, QString pass, int sex, int x, int isBoss)
{
    this->id=id;
    this->account=acc;
    this->password=pass;
    this->sex=sex;
}
void user::set_acc(QString acc)
{
    this->account=acc;
}

void user::set_pass(QString pass)
{
    this->password=pass;
}

void user::set_id(int id)
{
     this->id=id;
}
void user::set_sex(int sex)
{
    this->sex=sex;
}
void user::set_boss(int boss)
{
     this->isBoss=boss;
}
void Boss::set_acc(QString acc)
{
    this->account=acc;
}

void Boss::set_pass(QString pass)
{
    this->password=pass;
}

void Boss::set_id(int id)
{
     this->id=id;
}
void Boss::set_sex(int sex)
{
    this->sex=sex;
}
void Boss::set_board(int board)
{
    this->board=board;
}
void administrator::set_acc(QString acc)
{
    this->account=acc;
}

void administrator::set_pass(QString pass)
{
    this->password=pass;
}

void administrator::set_id(int id)
{
     this->id=id;
}
void administrator::set_sex(int sex)
{
    this->sex=sex;
}
//*********************重载输入输出流********************
ofstream &operator <<(ofstream &out,user & ur)//写入文件
{
    out<<ur.get_id()<<'\n';
    out<<ur.get_account().toStdString()<<'\n';
    out<<ur.get_pass().toStdString()<<'\n';
    out<<ur.get_sex()<<'\n';
      out<<ur.get_boss()<<'\n';
    return out;

}

ofstream &operator <<(ofstream &out,Boss & bs)//写入文件
{
    out<<bs.get_id()<<'\n';
    out<<bs.get_account().toStdString()<<'\n';
    out<<bs.get_pass().toStdString()<<'\n';
    out<<bs.get_sex()<<'\n';
    out<<bs.get_board()<<'\n';



    return out;

}
ofstream &operator <<(ofstream &out,administrator & admin)//写入文件
{
    out<<admin.get_id()<<'\n';
    out<<admin.get_account().toStdString()<<'\n';
    out<<admin.get_pass().toStdString()<<'\n';
    out<<admin.get_sex()<<'\n';

    return out;
}

ifstream &operator >>(ifstream &in,user & ur)//读出文件
{
    string buffer;
    getline(in,buffer);
    ur.set_id(QString::fromStdString(buffer).toInt());

    getline(in,buffer);
    ur.set_acc(QString::fromStdString(buffer));
    getline(in,buffer);
    ur.set_pass(QString::fromStdString(buffer));
    getline(in,buffer);
    ur.set_sex(QString::fromStdString(buffer).toInt());
    getline(in,buffer);
    ur.set_boss(QString::fromStdString(buffer).toInt());

    return in;

}

ifstream &operator >>(ifstream &in,Boss & bs)//读出文件
{
    string buffer;
    getline(in,buffer);
    bs.set_id(QString::fromStdString(buffer).toInt());
    getline(in,buffer);
    bs.set_acc(QString::fromStdString(buffer));
    getline(in,buffer);
    bs.set_pass(QString::fromStdString(buffer));
    getline(in,buffer);
    bs.set_sex(QString::fromStdString(buffer).toInt());
    getline(in,buffer);
    bs.set_board(QString::fromStdString(buffer).toInt());

    return in;

}
ifstream &operator >>(ifstream &in,administrator & admin)//读出文件
{
    string buffer;
    getline(in,buffer);
    admin.set_id(QString::fromStdString(buffer).toInt());
    getline(in,buffer);
   admin.set_acc(QString::fromStdString(buffer));
    getline(in,buffer);
    admin.set_pass(QString::fromStdString(buffer));
    getline(in,buffer);
    admin.set_sex(QString::fromStdString(buffer).toInt());

     return in;

}
