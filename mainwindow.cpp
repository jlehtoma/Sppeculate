#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    imageLabel->setScaledContents(true);

    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(showAbout()));
    connect(ui->actionOpenFolder, SIGNAL(triggered()), this, SLOT(openFolder()));
    connect(ui->actionNextItem, SIGNAL(triggered()), this, SLOT(nextItem()));
    connect(ui->actionPrevItem, SIGNAL(triggered()), this, SLOT(prevItem()));

    ui->scrollArea->setWidget(imageLabel);

    // TODO: traingItems MUST be initialized in the constructor!
    scaleFactor = 1.0;
    //qDebug() << trainingItems->count();

    updateUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::nextItem()
{
    qDebug("Next item");
    if ((currentIndex + 1) <= trainingItems->count()) {
        ++currentIndex;
        qDebug("CurrentIndex changed to: %d", currentIndex);
        showImage(currentIndex);
        updateUI();
    }
}

void MainWindow::prevItem()
{
    if ((currentIndex - 1) >= 0) {
        --currentIndex;
        qDebug("CurrentIndex changed to: %d", currentIndex);
        showImage(currentIndex);
        updateUI();
    }
}

void MainWindow::openFolder()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    "/home",
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    trainingItems = new TrainingSet(dir);
    currentIndex = 0;
    showImage(currentIndex);
    updateUI();
}

void MainWindow::showAbout()
{
    QString aboutText("<H3>Sppeculate " + QString(APP_VERSION) + "</H3>");
    QMessageBox::about(this, "About", aboutText);
}

void MainWindow::showImage(int index)
{
    if (trainingItems->count() >= index) {

        QString filePath = trainingItems->filePath(index);
        if (!filePath.isEmpty()) {
                QImage image(filePath);
                if (image.isNull()) {
                    QMessageBox::information(this, tr("Sppeculate"),
                                             tr("Cannot load %1.").arg(filePath));
                    return;
                }
        imageLabel->setPixmap(QPixmap::fromImage(image));
        scaleFactor = 1.0;

        ui->infoEdit->setText("<H2>" + trainingItems->fileName(index) + "</H2>");

        }
    }
}

void MainWindow::updateUI()
{
    if (trainingItems->count() > 0) {
        if (currentIndex == 0) {
            ui->actionPrevItem->setEnabled(false);
            ui->actionNextItem->setEnabled(true);
        }
        else {
            if (currentIndex == trainingItems->count()) {
                ui->actionPrevItem->setEnabled(true);
                ui->actionNextItem->setEnabled(false);
            }
            else {
                ui->actionPrevItem->setEnabled(true);
                ui->actionNextItem->setEnabled(true);
            }
        }
        ui->statusBar->showMessage("Zoom: " + QString::number(scaleFactor * 100.0) + "%");
    }


}

void MainWindow::normalSize()
{
    imageLabel->adjustSize();
    scaleFactor = 1.0;
}

void MainWindow::zoomIn()
{
    scaleImage(1.25);
}

void MainWindow::zoomOut()
{
    scaleImage(0.8);
}

void MainWindow::scaleImage(double factor)
{
    Q_ASSERT(imageLabel->pixmap());
    scaleFactor *= factor;
    imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

    adjustScrollBar(ui->scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(ui->scrollArea->verticalScrollBar(), factor);

    ui->actionZoomIn->setEnabled(scaleFactor < 3.0);
    ui->actionZoomOut->setEnabled(scaleFactor > 0.333);
}

void MainWindow::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}
