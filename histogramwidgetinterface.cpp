#include "histogramwidgetinterface.h"

HistoGramWidgetInterface::HistoGramWidgetInterface()
{

}

QString HistoGramWidgetInterface::name(){
    return "Histogram";
}

QString HistoGramWidgetInterface::group(){
    return "Display Widgets";
}

QString HistoGramWidgetInterface::toolTip(){
    return "nothing";
}

QString HistoGramWidgetInterface::whatsThis(){
    return "A simple histogram.";
}

QWidget HistoGramWidgetInterface::createWidget(QWidget *parent){
    return new Histogram(parent);
}
