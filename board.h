#ifndef BOARD_H
#define BOARD_H
#include <QString>
#include <post.h>
using namespace std;
//板块类
class board
{
public:
    board();
    int post_num;
    int get_post_num(){return this->posts.size();}
    void set_post_num(int n){this->post_num=n;}
    vector<Post> posts;//存储帖子
    friend ofstream &operator<<(ofstream &, board &);
       friend ifstream &operator>>(ifstream &,board &);
private:
    QString name;
};

#endif // BOARD_H
