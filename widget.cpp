#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->lineEdit_inDir->setText( "E:/AAA_LK_study/CamerUnsitorInfferProj/bin"  ) ;
    ui->lineEdit_outdir->setText( "E:/AAA_LK_study/CamerUnsitorInfferProj/binBatchCutOut"  ) ;
    ui->lineEdit_left->setText(  "0" );
    ui->lineEdit_top->setText(  "0" );
    ui->lineEdit_wid->setText(  "840" );
    ui->lineEdit_hei->setText(  "540" );

       connect(this,SIGNAL(mysignal(QString)), this ,SLOT(myslot(QString)));

}


Widget::~Widget()
{
    delete ui;
}

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

void  Ergodic ()
{
    std::string inDir ;

    QFileInfo fileInfo("F:\\data.txt");
    qDebug()<<"baseName = "<<fileInfo.baseName();
    qDebug()<<"fileName = "<<fileInfo.fileName();
    qDebug()<<"absoluteFilePath = "<<fileInfo.absoluteFilePath();
    qDebug()<<"filePath = "<<fileInfo.filePath();
    qDebug()<<"path = "<<fileInfo.path();
    qDebug()<<"size = "<<fileInfo.size();
    qDebug()<<"birthTime = "<<fileInfo.birthTime().toString("yyyy-MM-dd hh:mm:ss");
    qDebug()<<"lastModified = "<<fileInfo.lastModified().toString("yyyy-MM-dd hh:mm:ss");

    //baseName =  "data"
    //fileName =  "data.txt"
    //absoluteFilePath =  "F:/data.txt"
    //filePath =  "F:/data.txt"
    //path =  "F:/"
    //size =  315
    //birthTime =  "2021-02-23 21:54:13"
    //lastModified =  "2021-02-23 22:29:06"
}



//Qt遍历文件夹下一层的文件：
void  addFolderImages(QString path,  QStringList &string_list  )
{
    std::cout<< "addFolderImages, path = " <<  path.toStdString() << std::endl;

    //判断路径是否存在
    QDir dir(path);
    if(!dir.exists())
    {
        std::cerr<< "error,  !dir.exists()" <<   std::endl;

        return;
    }
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    QFileInfoList list = dir.entryInfoList();

    int file_count = list.count();
    std::cout<< "addFolderImages, file_count = " << file_count<< std::endl;

    if(file_count <= 0)
    {
        std::cerr<< "error,  file_count <= 0, file_count = " <<file_count<<   std::endl;
        return;
    }

    //    QStringList string_list;
    for(int i=0; i<file_count; i++)
    {
        QFileInfo file_info = list.at(i);
        QString suffix = file_info.suffix();
        if(QString::compare(suffix, QString("jpg"), Qt::CaseInsensitive) == 0)
        {
            QString absolute_file_path = file_info.absoluteFilePath();
            absolute_file_path = file_info.fileName();
            string_list.append(absolute_file_path);
        }
    }
}


//级联遍历文件夹及其子孙文件夹中的文件
void  addSubFolderImages(QString path)
{
    //判断路径是否存在
    QDir dir(path);
    if(!dir.exists())
    {
        return;
    }

    //获取所选文件类型过滤器
    QStringList filters;
    filters<<QString("*.jpeg")<<QString("*.jpg")<<QString("*.png")<<QString("*.tiff")<<QString("*.gif")<<QString("*.bmp");

    //定义迭代器并设置过滤器
    QDirIterator dir_iterator(path,
                              filters,
                              QDir::Files | QDir::NoSymLinks,
                              QDirIterator::Subdirectories);
    QStringList string_list;
    while(dir_iterator.hasNext())
    {
        dir_iterator.next();
        QFileInfo file_info = dir_iterator.fileInfo();
        QString absolute_file_path = file_info.absoluteFilePath();
        string_list.append(absolute_file_path);
    }
}

void  procOneIMg(std::string fileIN , std::string fileSave,  cv::Rect  roi   ){
    //    std::string fileIN;
    cv::Mat img= cv::imread(fileIN);
    //    cv::Rect  roi;//(left,top,wid,hei);
    cv::Mat out= img(roi);
    //    std::string fileSave;
    cv::imwrite(fileSave, out );
}


#include "iostream"
#include "QDebug"
//emit
void Widget::myslot(QString text)
{
    Log_Text_Display(  text) ;
    //      qDebug()<<"MY emit is beauty girl " ;// <<std::endl;
    qDebug()<<"main wind recieve message:  " << text ;// <<std::endl;
}


//、、------------------------------------
#include    <QThread>

