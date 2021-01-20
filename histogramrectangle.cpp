#include "histogramrectangle.h"
#include <QDebug>

HistogramRectangle::HistogramRectangle(QWidget *parent, QString title, QColor color) : QWidget(parent),
    _color(color),
    _channelName(new QLabel(this)),
    _value(25),
    _mousePressed(false),
    _absoluteValue(25.0)
{
    _channelName->setAlignment(Qt::AlignCenter);
    _channelName->setText(title);
}

HistogramRectangle::~HistogramRectangle(){
    delete _channelName;
}

void HistogramRectangle::mousePressEvent(QMouseEvent *event){
    if(event->y() <= height()-20){
        _mousePressed = true;
        setValue(100-event->y()/2);
        emit valueChanged(100-event->y()/2);
    }
}

void HistogramRectangle::mouseReleaseEvent(QMouseEvent *event){
    if(event->y() <= height()-20)
        _mousePressed = false;
}

void HistogramRectangle::mouseMoveEvent(QMouseEvent *event){
    if(_mousePressed){
        setValue(100-event->y()/2);
        emit valueChanged(100-event->y()/2);
    }
}

void HistogramRectangle::setValue(int value){
    _value = (value < 0) ? 0 : (value) > 100 ? 100 : value;
    repaint();
}

int HistogramRectangle::getValue() const{
    return _value;
}

void HistogramRectangle::setAbsoluteValue(double value){
    _absoluteValue = value;
}

double HistogramRectangle::getAbsoluteValue() const{
    return _absoluteValue;
}

QString HistogramRectangle::getName() const{
    return _channelName->text();
}

void HistogramRectangle::setGeometry(int x, int y, int w, int h){
    QWidget::setGeometry(x, y, w, h);
    _channelName->setGeometry(0, h-20, w, 20);
}

void HistogramRectangle::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QRect rect = event->rect();
    rect.setHeight(rect.height()-20);
    QRect oldRect = rect;
    rect.setY(rect.height()-rect.height()*_value/100);
    painter.fillRect(rect, _color);
    painter.setPen(_color.lighter(150));
    painter.drawRect(oldRect);
    painter.drawRect(oldRect.x()+1, oldRect.y()+1, oldRect.width()-1, oldRect.height()-1);
}

