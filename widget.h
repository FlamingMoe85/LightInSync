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

#define AMT_SECTIONS    2
#define AMT_DEVS_PER_SECTION    6
#define CHNLS_PER_CAN 8
#define UNIV_LENGTH 1 + (AMT_SECTIONS*AMT_DEVS_PER_SECTION*CHNLS_PER_CAN)

#define AMT_DEVICES 4
#define AMT_SPEAKER_HEADS 2
//#define UNIV_LENGTH 1 + (AMT_DEVICES*10)

//#define UNIV_LENGTH 1 + (AMT_SECTIONS*AMT_DEVS_PER_SECTION*CHNLS_PER_CAN) + (AMT_DEVICES*10) + (AMT_SPEAKER_HEADS*10)
#define UNIV_LENGTH 52

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

    //BundleSeriesManager


    QTimer timer;
    std::vector<uint8_t*> universum;
    uint8_t buf[UNIV_LENGTH];
    int itteration;

    Position *pos[51];
    MovingHead_RGBW_7x40_BeeEye_51Ch head;


private slots:
    void Slot_SendMsg();
    void Slot_TimerExpired();

};
#endif // WIDGET_H
