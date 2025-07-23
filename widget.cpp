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






pos = new Position(this, "Pos", false);
ui->verticalLayout->addWidget(pos, 0, 0);

pan = new Position(this, "Pan", true);
bsBeeEyesPan.SetUi(pan);
ui->verticalLayout->addWidget(pan, 1, 0);

tilt = new Position(this, "Tilt", true);
bsBeeEyesTilt.SetUi(tilt);
ui->verticalLayout->addWidget(tilt, 2, 0);

dimm = new Position(this, "Dimm", true);
bsBeeEyesDimm.SetUi(dimm);
ui->verticalLayout->addWidget(dimm, 3, 0);

zoom = new Position(this, "Zoom", false);
ui->verticalLayout->addWidget(zoom, 4, 0);

rotate = new Position(this, "Rotate", false);
ui->verticalLayout->addWidget(rotate, 5, 0);


shift = new Position(this, "RGB Device Shift", false);
ui->verticalLayout->addWidget(shift, 6, 0);

cT.RegisterCLient(&(bsBeeEyesDimm));
cT.RegisterCLient(&bsBeeEyesPan);
cT.RegisterCLient(&bsBeeEyesTilt);

    for(int device=0; device<AMT_BEE_EYES; device++)
    {

        cT.RegisterCLient(&(bsBeeEyeDevices[device]));
        bsBeeEyeDevices[device].SetUi(pos);
        bsBeeEyeDevices[device].SetType(NEW_BS);
        bsBeeEyeDevices[device].GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);

        bsBeeEyeDevices[device].RegisterClient(&(bsBeeEyesOuter6RGBdevs[device]));
        bsBeeEyeDevices[device].RegisterClient(&(bsBeeEyesZoom[device]));
        bsBeeEyeDevices[device].RegisterClient(&(bsBeeEyesRotate[device]));
        bsBeeEyesOuter6RGBdevs[device].GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);
        bsBeeEyesOuter6RGBdevs[device].SetType(NEW_BS);
        bsBeeEyesOuter6RGBdevs[device].SetUi(shift);

        beeEye[device] = new MovingHead_RGBW_7x40_BeeEye_51Ch(universum);
        beeEye[device]->Init(1+(device*51));
        bsBeeEyesZoom[device].RegisterClient(beeEye[device]->GetMapperZoom()); bsBeeEyesZoom[device].GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);
        bsBeeEyesZoom[device].SetUi(zoom);
        bsBeeEyesRotate[device].RegisterClient(beeEye[device]->GetMapperRotate()); bsBeeEyesRotate[device].GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);
        bsBeeEyesRotate[device].SetUi(rotate);

        for(int k=0; k< AMT_OuterRgbDevs; k++)
        {
            colorWheelOuterDevs[k].SetRgbDevice(beeEye[device]->GetRgbDevice(k+1));
            colorWheelOuterDevs[k].GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);
            bsBeeEyesOuter6RGBdevs[device].RegisterClient(&(colorWheelOuterDevs[k]));
        }
        bsBeeEyesDimm.RegisterClient(beeEye[device]->GetMapperDimmer()); bsBeeEyesDimm.GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);
        bsBeeEyesPan.RegisterClient(beeEye[device]->GetMapperPan()); bsBeeEyesPan.GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);
        bsBeeEyesTilt.RegisterClient(beeEye[device]->GetMapperTilt()); bsBeeEyesTilt.GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);
    }

    serial.setPortName("COM5");
    serial.setBaudRate(QSerialPort::Baud115200);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.open(QIODevice::ReadWrite);


    QObject::connect(&timer, &QTimer::timeout, this, &Widget::Slot_TimerExpired);
    QObject::connect(&cT, &ClientServer_Top::RequestValue, this, &Widget::Slot_GetMasterPosition);


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
    static float f = 0;

    for(int device=0; device<AMT_BEE_EYES; device++)
    {
        bsBeeEyeDevices[device].Request(itteration);

        bsBeeEyesDimm.Consume(itteration, f);
        bsBeeEyesPan.Consume(itteration, f);
        bsBeeEyesTilt.Consume(itteration, f);
        /*bsBeeEyesZoom.Request(itteration);
        bsBeeEyesRotate.Request(itteration);
        */
    }

    /*
    pan->Ping(itteration);
    tilt->Ping(itteration);
    dimm->Ping(itteration);
    zoom->Ping(itteration);
    rotate->Ping(itteration);
    shift->Ping(itteration);
    */


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

void Widget::Slot_GetMasterPosition(ClientServer_Top *b, int itterration)
{
    if(ui->checkBox->isChecked())
    {
        int v = ui->horizontalSlider_MasterPosition->value();
        v -= v%(ui->horizontalSlider_PositonSpeed->value());
        v += (ui->horizontalSlider_PositonSpeed->value());
        if(v > ui->horizontalSlider_MasterPosition->maximum())
        {
            v=0;
        }
        ui->horizontalSlider_MasterPosition->setSliderPosition(v);
    }
    float tmpF = (float)ui->horizontalSlider_MasterPosition->value() / (float)ui->horizontalSlider_MasterPosition->maximum();
    b->Serve(itterration,tmpF);
}
