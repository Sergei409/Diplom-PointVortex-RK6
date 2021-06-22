#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mainLayout = new QVBoxLayout(this);
    widgetForScroll = new QWidget(this);

    button_1 = new VortexWidget(this);
    button_2 = new VortexWidget(this);
    mainLayout->addWidget(button_1);
    mainLayout->addWidget(button_2);

    widgetForScroll->setLayout(mainLayout);

    ui->scrollArea->setWidgetResizable( true );
    ui->scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
    ui->scrollArea->setWidget(widgetForScroll);

    QObject::connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::onAddWidget);
    QObject::connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::makePlot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onAddWidget()
{
    button = new VortexWidget(this);
    mainLayout->addWidget(button);
}

void MainWindow::makePlot()
{
    double h = ui->doubleSpinBox_2->value();
    int t_end = ui->spinBox->value();
    int K = mainLayout->count();
    QVector<PointVortex> vortex(K);

    for (int i = 0; i<K;  i++)
    {
        VortexWidget* widget = qobject_cast<VortexWidget*>(mainLayout->itemAt(i)->widget());
        vortex[i].put(widget->spinBoxFor_x->value(), widget->spinBoxFor_y->value(), widget->spinBoxFor_omega->value());
    }

    PointVortex::RK6(vortex, vortex.size(), t_end, h);

    plot = new MakePlotWidget(vortex, t_end, h);
    plot->show();
}

void MainWindow::on_action_triggered()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("О программе");
    msgBox.setText("Первое поле ввода для ввода начальных значений точечного вихря по оси абсцисс\n"
"Второе поле ввода для ввода начальных значений точечного вихря по оси ординат\n"
"Третье поле ввода для ввода значения интенсивности точечного вихря");
    msgBox.exec();
}

void MainWindow::on_action_2_triggered()
{
    QApplication::quit();
}
