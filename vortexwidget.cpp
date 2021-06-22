#include "vortexwidget.h"
#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include <QDoubleSpinBox>

int VortexWidget::count = 0;

VortexWidget::VortexWidget(QWidget *parent): QWidget(parent)
{
    count++;
    ID = count;

    mainLayout = new QHBoxLayout;
    this->setLayout(mainLayout);

    labelFor_count = new QLabel(tr("Вихрь %1").arg(ID));
    labelFor_count->setFixedWidth(45);
    //labelFor_count->setMinimumSize(45,20);

    labelFor_x = new QLabel(tr("x:"));
    //labelFor_x->setAlignment(Qt::AlignCenter);
    labelFor_x->setFixedWidth(10);
    labelFor_y = new QLabel(tr("y:"));
    labelFor_y->setAlignment(Qt::AlignVCenter);
    labelFor_y->setFixedWidth(10);
    labelFor_omega = new QLabel(tr("omega:"));
    labelFor_omega->setFixedWidth(40);

    spinBoxFor_x = new QDoubleSpinBox;
    spinBoxFor_x->setMinimum(-999.99);
    spinBoxFor_x->setMaximum(999.99);
    spinBoxFor_x->setMinimumSize(50,20);

    spinBoxFor_y = new QDoubleSpinBox;
    spinBoxFor_y->setMinimum(-999.99);
    spinBoxFor_y->setMaximum(999.99);
    spinBoxFor_y->setMinimumSize(50,20);

    spinBoxFor_omega = new QDoubleSpinBox;
    spinBoxFor_omega->setMinimum(-999.99);
    spinBoxFor_omega->setMaximum(999.99);
    spinBoxFor_omega->setMinimumSize(50,20);

    removeWidget = new QPushButton("Исключить");
    removeWidget->setMinimumSize(40,20);
    if (ID==1 || ID==2){
        removeWidget->setEnabled(false);
    }

    mainLayout->addWidget(labelFor_count);
    mainLayout->addWidget(labelFor_x);
    mainLayout->addWidget(spinBoxFor_x);
    mainLayout->addWidget(labelFor_y);
    mainLayout->addWidget(spinBoxFor_y);
    mainLayout->addWidget(labelFor_omega);
    mainLayout->addWidget(spinBoxFor_omega);
    mainLayout->addWidget(removeWidget);

    QObject::connect(removeWidget, &QPushButton::clicked, this, &VortexWidget::onRemoveWidget);
    this->setMinimumSize(380,35);
    this->setMaximumHeight(40);
}

VortexWidget::~VortexWidget()
{
    --count;
    delete labelFor_count;
    delete spinBoxFor_x;
    delete spinBoxFor_y;
    delete spinBoxFor_omega;
    delete removeWidget;
    delete mainLayout;
}

void VortexWidget::onRemoveWidget()
{
    this->~VortexWidget();
}
