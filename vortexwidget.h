#ifndef VORTEXWIDGET_H
#define VORTEXWIDGET_H

//#include <QObject>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QHBoxLayout;
class QLabel;
class QPushButton;
class QDoubleSpinBox;
QT_END_NAMESPACE

class VortexWidget: public QWidget
{
    Q_OBJECT
public:
    VortexWidget(QWidget* parent);
    ~VortexWidget();

    void onRemoveWidget();

    static int count;

    QDoubleSpinBox *spinBoxFor_x;
    QDoubleSpinBox *spinBoxFor_y;
    QDoubleSpinBox *spinBoxFor_omega;

private:
    int ID=0;

    QHBoxLayout *mainLayout;

    QLabel *labelFor_count;
    QLabel *labelFor_x;
    QLabel *labelFor_y;
    QLabel *labelFor_omega;
    QPushButton *removeWidget;
};

#endif // VORTEXWIDGET_H
