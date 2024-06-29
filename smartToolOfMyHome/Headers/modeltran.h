// modelTran.h

#ifndef MODELTRAN_H
#define MODELTRAN_H

#include <QDialog>
#include <QTime>

namespace Ui {
class modelTran;
}

class modelTran : public QDialog
{
    Q_OBJECT

public:
    explicit modelTran(QWidget *parent = nullptr);
    ~modelTran();

signals:
    void timeSelected(int timeInSeconds);


public slots:
    void on_timeEdit_editingFinished();
    void onTimeChanged(const QTime& time);

private:
    Ui::modelTran *ui;
};

#endif // MODELTRAN_H
