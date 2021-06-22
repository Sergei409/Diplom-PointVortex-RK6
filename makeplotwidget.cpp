#include "makeplotwidget.h"

MakePlotWidget::MakePlotWidget(QVector<PointVortex>& vortex, const int& t_end, const double& h)
{
    this->setWindowTitle("График траекторий");
    this->setGeometry(100, 100, 600, 600);
    this->legend->setVisible(true);
    QCPCurve **vortexfunc = new QCPCurve * [vortex.size()];
    //errorLayout = new QVBoxLayout;

    for (int l=0; l<vortex.size(); l++){
        vortexfunc[l]= new QCPCurve(this->xAxis, this->yAxis);

        QVector<QCPCurveData> dataVortex(t_end / h);
        for (int i=0; i< t_end / h; ++i)
        {
          dataVortex[i] = QCPCurveData(i, vortex[l].get_x_i(i), vortex[l].get_y_i(i));
        }

        vortexfunc[l]->data()->set(dataVortex, true);

        vortexfunc[l]->setName(tr("%1 вихрь").arg(l+1));

        switch (l){
        case 0:
            vortexfunc[l]->setPen(QPen(Qt::blue));
            break;
        case 1:
            vortexfunc[l]->setPen(QPen(Qt::red));
            break;
        case 2:
            vortexfunc[l]->setPen(QPen(Qt::green));
            break;
        default:
            srand(l);
            vortexfunc[l]->setPen(QPen({rand() % 255, rand() % 255, rand() % 255}));
            break;
        }
    }

    this->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    this->axisRect()->setupFullAxesBox();
    this->rescaleAxes();
    this->plotLayout()->addElement(1, 0, new QCPTextElement(this, tr("Для шага ЧМ %1 погрешность по Q %2").arg(h).arg(PointVortex::error_ForQ(vortex, t_end, h),0, 'e', 2)));
    this->plotLayout()->addElement(2, 0, new QCPTextElement(this, tr("Для шага ЧМ %1 погрешность по P %2").arg(h).arg(PointVortex::error_ForP(vortex, t_end, h),0, 'e', 2)));
    this->plotLayout()->addElement(3, 0, new QCPTextElement(this, tr("Для шага ЧМ %1 погрешность по I %2").arg(h).arg(PointVortex::error_ForI(vortex, t_end, h),0, 'e', 2)));
    delete[] vortexfunc;
    vortex.clear();
}

MakePlotWidget::~MakePlotWidget()
{

}

void MakePlotWidget::closeEvent(QCloseEvent *event)
{
    this->~MakePlotWidget();
    QWidget::closeEvent(event);
}
