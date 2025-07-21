#include "widget.h"
#include "ui_widget.h"

#include <QDebug>

QStringList channelNames = {
    "Pan	",
    "PanFine	",
    "Tilt	",
    "TiltFine	",
    "PanTiltSpeed	",
    "Zoom	",
    "Rotate	",
    "Dimmer	",
    "Strobe	",
    "RedDimm	",
    "GreenDimm	",
    "BlueDimm	",
    "WhiteDimm	",
    "CT	",
    "Wash	",
    "StaticEff	",
    "DynEff	",
    "DynEffSpeed	",
    "BkGrndRed	",
    "BkGrndGreen	",
    "BkGrndBlue	",
    "BkGrndWhite	",
    "Reset	",
    "Red_1	",
    "Green_1	",
    "Blue_1	",
    "White_1	",
    "Red_2	",
    "Green_2	",
    "Blue_2	",
    "White_2	",
    "Red_3	",
    "Green_3	",
    "Blue_3	",
    "White_3	",
    "Red_4	",
    "Green_4	",
    "Blue_4	",
    "White_4	",
    "Red_5	",
    "Green_5	",
    "Blue_5	",
    "White_5	",
    "Red_6	",
    "Green_6	",
    "Blue_6	",
    "White_6	",
    "Red_7	",
    "Green_7	",
    "Blue_7	",
    "White_7	"

};

Widget::Widget(QWidget *parent)
    :   QWidget(parent),
        ui(new Ui::Widget)
{
    ui->setupUi(this);

    //ui->verticalLayout_Player->addWidget(&audioPlayerFrontEnd);

    for(int i=0; i<UNIV_LENGTH; i++)
    {
        universum.push_back(&(buf[i]));
        buf[i] = 0;
    }






    for(int device=0; device<AMT_BEE_EYES; device++)
    {

        bsBeeEyeDevices.RegisterClient(&(bsBeeEyesOuter6RGBdevs[device]));
        bsBeeEyesOuter6RGBdevs[device].GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);
        bsBeeEyesOuter6RGBdevs[device].SetType(NEW_BS);
        beeEye[device] = new MovingHead_RGBW_7x40_BeeEye_51Ch(universum);
        beeEye[device]->Init(1+(device*51));
        for(int k=0; k< AMT_OuterRgbDevs; k++)
        {
            colorWheelOuterDevs[k].SetRgbDevice(beeEye[device]->GetRgbDevice(k+1));
            colorWheelOuterDevs[k].GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);
            bsBeeEyesOuter6RGBdevs[device].RegisterClient(&(colorWheelOuterDevs[k]));
        }
        bsBeeEyesDimm.RegisterClient(beeEye[device]->GetMapperDimmer()); bsBeeEyesDimm.GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);
        bsBeeEyesPan.RegisterClient(beeEye[device]->GetMapperPan()); bsBeeEyesPan.GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);
        bsBeeEyesTilt.RegisterClient(beeEye[device]->GetMapperTilt()); bsBeeEyesTilt.GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);
        bsBeeEyesZoom.RegisterClient(beeEye[device]->GetMapperZoom()); bsBeeEyesZoom.GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);
        bsBeeEyesRotate.RegisterClient(beeEye[device]->GetMapperRotate()); bsBeeEyesRotate.GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);
        bsBeeEyesOuter6RGBdevs[device].SetSerParamShift(&bsBeeEyesOuter6RGBdevsShift);
    }

    pos = new Position(this, &bsBeeEyeDevices, "Pos", true);
    bsBeeEyeDevices.SetAlternateServer(pos);
    bsBeeEyeDevices.SetType(NEW_BS);
    bsBeeEyeDevices.GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);
    ui->gridLayout->addWidget(pos, 0, 0);

    pan = new Position(this, &bsBeeEyesPan, "Pan", true);
    bsBeeEyesPan.SetAlternateServer(pan);
    ui->gridLayout->addWidget(pan, 1, 0);

    tilt = new Position(this, &bsBeeEyesTilt, "Tilt", true);
    bsBeeEyesTilt.SetAlternateServer(tilt);
    ui->gridLayout->addWidget(tilt, 2, 0);

    dimm = new Position(this, &bsBeeEyesDimm, "Dimm", true);
    bsBeeEyesDimm.SetAlternateServer(dimm);
    ui->gridLayout->addWidget(dimm, 3, 0);

    zoom = new Position(this, &bsBeeEyesZoom, "Zoom", true);
    bsBeeEyesZoom.SetAlternateServer(zoom);
    ui->gridLayout->addWidget(zoom, 4, 0);

    rotate = new Position(this, &bsBeeEyesRotate, "Rotate", true);
    bsBeeEyesRotate.SetAlternateServer(rotate);
    ui->gridLayout->addWidget(rotate, 5, 0);

    shift = new Position(this, &bsBeeEyesOuter6RGBdevsShift, "RGB Device Shift", true);
    bsBeeEyesOuter6RGBdevsShift.SetAlternateServer(shift);
    ui->gridLayout->addWidget(shift, 6, 0);
    bsBeeEyesOuter6RGBdevsShift.GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);



    serial.setPortName("COM5");
    serial.setBaudRate(QSerialPort::Baud115200);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.open(QIODevice::ReadWrite);


    QObject::connect(&timer, &QTimer::timeout, this, &Widget::Slot_TimerExpired);


    timer.setInterval(100);
    timer.start();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::Slot_SendMsg()
{
    static QString sendMsg;

    sendMsg.clear();
    sendMsg.append('0'-48);

    //serial.write(sendMsg.toLatin1());

}

void Widget::Slot_TimerExpired()
{
    itteration++;


    for(int device=0; device<AMT_BEE_EYES; device++)
    {
        bsBeeEyeDevices.Request(itteration);
        bsBeeEyesOuter6RGBdevsShift.Request(itteration);
        bsBeeEyesDimm.Request(itteration);
        bsBeeEyesPan.Request(itteration);
        bsBeeEyesTilt.Request(itteration);
        bsBeeEyesZoom.Request(itteration);
        bsBeeEyesRotate.Request(itteration);
    }

    pan->Ping(itteration);
    tilt->Ping(itteration);
    dimm->Ping(itteration);
    zoom->Ping(itteration);
    rotate->Ping(itteration);
    shift->Ping(itteration);


    static QString sendMsg, debugMsg;
    debugMsg.clear();
    sendMsg.clear();
    for(uint8_t* v : universum)
    {
        sendMsg.append((*v));
        debugMsg += " " + QString::number(*v);
        *v = 0;
    }
    qDebug() << " ";
    qDebug() << debugMsg.toLatin1();
    //qDebug() << sendMsg.toLatin1();
    if(serial.isOpen())
    {
      serial.write(sendMsg.toLatin1());
    }
    //
}

