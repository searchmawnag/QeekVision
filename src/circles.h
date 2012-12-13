#ifndef CIRCLES_H
#define CIRCLES_H

#include <opencv2/imgproc/imgproc.hpp>
#include <QCheckBox>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QRadioButton>
#include <QSlider>
#include <QSpinBox>
#include <QWidget>

#include "ellipseobject.h"
#include "histograms.h"
#include "processthread.h"



using namespace cv;
using namespace std;

class Circles : public ProcessThread
{
    Q_OBJECT
private:
    /// UI members
    QCheckBox *_showBlur, *_showCanny, *_equalize;
    QComboBox *_countoursApprox;
    QDoubleSpinBox *_eccentricityThreshold, *_errorSlider, *_sigmaX, *_sigmaY;
    QHBoxLayout *_imageFormatLayout, *_kernelLayout, *_showLayout, *_sigmaLayout, *_thresholdLayout;
    QLabel *_blurTypeLabel, *_countoursApproxLabel, *_eccentricityThresholdLabel, *_erodeDilateStepsLabel, *_errorLabel,
            *_kernelSizeLabel, *_minRadiusLabel, *_maxRadiusLabel, *_param1Label, *_param2Label, *_sigmaLabel, *_thresholdLabel;
    QLineEdit *_kernelSizeValue, *_thresholdValue;
    QRadioButton *_standardBlur, *_gaussianBlur;
    QSpinBox  *_minRadiusSlider, *_maxRadiusSlider, *_param1Slider, *_param2Slider;
    QSlider *_kernelSize, *_erodeDilateSteps, *_thresholdSlider;
    QWidget *_kernelWidget, *_showWidget, *_sigmaWidget, *_thresholdWidget;
    QToolBar *_circlesToolBar;

    /// Output
    EllipseObject ellipse_;
    bool circleFound_, ellipseFound_;
    Mat blurFrame_, cannyFrame_, _histFrame;

    /// Input/Output
    Point frameCenter;

private slots:
    void kernelValueChanged(int value);
    void selectBlurType(bool value);
    void thresholdValueChanged(int value);

private slots:
    int exec();
    void run();

public slots:
    void stop();

public:
    Circles(QObject *parent = 0);
    ~Circles();

    bool circleFound();
    bool ellipseFound();
    Mat getBlurredFrame();
    Mat getCannyFrame();
    Mat getHistogramPlot();
    EllipseObject getEllipse();
    bool hasBlurredFrame();
    bool hasCannyFrame();
    void setCenter(Point cPoint);

    /// Process3ad Overrided
    bool hasToolBar();
    QToolBar *toolBar();
};

#endif // CIRCLES_H
