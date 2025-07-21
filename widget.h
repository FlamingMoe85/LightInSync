#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QTimer>
#include <QSerialPort>

#include "../Experiment/ClientServer_Top.h"



#include "../../../share/EffectStructureBlocks/BundleSeriesManager.h"
#include "../../../share/Mapper/ColorWheelMapper.h"
#include "../../../share/Mapper/OneChannelMapper.h"
#include "../../../share/Devices/DmxDevices/RGBWA_UV_MiniMovingHead.hpp"
#include "../../../share/Devices/DmxDevices/MovingHead_RGBWA_UV.hpp"
#include "../../../share/FunctionOwners.hpp"

#include "../../../share/Devices/DmxDevices/Device.hpp"

#include "../Experiment/Ui/ShadeWidget.h"
#include "../Experiment/Ui/CustomScrollArea.h"
#include "../Experiment/Ui/EffectEditor.h"

#include "../Experiment/Audio/AudioPlayer.h"
#include "../Experiment/Audio/AudioPlayerFrontend.h"

#include "../Experiment/ControlInputs/Position.h"

#include "../../../share/Devices/DmxDevices/MovingHead_RGBW_7x40_BeeEye_51Ch.hpp"

#define AMT_BEE_EYES    1
#define UNIV_LENGTH 1+ (AMT_BEE_EYES*51)

#define AMT_OuterRgbDevs    6

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

    QSerialPort serial;

    BundleSeries bsBeeEyeDevices;
    MovingHead_RGBW_7x40_BeeEye_51Ch *beeEye[AMT_BEE_EYES];
    BundleSeries    bsBeeEyesOuter6RGBdevs[AMT_BEE_EYES],
                    bsBeeEyesRgbShift[AMT_BEE_EYES],
                    bsBeeEyesOuter6RGBdevsShift,
                    bsBeeEyesDimm,
                    bsBeeEyesPan,
                    bsBeeEyesTilt,
                    bsBeeEyesZoom,
                    bsBeeEyesRotate;
    ColorWheelMapper colorWheelOuterDevs[AMT_BEE_EYES * AMT_OuterRgbDevs];


    QTimer timer;
    std::vector<uint8_t*> universum;
    uint8_t buf[UNIV_LENGTH];
    int itteration;

    Position *pos, *pan, *tilt, *dimm, *zoom, *rotate, *shift;

private slots:
    void Slot_SendMsg();
    void Slot_TimerExpired();

};
#endif // WIDGET_H
