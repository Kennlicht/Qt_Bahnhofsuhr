/****************************************************************************
**
** Copyright (C) 1992-2000 Trolltech AS.  All rights reserved.
**
** This file is part of an example program for Qt.  This example
** program may be used, distributed and modified without limitation.
**
*****************************************************************************/

#include <QDateTime>
#include <QtGlobal>
#include <QPolygon>

#include "analogclock.h"


AnalogClock::AnalogClock(QWidget* parent, const char* name) : QWidget(parent)
{
  setObjectName(name);

  time = QTime::currentTime();                  // get current time
  QTimer* secsTimer = new QTimer(this);         // create timer
  //connect(secsTimer, SIGNAL(timeout()), SLOT(timeout()));
  connect(secsTimer, &QTimer::timeout, this, &AnalogClock::onTimeout);
  secsTimer->start(100);                        // emit signal every 100ms
  
  setWindowTitle("Uhr");
  setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
  // kann man die bei Größenänderung nachträglich beeinflussen?
  //setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);

  setPalette(QPalette(Qt::white));              // weißer Hintergrund
  setMinimumWidth(120);
  setMinimumHeight(120);
}


void AnalogClock::onTimeout()
{
  update();
}


void AnalogClock::paintEvent(QPaintEvent*)
{
  if (!isVisible())
    return;
  time = QTime::currentTime();                  // aktuelle Uhrzeit
  
  QPainter paint(this);
  paint.setRenderHint(QPainter::Antialiasing);
  paint.setPen(Qt::black);                      // Ziffern und Zeiger schwarz
  paint.setBrush(Qt::black);
  
  QPoint cp = rect().center();                  // widget center point
  int d = qMin(width(), height());              // we want a circular clock
  
  QTransform matrix;                            // setup transformation matrix
  matrix.translate(cp.x(), cp.y());             // origin at widget center
  matrix.scale(d / 1100.0f, d / 1100.0f);       // scale coordinate system
  
  for (int i = 0; i < 60; i++)                  // draw hour lines
  {
    paint.setWorldTransform(matrix);
    
    if (i % 5 == 0)
      paint.drawRect(380, -15, 120, 30);        // 5 minute ticks
    else
      paint.drawRect(460, -10, 40, 20);         // minute ticks
    matrix.rotate(6);
  }
  
  QPolygon pts;
  
  // Stundenzeiger
  float h_angle = 30 * (time.hour() % 12 - 3) + time.minute() / 2;
  matrix.rotate(h_angle);                       // rotate to draw hour hand
  paint.setWorldTransform(matrix);
  pts.setPoints(5,
                -60, -20,
                350, -20,
                370, 0,
                350, 20,
                -60, 20);
  paint.drawPolygon(pts);
  matrix.rotate(-h_angle);                      // rotate back to zero
  
  // Minutenzeiger
  float m_angle = (time.minute() - 15) * 6;
  matrix.rotate(m_angle);                       // rotate to draw minute hand
  paint.setWorldTransform(matrix);
  pts.setPoints(5,
                -100, -15,
                435, -15,
                450, 0,
                435, 15,
                -100, 15);
  paint.drawPolygon(pts);
  matrix.rotate(-m_angle);                      // rotate back to zero
  
  paint.setPen(Qt::red);
  paint.setBrush(Qt::red);                      // rote Füllung
  
  // Sekundenzeiger in drei Teilen
  float s_angle = (time.second() - 15) * 6;
  if (time.second() < 59)                       // kurzer Stopp für Synchronisation
    s_angle += time.msec() * 0.006;
  matrix.rotate(s_angle);
  paint.setWorldTransform(matrix);
  pts.setPoints(4,
                -54, -10,
                310, -6,
                310, 6,
                -54, 10);
  paint.drawPolygon(pts);                       // erstes Stück bis zum Kreis
  pts.setPoints(5,
                360, -5,
                480, -4,
                485, 0,
                480, 4,
                360, 5);
  paint.drawPolygon(pts);                       // zweites Stück ab Kreis
  
  paint.setPen(QPen(Qt::red, 16, Qt::SolidLine));
  paint.setBrush(Qt::NoBrush);                  // keine Füllung
  
  paint.drawEllipse(310, -25, 50, 50);          // der Kreis
  matrix.rotate(-s_angle);                      // rotate back to zero
}
