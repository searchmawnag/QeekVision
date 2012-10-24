#include "camerathread.h"

#include <QDebug>

#include <opencv/highgui.h>

CameraThread::CameraThread(QObject *parent) : QThread(parent) {
    /// Cleaning FPS counter
    _fps = 0;

    /// ToolBar Settings
    _startAction = new QAction(QIcon(":/icons/start.png"), "Start", this);
    _startAction->setToolTip("Start Capture Stream");
    _startAction->setShortcut(Qt::Key_Space);
    _startAction->setEnabled(false);
    _stopAction = new QAction(QIcon(":/icons/stop.png"), "Stop", this);
    _stopAction->setToolTip("Stop Capture Stream");
    _stopAction->setShortcut(Qt::Key_Space);
    _stopAction->setEnabled(false);
    _settingsAction = new QAction(QIcon(":/icons/settings.png"), "Stop", this);
    _settingsAction->setToolTip("Open Configuration Dialog");
    _settingsAction->setShortcut(Qt::CTRL+Qt::Key_T);
    _settingsAction->setEnabled(true);
    _subsystemLabel = new QLabel("Driver Type:");
    _subsystemComboBox = new QComboBox();
#ifdef _V4L_CAMERA_THREAD
    _subsystemComboBox->addItem("Video4Linux");
#endif //_V4L_CAMERA_THREAD
    _threadToolBar = new QToolBar("Thread Commands");
    _threadToolBar->setObjectName("threadToolBar");
    _threadToolBar->addAction(_startAction);
    _threadToolBar->addAction(_stopAction);
    _threadToolBar->addAction(_settingsAction);
    _threadToolBar->addSeparator();
    _threadToolBar->addWidget(_subsystemLabel);
    _threadToolBar->addWidget(_subsystemComboBox);

    /// ToolBar signals connections
    connect(_startAction, SIGNAL(triggered()), this, SLOT(start()));
    connect(_stopAction, SIGNAL(triggered()), this, SLOT(stop()));
}

CameraThread::~CameraThread(){ }

float CameraThread::getFPS() {
    return _fps;
}

Mat CameraThread::getFrame() {
    if(_cvMatbuffer.isEmpty()) {
        qWarning() << "[CAMERA_THREAD] << getFrame() - No Available frame in capture buffer!";
        return Mat(getHeight(), getWidth(), CV_8UC3, Scalar(0,0,0));
    }
    return _cvMatbuffer.dequeue();
}

QImage CameraThread::mat2qImage(Mat src) {
    return QImage(src.data, src.cols, src.rows, QImage::Format_RGB888);
}

QToolBar *CameraThread::toolBar() {
    return _threadToolBar;
}


