#ifndef IMAGEMARKUPWIDGET_H
#define IMAGEMARKUPWIDGET_H

#include <QApplication>
#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QVector>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QFileDialog>
#include <QDebug>
#include <QPushButton>

/*!
 * \class ImageMarkupWidget
 * \brief Класс ImageMarkupWidget предоставляет виджет для загрузки, отображения
 * и аннотирования изображений с помощью точек и регионов.
 *
 * ImageMarkupWidget позволяет пользователям загружать изображение из файла, выделять точки, кликнув на изображение,
 * объединять выделенные точки в регионы, а также сохранять/загружать эти регионы в/из файла CSV.
 * Он предлагает базовые возможности взаимодействия с изображением такие как масштабирование и навигация через события клавиатуры и/или мыши.
 */
class ImageMarkupWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief ImageMarkupWidget конструирует экземпляр ImageMarkupWidget
     * \param parent Родительский виджет для данного ImageMarkupWidget.
     */
    ImageMarkupWidget(QWidget *parent = nullptr);

public slots:
    /*!
     * \brief loadImage Открывает диалог для выбора файла изображения, который будет загружен в виджет.
     */
    void loadImage();

    /*!
     * \brief emitPointsSelected Излучает сигнал, указывающий на то, что одна или несколько точек были выделены.
     */
    void emitPointsSelected();

    /*!
     * \brief mergePoints Объединяет выделенные точки в регион.
     */
    void mergePoints();

    /*!
     * \brief saveRegionsToCsv Сохраняет определенные регионы в файл CSV.
     */
    void saveRegionsToCsv();

    /*!
     * \brief readRegionsFromCsv Загружает регионы из файла CSV.
     */
    void readRegionsFromCsv();

protected:
    /*!
     * \brief paintEvent Обрабатывает отрисовку изображения, выделенных точек и регионов на виджете.
     * \param event Событие, содержащее детали события отрисовки.
     */
    void paintEvent(QPaintEvent *event) override;

    /*!
     * \brief mousePressEvent Обрабатывает события нажатия кнопки мыши для выбора точек на изображении.
     * \param event Событие, содержащее детали события нажатия кнопки мыши.
     */
    void mousePressEvent(QMouseEvent *event) override;

    /*!
     * \brief keyPressEvent Обрабатывает события нажатия клавиш для интерактивной навигации по изображению, такие как масштабирование.
     * \param event Событие, содержащее детали события нажатия клавиши.
     */
    void keyPressEvent(QKeyEvent *event) override;

    /*!
     * \brief wheelEvent Обрабатывает события прокрутки колесика для интерактивного масштабирования изображения.
     * \param event Событие, содержащее детали события прокрутки колесика.
     */
    void wheelEvent(QWheelEvent *event) override;

signals:
    /*!
     * \brief pointsSelected Этот сигнал излучается, когда одна или несколько точек выделены на изображении.
     */
    void pointsSelected();

private:
    QImage image; ///< Отображаемое в виджете изображение.
    QVector<QPoint> points; ///< Коллекция выделенных точек на изображении.
    QVector<QVector<QPoint>> regions; ///< Коллекция регионов, каждый представлен вектором точек.
    qreal scale = 1.0; ///< Текущий масштаб отображения изображения.
};
#endif // IMAGEMARKUPWIDGET_H
