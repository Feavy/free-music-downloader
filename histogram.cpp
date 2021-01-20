#include "histogram.h"
#include "histogramrectangle.h"

#include <QDebug>
#include <vector>
#include <cstdlib>
#include <QColor>

Histogram::Histogram(QWidget *parent) : QWidget(parent),
    _rectanglesAmount(4)
{
    _rectangles[0] = new HistogramRectangle(this, "NoCopyrightSound", QColor(255, 80, 80));
    _rectangles[1] = new HistogramRectangle(this, "FutureHouseMusic", QColor(51, 102, 255));
    _rectangles[2] = new HistogramRectangle(this, "MrSuicideSheep", QColor(255, 204, 102));
    _rectangles[3] = new HistogramRectangle(this, "MonsterCat", QColor(51, 153, 102));

    for(HistogramRectangle *rect : _rectangles)
        connect(rect, SIGNAL(valueChanged(int)), this, SLOT(rectangleValueChanged(int)));

}

Histogram::~Histogram(){
    delete _rectangles;
}

double Histogram::getRectangleValue(int index){
    return _rectangles[index]->getAbsoluteValue();
}

void Histogram::rectangleValueChanged(int newValue){

    HistogramRectangle *emitter = qobject_cast<HistogramRectangle*>(sender());

    int total = 0;

    for(HistogramRectangle *rect : _rectangles)
        total += rect->getValue();

    for(HistogramRectangle *rect : _rectangles)
        rect->setAbsoluteValue((double)(rect->getValue())/total*100);

}

void Histogram::setGeometry(int x, int y, int w, int h){
    QWidget::setGeometry(x, y, w, h);
    x = 0;
    for(HistogramRectangle *rect : _rectangles){
        rect->setGeometry(x, 0, w/5, h);
        x += w/5 + w/15;
    }
}
