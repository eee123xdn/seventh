#include "piggame.h"
#include "ui_piggame.h"
#include<QPushButton>
#include"page1.h"
#include"page2.h"
#include"page3.h"
#include"page4.h"
#include"page5.h"
#include"config.h"
#include"store.h"
#include"honor.h"
#include<QTime>
#include<QTimer>
#include<QString>
#include<QDebug>
QTimer* my_timer1=new QTimer();//设置一个Qtimer
QTimer* my_timer2=new QTimer();//设置一个Qtimer
PigGame::PigGame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PigGame)
{
    ui->setupUi(this);
    PigGame::new_game();
    QTimer* my_timer=new QTimer();//设置一个Qtimer
    connect(my_timer,SIGNAL(timeout()),this,SLOT(goout()));//将QTimer绑定给goout函数
    my_timer->start(90000);//开始1000毫秒执行一次goout
    connect(my_timer1,SIGNAL(timeout()),this,SLOT(illmode()));//将QTimer1绑定给illmode函数
    my_timer1->start(1000);//开始1000毫秒执行一次goout
    connect(my_timer2,SIGNAL(timeout()),this,SLOT(healthemode()));//将QTimer2绑定给healthemode函数
}

PigGame::~PigGame()
{
    delete ui;

}
void PigGame::new_game()
{
    p = head;
    //350hua or bai
    for(int i = 0;i<70;i++)
    {
        for(int K=0;K<5;K++)
        {
            qsrand(QTime(0,0,0).secsTo(QTime::currentTime())+K*10000+i);
            p->data[K][0]=qrand()%2+1;

            //p->data[K][1] = 200;
            p->data[K][2] = 1;
            p->data[K][3] = 0;
            p->data[K][4] = 0;
        }
        for(int K=5;K<10;K++)         //每个猪圈后面五个位置没装，种类定为4
        {
            p->data[K][0] = 4;
            p->data[K][1] = 0;
            p->data[K][2] = 0;
            p->data[K][3] = 0;
            p->data[K][4] = 0;
        }
        p->number=5;
        p->flag=0;
        p->N = new Node();
        p=p->N;
    }
    //150hei
    for(int i = 70;i<100;i++)
    {
        p->type = true;
        for(int K=0;K<5;K++)
        {
            p->data[K][0] = 3;
            p->data[K][2] = 1;
            p->data[K][3] = 0;
            p->data[K][4] = 0;
        }
        for(int K=5;K<10;K++)         //每个猪圈后面五个位置没装，种类定为4
        {
            p->data[K][0] = 4;
            p->data[K][1] = 0;
            p->data[K][2] = 0;
            p->data[K][3] = 0;
            p->data[K][4] = 0;
        }
        p->number=5;
        p->flag=0;
        p->N = new Node();
        p=p->N;
    }
    p=head;
    for(int i = 0;i<100;i++)
    {

        for(int K=0;K<5;K++)
        {


                    qsrand(QTime(0,0,0).secsTo(QTime::currentTime())+K*100+i);
                    p->data[K][1]=qrand()%300+200;
                    //if(i>=70)

                    //qDebug()<<p->data[K][0];
                    }


        p=p->N;

        }

     sum = 500;           //sum一开始赋予500
    //MainWindow::savefile_zhuangtai("a");

}
void PigGame::illmode()
{
        p=head;
        int m;
        if(illcheck() == false)      //没病猪就开始随机生成一只病猪
        {
            qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
            int x=qrand()%20+60;
            if(x==61)
            {
                qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
                m=qrand()%100;
                for(int i=0;i<100;i++)
                {
                    if(i==m)
                    {
                        int n=qrand()%10;
                        p->data[n][3]=1;       //该猪已经被感染
                        p->flag=1;             //猪圈已经被感染
                        cnt=std::max(m,100-m)*7+50;
                        break;
                    }
                    p=p->N;
                }
            }
        }
        if(cnt == 0&&illcheck()==true)
        {
            QString ac = "有瘟疫的猪圈有"+QString::number(illsum())+"个，占到了所有猪圈的"+QString::number(illsum())+"%";
            this->ui->lb_ill_pigsty->setText(ac);
            this->ui->lb_ill_arise->setText("养猪场出现瘟疫");
            this->ui->lb_daed_day->setText("如果未隔离，最快"+QString::number(cnt)+"天后全部猪就会死亡");
        }
        else if(illcheck()==false)
        {
            this->ui->lb_ill_pigsty->setText("有瘟疫的猪圈有0个，占到了所有猪圈的0%");
            this->ui->lb_ill_arise->setText("养猪场未出现瘟疫");
            this->ui->lb_daed_day->setText("恭喜你，目前你的猪尚未感染瘟疫");
        }
            else
       {
            QString ac = "有瘟疫的猪圈有"+QString::number(illsum())+"个，占到了所有猪圈的"+QString::number(illsum())+"%";
            this->ui->lb_ill_pigsty->setText(ac);
            this->ui->lb_ill_arise->setText("养猪场出现瘟疫");
            QString ab = "如果未隔离，最快"+QString::number(cnt)+"天后全部猪就会死亡";
            this->ui->lb_daed_day->setText(ab);
            cnt--;
        }
        p=head;
        if(check())        //没有全部感染死亡
            {
                for(int i=0;i<100;i++)
                {
                    for(int k=0;k<10;k++)
                    {
                        if(p->data[k][3]==1)
                        {
                            continue;
                        }
                        else if(p->flag==1)
                        {
                            int x=qrand()%100;
                            if(x<50)
                            {
                                p->data[k][3]=1;
                                p->data[k][4]=180;
                            }
                        }
                        else if(p->flag==0&&((p->F!=NULL&&p->F->flag==1)||(p->N!=NULL&&p->N->flag==1)))
                        {
                            int x=qrand()%100;
                            if(x<15)
                            {
                                p->flag=1;
                                p->data[k][3]=1;
                                p->data[k][4]=180;
                            }
                        }
                    }
                    p=p->N;
                }
            }
}
void PigGame::on_btn_config_clicked()
{
    config *a = new config(this);
    a->show();
}

