#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <imagemarkupwidget.h>

/*!
 * \class MainWindow
 * \brief Класс MainWindow представляет главное окно приложения.
 *
 * Этот класс унаследован от QMainWindow и организует основные виджеты и интерфейсы пользователя,
 * такие как меню, панели инструментов, статус-бар и центральный виджет. В данном случае, центральным виджетом
 * является ImageMarkupWidget, который позволяет пользователю работать с разметкой изображений.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief Конструктор класса MainWindow.
     * \param parent Указатель на родительский виджет, по умолчанию равен nullptr.
     *
     * Инициализирует новый экземпляр MainWindow с заданным родителем.
     */
    MainWindow(QWidget *parent = nullptr);

private:
    ImageMarkupWidget *widget; //!< Указатель на виджет для разметки изображений.
    QScrollArea *scrollArea; //!< Указатель на область прокрутки для размещения виджетов, требующих больше пространства, чем доступно.

    /*!
     * \brief Настраивает меню файла в главном окне.
     *
     * Этот метод добавляет пункты меню и соответствующие действия для работы с файлами,
     * такие как открытие и сохранение.
     */
    void setupFileMenu();
};

#endif // MAINWINDOW_H
