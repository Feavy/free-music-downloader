#ifndef HISTOGRAMRECTANGLE_H
#define HISTOGRAMRECTANGLE_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QLabel>

class HistogramRectangle : public QWidget
{
    Q_OBJECT
public:
    HistogramRectangle(QWidget *parent, QString title, QColor color);
    ~HistogramRectangle();
    void paintEvent(QPaintEvent *event);
    void setGeometry(int x, int y, int w, int h);
    void setValue(int value);
    int getValue() const;
    QString getName() const;
    void setAbsoluteValue(double value);
    double getAbsoluteValue() const;
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    bool _mousePressed;
    double _absoluteValue;
    int _value;
    QColor _color;
    QLabel *_channelName;
signals:
    void valueChanged(int newValue);
public slots:
};

#endif // HISTOGRAMRECTANGLE_H
