#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include "trainingset.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QLabel *imageLabel;
    int currentIndex;
    double scaleFactor;
    TrainingSet *trainingItems;

private slots:
    void openFolder();
    void showImage(int index);
    void nextItem();
    void prevItem();
};

#endif // MAINWINDOW_H
