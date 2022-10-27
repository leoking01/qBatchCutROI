#include "qdicethread.h"
#include    <QTime>


#include "opencv2/opencv.hpp"
#include "string"
#include "iostream"

#include <opencv2/opencv.hpp>
#include <opencv2/core/utils/filesystem.hpp>
// 推荐重命名namespace
// namespace cvfs = cv::utils::fs;
#include "QDateTime"
#include "QDebug"
#include "QFile"
#include "QFileInfo"
#include "QString"
#include "QDir"
#include "QDirIterator"

#include "widget.h"
QDiceThread::QDiceThread()
{
    connect(this,SIGNAL(mysignal(QString)), w  ,SLOT(myslot(QString)));
}

void QDiceThread::diceBegin()
{ //开始掷骰子
    m_Paused=false;
}

void QDiceThread::dicePause()
{//暂停掷骰子
    m_Paused=true;
}

void QDiceThread::stopThread()
{//停止线程
    m_stop=true;
}

void  procOneIMg(std::string fileIN , std::string fileSave,  cv::Rect  roi   );

void QDiceThread::run(   )
{//线程任务
    m_stop=false;//启动线程时令m_stop=false
    m_seq=0; //掷骰子次数
    qsrand(QTime::currentTime().msec());//随机数初始化，qsrand是线程安全的

    //    while(!m_stop)//循环主体
    //    {
    //        if (!m_Paused)
    //        {
    //            m_diceValue=qrand(); //获取随机数
    //            m_diceValue=(m_diceValue % 6)+1;
    //            m_seq++;
    //            emit newValue(m_seq,m_diceValue);  //发射信号
    //        }
    //        msleep(500); //线程休眠500ms
    //    }

    int nums = string_list.size() ;
    std::cout<< "nums= " << nums << std::endl;

    int idCont = 0 ;
    for(QStringList::Iterator  it =string_list.begin();it!=string_list.end();it++ ){
        std::string fileIN = indir + "/" + it->toStdString() ;
        std::string fileSave = outdir + "/" + it->toStdString() ;
        std::cout<< "now proc ( " << idCont<< " ," << nums<< " ), "<< fileIN<<  std::endl;
        procOneIMg( fileIN , fileSave ,roi );
        idCont ++ ;

        QTime timeNow = QTime::currentTime();

        QString time = timeNow.toString() + QString("__");
        static  int  id = 0 ;
        id++ ;
        time +=  QString::number( id ) ;

        emit mysignal(  QString("child get now time = ")+ time + QString(", finish proc file :  ") + QString(fileIN.c_str()) + "\n"  );

        // Log_Text_Display("finish proc file : "+ QString(fileIN.c_str()) + "\n" );
        // ui->plainTextEdit->appendPlainText( "finish proc file : "+ QString(fileIN.c_str())  ) ;
        // ui->plainTextEdit->
    }

    //  在  m_stop==true时结束线程任务
    //    quit();//相当于  exit(0),退出线程的事件循环
}

//、、---------------------------
void QDiceThread::runThread(){
    run(   ) ;
}
