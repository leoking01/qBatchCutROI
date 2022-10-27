#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->lineEdit_inDir->setText( "../data/bin"  ) ;
    ui->lineEdit_outdir->setText( "../data/binBatchCutOut"  ) ;
    ui->lineEdit_left->setText(  "0" );
    ui->lineEdit_top->setText(  "0" );
    ui->lineEdit_wid->setText(  "840" );
    ui->lineEdit_hei->setText(  "540" );



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
#include <thread>
#include    <QTime>
#include "qdicethread.h"

void
threadfun2(std::string indir, std::string outdir, cv::Rect  roi,  QStringList  string_list ){
    QDiceThread  qt ;
    qt.indir =  indir ;
    qt.outdir = outdir ;
    qt.roi = roi;
    qt.string_list = string_list;

    //       qt.run();

    qt.start(QThread::Priority::HighPriority);
    qt.wait();
}



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

    if( 1 )
    {
        QDiceThread *qt = new QDiceThread ;
        qt->indir =  indir ;
        qt->outdir = outdir ;
        qt->roi = roi;
        qt->string_list = string_list;

        //方法1：
        if( 1 )
        {
               qt->start(QThread::Priority::HighPriority);
        }
//方法2：
        if( 0 )
        {
            QThread * thread = new QThread;
            connect(thread, SIGNAL(started()), qt , SLOT(runThread()));
            qt->moveToThread( thread);
            thread->start();
        }
    }
//方法3：
    if( 0 )
    {
        //std::thread t1(threadfun1);
        std::thread t2(threadfun2, indir, outdir, roi, string_list );
        //   t1.join();		// 等待线程 t1 执行完毕
        std::cout << "join" << std::endl;
        t2.detach();	// 将线程 t2 与主线程分离
    }
//方法4：  threadPools

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



Widget *w = NULL;
