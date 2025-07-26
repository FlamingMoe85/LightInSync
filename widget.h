#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QTimer>
#include <QSerialPort>

#include "../Experiment/ClientServer_Top.h"



#include "../../../share/EffectStructureBlocks/BundleSeriesManager.h"
#include "../../../share/Mapper/ColorWheelMapper.h"
#include "../../../share/Mapper/OneChannelMapper.h"
#include "../../../share/FunctionOwners.hpp"

#include "../../../share/Devices/DmxDevices/Device.hpp"

#include "../Experiment/Ui/ShadeWidget.h"
#include "../Experiment/Ui/CustomScrollArea.h"
#include "../Experiment/Ui/EffectEditor.h"

#include "../Experiment/Audio/AudioPlayer.h"
#include "../Experiment/Audio/AudioPlayerFrontend.h"

#include "../Experiment/ControlInputs/Position.h"

#include "../../../share/Devices/DmxDevices/Device.hpp"
#include "../../../share/Devices/DmxDevices/MovingHead_RGBWA_UV.hpp"
#include "../../../share/Devices/DmxDevices/MovingHead_RGBW_7x40_BeeEye_51Ch.hpp"

#define AMT_BEE_EYES        1
#define AMT_MOVING_HEADS    4
#define AMT_CANS            12
#define UNIV_LENGTH 1+ (AMT_BEE_EYES*51) + (AMT_MOVING_HEADS * 10) + (AMT_CANS * 8)

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

    ClientServer_Top cT;
    BundleSeries masterBs;
    Position *masterControls;

    MovingHead_RGBW_7x40_BeeEye_51Ch *beeEye[AMT_BEE_EYES];
    BundleSeries    bsBeeEyeDevices[AMT_BEE_EYES],
                    bsBeeEyesOuter6RGBdevs[AMT_BEE_EYES],
                     bsBeeEyesOuter6RGBdevsDimm[AMT_BEE_EYES],
                    bsBeeEyesOuter6White[AMT_BEE_EYES],
                    bsBeeEyesDimm,
                    bsBeeEyesPan,
                    bsBeeEyesTilt,
                    bsBeeEyesZoom[AMT_BEE_EYES],
                    bsBeeEyesRotate[AMT_BEE_EYES];
    ColorWheelMapper colorWheelOuterDevs[AMT_BEE_EYES * AMT_OuterRgbDevs];
    Position *pos, *pan, *tilt, *dimm, *zoom, *rotate, *shift, *rgbDimm;

    MovingHead_RGBWA_UV *movingHeads[AMT_MOVING_HEADS];
    BundleSeries    movingHeadDevices[AMT_MOVING_HEADS],
                    movingHeadsRGBdevs[AMT_MOVING_HEADS],
                    movingHeadsWhite[AMT_MOVING_HEADS],
                    movingHeadsDimm,
                    movingHeadsPan[AMT_MOVING_HEADS],
                    movingHeadsTilt[AMT_MOVING_HEADS];
    ColorWheelMapper colorWheelMovingHeads[AMT_MOVING_HEADS];
    Position *posMovingHeads, *panMovingHeads, *tiltMovingHeads, *dimmMovingHeads;

    Device *cans[AMT_CANS];
    BundleSeries    canDevices[AMT_CANS],
                    canRGBdevs[AMT_CANS],
                    canWhite[AMT_CANS],
                    canRgbDimm[AMT_CANS],
                    canWhiteDimm[AMT_CANS];
    ColorWheelMapper colorWheelCan[AMT_CANS];
    Position *posCans, *dimmWhiteCans, *dimmRgbCans;


    QTimer timer;
    std::vector<uint8_t*> universum;
    uint8_t buf[UNIV_LENGTH];
    int itteration;


private slots:
    void Slot_SendMsg();
    void Slot_TimerExpired();
    void Slot_GetMasterPosition(ClientServer_Top *b, int itterration);

};
#endif // WIDGET_H
