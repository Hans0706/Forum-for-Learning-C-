
#include"post.h"

Comment::Comment(QString text,QString author,QString time,int rpl_flo)
{
    this->author=author;
    this->text=text;
    this->time=time;

    this->rpl_flo=rpl_flo;
}

QString Comment::get_author()
{
    return this->author;
}

QString Comment::get_text()
{
    return this->text;
}

QString Comment::get_time()
{
    return this->time;
}

int Comment::get_pla()
{
    return this->rpl_flo;
}

void Comment::set_text(QString a){this->text=a;}
void Comment::set_time(QString t){this->time=t;}
void Comment::set_author(QString n){this->author=n;}
void Comment::set_pla(int f){this->rpl_flo=f;}
//*********************重载输入输出流********************
ofstream &operator <<(ofstream &out,Comment & co)//写入文件
{
   out<<co.get_text().toStdString()<<'\n';
    out<<co.get_author().toStdString()<<'\n';
    out<<co.get_time().toStdString()<<'\n';
    out<<co.get_pla()<<'\n';

    return out;

}

ifstream &operator >>(ifstream &in,Comment & co)//读出文件
{
    string buffer;
    getline(in,buffer);

   co.set_text(QString::fromStdString(buffer));
    getline(in,buffer);
    co.set_author(QString::fromStdString(buffer));
    getline(in,buffer);
    co.set_time(QString::fromStdString(buffer));
    getline(in,buffer);
    co.set_pla(QString::fromStdString(buffer).toInt());

     return in;

}
