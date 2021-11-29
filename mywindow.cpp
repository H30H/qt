#include "mywindow.h"
#include "mainwindow.h"
#include "element.h"

#include <QGridLayout>
#include <QSurfaceFormat>

myWindow::myWindow()
{    
    QSurfaceFormat fmt;
    fmt.setSamples(8); //2, 4, 8, 16

    auto *w = new MainWindow(this);
    w->setFormat(fmt);
    w->resetSimulateSpeed(40);
    w->resetAccuracy(5000);

//    auto *elem = new element(150, std::pair<int, int>(500, 500), std::pair<int, int>(0, 0), {0, 0}, w);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(w, 0, 0);
    setLayout(layout);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, w, &MainWindow::animate);
    timer->start(13);
}
