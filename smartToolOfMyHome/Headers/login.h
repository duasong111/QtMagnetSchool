#ifndef LOGIN_H
#define LOGIN_H
#include <QDateTime>
#include <QWidget>
//#include <QTcpSocket.h>
#include "widget.h"
namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();

private slots:
    void on_loginConnect_clicked();
     void signal_swap();

private:
    Ui::login *ui;
    Widget *mainPage;
    QTcpSocket *tcpSocket;
    QTimer *timer;
};

#endif // LOGIN_H