void PigGame::on_btn_store_clicked()
{
    store *a = new store(this);
    a->show();
}

void PigGame::on_btn_honor_clicked()
{
    honor *a = new honor(this);
    a->show();
}

void PigGame::on_btn_nextpage_clicked()
{
    int nIndex = ui->stackedWidget->currentIndex();

        // 获取下一个需要显示的页面索引
        ++nIndex;

        // 当需要显示的页面索引大于等于总页面时，切换至首页
        if (nIndex == 5)
            nIndex = 0;

       ui->stackedWidget->setCurrentIndex(nIndex);
}

void PigGame::on_btn_frontpage_clicked()
{
    int nIndex = ui->stackedWidget->currentIndex();

        // 获取下一个需要显示的页面索引
        --nIndex;

        // 当需要显示的页面索引大于等于总页面时，切换至首页
        if (nIndex == -1)
            nIndex = 4;

       ui->stackedWidget->setCurrentIndex(nIndex);
}
void PigGame::goout()//chu lan
{
    qDebug()<<"go out";
    sum_money = 0;
    int hua=0,bai = 0,hei = 0;;
    int numpig = 0;
    *p = *head;
    //grow shuiji
    for(int i = 0;i<100;i++)
    {
        for(int K=0;K<10;K++)
        {
            if((p->data[K][1]>=750||p->data[K][2]>360)&&p->data[K][0]<=3&&p->data[K][3]==0)//一个月30天//注意：要该猪不是空，且未被感染
            {
                numpig ++;
                if(p->data[K][0]==1)
                    sum_money += 7*p->data[K][1]/10;
                if(p->data[K][0]==2)
                    sum_money += 6*p->data[K][1]/10;
                if(p->data[K][0]==3)
                    sum_money += 15*p->data[K][1]/10;
                if(p->type == false)
                {
                qsrand(QTime(0,0,0).secsTo(QTime::currentTime())+K*10000+i);
                p->data[K][0]=qrand()%2+1;
                if(p->data[K][0] == 1)
                    hua++;
                if(p->data[K][0] == 2)
                    bai++;
                qsrand(QTime(0,0,0).secsTo(QTime::currentTime())+K*100+i);
                p->data[K][1]=qrand()%300+200;
                p->data[K][2]=1;           //补充的几个信息都要初始化
                p->data[K][3]=0;
                p->data[K][4]=0;
                }
                else
                {
                    hei++;
                    p->data[K][0]=3;
                    qsrand(QTime(0,0,0).secsTo(QTime::currentTime())+K*100+i);
                    p->data[K][1]=qrand()%300+200;
                    p->data[K][2]=1;
                    p->data[K][3]=0;
                    p->data[K][4]=0;
                }
            }
        }

        p=p->N;
    }
    //MainWindow::savefile_chulan(QString::number(sum)+"|"+QString::number(numpig)+"|"+QString::number(hua)+"|"+QString::number(bai)+"|"+QString::number(hei));
    //MainWindow::savefile_zhuangtai("a");
    QString ab = QString::number(sum_money) + "|" +QString::number(numpig);//返回，一会用正则表达式搞一波
}
 bool PigGame::check()
 {
     p=head;
     for(int i=0;i<100;i++)
     {
         for(int k=0;k<10;k++)
         {
             if(p->data[k][3] == 0&&p->data[k][0]<=3)
                {p=head;
                 return true;
             }

         }
         p=p->N;
     }
     p=head;
     return false;
 }
 bool PigGame::illcheck()
 {
     p=head;
     for(int i=0;i<100;i++)
     {
         for(int k=0;k<10;k++)
         {
             if(p->data[k][3] == 1)
             {
                 p=head;
                 return true;
             }
         }

         p=p->N;

     }
     p=head;
     return false;
 }

void PigGame::on_btn_geli_clicked()
{
    if(illcheck()&&my_timer2->isActive() == false)    //避免每次点开始隔离都从150开始，避免多线程问题
    {
        p=head;
    healthtime = 150;
    my_timer1->stop();
    this->ui->lb_daed_day->setText("开始隔离，停止计算死亡时间");
    this->ui->lb_ill_arise->setText("出现瘟疫，开始隔离");
    my_timer2->start(1000);//开始1000毫秒执行一次healthemode
    }

}
void PigGame::healthemode()
{
    this->ui->lb_health_day->setText("还有"+QString::number(healthtime)+"天隔离完成,在此期间病猪不可出栏");
    healthtime--;
    if(healthtime == -1)
    {
        this->ui->lb_health_day->setText("目前处于非隔离状态");
        p = head;
        for(int i = 0;i<100;i++)
        {
            for (int k = 0;k<10;k++)
            {
                p->data[k][3] = 0;
            }
            p->flag = 0;
            p=p->N;
        }
        p = head;
        my_timer2->stop();
        my_timer1->start(1000);
    }
}
int PigGame::illsum()
{
    int summ = 0;
    p=head;
    for(int i = 0;i<=99;i++)
    {
        if(p->flag == 1)
            summ++;
        p=p->N;
    }
    p=head;
    return summ;
}
