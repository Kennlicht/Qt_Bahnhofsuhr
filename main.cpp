/****************************************************************************
**
** Copyright (C) 1992-1998 Troll Tech AS.  All rights reserved.
**
** This file is part of an example program for Qt.  This example
** program may be used, distributed and modified without limitation.
**
*****************************************************************************/

/* this file is derived from the qt 'aclock' example */

#include <QApplication>

#include "analogclock.h"


int main(int argc, char **argv)
{
    QApplication a(argc, argv);

#if 1
    // Auf dem Heap...
    AnalogClock *clock = new AnalogClock;
    clock->resize(200, 120);    // So breit, damit sich das Fenster anfassen und verschieben lässt
    a.setActiveWindow(clock);
    clock->show();

    int result = a.exec();
    delete clock;
    return result;
#else
    // Oder auf dem Stack...
    AnalogClock clock;
    clock.resize(200, 120);     // So breit, damit sich das Fenster anfassen und verschieben lässt
    a.setActiveWindow(&clock);
    clock.show();

    int result = a.exec();
    return result;
#endif    
}

