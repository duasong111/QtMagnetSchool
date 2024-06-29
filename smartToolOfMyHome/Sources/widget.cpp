#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>
#include <QPushButton>
#include <QMetaObject>
#include <QMetaProperty>
#include "globalvariable.h"
#include <QMovie>
#include <QLabel>
#include <QTimer>
#include <QVBoxLayout>
#include  <QSize>
#include "modeltran.h"
#include <QMouseEvent>
#pragma execution_character_set("utf-8")
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    startTimer(1000);//间隔是1S进行显示输出
    socket = new QTcpSocket(this); //去连接服务器的操作
    socket -> connectToHost("192.168.177.128 ", 8000);
    if (socket->waitForConnected()) {
        qDebug() << "Received";
        socket->write("Hello from client!\n"); // 发送消息到服务器端
        ui->textBrowser->insertPlainText("连接服务器成功！\n");
        socket->waitForBytesWritten(1000);
        socket->waitForReadyRead(1000);
    } else {
        qDebug() << "Connection failed!";
    }
}

Widget::~Widget()
{
    delete ui;
}
//对失误点击进行处理
void Widget::closeEvent(QCloseEvent *event)
{
    QMessageBox::Button btn = QMessageBox::question(this,"提示信息","确定关闭窗口吗");
    if(btn == QMessageBox::Yes){
        event->accept();
    }else{
        event->ignore();
    }
}

//对时间控件去添加定义 --- 逻辑上存在问题，需要去进行修改
void Widget::timerEvent(QTimerEvent *event)
{
    if(timeTemp<86400 and timeTemp > 0){ //小于24小时才进行显示
        controlImageChangeAir("ON");//空调自然就亮了
        controlAirconditionImage("倒计时中","ON");//不传输任何的，防止一直重复
        QTime timeLeft(0, (timeTemp / 60) % 60, timeTemp % 60);
        ui->labelTime->setText(timeLeft.toString("hh:mm:ss.zzz"));// 在标签上显示格式化后的倒计时
        timeTemp--;
        if(timeTemp%2==0){  //对其的颜色进行不停的更换
            ui->labelTime->setStyleSheet("border-image: url(:/picture/white.png)");
        }else{
            ui->labelTime->setStyleSheet("border-image: url(:/picture/redBackground.jpg)");
        }
    }
    if(timeTemp<= 0){
        //        abnormalReminder("空调倒计时结束喽~");
        controlImageChangeAir("OFF");
        controlAirconditionImage("关闭空调","OFF");
        timeTemp=100000000000000000; //肯定不能这样搞
        roomToolOpen="1";
    }
}

//异常提醒的封装
void Widget::abnormalReminder(const QString& remainderMessage)
{
    QMessageBox *msgBox = new QMessageBox;
    msgBox->setWindowTitle("异常提示");
    msgBox->setText(remainderMessage);
    msgBox->setStandardButtons(QMessageBox::Ok);
    msgBox->exec();
}

//去对那个冰箱的的换图以及textBrow显示进行封装
void Widget::controlRefrigeratorImage(const QString& data,const QString &statue){
    ui->toolButton_7->setStyleSheet(QString("border-image: url(:/picture/refri%1.png);").arg(statue));
    ui->textBrowser->append(data);
    ui->refriLabel->setText(data);
    QString formattedData = QString("%1%2\n").arg(data).arg(formattedTime);
    socket->write(formattedData.toUtf8());

}

//对空调的换图以及textBrow显示进行封装
void Widget::controlAirconditionImage(const QString& data,const QString &statue){
    ui->toolButton->setStyleSheet(QString("border-image: url(:/picture/airCondition%1.png);").arg(statue));
    ui->airLabel->setText(data);
    ui->textBrowser->append(data);
    QString formattedData = QString("%1%2\n").arg(data).arg(formattedTime);
    socket->write(formattedData.toUtf8());
}

//对电灯的换图以及textBrow显示进行封装
void Widget::controlLampImage(const QString& data,const QString &statue){
    ui->toolButton_2->setStyleSheet(QString("border-image: url(:/picture/lamp%1.png);").arg(statue));
    ui->textBrowser->append(data);
    ui->lampLabel->setText(data);
    QString formattedData = QString("%1%2\n").arg(data).arg(formattedTime);
    socket->write(formattedData.toUtf8());

}
//对WIFI的换图以及textBrow显示进行封装
void Widget::controlWIFIImage(const QString& data,const QString &statue){
    ui->toolButton_6->setStyleSheet(QString("border-image: url(:/picture/wifi%1.png);").arg(statue));
    ui->textBrowser->append(data);
    ui->wifiLabel->setText(data);
    QString formattedData = QString("%1%2\n").arg(data).arg(formattedTime);
    socket->write(formattedData.toUtf8());
}

