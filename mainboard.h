#ifndef MAINBOARD_H
#define MAINBOARD_H
#include<QListWidget>
#include<QListWidgetItem>
#include<QTableWidgetItem>
#include <QWidget>
#include<user.h>
#include<board.h>
#include<post.h>

#include<QMouseEvent>
using namespace std;
//板块窗口
namespace Ui {
class mainBoard;
}

class mainBoard : public QWidget
{
    Q_OBJECT

public:
    explicit mainBoard(QWidget *parent = 0);
    ~mainBoard();

    void set_posts();
    int type;   //0=user 1=admin  Boss=2  anonymy=3
    void show_posts();
    void on_tableWidget_itemClicked(QTableWidgetItem *item);
    void show_user();
    QPushButton *top;
    QPushButton *setB;
    QPushButton *clearB;
void search();
void show_comments();
     //bool eventFilter(QObject *watched, QEvent *event);
    vector<board> boards;
    vector<user> Users;
    vector<Boss> owner;         //版主信息
    vector<administrator> admins;
    QString *names;
    int cur_board=0;
    //登陆论坛
    normalUser* currentUser;
    administrator* currentAdmin;
    Boss* currentOwner;//版主
    Post* currentPost;
private:
    Ui::mainBoard *ui;

    void save_system();
    void get_system(QString filename);
    void get_users_data();
    void change_por(QString filename);
private slots:
    void to_post();
    void goto_post(QTableWidgetItem *item);
    //void write_comment();
    void write_comment1();
   // void delet_comment();
    void delet_post();
    void deleting();
    void clear_post();
    void set_Boss();    //设置版主啊啊
    void set_Boss1();
    void show_Boss(int);   //写到set-BOSS里面了
    void delete_Boss(); //撤销版主啊啊啊
    void show_cur_boss(int b);
    void delet_comment(QTableWidgetItem *item);
    void personal();
    void top_post();
void log_out();
   // void set_Boss2();
  //  void post_info(int a);
};

#endif // MAINBOARD_H
