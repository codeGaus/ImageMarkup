#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    widget = new ImageMarkupWidget;
    scrollArea->setWidget(widget);

    setCentralWidget(scrollArea);

    setupFileMenu();
}

void MainWindow::setupFileMenu()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(tr("Open image..."),widget, &ImageMarkupWidget::loadImage);//???
    fileMenu->addAction(tr("Open markup..."), widget, &ImageMarkupWidget::readRegionsFromCsv);
    fileMenu->addAction(tr("Save markup as..."), widget, &ImageMarkupWidget::saveRegionsToCsv);
    menuBar()->addAction(tr("Merge points"), widget, &ImageMarkupWidget::mergePoints);
}