//对电视机的换图操作换图以及textBrow显示进行封装
void Widget::controlTVImage(const QString& data,const QString &statue){
    ui->controlTV->setStyleSheet(QString("border-image: url(:/picture/tvPicture%1.png);").arg(statue));
    ui->textBrowser->append(data);
    ui->tvLabel->setText(data);
    QString formattedData = QString("%1%2\n").arg(data).arg(formattedTime);
    socket->write(formattedData.toUtf8());
}

//对电源的换图以及textBrow显示进行封装
void Widget::controlElectricImage(const QString& data,const QString &statue){
    ui->toolButton_3->setStyleSheet(QString("border-image: url(:/picture/electric%1.png);").arg(statue));
    ui->textBrowser->append(data);
    ui->electricLabel->setText(data);
    QString formattedData = QString("%1%2\n").arg(data).arg(formattedTime);
    socket->write(formattedData.toUtf8());
}

//对是否在家的换图以及textBrow显示进行封装
void Widget::controlHomeImage(const QString& data,const QString &statue){
    ui->toolButton_5->setStyleSheet(QString("border-image: url(:/picture/home%1.png);").arg(statue));
    ui->textBrowser->append(data);
    ui->homeLabel->setText(data);
    QString formattedData = QString("%1%2\n").arg(data).arg(formattedTime);
    socket->write(formattedData.toUtf8());
}

//去对换图进行设置
void Widget::controlImageChangeHome(const QString &imageStatu){
    ui->controlHome->setStyleSheet(QString("border-image: url(:/picture/swtich%1.png);").arg(imageStatu));
}

//去控制wifi的图
void Widget::controlImageChangeWIFI(const QString &imageStatu){
    ui->controlWIFI->setStyleSheet(QString("border-image: url(:/picture/swtich%1.png);").arg(imageStatu));
}
//去控制空调
void Widget::controlImageChangeAir(const QString &imageStatu){
    ui->controlAir->setStyleSheet(QString("border-image: url(:/picture/swtich%1.png);").arg(imageStatu));
}

//去控制电源
void Widget::controlImageChangeElect(const QString &imageStatu){
    ui->controlElect->setStyleSheet(QString("border-image: url(:/picture/swtich%1.png);").arg(imageStatu));
}

//去控制灯
void Widget::controlImageChangeLamp(const QString &imageStatu){
    ui->controlLamp->setStyleSheet(QString("border-image: url(:/picture/swtich%1.png);").arg(imageStatu));
}

//去控制冰箱
void Widget::controlImageChangeRefri(const QString &imageStatu){
    ui->controlRefri->setStyleSheet(QString("border-image: url(:/picture/swtich%1.png);").arg(imageStatu));
}

//手动去设置冰箱
void Widget::on_toolButton_7_clicked()
{
    if(roomToolOpen=="0"){
        controlRefrigeratorImage("打开冰箱","ON");
        controlImageChangeRefri("ON");
        roomToolOpen="1";
    }else{

        controlRefrigeratorImage("关闭冰箱","OFF");
        controlImageChangeRefri("OFF");
        roomToolOpen="0";
    }
}

//手动去打开电视
void Widget::on_controlTV_clicked()
{
    if (roomToolOpen == "0") {
        controlTVImage("关闭电视","OFF");
        ui->controlDianShi->setStyleSheet("border-image: url(:/picture/swtichOFF.png);");
        roomToolOpen = "1";
    } else {
        controlTVImage("打开电视","ON");
        ui->controlDianShi->setStyleSheet("border-image: url(:/picture/swtichON.png);");
        roomToolOpen = "0";
    }
}

//对于空调按钮的设置
void Widget::on_toolButton_clicked()
{
    if(roomToolOpen=="0"){
        controlAirconditionImage("打开空调","ON");
        controlImageChangeAir("ON");
        roomToolOpen="1";
    }else{
        controlAirconditionImage("关闭空调","OFF");
        controlImageChangeAir("OFF");
        roomToolOpen="0";
    }
}

//对于开关灯按钮的设置
void Widget::on_toolButton_2_clicked()
{
    if(roomToolOpen=="0"){
        ui->widget->setStyleSheet(QString("border-image: url(:/tu/backGroundDark.jpg)"));
        controlImageChangeLamp("OFF");
        controlLampImage("关灯","OFF");
        roomToolOpen="1";
    }else{
        ui->widget->setStyleSheet(QString("border-image: url(:/tu/background.jpg)"));
        controlImageChangeLamp("ON");
        controlLampImage("开 灯","ON");
        roomToolOpen="0";
    }
}

