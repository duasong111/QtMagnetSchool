#include "login.h"
#include <QWidget>
#include "widget.h"
#include "ui_login.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QTcpSocket>
#include <QHostAddress>
login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login),
    mainPage(nullptr),
  tcpSocket(new QTcpSocket(this))
{
    ui->setupUi(this);
    ui->loginName->setText("192.168.177.128"); //去初始化用户名的默认值
}

login::~login()
{
    delete ui;
    if (mainPage) {
        delete mainPage;
    }
}

void login::on_loginConnect_clicked()
{
    QString ip = ui->loginName->text(); //去获取输入的值
    QString port=ui->loginPassword->text();;
    mainPage = new Widget();
    if(nullptr==ip||nullptr==port){
        qDebug()<<"错误，端口或Ip地址不能为空";
        return;
    }else{
        if(ip!="192.168.177.128"||port!="8888"){
            QMessageBox *msgBox = new QMessageBox;
            msgBox->setWindowTitle("登录异常提示！");
            msgBox->setText("IP地址或端口错误，请重新输入");
            msgBox->setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
            msgBox->exec();
        }else{
             qDebug()<<"传输过来了"<<ip<<port;
            mainPage->show(); //主页面显示出来
            this->close(); //将登录页面去进行关闭
        }
    }
}

void login::signal_swap()
{
    qDebug()<<"进入虚拟环境";
}
