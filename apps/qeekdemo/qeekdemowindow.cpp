#include "qeekdemowindow.h"
#include "opencvcamera.h"
#include "v4lcamera.h"
#include "ui_qeekdemowindow.h"

#define HEIGHT_OFFSET 47

QeekDemoWindow::QeekDemoWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::QeekDemoWindow) {
    ui->setupUi(this);

    capture3ad = new V4LCamera();
    driverSelectDialog = new QVDriverSelect(DRIVER_V4L);
    imageWidget = new QVDisplayWidget(ui->centralwidget);

    connect(driverSelectDialog, SIGNAL(accepted()), this, SLOT(acceptedDriverSelection()));
    connect(driverSelectDialog, SIGNAL(accepted()), this, SLOT(show()));

    driverSelectDialog->move(200, 200);
    driverSelectDialog->show();
    ui->actionSaveFrame->setEnabled(false);

}

QeekDemoWindow::~QeekDemoWindow() {
    delete ui;
    if (capture3ad) {
        if (capture3ad->isRunning())
            capture3ad->stop();
        capture3ad->deleteLater();
    }
    delete imageWidget;
}

void QeekDemoWindow::acceptedDriverSelection() {
    switch(driverSelectDialog->getDriverType()) {
    case DRIVER_V4L:
        break;
    default:
        delete capture3ad;
        capture3ad = new OpenCVCamera();
        break;
    }
    connect(capture3ad, SIGNAL(availableFrame()), this, SLOT(showFrame()));
    addToolBar(capture3ad->toolBar());
}

void QeekDemoWindow::on_actionSaveFrame_triggered() {
    if (imwrite("capturedFrame.png", currentFrame))
        ui->statusbar->showMessage("Frame succesfully Saved!");
    else
        ui->statusbar->showMessage("Error saving frame!");
}

void QeekDemoWindow::showFrame() {
    ui->actionSaveFrame->setEnabled(true);
    this->resize(capture3ad->getWidth(), capture3ad->getHeight() + HEIGHT_OFFSET + capture3ad->toolBar()->size().height());
    currentFrame = capture3ad->getFrame();
    imageWidget->displayImage(currentFrame);
    if (imageWidget->hasMouseTracking()) {
        ui->statusbar->showMessage(QString("Pos: (%1,%2)").arg(imageWidget->getMouseXPos()).arg(imageWidget->getMouseYPos()));
    }
}
