#ifndef GIGESETTINGS_H
#define GIGESETTINGS_H

#include <QDialog>

namespace Ui {
class GigESettings;
}

class GigESettings : public QDialog
{
    Q_OBJECT
    
private:
    Ui::GigESettings *ui;

private slots:
    void cameraChangedSlot();
public:
    explicit GigESettings(QWidget *parent = 0);
    ~GigESettings();
    
    void addCameraList(QStringList cameraList);
    int getExposure();
    int getGain();
    int getPacketSize();
    QString getPixelFormat();
    quint8 getSelectedCamera();
    bool isAutoPacketSize();
    void setCameraIPData(QStringList ipData);
    void setExposure(int value);
    void setGain(int value);
    void setPacketSize(int value);
    void setPixelFormat(QString value);

signals:
    void cameraChanged();
};

#endif // GIGESETTINGS_H
