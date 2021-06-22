#ifndef MAKEPLOTWIDGET_H
#define MAKEPLOTWIDGET_H

#include <QWidget>
#include "pointvortex.h"
#include "qcustomplot.h"

//class QVBoxLayout;

class MakePlotWidget: public QCustomPlot
{
private:
    //QVBoxLayout *errorLayout;
protected:
    void closeEvent(QCloseEvent *event);
public:
    MakePlotWidget(QVector<PointVortex>& vortex, const int& t_end, const double& h);
    ~MakePlotWidget();
};

#endif // MAKEPLOTWIDGET_H