//对于开关WiFi的设置
void Widget::on_toolButton_6_clicked()
{
    if(roomToolOpen=="0"){
        controlWIFIImage("打开WIFIing","ON");
        controlImageChangeWIFI("ON");
        roomToolOpen="1";
    }else{

        controlWIFIImage("关闭WIFIing","OFF");
        controlImageChangeWIFI("OFF");
        roomToolOpen="0";
    }
}

//对于家庭电源的控制到时候去写一个更加具体的
void Widget::on_toolButton_3_clicked()
{
    if(statusFlag=="0"){
        controlImageChangeElect("ON");
        controlElectricImage("通电","ON");
        statusFlag="1";
    }else{
        //如果电闸是关闭状态的话所有的设备都是关闭的状态
        controlElectricImage("关闭电源","OFF");
        controlImageChangeElect("OFF");
        //所有设备进行关闭
        controlWIFIImage("关闭WIFI","OFF");
        controlAirconditionImage("关闭空调","OFF");
        controlLampImage("关灯","OFF");
        ui->widget->setStyleSheet(QString("border-image: url(:/tu/backGroundDark.jpg)"));
        controlHomeImage("停电了","OFF");

        controlImageChangeElect("OFF");//开关按钮图标状态
        controlImageChangeHome("OFF");
        controlImageChangeWIFI("OFF");
        controlImageChangeRefri("OFF");
        controlImageChangeAir("OFF");
        controlImageChangeLamp("OFF");

        timeTemp=-100;//关闭定时功能
        statusFlag="0";
    }
}

//对于是否离开家还是回家进行设置
void Widget::on_toolButton_5_clicked()
{
    if(roomToolOpen=="0"){
        controlHomeImage("回到家了","ON");
        controlImageChangeHome("ON");
        roomToolOpen="1";
    }else{
        controlHomeImage("离开家了","OFF");
        controlImageChangeHome("OFF");
        roomToolOpen="0";
    }
}

//对于开关去控制离开家还是在家的情况
void Widget::on_controlHome_clicked()
{
    if (statusFlag == "1") {  // 电源为通电状态
        if(roomToolOpen=="0"){
            controlImageChangeHome("ON");
            controlHomeImage("到家了","ON");
            roomToolOpen="1";
        }else{
            controlImageChangeHome("OFF");
            controlHomeImage("离家了","OFF");
            roomToolOpen="0";
        }
    } else {
        abnormalReminder("电源已断电，无法操作功能按钮");
    }
}

//使用开关去控制电灯是否亮
void Widget::on_controlLamp_clicked()
{
    if (statusFlag == "1") {  // 电源为通电状态
        if(roomToolOpen=="0"){
            ui->widget->setStyleSheet(QString("border-image: url(:/tu/backGroundDark.jpg)"));
            controlImageChangeLamp("OFF");
            controlLampImage("关灯","OFF");
            roomToolOpen="1";
        }else{
            ui->widget->setStyleSheet(QString("border-image: url(:/tu/background.jpg)"));
            controlImageChangeLamp("ON");
            controlLampImage("开 灯","ON");
            roomToolOpen="0";
        }
    } else {
        abnormalReminder("电源已断电，无法操作功能按钮");
    }
}

//去进行控制空调的开关情况
void Widget::on_controlAir_clicked()
{
    if (statusFlag == "1") {  // 电源为通电状态
        if(roomToolOpen=="0"){
            controlImageChangeAir("OFF");
            controlAirconditionImage("关闭空调","OFF");
            roomToolOpen="1";
            timeTemp=-100;//关闭定时功能
        }else{
            QMessageBox *msgBox = new QMessageBox;
            msgBox->setWindowTitle("模式选择");
            msgBox->setText("用户可选择直接打开或进行倒计时操作");
            msgBox->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
            // 获取"OK"按钮并设置文本为"直接开启"
            QAbstractButton* okButton = msgBox->button(QMessageBox::Ok);
            okButton->setText("直接开启");
            //另一个就是去设置倒计时
            QAbstractButton* timeButton = msgBox->button(QMessageBox::Cancel);
            timeButton->setText("倒计时");
            int result = msgBox->exec();
            if (result == QMessageBox::Ok) {
                controlImageChangeAir("ON");
                controlAirconditionImage("打开空调","ON");
                roomToolOpen="0";
            } else if (result == QMessageBox::Cancel) {
                modelTran *modelTranPage = new modelTran;
                modelTranPage->show();
            }
        }
    } else {
        abnormalReminder("电源已断电，无法操作功能按钮");
    }
}

