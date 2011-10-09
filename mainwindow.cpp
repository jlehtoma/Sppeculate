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

    connect(ui->actionOpenFolder, SIGNAL(triggered()), this, SLOT(openFolder()));
    connect(ui->prevButton, SIGNAL(clicked()), this, SLOT(prevItem()));
    connect(ui->nextButton, SIGNAL(clicked()), this, SLOT(nextItem()));

    ui->scrollArea->setWidget(imageLabel);
   //setCentralWidget(ui->scrollArea);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::nextItem()
{
    if ((currentIndex + 1) <= trainingItems->count()) {
        ++currentIndex;
        showImage(currentIndex);
    }
}

void MainWindow::prevItem()
{
    if ((currentIndex - 1) >= 0) {
        --currentIndex;
        showImage(currentIndex);
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
}

void MainWindow::showImage(int index)
{
    qDebug("Index: %d", index);
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
