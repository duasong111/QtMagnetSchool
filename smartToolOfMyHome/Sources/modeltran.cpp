
#include "modelTran.h"
#include "ui_modelTran.h"
#include <QDebug>
#include <QMessageBox>
#include "globalvariable.h"
#pragma execution_character_set("utf-8")
modelTran::modelTran(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modelTran)
{
    ui->setupUi(this);
}
modelTran::~modelTran()
{
    delete ui;
    connect(ui->timeEdit, &QTimeEdit::timeChanged, this, &modelTran::onTimeChanged);
}
void modelTran::on_timeEdit_editingFinished()
{
    QTime selectedTime = ui->timeEdit->time();
    int totalSeconds = selectedTime.hour() * 3600 + selectedTime.minute() * 60 + selectedTime.second();
    qDebug() << "转化为数字是：" << totalSeconds;
    modelTime = totalSeconds;
    emit timeSelected(totalSeconds);
}
//这个问题到目前还是没有解决的，就是关于这个传输值的问题
void modelTran::onTimeChanged(const QTime& time)
{
    int totalSeconds = time.hour() * 3600 + time.minute() * 60 + time.second();
    qDebug() << "接收到的时间是：" << totalSeconds;
    // 处理接收到的编辑后的时间，可以更新其他部分的逻辑
}

