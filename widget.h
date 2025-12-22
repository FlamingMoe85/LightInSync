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
#include "../Experiment/ControlInputs/SaveLoadScene.h"


#include "../../../share/Devices/DmxDevices/MovingHead_RGBW_7x40_BeeEye_51Ch.hpp"

#define AMT_BEE_EYES        4
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
                    bsBeeEyesInnerRgbDevDimm[AMT_BEE_EYES],
                    bsBeeEyesOuter6White[AMT_BEE_EYES],
                    bsBeeEyesInnerWhite[AMT_BEE_EYES],
                    bsBeeEyesDimm[1],
                    bsBeeEyesPan[AMT_MOVING_HEADS],
                    bsBeeEyesTilt[AMT_MOVING_HEADS],
                    bsBeeEyesZoom[AMT_MOVING_HEADS],
                    bsBeeEyesRotate[AMT_MOVING_HEADS];
    ColorWheelMapper colorWheelOuterDevs[AMT_BEE_EYES * AMT_OuterRgbDevs];
    ColorWheelMapper colorWheelInnerDev[AMT_BEE_EYES];
    Position *pos[1], *pan[1], *tilt[1], *dimm[1], *zoom[1], *rotate[1], *shift[1], *rgbDimm[1], *shiftWhite[1], *rgbInnDimm[1], *innerWhite[1];





    QTimer timer;
    std::vector<uint8_t*> universum;
    uint8_t buf[UNIV_LENGTH];
    int itteration;

    SaveLoadScene saveLoadBeeEyes;


private slots:
    void Slot_SendMsg();
    void Slot_TimerExpired();
    void Slot_GetMasterPosition(ClientServer_Top *b, int itterration);
    void Slot_ConnectCom();

};
#endif // WIDGET_H
