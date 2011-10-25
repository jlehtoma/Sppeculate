#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include "dataform.h"
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
    DataForm *dataForm;
    QLabel *imageLabel;
    int currentIndex;
    double scaleFactor;
    TrainingSet *trainingItems;

    void closeEvent(QCloseEvent *event);
    void readSettings();
    void writeSettings();
    void scaleImage(double factor);
    void scaleFixedImage(int factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

private slots:
    void openFolder();
    void showAbout();
    void showConfig();
    void showImage(int index);

    void toggleFullScreen(bool toggle);

    void nextItem();
    void prevItem();

    void updateUI();

    void normalSize();
    void zoomIn();
    void zoomOut();
    void zoom(int scaling);
};

#endif // MAINWINDOW_H
