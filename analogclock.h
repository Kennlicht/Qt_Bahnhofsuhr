#ifndef CENTRALCLOCK_H
#define CENTRALCLOCK_H

#include <QWidget>
#include <QTime>
#include <QTimer>
#include <QPainter>
#include <QApplication>


class AnalogClock : public QWidget		// analog clock widget
{
    Q_OBJECT
public:
    AnalogClock(QWidget *parent=0, const char *name=0);

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void onTimeout();

private:
    QTime time;
};

#endif
