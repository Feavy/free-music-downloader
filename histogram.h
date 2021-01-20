#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <histogramrectangle.h>
#include <QWidget>
#include <QList>

class Histogram : public QWidget
{
    Q_OBJECT
public:
    Histogram(QWidget *parent = 0);
    ~Histogram();
    void setGeometry(int x, int y, int w, int h);
    double getRectangleValue(int index);
private:
    HistogramRectangle* _rectangles[4];
    int _rectanglesAmount;
signals:

public slots:
    void rectangleValueChanged(int newValue);
};

#endif // HISTOGRAM_H