class QDiceThread : public QThread
{
    Q_OBJECT
private:
    int     m_seq=0;//掷骰子次数序号
    int     m_diceValue;//骰子点数
    bool    m_Paused=true; //掷一次骰子
    bool    m_stop=false; //停止线程
protected:
    void    run() Q_DECL_OVERRIDE;  //线程任务
public:
    QDiceThread();

    void    diceBegin();//掷一次骰子
    void    dicePause();//暂停
    void    stopThread(); //结束线程
signals:
    void    newValue(int seq,int diceValue); //产生新点数的信号
};
#include    <QTime>

QDiceThread::QDiceThread()
{

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

void QDiceThread::run()
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


    int idCont = 0 ;
    for(QStringList::Iterator  it =string_list.begin();it!=string_list.end();it++ ){

        std::string fileIN = indir + "/" + it->toStdString() ;
        std::string fileSave = outdir + "/" + it->toStdString() ;
        std::cout<< "now proc ( " << idCont<< " ," << nums<< " ), "<< fileIN<<  std::endl;
        procOneIMg( fileIN , fileSave ,roi );
        idCont ++ ;


        QTime timeNow = QTime::currentTime();

        QString  time = timeNow.toString() + QString("__");
        static  int  id = 0 ;
        id++ ;
        time +=  QString::number( id ) ;
       emit mysignal(  QString("child get now time = ")+ time + QString(", finish proc file :  ") + QString(fileIN.c_str()) + "\n"  );

//        Log_Text_Display("finish proc file : "+ QString(fileIN.c_str()) + "\n" );
        //        ui->plainTextEdit->appendPlainText( "finish proc file : "+ QString(fileIN.c_str())  ) ;
        //         ui->plainTextEdit->
    }



//  在  m_stop==true时结束线程任务
//    quit();//相当于  exit(0),退出线程的事件循环
}

//、、---------------------------

void Widget::on_pushButton_cut_clicked()
{
    std::string  indir = ui->lineEdit_inDir->text().toStdString();
    std::string  outdir =   ui->lineEdit_outdir->text().toStdString();
    std::cout<< "indir = " << indir<< std::endl;

    int left =  ui->lineEdit_left->text().toUInt();
    int top =  ui->lineEdit_top->text().toUInt();
    int wid =  ui->lineEdit_wid->text().toUInt();
    int hei =  ui->lineEdit_hei->text().toUInt();

    cv::Rect  roi(left,top,wid,hei);

    QStringList  string_list  ;
    addFolderImages( indir.c_str() ,   string_list  ) ;

    int nums =  string_list.size() ;
    std::cout<< "nums= " << nums << std::endl;

//    int idCont = 0 ;
//    for(QStringList::Iterator  it =string_list.begin();it!=string_list.end();it++ ){

//        std::string fileIN = indir + "/" + it->toStdString() ;
//        std::string fileSave = outdir + "/" + it->toStdString() ;
//        std::cout<< "now proc ( " << idCont<< " ," << nums<< " ), "<< fileIN<<  std::endl;
//        procOneIMg( fileIN , fileSave ,roi );
//        idCont ++ ;


//        QTime timeNow = QTime::currentTime();

//        QString  time = timeNow.toString() + QString("__");
//        static  int  id = 0 ;
//        id++ ;
//        time +=  QString::number( id ) ;
//       emit mysignal(  QString("child get now time = ")+ time + QString(", finish proc file :  ") + QString(fileIN.c_str()) + "\n"  );

////        Log_Text_Display("finish proc file : "+ QString(fileIN.c_str()) + "\n" );
//        //        ui->plainTextEdit->appendPlainText( "finish proc file : "+ QString(fileIN.c_str())  ) ;
//        //         ui->plainTextEdit->
//    }
}


#include "QScrollBar"
/*日志显示*/
void Widget::Log_Text_Display(QString text)
{
    QPlainTextEdit *plainTextEdit_log=ui->plainTextEdit;

    //设置只读
    if(!plainTextEdit_log->isReadOnly())
    {
        plainTextEdit_log->setReadOnly(true);
    }

    //设置光标到文本末尾
    plainTextEdit_log->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
    //当文本数量超出一定范围就清除
    if(plainTextEdit_log->toPlainText().size()>1024*4)
    {
        plainTextEdit_log->clear();
    }
    plainTextEdit_log->insertPlainText(text);
    //移动滚动条到底部
    QScrollBar *scrollbar = plainTextEdit_log->verticalScrollBar();
    if(scrollbar)
    {
        scrollbar->setSliderPosition(scrollbar->maximum());
    }
}

