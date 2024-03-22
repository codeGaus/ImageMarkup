#include "imagemarkupwidget.h"


ImageMarkupWidget::ImageMarkupWidget(QWidget *parent) : QWidget(parent)
    {
        setFixedSize(200, 150);
        setWindowTitle("Image Markup Tool");

        connect(this, &ImageMarkupWidget::pointsSelected, this, &ImageMarkupWidget::mergePoints);
    }


    void ImageMarkupWidget::paintEvent(QPaintEvent *event)
    {
        QPainter painter(this);

        if (!image.isNull()) {
            painter.drawImage(0, 0, image.scaled(image.size() * scale));
            setFixedSize(image.width()*scale, image.height()*scale);
        }

        painter.setPen(QPen(Qt::red, 2,Qt::DotLine));
        for (int i = 0; i < points.size() - 1; ++i)
        {
            painter.drawLine(points[i] * scale, points[i + 1] * scale);
        }

        if (points.size() > 0) {
            painter.drawLine(points[points.size() - 1] * scale, points[0]* scale);
            painter.setPen(QPen(Qt::green, 4));
            painter.drawPoint(points[points.size() - 1] * scale);
        }

        painter.setPen(QPen(Qt::green, 2));
        painter.setBrush(QBrush(Qt::green,Qt::BDiagPattern));
        for (int i = 0; i < regions.size(); ++i)
        {
            QVector<QPoint> regionI = regions[i];
            for (int j = 0; j < regionI.size(); ++j){
                regionI[j]*=scale;
            }
            painter.drawPolygon(QPolygon(regionI));
        }
    }

    void ImageMarkupWidget::mousePressEvent(QMouseEvent *event)
    {
        QPoint clickPos = event->pos();
        bool isOnPol = false;
        QPoint scaledPos = clickPos / scale;

        for (int i = 0; i < regions.size(); ++i)
        {
            QVector<QPoint> regionI = regions[i];
            QPolygon poly(regionI);

            if (poly.containsPoint(scaledPos, Qt::WindingFill)) {
                this->mergePoints();
                for (QPoint &pt : regionI) {
                    points.push_back(pt);
                }
                isOnPol = true;
                break;
                regions.remove(i);
            }
        }
        if (!isOnPol){
            points.push_back(scaledPos);
        }
        this->setFocus();
        update();
    }

    void ImageMarkupWidget::keyPressEvent(QKeyEvent *event)
    {
        if (event->key() == Qt::Key_Z && (event->modifiers() & Qt::ControlModifier))
        {
            if (!points.isEmpty()) {
                points.pop_back();
                update();
            } else if (!regions.isEmpty()){
                points = regions.back();
                regions.pop_back();
                update();
            }
        }
    }

    void ImageMarkupWidget::wheelEvent(QWheelEvent *event)
    {
        if (QApplication::keyboardModifiers() == Qt::ControlModifier)
        {
        if (event->angleDelta().y() > 0)
        {
            if (scale < 3) {
            scale *= 1.1;
            }
        }
        else
        {
            if (scale > 0.1){
            scale /= 1.1;
            }
        }
        event->accept();
        update();
        }
    }

    void ImageMarkupWidget::loadImage()
    {
        QString fileName = QFileDialog::getOpenFileName(this, "Open Image", "", "Images (*.png *.jpg *.jpeg)");
        if (!fileName.isEmpty())
        {
            image = QImage(fileName);
            update();
        }
    }

    void ImageMarkupWidget::emitPointsSelected()
    {
        emit pointsSelected();
    }

    void ImageMarkupWidget::mergePoints()
    {
        regions.append(points);
        points.clear();
        update();
    }

    void ImageMarkupWidget::saveRegionsToCsv()
    {
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "",
                                tr("CSV Files (*.csv);;All Files (*)"));
        if (fileName.isEmpty())
            return;

        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qWarning("Не удалось открыть файл.");
            return;
        }

        QTextStream out(&file);
        for (const QVector<QPoint> &region : regions) {
            QStringList pointsList;
            for (const QPoint &point : region) {
                pointsList.append(QString("%1,%2").arg(point.x()).arg(point.y()));
            }
            out << pointsList.join(";") << "\n";
        }
    }

    void ImageMarkupWidget::readRegionsFromCsv()
    {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",
                                tr("CSV Files (*.csv);;All Files (*)"));
        if (fileName.isEmpty())
            return;

        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qWarning("Не удалось открыть файл.");
            return;
        }

        QTextStream in(&file);
        regions.clear();

        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList pointPairs = line.split(";");
            QVector<QPoint> region;
            for (const QString &pointPair : pointPairs) {
                QStringList points = pointPair.split(",");
                if (points.size() == 2) {
                    int x = points.at(0).toInt();
                    int y = points.at(1).toInt();
                    region.append(QPoint(x, y));
                }
            }
            regions.append(region);
        }
    }

