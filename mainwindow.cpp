#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "trainingset.h"
#include "configdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::Dark);
    imageLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    imageLabel->setScaledContents(true);

    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(showAbout()));
    connect(ui->actionOpenFolder, SIGNAL(triggered()), this, SLOT(openFolder()));
    connect(ui->actionNextItem, SIGNAL(triggered()), this, SLOT(nextItem()));
    connect(ui->actionPrevItem, SIGNAL(triggered()), this, SLOT(prevItem()));
    connect(ui->actionZoomIn, SIGNAL(triggered()), this, SLOT(zoomIn()));
    connect(ui->actionZoomOut, SIGNAL(triggered()), this, SLOT(zoomOut()));
    connect(ui->actionZoomDefault, SIGNAL(triggered()), this, SLOT(normalSize()));
    connect(ui->zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(zoom(int)));
    connect(ui->actionSettings, SIGNAL(triggered()), this, SLOT(showConfig()));

    connect(ui->actionFullscreen, SIGNAL(triggered(bool)),
            this, SLOT(toggleFullScreen(bool)));

    connect(ui->actionAbout_Qt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    // Initiate the DataForm
    dataForm = new DataForm;
    ui->formDockWidget->setWidget(dataForm);

    // Set the show/hide action for the formDockWidget
    QAction *formAction = ui->formDockWidget->toggleViewAction();
    formAction->setIcon(QIcon(":/share/icons/editor.svg"));
    formAction->setShortcut(QKeySequence(tr("F6")));
    formAction->setToolTip("Toggle answer form");
    ui->menuView->insertAction(ui->actionFullscreen, formAction);
    ui->mainToolBar->insertAction(ui->actionSettings, formAction);

    ui->scrollArea->setWidget(imageLabel);
    trainingItems = new TrainingSet;

    // TODO: traingItems MUST be initialized in the constructor!
    scaleFactor = 1.0;
    //qDebug() << trainingItems->count();

    // Read the initial settings
    readSettings();

    updateUI();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete trainingItems;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox msgBox;
    msgBox.setText("You are about to exit");
    msgBox.setInformativeText("Are you sure?");
    msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
    msgBox.setDefaultButton(QMessageBox::Yes);
    msgBox.setIconPixmap(QPixmap(":/images/help-contents.svg"));
    int ret = msgBox.exec();
    if (ret == QMessageBox::Yes) {
                writeSettings();
                event->accept();
        } else {
                event->ignore();
        }
}

void MainWindow::readSettings()
{
        qDebug() << "Reading settings";
        QSettings settings("Sppeculate");
        restoreGeometry(settings.value("MainWindow/geometry").toByteArray());
        restoreState(settings.value("MainWindow/windowState").toByteArray());
        QString recentPath(settings.value("MainWindow/recentPath").toString());
        if (!recentPath.isEmpty()){
            trainingItems->readData(recentPath);
            qDebug() << "Found path to previous location: " << recentPath;
            currentIndex = 0;
            showImage(currentIndex);
        }
        else {
            qDebug("No previous settings found");
        }
}

void MainWindow::writeSettings()
{
        qDebug() << "Writing settings";
        QSettings settings("Sppeculate");
        settings.setValue("MainWindow/geometry", saveGeometry());
        settings.setValue("MainWindow/windowState", saveState());
        QString recentPath(trainingItems->getRootPath());
        if (!recentPath.isEmpty()) {
            settings.setValue("MainWindow/recentPath", recentPath);
            qDebug() << "Wrote location " << recentPath;
        }
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
    trainingItems->readData(dir);
    currentIndex = 0;
    showImage(currentIndex);
    updateUI();
}

void MainWindow::showAbout()
{
    QString aboutText("<H3>Sppeculate " + QString(APP_VERSION) + "</H3>");
    QMessageBox::about(this, "About", aboutText);
}

void MainWindow::showConfig()
{
    configDialog *dlg = new configDialog(this);
    if (dlg->exec()) {
        int i = 1;
    }
}

void MainWindow::showImage(int index)
{
    if (trainingItems->count() >= index) {

        QString filePath = trainingItems->getFilePath(index);
        if (!filePath.isEmpty()) {
                QImage image(filePath);
                if (image.isNull()) {
                    QMessageBox::information(this, tr("Sppeculate"),
                                             tr("Cannot load %1.").arg(filePath));
                    return;
                }
        imageLabel->setPixmap(QPixmap::fromImage(image));
        imageLabel->adjustSize();
        scaleFactor = 1.0;

        }
    }
}

void MainWindow::updateUI()
{
    if (trainingItems->count() > 0) {
        ui->actionZoomIn->setEnabled(true);
        ui->actionZoomOut->setEnabled(true);
        ui->actionZoomDefault->setEnabled(true);
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
        ui->zoomLabel->setText(QString::number(scaleFactor * 100.0) + "%");
        ui->zoomSlider->setValue(int(scaleFactor * 100.0));
    }
    else {
        ui->actionZoomIn->setEnabled(false);
        ui->actionZoomOut->setEnabled(false);
        ui->actionZoomDefault->setEnabled(false);
    }
    ui->actionZoomIn->setEnabled(scaleFactor < 3.0);
    ui->actionZoomOut->setEnabled(scaleFactor > 0.333);
}

void MainWindow::normalSize()
{
    qDebug("Zooming to default size");
    imageLabel->adjustSize();
    scaleFactor = 1.0;
    updateUI();
}

void MainWindow::zoomIn()
{
    scaleImage(1.25);
}

void MainWindow::zoomOut()
{
    scaleImage(0.8);
}

void MainWindow::zoom(int scaling)
{
    scaleFixedImage(scaling);
}

void MainWindow::scaleImage(double factor)
{
    Q_ASSERT(imageLabel->pixmap());
    scaleFactor *= factor;
    qDebug("Zooming with factor %f", scaleFactor);
    //imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());
    qDebug() << scaleFactor * imageLabel->pixmap()->size();
    imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

    adjustScrollBar(ui->scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(ui->scrollArea->verticalScrollBar(), factor);
    updateUI();
}

void MainWindow::scaleFixedImage(int factor)
{
    Q_ASSERT(imageLabel->pixmap());
    scaleFactor = factor / 100.0;
    qDebug("Zooming with factor %f", scaleFactor);
    //imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());
    qDebug() << scaleFactor * imageLabel->pixmap()->size();
    imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

    adjustScrollBar(ui->scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(ui->scrollArea->verticalScrollBar(), factor);
    updateUI();
}

void MainWindow::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}

void MainWindow::toggleFullScreen(bool toggle)
{
    if (toggle){
        this->showFullScreen();
    } else {
        this->showNormal();
        this->showMaximized();
    }
}
