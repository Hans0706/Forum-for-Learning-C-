#include "board.h"

board::board()
{

}

ofstream &operator <<(ofstream &out,board & bord)//写入文件
{

    out<<bord.posts.size()<<'\n';
    for(int i=0;i<bord.posts.size();i++)
    out<<bord.posts[i];

    return out;

}

ifstream &operator >>(ifstream &in,board & bord)//读出文件
{
    string buffer;

    int a;
    getline(in,buffer);
    bord.set_post_num(QString::fromStdString(buffer).toInt());
    a=QString::fromStdString(buffer).toInt();

    for(int i=0;i<a;i++)

    {
        Post c;
       in>>c;
       bord.posts.push_back(c);
    }







    return in;

}
