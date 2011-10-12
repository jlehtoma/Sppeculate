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
    TrainingSet trainingItems;

    void closeEvent(QCloseEvent *event);
    void readSettings();
    void writeSettings();
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

private slots:
    void openFolder();
    void showAbout();
    void showImage(int index);

    void nextItem();
    void prevItem();

    void updateUI();

    void normalSize();
    void zoomIn();
    void zoomOut();
};

#endif // MAINWINDOW_H
