#include "mainboard.h"
#include "ui_mainboard.h"
#include<post.h>
#include<board.h>
#include<pe.h>
#include<QWidget>
#include<QFileDialog>
#include<QInputDialog>
#include<QLayout>
#include<QMenu>
#include<QMenuBar>
#include<QApplication>
#include<QTableWidget>
#include<QTableWidgetItem>
#include<QDateTime>
#include<QTime>
#include<QImage>
#include<QEvent>
#include<QFile>
#include<QString>
using namespace std;
mainBoard::mainBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainBoard)
{
    ui->setupUi(this);

    //    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
//    ui->tableWidget->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Stretch);
//    ui->tableWidget->horizontalHeader()->setSectionResizeMode(3,QHeaderView::ResizeToContents);


      //槽函数连接ing

     int a1=QMessageBox::warning(NULL,tr("choose mode"),tr("是否要加载历史数据"),QMessageBox::Yes|QMessageBox::No);
        if(a1==QMessageBox::Yes)
       {
            this->get_users_data();//get system


        }
        else
        {
            Boss a1(2016211001,"111","111",0,1);
            owner.push_back(a1);
            set_posts();
        }
     this->show_posts();//show the posts
        this->show_cur_boss(0);

}

mainBoard::~mainBoard()
{
    delete ui;
}
void mainBoard::personal()
{

    try{
        QFileInfo fileinfo;
        QString a=QFileDialog::getOpenFileName(NULL,tr("打开文件"));
        fileinfo = QFileInfo(a);
        QString t=fileinfo.suffix();
        QString c="打开失败";
          if(a.size()==0||(t!="jpg"&&t!="png"))
              throw c;
          else
          change_por(a);
    }
    catch(QString str)
    {
         QFileInfo fileinfo;
        QMessageBox::warning(NULL,tr("打开失败"),str);
               QString b=QFileDialog::getOpenFileName(NULL,tr("请重新打开文件"));

               change_por(b);
    }

}
void mainBoard::change_por(QString filename)
{
    QImage Image;
    Image.load(filename);
    QPixmap pixmap = QPixmap::fromImage(Image);

            int wid=ui->label_3->width();
            int height=ui->label_3->height();
            if(! ( Image.load(filename)  ) ) //加载图像
            {
                QMessageBox::information(this,
                                         tr("打开图像失败"),
                                         tr("打开图像失败!"));

                return;
            }
          // QPixmap fitpixmap = pixmap.scaled(wid, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
           QPixmap fitpixmap = pixmap.scaled(wid, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
            ui->label_3->setPixmap(fitpixmap);
}
void mainBoard::search()
{
    std::vector<Boss>::iterator it=std::find(owner.begin(),owner.end(),Boss(0,currentUser->account,currentUser->password,0,0));
    if(it!=owner.end())
    {

        currentUser->isBoss=it->board;
    }
}

void mainBoard::top_post()
{
    bool ok;

    int num;
   int index=this->ui->tabWidget->currentIndex();
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                         tr("请输入想置顶的帖子"), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    if (ok && !text.isEmpty())
        num=text.toInt();
    this->boards[index].posts[num-1].rank=1;
    std::sort(boards[index].posts.begin(),boards[index].posts.end());
    //TODO 智能把置顶的放到最底下什么鬼
//std::reverse(boards[index].posts.begin(),boards[index].posts.end());
    show_posts();

}
void mainBoard::goto_post(QTableWidgetItem *item)
{
    a=new pe;
    currentPost=new Post;
int bo=this->ui->tabWidget->currentIndex(); //当前所在版块

    int i=item->tableWidget()->currentRow();
    this->currentPost->num=i;

currentPost->set_author(this->boards[bo].posts[i].get_author());
currentPost->com_num=this->boards[bo].posts[i].com_num;
    a->cur_post->setText(this->boards[bo].posts[i].get_text());
    a->comment1->clear();

    if(this->type==3)
    {
        a->text->hide();
        a->pla->hide();
        a->lb2->hide();
        a->lb3->hide();
        a->sent->hide();

       a->lb4->show();
    }
    else
        a->lb4->hide();
    a->show();

   connect(a->sent,SIGNAL(clicked()),this,SLOT(write_comment1()));  //这儿的参数有问题 传不进去 得重写
   if(this->type==1)
   connect(a->comment1,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(delet_comment(QTableWidgetItem*)));
   show_comments();
    delet_post();

}

void mainBoard::to_post()
{//发帖
    int bo=this->ui->tabWidget->currentIndex(); //当前所在版块
    if(this->type!=1)
    {
        QString b=currentUser->account;
        QDateTime current_date_time =QDateTime::currentDateTime();
    int num=boards[bo].posts.size();
       Post a(ui->lineEdit->text(),ui->textEdit->toPlainText(),b,QString( current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd")));
        this->boards[bo].posts.push_back(a);
//       currentPost==new Post;
//       currentPost->set_author(b);
       boards[bo].posts[num].com_num=0;
        this->show_posts();
    }
    else
         QMessageBox::about(NULL,"Tips","Sorry! You do not have permissions to post.");

}

void mainBoard::show_user() //显示当前登陆者
{
    QString acc1;
    int id1;
    QString pass1;
    int isBoss1;
    int sex1;
    if(this->type==0||this->type==2)
    {
        ui->label_12->hide();
        //虚函数的使用
        currentUser->show_info(acc1,isBoss1,id1,sex1);
        QString s = QString("%1").arg(id1);
        ui->label_5->setText(acc1);
        ui->label_7->setText(s);
        ui->label_9->setText("0");
        ui->label_11->setText("0");
        if(sex1==0)
        {
            QImage Image;
            Image.load("C:\\Users\\19146\\Desktop\\demo\\1.0_version\\girl.png");
            QPixmap pixmap = QPixmap::fromImage(Image);

                    int wid=ui->label_3->width();
                    int height=ui->label_3->height();
                    if(! ( Image.load("C:\\Users\\19146\\Desktop\\demo\\1.0_version\\girl.png")  ) ) //加载图像
                    {
                        QMessageBox::information(this,
                                                 tr("打开图像失败"),
                                                 tr("打开图像失败!"));

                        return;
                    }
                  // QPixmap fitpixmap = pixmap.scaled(wid, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
                   QPixmap fitpixmap = pixmap.scaled(wid, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
                    ui->label_3->setPixmap(fitpixmap);
        }
        else if(sex1==1)
        {
            QImage Image;
            Image.load("C:\\Users\\19146\\Desktop\\demo\\1.0_version\\boy.png");
            QPixmap pixmap = QPixmap::fromImage(Image);

                    int wid=ui->label_3->width();
                    int height=ui->label_3->height();
                    if(! ( Image.load("C:\\Users\\19146\\Desktop\\demo\\1.0_version\\boy.png")  ) ) //加载图像
                    {
                        QMessageBox::information(this,
                                                 tr("打开图像失败"),
                                                 tr("打开图像失败!"));

                        return;
                    }
                  // QPixmap fitpixmap = pixmap.scaled(wid, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
                   QPixmap fitpixmap = pixmap.scaled(wid, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
                    ui->label_3->setPixmap(fitpixmap);
        }


    }
    else if(this->type==3)
    {
        ui->label->hide();
        ui->label_2->hide();
        ui->lineEdit->hide();
        ui->textEdit->hide();
        ui->pushButton->hide();
        ui->pushButton_2->hide();
        ui->pushButton_3->hide();
        ui->pushButton_4->hide();
        ui->pushButton_6->hide();
        ui->label_12->show();
        ui->label_5->setText("****");
        ui->label_7->setText("****");
        ui->label_9->setText("****");
        ui->label_11->setText("****");
        QImage Image;
        Image.load("C:\\Users\\19146\\Desktop\\demo\\1.0_version\\anony.png");
        QPixmap pixmap = QPixmap::fromImage(Image);

                int wid=ui->label_3->width();
                int height=ui->label_3->height();
                if(! ( Image.load("C:\\Users\\19146\\Desktop\\demo\\1.0_version\\anony.png")  ) ) //加载图像
                {
                    QMessageBox::information(this,
                                             tr("打开图像失败"),
                                             tr("打开图像失败!"));

                    return;
                }
              // QPixmap fitpixmap = pixmap.scaled(wid, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
               QPixmap fitpixmap = pixmap.scaled(wid, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
                ui->label_3->setPixmap(fitpixmap);
    }
else
    {
         ui->label_12->hide();
currentAdmin->show_info(acc1,pass1,id1,sex1);
        QString s = QString("%1").arg(id1);
        ui->label_5->setText(acc1);
        ui->label_7->setText(s);
        ui->label_9->setText("0");
        ui->label_11->setText("0");
        if(sex1==0)
        {
            QImage Image;
            Image.load("C:\\Users\\19146\\Desktop\\demo\\1.0_version\\girl.png");
            QPixmap pixmap = QPixmap::fromImage(Image);

                    int wid=ui->label_3->width();
                    int height=ui->label_3->height();
                    if(! ( Image.load("C:\\Users\\19146\\Desktop\\demo\\1.0_version\\girl.png")  ) ) //加载图像
                    {
                        QMessageBox::information(this,
                                                 tr("打开图像失败"),
                                                 tr("打开图像失败!"));

                        return;
                    }
                  // QPixmap fitpixmap = pixmap.scaled(wid, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
                   QPixmap fitpixmap = pixmap.scaled(wid, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
                    ui->label_3->setPixmap(fitpixmap);
        }
        else if(sex1==1)
        {
            QImage Image;
            Image.load("C:\\Users\\19146\\Desktop\\demo\\1.0_version\\LYJ.png");
            QPixmap pixmap = QPixmap::fromImage(Image);

                    int wid=ui->label_3->width();
                    int height=ui->label_3->height();
                    if(! ( Image.load("C:\\Users\\19146\\Desktop\\demo\\1.0_version\\LYJ.png")  ) ) //加载图像
                    {
                        QMessageBox::information(this,
                                                 tr("打开图像失败"),
                                                 tr("打开图像失败!"));

                        return;
                    }
                  // QPixmap fitpixmap = pixmap.scaled(wid, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
                   QPixmap fitpixmap = pixmap.scaled(wid, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
                    ui->label_3->setPixmap(fitpixmap);
        }
    }


}
void mainBoard::show_posts()
{// 把帖子显示在tablewidget上

    for(int i=0;i<this->boards[0].posts.size();i++)
    {
       ui->tableWidget->setItem(i,0,new QTableWidgetItem(this->boards[0].posts[i].get_title()));
       ui->tableWidget->setItem(i,1,new QTableWidgetItem(this->boards[0].posts[i].get_author()));
       ui->tableWidget->setItem(i,2,new QTableWidgetItem(this->boards[0].posts[i].get_time()));
    }
    for(int i=0;i<this->boards[1].posts.size();i++)
    {
       ui->tableWidget_2->setItem(i,0,new QTableWidgetItem(this->boards[1].posts[i].get_title()));
       ui->tableWidget_2->setItem(i,1,new QTableWidgetItem(this->boards[1].posts[i].get_author()));
       ui->tableWidget_2->setItem(i,2,new QTableWidgetItem(this->boards[1].posts[i].get_time()));
    }
    for(int i=0;i<this->boards[2].posts.size();i++)
    {
       ui->tableWidget_3->setItem(i,0,new QTableWidgetItem(this->boards[2].posts[i].get_title()));
       ui->tableWidget_3->setItem(i,1,new QTableWidgetItem(this->boards[2].posts[i].get_author()));
       ui->tableWidget_3->setItem(i,2,new QTableWidgetItem(this->boards[2].posts[i].get_time()));
    }

}
 void mainBoard::set_posts()
 {//初始化帖子
     //初始化版块一及帖子(*^▽^*)
  QDateTime current_date_time =QDateTime::currentDateTime();
     board * a =new board;
     Post  b(QString("test"),QString("this is a message for test."),QString("halo"),QString( current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd")));
     Post  c(QString("test2"),QString("this is another test."),QString("kiki"),QString( current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd")));
     Post  d(QString("test3"),QString("this is the final test."),QString("XIa"),QString( current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd")));
     a->posts.push_back(b);
      a->posts.push_back(c);
      a->posts.push_back(d);

     this->boards.push_back(*a);

       //初始化版块二及帖子(*^▽^*)
      board * a2 =new board;
      Post  b2(QString("test"),QString("this is a message for test."),QString("halo"),QString( current_date_time.toString("yyyy.MM.dd hh:mm:ss")));
      Post  c2(QString("test2"),QString("this is another test."),QString("kiki"),QString( current_date_time.toString("yyyy.MM.dd hh:mm:ss")));
      Post  d2(QString("test3"),QString("this is the final test."),QString("XIa"),QString( current_date_time.toString("yyyy.MM.dd hh:mm:ss")));
      a2->posts.push_back(b2);
       a2->posts.push_back(c2);
       a2->posts.push_back(d2);

      this->boards.push_back(*a2);

        //初始化版块三及帖子(*^▽^*)
       board * a3 =new board;
       Post  b3(QString("test"),QString("this is a message for test."),QString("halo"),QString( current_date_time.toString("yyyy.MM.dd hh:mm:ss")));
       Post  c3(QString("test2"),QString("this is another test."),QString("kiki"),QString( current_date_time.toString("yyyy.MM.dd hh:mm:ss")));
       Post  d3(QString("test3"),QString("this is the final test."),QString("XIa"),QString( current_date_time.toString("yyyy.MM.dd hh:mm:ss")));
       a3->posts.push_back(b3);
        a3->posts.push_back(c3);
        a3->posts.push_back(d3);

       this->boards.push_back(*a3);


      //初始化板块一帖子的评论(*^▽^*)
      Comment x(QString("人间有真情"),QString("Elena"),QString( current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd")),0);
      Comment y(QString("人间有真爱"),QString("Stefan"),QString( current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd")),0);
      boards[0].posts[0].comments.push_back(x);
      boards[0].posts[0].comments.push_back(y);
         boards[0].posts[0].com_num=2;
      Comment z1(QString("人间MEI有真情"),QString("Damon"),QString( current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd")),0);
      Comment z2(QString("人间MEI有真爱"),QString("Carol"),QString( current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd")),0);
      boards[0].posts[1].comments.push_back(z1);
      boards[0].posts[1].comments.push_back(z2);

     boards[0].posts[1].com_num=2;
 }


void mainBoard::write_comment1()//m记录第几个帖子下面的 这个参数得重写 函数好好想
{
     int bo=this->ui->tabWidget->currentIndex(); //当前所在版块
    if(currentPost->get_author()==currentUser->account)
        a->delet->hide();

    currentUser->po_num++;        //开始写帖子
    int m=this->currentPost->num;
     QString s = QString("%1").arg(currentUser->id);
      QString b=currentUser->account;
      QDateTime current_date_time =QDateTime::currentDateTime();
      QString pla=a->pla->text();
      int i=pla.toInt();
      Comment new1(a->text->toPlainText(),currentUser->account,QString( current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd")),i);
    this->boards[bo].posts[m].comments.push_back(new1);
currentPost->com_num=boards[bo].posts[m].comments.size();
      this->show_comments();
}

void mainBoard::show_comments() //显示评论
{
    //子窗口的show
    int bo=this->ui->tabWidget->currentIndex(); //当前所在版块
    int y=this->currentPost->num;
    // 把帖子显示在tablewidget上
//    a->comment1->resizeColumnsToContents();
a->comment1->setEditTriggers(QAbstractItemView::NoEditTriggers);
a->comment1->setSelectionBehavior(QAbstractItemView::SelectRows);
        for(int i=0;i<this->boards[bo].posts[y].comments.size();i++)
        {
            int pla=this->boards[bo].posts[y].comments[i].get_pla();
            QString c1=QString::number(pla);
            QString c=QString("回复")+c1+QString("楼");
           a->comment1->setItem(i,0,new QTableWidgetItem(this->boards[bo].posts[y].comments[i].get_author()));
           if(this->boards[bo].posts[y].comments[i].rpl_flo==0)
           a->comment1->setItem(i,1,new QTableWidgetItem(QString("回复原贴")));
    else
           {

               a->comment1->setItem(i,1,new QTableWidgetItem(c));


           }
               a->comment1->setItem(i,2,new QTableWidgetItem(this->boards[bo].posts[y].comments[i].get_text()));
           a->comment1->setItem(i,3,new QTableWidgetItem(this->boards[bo].posts[y].comments[i].get_time()));
        }


}

void mainBoard::delet_post()
{
//.... logic
//    if((this->type==0&&currentPost->get_author()!=currentUser->account)||
//            (this->type==0&&currentPost->get_author()==currentUser->account&&currentPost->com_num==0))
//    {
//        a->delet->hide();
//    }
    int m=this->ui->tabWidget->currentIndex();
    if(this->type==1||(this->type==2&&currentUser->isBoss==m+1)||(currentPost->get_author()==currentUser->account&&currentPost->com_num==0))
    {


            {
            a->delet->show();
    connect(a->delet,SIGNAL(clicked()),this,SLOT(deleting()));
        }
    }
    else
    {
        a->delet->hide();
    }
}

void mainBoard::deleting()
{
     int m=this->ui->tabWidget->currentIndex(); //当前所在版块
    int n=this->currentPost->num;
    this->boards[m].posts.erase(boards[m].posts.begin()+n);
    QMessageBox::about(NULL,"Tips","Deleting the post Successfully");
    a->close();

        //刷新一下界面
    ui->tableWidget->clear();
    for(int i=0;i<this->boards[m].posts.size();i++)
    {
       ui->tableWidget->setItem(i,0,new QTableWidgetItem(this->boards[m].posts[i].get_title()));
       ui->tableWidget->setItem(i,1,new QTableWidgetItem(this->boards[m].posts[i].get_author()));
       ui->tableWidget->setItem(i,2,new QTableWidgetItem(this->boards[m].posts[i].get_time()));
    }


}
void mainBoard::clear_post()
{
    ui->lineEdit->clear();
    ui->textEdit->clear();
}
void mainBoard::set_Boss()
{
       s=new setting;
       s->x1->setCurrentIndex(0);
        s->cancel->hide();
           for(int i=0;i<this->Users.size();i++)
      {
               s->renM->setItem(i,0,new QTableWidgetItem(this->Users[i].get_account()));
               for(int j=0;j<this->owner.size();j++)
              {

                if(Users[i].account==owner[j].account)
                  Users[i].isBoss=1;
              }
               if(Users[i].isBoss!=0)
               {
                     s->renM->item(i,1)->setFlags( s->renM->item(i,0)->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
                     s->renM->item(i,1)->setCheckState(Qt::Checked);
               }
       }
       s->show();

   connect(s->set,SIGNAL(clicked()),this,SLOT(set_Boss1()));

     connect(s->x1,SIGNAL(currentChanged(int)),this,SLOT(show_Boss(int)));
}
//没写完传参的问题还是
void mainBoard::set_Boss1()
{
    int num;
    QString name;
    QString str;
    QString sen;
for(int i=0;i<this->Users.size();i++)
 {
    if(Users[i].isBoss==0&&s->renM->item(i,1)->checkState()==Qt::Checked)
    {
        //s->renM->item(i,0)->setTextColor(Qt::green);
        if(s->box->currentIndex()==0) {num=1;str="C++";}
        else if(s->box->currentIndex()==1) {num=2;str=("JAVA");}
        else {num=3;str=("Python");}

        s->renM->item(i,1)->setFlags( s->renM->item(i,0)->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);

        name=Users[i].get_account()+QString(".");
        Users[i].isBoss=i+1;
         Boss a1(Users[i].id,Users[i].account,Users[i].password,Users[i].sex,num);
        owner.push_back(a1);
        sen=name+QString("被任命为")+str+QString("版块版主啦！");
          QMessageBox::about(NULL,"Tips",sen);

    }
    if(this->Users[i].isBoss==0)
    {

        s->renM->item(i,1)->setCheckState(Qt::Unchecked);
    }

 }

int num1=this->ui->tabWidget->currentIndex();
this->ui->label_14->clear();
        show_cur_boss(num1);



}
 //TODO  撤销版主 显示当前版主 还有就是一个人做多个版主
void mainBoard::show_Boss(int index)
{
    if(index==1)
    {
        s->cancel->show();
        s->box->hide();
        s->set->hide();
        for(int i=0;i<owner.size();i++)
        {
            if(owner[i].board==1) s->quX->setItem(0,0,new QTableWidgetItem(this->owner[i].get_account()));
            else if(owner[i].board==2) s->quX->setItem(1,0,new QTableWidgetItem(this->owner[i].get_account()));
             else if(owner[i].board==3) s->quX->setItem(2,0,new QTableWidgetItem(this->owner[i].get_account()));
        }
    }
        else if(index==0)
        {
        s->cancel->hide();
            s->box->show();
            s->set->show();
            for(int i=0;i<this->Users.size();i++)
            {
                s->renM->setItem(i,0,new QTableWidgetItem(this->Users[i].get_account()));
            }
        }


     connect(s->cancel,SIGNAL(clicked()),this,SLOT(delete_Boss()));
}

void mainBoard::delete_Boss()
{
    QString name[10];
    for(int m=0;m<3;m++)
    {
        name[m]="*";
    }
    QString bod[10];
    QString sen;


  for(int i=0;i<3;i++)
  {
      if(s->quX->item(i,1)->checkState()==Qt::Checked)
      {
          s->quX->item(i,1)->setFlags( s->quX->item(i,0)->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
          s->quX->item(i,1)->setCheckState(Qt::Unchecked);
          if(i==0)
          {
              name[i]=s->quX->item(i,0)->text();
              bod[i]="C++";
             for(int m=0;m<3;m++)
             {
                 if(owner[m].board==1)
                     owner[m].board=0;

             }
          }
          else if(i==1)
          {
              name[i]=s->quX->item(i,0)->text();
              bod[i]="JAVA";
              for(int m=0;m<3;m++)
              {
                  if(owner[m].board==2)
                      owner[m].board=0;
              }

          }
         else if(i==2)
          {
              name[i]=s->quX->item(i,0)->text();
              bod[i]="Python";
              for(int m=0;m<3;m++)
              {
                  if(owner[m].board==3)
                      owner[m].board=0;
              }
          }
      }

  }
  for(int i=0;i<3;i++)
  {
      if(name[i]!="*")
  {
          sen=QString("经理事会决定，已撤销")+name[i]+QString("在")+bod[i]+QString("的版主职务");
 QMessageBox::about(NULL,"Tips",sen);
  }

   }

    show_Boss(0);
  show_cur_boss(0);


}

void mainBoard::show_cur_boss(int b)        //记下点撤销的时候在哪个版面传进来的当前在哪个界面
{

    this->ui->label_14->clear();
    for(int i=0;i<owner.size();i++)
    {
        if(owner[i].board==b+1)
            this->ui->label_14->setText(owner[i].account);
    }
}

void mainBoard::log_out()
{
    if(QMessageBox::Ok ==QMessageBox::warning(this,"温馨提示","是否要离开论坛?",QMessageBox::Ok,QMessageBox::No))
    {
    QMessageBox::information(this,"温馨提示","注销");
    save_system();
    if(a!=NULL)
    a->close();
    if(s!=NULL)
    s->close();
    this->close();

    }
    else
    {
    QMessageBox::information(this,"温馨提示","不注销");

    }



}

void mainBoard::delet_comment(QTableWidgetItem *item)
{
    int m=this->ui->tabWidget->currentIndex();
    int n=this->currentPost->num;
    int i=item->tableWidget()->currentRow();
    if(this->type==1)
    {


          a->delet_comment(i);
            this->boards[m].posts[n].comments.erase(boards[m].posts[n].comments.begin()+n);

    }


    else
        {

        }
    }

//**************加载用户信息***************
void mainBoard::get_users_data()
{
    try{
        QFileInfo fileinfo;

        QString a=QFileDialog::getOpenFileName(NULL,tr("打开文件"));
         fileinfo = QFileInfo(a);
         QString t=fileinfo.suffix();
         QString c="打开失败";
          if(a.size()==0||t!="txt")
              throw c;
          else
           get_system(a);
    }
    catch(QString str)
    {
        QMessageBox::warning(NULL,tr("打开失败"),str);
               QString b=QFileDialog::getOpenFileName(NULL,tr("请重新打开文件"));
              get_system(b);
    }
}


//***************信息存盘*******************
void mainBoard::save_system()
{
    ofstream file("C:\\Users\\19146\\Desktop\\demo\\1.0_version\\BOSS.txt");
    if(!file.is_open())
        QMessageBox::warning(NULL,"warning","未打开文件");
    file<<(int)owner.size()<<'\n';//版主用户
    for(int i=0;i<owner.size();i++)
    {
        file<<this->owner[i];


    }
    file<<(int )Users.size()<<'\n';//用户
    for(int i=0;i<Users.size();i++)
    {
        file<<this->Users[i];
    }

    file<<(int )admins.size()<<'\n';//管理员
    for(int i=0;i<admins.size();i++)
    {
        file<<this->admins[i];
    }

    file<<(int )boards.size()<<'\n';//版块
    for(int i=0;i<boards.size();i++)
    {
        file<<this->boards[i];
    }

    file.close();
}

//*****************信息读盘*******************
void mainBoard::get_system(QString filename)
{
    ifstream file1(filename.toStdString());
    if(filename!=NULL)
{


    try{
            char ss[100];
            int num=0;
        file1>>num;
        QString c="文件读取错误";
          if(num<0)
              throw c;
          else{
              file1.getline(ss,100);
              for(int i=0;i<num;i++)
              {
                 Boss a;
                 file1>>a;
                 owner.push_back(a);


              }
              file1>>num;
              file1.getline(ss,100);
              for(int i=0;i<num;i++)
              {
                  user b;
                  file1>>b;
                  Users.push_back(b);
              }

              file1>>num;
              file1.getline(ss,100);
              for(int i=0;i<num;i++)
              {
                  administrator d;
                  file1>>d;
                  admins.push_back(d);
              }

              file1>>num;
              file1.getline(ss,100);
              for(int i=0;i<num;i++)
              {
                  board c;
                  file1>>c;
                  boards.push_back(c);
              }


              file1.close();
          }

    }
    catch(QString str)
    {
        QMessageBox::warning(NULL,tr("打开失败"),str);
        QString b=QFileDialog::getOpenFileName(NULL,tr("请重新打开文件"));
              get_system(b);

    }

}
else
{
   set_posts();
}

}
