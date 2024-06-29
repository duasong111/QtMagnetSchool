// globalvariables.h
#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

#include <QString>

extern QString statusFlag; // 声明一个全局字符串变量
extern int timeTemp;
extern int modelTime;
extern bool refriFlag;

extern QDateTime currentTime; //将时间设置成全局变量
extern QString formattedTime;
#endif // GLOBALVARIABLES_H
