#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include "vortexwidget.h"
#include "pointvortex.h"
#include "qcustomplot.h"
#include "makeplotwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

QT_BEGIN_NAMESPACE
class QVBoxLayout;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //void onAddWidget();

private:
    Ui::MainWindow *ui;

    QVBoxLayout *mainLayout;
    QWidget *widgetForScroll;

    VortexWidget* button_1;
    VortexWidget* button_2;
    VortexWidget* button;

    MakePlotWidget *plot;

private slots:
    void makePlot();
    void onAddWidget();
    void on_action_triggered();
    void on_action_2_triggered();
};
#endif // MAINWINDOW_H
