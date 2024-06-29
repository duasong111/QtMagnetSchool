    #include "widget.h"
    #include "login.h"
    #include <QApplication>
    #include "globalvariable.h"
    #include <QDateTime>
    QString statusFlag = "1"; // 初始化全局字符串变量
    int timeTemp=100000;
    int modelTime=1;
    bool refriFlag=false;
    
    QDateTime currentTime = QDateTime::currentDateTime(); //为了调用它们分配内存
    QString formattedTime = currentTime.toString("yyyy-MM-dd hh:mm:ss");
    int main(int argc, char *argv[])
    {
        QApplication a(argc, argv);
            Widget w;
            w.show();
    //    login w;
    //    w.show();
    
        return a.exec();
    }