//总电闸控制开关
void Widget::on_controlElect_clicked()
{
    if(statusFlag=="0"){
        controlImageChangeElect("ON");
        controlElectricImage("通电","ON");
        statusFlag="1";
    }else{
        //将总电闸关闭了，这个时候所有的设备都应该是进行的是不能正常通电的情况了
        QMessageBox *msgBox = new QMessageBox;
        msgBox->setWindowTitle("关闭提示");
        msgBox->setText("确定要关闭所有的设备吗");
        msgBox->setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
        int result = msgBox->exec();
        if(result==QMessageBox::Ok){
            controlElectricImage("断电","OFF");
            controlRefrigeratorImage("关闭冰箱","OFF"); //设备状态
            controlWIFIImage("关闭WIFI","OFF");
            controlAirconditionImage("关闭空调","OFF");
            controlLampImage("关灯","OFF");
            ui->widget->setStyleSheet(QString("border-image: url(:/tu/backGroundDark.jpg)"));
            controlHomeImage("停电了","OFF");
            controlTVImage("关闭电视","OFF");

            ui->controlDianShi->setStyleSheet("border-image: url(:/picture/swtichOFF.png);");//电视的按钮图标进行关闭
            controlImageChangeElect("OFF");//开关按钮图标状态
            controlImageChangeHome("OFF");
            controlImageChangeWIFI("OFF");
            controlImageChangeRefri("OFF");
            controlImageChangeAir("OFF");
            controlImageChangeLamp("OFF");
            timeTemp=-100;//关闭定时功能
        }
        statusFlag="0";
    }
}

//对冰箱的控制按钮
void Widget::on_controlRefri_clicked()
{
    if (statusFlag == "1") {  // 电源为通电状态
        if(roomToolOpen=="0"){
            controlImageChangeRefri("ON");
            controlRefrigeratorImage("打开冰箱","ON");
            roomToolOpen="1";
        }else{
            controlImageChangeRefri("OFF");
            controlRefrigeratorImage("关闭冰箱","OFF");
            roomToolOpen="0";
        }
    } else {
        abnormalReminder("电源已断电，无法操作功能按钮");
    }
}
//对WIFI的控制按钮
void Widget::on_controlWIFI_clicked()
{
    if (statusFlag == "1") {  // 电源为通电状态
        if(roomToolOpen=="0"){
            controlImageChangeWIFI("OFF");
            controlWIFIImage("关闭WIFI","OFF");
            roomToolOpen="1";
        }else{
            controlImageChangeWIFI("ON");
            controlWIFIImage("打开WIFI","ON");
            roomToolOpen="0";
        }
    } else {
        abnormalReminder("电源已断电，无法操作功能按钮");
    }
}
//对电视的控制
void Widget::on_controlDianShi_clicked()
{
    if (statusFlag == "1") {  // 电源为通电状态
        QSize openSize(250,240);
        if(isOpen){
            QMovie *movie = new QMovie(":/picture/carGIF.gif");
            ui->controlDianShi->setStyleSheet("border-image: url(:/picture/swtichON.png);");
            movie->setScaledSize(openSize);
            ui->controlTV->setMovie(movie);
            movie->start();
            ui->textBrowser->insertPlainText("打开电视成功\n");
            QString formattedData = QString("%1%2\n").arg("电视打开状态").arg(formattedTime);
            socket->write(formattedData.toUtf8());
        }else{
            ui->controlTV->setStyleSheet("border-image: url(:/picture/black.png);");
            QPixmap fanPixmap(":res/电视.png");
            ui->controlTV->setPixmap(fanPixmap.scaled(openSize,Qt::KeepAspectRatio,Qt::SmoothTransformation));
            ui->controlTV->setMovie(nullptr);
            ui->textBrowser->insertPlainText("关闭电视成功\n");
            QString formattedData = QString("%1%2\n").arg("电视关闭状态").arg(formattedTime);
            ui->controlDianShi->setStyleSheet("border-image: url(:/picture/swtichOFF.png);");
            socket->write(formattedData.toUtf8());
        }
        isOpen=!isOpen;
    } else {
        abnormalReminder("电源已断电，无法操作功能按钮");
    }
}

//对空调倒计时的设置（左下角那个小的按钮）
void Widget::on_timeEdit_editingFinished()
{
    QTime selectedTime = ui->timeEdit->time();
    int totalSeconds = selectedTime.hour() * 3600 + selectedTime.minute() * 60 + selectedTime.second();
    timeTemp=totalSeconds;
}

