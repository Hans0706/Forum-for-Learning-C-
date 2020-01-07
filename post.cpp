#include "post.h"
#include"QTime"
#include"QDate"
Post::Post(QString title,QString text, QString author,QString time)
{
    this->title=title;
    this->text=text;
    this->author=author;
    this->time=time;
}
Post::Post()
{

}

QString Post::get_text()
{
    return this->text;
}
QString Post::get_title()
{
    return this->title;

}
QString Post::get_author()
{
    return this->author;
}

QString Post::get_time()
{
    return this->time;
}
void Post::set_text(QString a){this->text=a;}
void Post::set_time(QString t){this->time=t;}
void Post::set_author(QString n){this->author=n;}
void Post::set_title(QString tl){this->title=tl;}
//*********************重载输入输出流********************
ofstream &operator <<(ofstream &out,Post & co)//写入文件
{
    out<<co.get_title().toStdString()<<'\n';
   out<<co.get_text().toStdString()<<'\n';
    out<<co.get_author().toStdString()<<'\n';
    out<<co.get_time().toStdString()<<'\n';

     out<<co.comments.size()<<'\n';
     for(int i=0;i<co.comments.size();i++)
        out<<co.comments[i];
    return out;

}

ifstream &operator >>(ifstream &in,Post & co)//读出文件
{
    string buffer;
int a;
    getline(in,buffer);

    co.set_title(QString::fromStdString(buffer));
     getline(in,buffer);
   co.set_text(QString::fromStdString(buffer));
    getline(in,buffer);
    co.set_author(QString::fromStdString(buffer));
    getline(in,buffer);
    co.set_time(QString::fromStdString(buffer));
    getline(in,buffer);
    a=QString::fromStdString(buffer).toInt();
    for(int i=0;i<a;i++)

    {
       Comment c;
       in>>c;
       co.comments.push_back(c);
    }
     return in;

}
