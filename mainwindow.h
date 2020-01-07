#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QAction>
#include <QMainWindow>
#include<qmainwindow.h>
#include<mainboard.h>
#include<post.h>
#include<vector>
#include<QMessageBox>
#include<user.h>
#include<QTcpServer>
#include<QTcpSocket>
#include<QLineEdit>
#include<QPushButton>
#include<QWidget>
#include<QAction>
#include<QMenu>
#include<QFileDialog>
#include<QFile>
#include<QTableWidget>
#include<QTableWidgetItem>
#define USER 0
#define ADMINE 1

using namespace std;

typedef struct account
{

    int id;
    int sex;
    int is_Boss;
    QString stringAcc;
    QString stringPassword;

    int kind;
    account(QString a,QString b,int c,int id,int sex)
    {
        this->stringAcc=a;
        this->stringPassword=b;
        this->kind=c;
        this->id=id;
        this->sex=sex;
    }
    bool operator==(const account& ele)
    {
        return stringAcc==ele.stringAcc&&stringPassword==ele.stringPassword;
    }
}ACCOUNT;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void getCurrentuser(QString name);
    void getCurrentAdmin(QString name);
    void setUser();
    //void showData();
private:
    Ui::MainWindow *ui;
    vector<QTcpSocket*> socket_client;
         QTcpServer *server;
         QTcpSocket *client_connection;
    void creatAction();
    void creatMenu();
    void creatToolbars();
    void creatWidget();


    mainBoard *b;   //主论坛
    //Post *c;        //帖子界面


    QAction login;
    vector<ACCOUNT> account;

    vector<normalUser> users;    //普通用户信息
//    vector<Boss> owner;         //版主信息
    vector<administrator> admin;//管理员信息
    QString* userNames;
    QAction* about_us;
       QAction* system_data;
       QAction* check_data;

       QMenu* about;
       QAction* contact;
       QMenu* data_bar;

//       //登陆论坛
//       normalUser* currentUser;
//       administrator* currentAdmin;
//       Boss* currentOwner;//版主





private slots:
    void logIn1();  //Normal Users
    void logIn2();  //Adminstrator
    void logIn3();  //Anonym
    void signIn();  //只有普通用户可以注册 管理员不可以注册
    void signIn2();
    void signIn3(QString acc,QString id,QString pass);
    void inputFile();
    void acceptConnection();
    void readClient();
#endif //


};
