#ifndef QDICETHREAD_H
#define QDICETHREAD_H

#include    <QThread>
#include "opencv2/opencv.hpp"


#include "string"
#include "iostream"


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


class QDiceThread : public QThread
{
    Q_OBJECT
private:
    int     m_seq=0;//掷骰子次数序号
    int     m_diceValue;//骰子点数
    bool    m_Paused=true; //掷一次骰子
    bool    m_stop=false; //停止线程
protected:
    void    run( ) Q_DECL_OVERRIDE;  //线程任务

public slots:
    void runThread();

public:
    QDiceThread();

    QStringList  string_list ;
    cv::Rect roi ;
     std::string  indir ;
     std::string outdir ;

    void    diceBegin();//掷一次骰子
    void    dicePause();//暂停
    void    stopThread(); //结束线程
signals:
    void    newValue(int seq,int diceValue); //产生新点数的信号

    signals:
        void mysignal(QString  );//信号
};

#endif // QDICETHREAD_H
