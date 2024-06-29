#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include <QCloseEvent>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDateTime>
namespace Ui {
class Widget;
}
class Widget : public QWidget
{
    QString roomToolOpen="0";
    QString electOpen="0";
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

protected:
    virtual void closeEvent(QCloseEvent *event);
    void timerEvent(QTimerEvent *event);
private slots:

    void on_toolButton_clicked();
    void on_toolButton_2_clicked();
    void on_controlHome_clicked();
    void on_toolButton_3_clicked();
    void on_toolButton_5_clicked();
    void on_controlLamp_clicked();
    void on_controlAir_clicked();
    void on_controlElect_clicked();
    void on_toolButton_6_clicked();
    void on_toolButton_7_clicked();
    void on_controlRefri_clicked();
    void on_controlWIFI_clicked();
    void on_controlTV_clicked(); //上述都是通过手动去进行点击操作的

    void controlRefrigeratorImage(const QString& data,const QString &statue); //在这里去将那个控制以及显示的去进行封装
    void controlAirconditionImage(const QString& data,const QString &statue); //在这里去将那个控制空调
    void controlLampImage(const QString& data, const QString& statue); //对电灯的控制封装
    void controlWIFIImage(const QString& data,const QString& statue); //对wifi的控制封装
    void controlElectricImage(const QString& data,const QString& statue); //对电源的控制封装
    void controlHomeImage(const QString& data,const QString& statue); //对是否在家的控制封装
    void controlTVImage(const QString& data,const QString &statue); //对电视机的图片转换

    void controlImageChangeHome(const QString &imageStatu); //其实本来想的是去封装一个就行
    void controlImageChangeWIFI(const QString &imageStatu); // 然后后续的去对传输后边的值即可
    void controlImageChangeAir(const QString &imageStatu);  //但是尝试了很多中方式，还是失败了。无奈去建立了五个
    void controlImageChangeElect(const QString &imageStatu);
    void controlImageChangeRefri(const QString &imageStatu);
    void controlImageChangeLamp(const QString &imageStatu);
    void abnormalReminder(const QString &remainderMessage); //断电后点击的异常提醒

    void on_controlDianShi_clicked();//去控制电视（存在的问题是，我无法去进行通过控制切换GIF，因为它是一个标签不是一个按钮）
    void on_timeEdit_editingFinished(); //去设置倒计时的功能

private:
    Ui::Widget *ui;
    QTcpSocket *socket;
     bool isOpen;

};

#endif // WIDGET_H
