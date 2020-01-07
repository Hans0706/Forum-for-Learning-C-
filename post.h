#ifndef POST_H
#define POST_H
#include<QWidget>
#include<QString>
#include<vector>
#include<QMessageBox>
#include<QDataStream>
//#inlcude<QTextBrowser>

#include<fstream>
using namespace std;

class Comment
{
public:

    Comment(QString text,QString author,QString time,int rpl_flo);
    Comment(){}
    QString get_text();//评论内容
    QString get_time();//评论时间
    QString get_author();//评论员

    int get_pla();  //回复
    void set_text(QString a);
    void set_time(QString t);
    void set_author(QString n);
    void set_pla(int f);
    int rpl_flo;

    friend ofstream &operator<<(ofstream &, Comment &);
       friend ifstream &operator>>(ifstream &,Comment &);
private:
    QString author;
    QString time;
    QString text;


};


typedef struct post
{
    QString poster;
    QString time;
    QString text;
    QString title;

    post(QString name,QString times,QString texts,QString titles)
    {
        this->poster=name;
        this->time=times;
        this->text=texts;
        this->title=titles;
    }
    bool operator ==(const post ele)
    {
        if(ele.poster==this->poster)
            return 1;
        else
            return 0;
    }


}POST;
//帖子类
class Post
{
public:
    QString text;
    Post();
    friend bool operator <(const Post& a,const Post& b)
    {
        return a.rank<b.rank;
    }

     int rank=2;
    void set_title(QString tl);
    void set_text(QString a);
    void set_time(QString t);
    void set_author(QString n);
   void set_com_num(int n);
    Post(QString title,QString text, QString author,QString time);
    QString get_time();
    QString get_text();
    QString get_title();
    QString get_author();
    int get_com_num();
    vector<Comment> comments;   //存储评论
    int num;        //存一下第几个帖子
    int com_num=0;
    friend ofstream &operator<<(ofstream &,Post&);
       friend ifstream &operator>>(ifstream &,Post &);
private:
    int id;
    QString contet;
    QString title;
    QString time;
    QString author;



};


#endif // POST_H
