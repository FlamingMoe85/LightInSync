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
#include "../Experiment/SequenceUis/SequenceEditor.h"
#include "../Experiment/PlaylistManagement/PlaylistManager.h"

#include "../Experiment/Audio/AudioPlayer.h"
#include "../Experiment/Audio/AudioPlayerFrontend.h"

#include "../Experiment/ControlInputs/Position.h"
#include "../Experiment/ControlInputs/SaveLoadScene.h"
#include "../Experiment/ControlInputs/ScrollAreaWithVertLayout.h"
#include "../Experiment/ControlInputs/SceneLoadButtons.h"

#include "../../../share/Devices/DmxDevices/Device.hpp"
#include "../../../share/Devices/DmxDevices/MovingHead_RGBWA_UV.hpp"
#include "../../../share/Devices/DmxDevices/MovingHead_RGBW_7x40_BeeEye_51Ch.hpp"
#include "../../../share/Devices/DmxDevices/PinSpotRGBW_7Ch.hpp"
#include "../../../share/Devices/DmxDevices/Par_RGBWAUV_10Ch.hpp"

#define AMT_BEE_EYES        4
#define AMT_MOVING_HEADS    4
#define AMT_CANS            12
#define AMT_PINSPOTS        1
#define AMT_PARS            1
#define UNIV_LENGTH 1+ (AMT_BEE_EYES*51) + (AMT_MOVING_HEADS * 10) + (AMT_CANS * 8) + (AMT_PINSPOTS*7)

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
                    bsBeeEyesDimm[2],
                    bsBeeEyesPan[AMT_MOVING_HEADS],
                    bsBeeEyesTilt[AMT_MOVING_HEADS],
                    bsBeeEyesZoom[AMT_BEE_EYES],
                    bsBeeEyesRotate[AMT_BEE_EYES];
    ColorWheelMapper colorWheelOuterDevs[AMT_BEE_EYES * AMT_OuterRgbDevs];
    ColorWheelMapper colorWheelInnerDev[AMT_BEE_EYES];
    Position *pos[2], *pan[2], *tilt[2], *dimm[2], *zoom[2], *rotate[2], *shift[2], *rgbDimm[2], *shiftWhite[2], *rgbInnDimm[2], *innerWhite[2];


    MovingHead_RGBWA_UV *movingHeads[AMT_MOVING_HEADS];
    BundleSeries    movingHeadDevices[AMT_MOVING_HEADS],
                    movingHeadsRGBdevs[AMT_MOVING_HEADS],
                    movingHeadsRGBdimm[AMT_MOVING_HEADS],
                    movingHeadsWhite[AMT_MOVING_HEADS],
                    movingHeadsDimm,
                    movingHeadsPan[AMT_MOVING_HEADS],
                    movingHeadsTilt[AMT_MOVING_HEADS];
    ColorWheelMapper colorWheelMovingHeads[AMT_MOVING_HEADS];
    Position *posMovingHeads, *panMovingHeads, *tiltMovingHeads, *dimmMovingHeads, *whiteMovingHeads, *rgbMovingHeads, *rgbDimmMovingHeads;

    PinSpotRGBW_7Ch *pinSpots[AMT_PINSPOTS];
    BundleSeries    pinSpotDevices,
                    pinSpotRed[AMT_PINSPOTS],
                    pinSpotGreen[AMT_PINSPOTS],
                    pinSpotBlue[AMT_PINSPOTS],
                    pinSpotWhite[AMT_PINSPOTS];
    Position *posPinSpotRed, *posPinSpotGreen, *posPinSpotBlue, *posPinSpotWhite;

    Par_RGBWAUV_10Ch *pars[AMT_PARS];
    BundleSeries    parSpotDevices,
                    parDimm,
                    parSpotRed,
                    parSpotGreen,
                    parSpotBlue,
                    parSpotWhite;
    Position *posParSpotRed, *posParSpotGreen, *posParSpotBlue, *posParSpotWhite, *posParDimm;

    /*
    Device *cans[AMT_CANS];
    BundleSeries    canDevices[AMT_CANS],
                    canRGBdevs[AMT_CANS],
                    canWhite[AMT_CANS],
                    canRgbDimm[AMT_CANS],
                    canWhiteDimm[AMT_CANS];
    ColorWheelMapper colorWheelCan[AMT_CANS];
    Position *posCans, *dimmWhiteCans, *dimmRgbCans;
    */


    QTimer timer;
    std::vector<uint8_t*> universum;
    uint8_t buf[UNIV_LENGTH];
    int itteration;

    SaveLoadScene saveLoadBeeEyes, saveLoadBeeEyes_Side, saveLoadHeads, saveLoadPinSpot, saveLoadPars;
    QList<SaveLoadScene*> saveLoadSceneList;

    int currentPage;
    ScrollAreaWithVertLayout page_0, page_1, page_2, page_3, page_4, page_5, page_6;
    SequenceEditor sequenceEditor;
    QList<ScrollAreaWithVertLayout*> FixtureList;
    void UpdatePageSelection();

    SceneLoadButtons *loadButtons_1, *loadButtons_2, *loadButtons_3, *loadButtons_4;

     void ConnectFixturePagesToNameButtons();
     void DisonnectFixturePagesFromNameButtons();
     void ConnectFixturePagesToSequenceEditor();
     void DisonnectFixturePagesFromSequenceEditor();

     PlaylistManager playlistManager;

private slots:
    void Slot_SendMsg();
    void Slot_TimerExpired();
    void Slot_GetMasterPosition(ClientServer_Top *b, int itterration);
    void Slot_PrevPage();
    void Slot_NextPage();

};
#endif // WIDGET_H
