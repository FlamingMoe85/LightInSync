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

PositionInit_t posInit;

saveLoadBeeEyes.name = "_BeeEyes";
ui->verticalLayout->addWidget(&saveLoadBeeEyes);

cT.RegisterCLient(&masterBs);
posInit.name = "Master"; posInit.overridePos = Qt::CheckState::Unchecked; posInit.enableShift = true; posInit.enableSpan = true; posInit.enableSpeed = false;
masterControls = new Position(this, posInit);
masterBs.GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);
masterBs.SetUi(masterControls);
masterBs.SetType(NEW_BS);
ui->verticalLayout_MasterControl->addWidget(masterControls);

Position* tmpPos;
posInit.name = "Pos"; posInit.overridePos = Qt::CheckState::Unchecked; posInit.enableShift = true; posInit.enableSpan = false; posInit.enableSpeed = true;
pos = tmpPos = new Position(this, posInit);
ui->verticalLayout->addWidget(pos);
saveLoadBeeEyes.AddPositionUi(tmpPos);

posInit.name = "Pan"; posInit.enableShift = true; posInit.enableSpan = true; posInit.enableSpeed = true;
pan = tmpPos = new Position(this, posInit);
bsBeeEyesPan.SetUi(pan);
ui->verticalLayout->addWidget(pan);
saveLoadBeeEyes.AddPositionUi(tmpPos);

posInit.name = "Tilt"; posInit.overridePos = Qt::CheckState::Checked; posInit.enableShift = true; posInit.enableSpan = true; posInit.enableSpeed = true;
tilt = tmpPos = new Position(this, posInit);
bsBeeEyesTilt.SetUi(tilt);
ui->verticalLayout->addWidget(tilt);
saveLoadBeeEyes.AddPositionUi(tmpPos);

posInit.name = "Dimm"; posInit.overridePos = Qt::CheckState::Checked; posInit.enableShift = true; posInit.enableSpan = true; posInit.enableSpeed = true;
dimm = tmpPos = new Position(this, posInit);
bsBeeEyesDimm.SetUi(dimm);
ui->verticalLayout->addWidget(dimm);
saveLoadBeeEyes.AddPositionUi(tmpPos);

posInit.name = "Zoom"; posInit.overridePos = Qt::CheckState::Checked; posInit.enableShift = true; posInit.enableSpan = true; posInit.enableSpeed = true;
zoom = tmpPos = new Position(this, posInit);
ui->verticalLayout->addWidget(zoom);
saveLoadBeeEyes.AddPositionUi(tmpPos);

posInit.name = "Rotate"; posInit.overridePos = Qt::CheckState::Checked; posInit.enableShift = true; posInit.enableSpan = true; posInit.enableSpeed = true;
rotate = tmpPos = new Position(this, posInit);
ui->verticalLayout->addWidget(rotate);
saveLoadBeeEyes.AddPositionUi(tmpPos);


posInit.name = "RGB Device Shift"; posInit.overridePos = Qt::CheckState::Checked; posInit.enableShift = true; posInit.enableSpan = true; posInit.enableSpeed = true;
shift = tmpPos = new Position(this, posInit);
ui->verticalLayout->addWidget(shift);
saveLoadBeeEyes.AddPositionUi(tmpPos);

posInit.name = "RGB Dimm Ring"; posInit.overridePos = Qt::CheckState::Checked; posInit.enableShift = false; posInit.enableSpan = false; posInit.enableSpeed = false;
rgbDimm = tmpPos = new Position(this, posInit);
ui->verticalLayout->addWidget(rgbDimm);
saveLoadBeeEyes.AddPositionUi(tmpPos);

posInit.name = "RGB Dimm Inner"; posInit.overridePos = Qt::CheckState::Checked; posInit.enableShift = false; posInit.enableSpan = false; posInit.enableSpeed = false;
rgbInnDimm = tmpPos = new Position(this, posInit);
ui->verticalLayout->addWidget(rgbInnDimm);
saveLoadBeeEyes.AddPositionUi(tmpPos);


posInit.name = "White Ring Dimm"; posInit.overridePos = Qt::CheckState::Checked; posInit.enableShift = true; posInit.enableSpan = true; posInit.enableSpeed = true;
shiftWhite = tmpPos = new Position(this, posInit);
ui->verticalLayout->addWidget(shiftWhite);
saveLoadBeeEyes.AddPositionUi(tmpPos);

posInit.name = "Inner White"; posInit.overridePos = Qt::CheckState::Checked; posInit.enableShift = true; posInit.enableSpan = true; posInit.enableSpeed = true;
innerWhite = tmpPos = new Position(this, posInit);
ui->verticalLayout->addWidget(innerWhite);
saveLoadBeeEyes.AddPositionUi(tmpPos);


cT.RegisterCLient(&(bsBeeEyesDimm));
cT.RegisterCLient(&bsBeeEyesPan);
cT.RegisterCLient(&bsBeeEyesTilt);

    for(int device=0; device<AMT_BEE_EYES; device++)
    {

        beeEye[device] = new MovingHead_RGBW_7x40_BeeEye_51Ch(universum);
        beeEye[device]->Init(1+ (AMT_CANS*8) +(AMT_MOVING_HEADS*10)+(device*51));

        masterBs.RegisterClient(&(bsBeeEyeDevices[device]));
        bsBeeEyeDevices[device].SetUi(pos);
        bsBeeEyeDevices[device].SetType(NEW_BS);
        bsBeeEyeDevices[device].GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);

        bsBeeEyeDevices[device].RegisterClient(&(bsBeeEyesOuter6RGBdevs[device]));
        bsBeeEyeDevices[device].RegisterClient(&(bsBeeEyesOuter6RGBdevsDimm[device]));
        bsBeeEyeDevices[device].RegisterClient(&(bsBeeEyesOuter6White[device]));
        bsBeeEyeDevices[device].RegisterClient(&(bsBeeEyesZoom[device]));
        bsBeeEyeDevices[device].RegisterClient(&(bsBeeEyesRotate[device]));
        bsBeeEyeDevices[device].RegisterClient(&(colorWheelInnerDev[device]));
        bsBeeEyeDevices[device].RegisterClient(&(bsBeeEyesInnerRgbDevDimm[device]));
        bsBeeEyeDevices[device].RegisterClient(&(bsBeeEyesInnerWhite[device]));

        bsBeeEyesInnerWhite[device].GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);
        bsBeeEyesInnerWhite[device].RegisterClient(beeEye[device]->GetMapperWhite_1());
        bsBeeEyesInnerWhite[device].SetUi(innerWhite);

        colorWheelInnerDev[device].SetRgbDevice(beeEye[device]->GetRgbDevice(0));
        colorWheelInnerDev[device].GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);
        bsBeeEyesInnerRgbDevDimm[device].GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);
        bsBeeEyesInnerRgbDevDimm[device].RegisterClient(colorWheelInnerDev[device].GetDimm());
        bsBeeEyesInnerRgbDevDimm[device].SetType(NEW_BS);
        bsBeeEyesInnerRgbDevDimm[device].SetUi(rgbInnDimm);

        bsBeeEyesOuter6RGBdevs[device].GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);
        bsBeeEyesOuter6RGBdevs[device].SetType(NEW_BS);
        bsBeeEyesOuter6RGBdevs[device].SetUi(shift);
        bsBeeEyesOuter6RGBdevsDimm[device].GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);
        bsBeeEyesOuter6RGBdevsDimm[device].SetType(NEW_BS);
        bsBeeEyesOuter6RGBdevsDimm[device].SetUi(rgbDimm);

        bsBeeEyesZoom[device].RegisterClient(beeEye[device]->GetMapperZoom()); bsBeeEyesZoom[device].GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);
        bsBeeEyesZoom[device].SetUi(zoom);
        bsBeeEyesRotate[device].RegisterClient(beeEye[device]->GetMapperRotate()); bsBeeEyesRotate[device].GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);
        bsBeeEyesRotate[device].SetUi(rotate);

        bsBeeEyesOuter6White[device].SetUi(shiftWhite);
        bsBeeEyesOuter6White[device].SetType(NEW_BS);
        bsBeeEyesOuter6White[device].GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);
        bsBeeEyesOuter6White[device].RegisterClient(beeEye[device]->GetMapperWhite_2());
        bsBeeEyesOuter6White[device].RegisterClient(beeEye[device]->GetMapperWhite_3());
        bsBeeEyesOuter6White[device].RegisterClient(beeEye[device]->GetMapperWhite_4());
        bsBeeEyesOuter6White[device].RegisterClient(beeEye[device]->GetMapperWhite_5());
        bsBeeEyesOuter6White[device].RegisterClient(beeEye[device]->GetMapperWhite_6());
        bsBeeEyesOuter6White[device].RegisterClient(beeEye[device]->GetMapperWhite_7());

        for(int k=0; k< AMT_OuterRgbDevs; k++)
        {
            colorWheelOuterDevs[(device*AMT_OuterRgbDevs)+k].SetRgbDevice(beeEye[device]->GetRgbDevice(k+1));
            colorWheelOuterDevs[(device*AMT_OuterRgbDevs)+k].GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);
            bsBeeEyesOuter6RGBdevs[device].RegisterClient(&(colorWheelOuterDevs[(device*AMT_OuterRgbDevs)+k]));
            bsBeeEyesOuter6RGBdevsDimm[device].RegisterClient((colorWheelOuterDevs[(device*AMT_OuterRgbDevs)+k]).GetDimm());

        }
        bsBeeEyesDimm.RegisterClient(beeEye[device]->GetMapperDimmer()); bsBeeEyesDimm.GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);
        bsBeeEyesPan.RegisterClient(beeEye[device]->GetMapperPan());
        bsBeeEyesPan.GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);
        if(device & 1)beeEye[device]->GetMapperPan()->GetFuncCont()->ClearSections();
        if(device & 1)beeEye[device]->GetMapperPan()->GetFuncCont()->AddFunctionSectionByParams(1, 0, 0, 1);
        bsBeeEyesTilt.RegisterClient(beeEye[device]->GetMapperTilt()); bsBeeEyesTilt.GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);
    }

    saveLoadHeads.name = "_Heads";
    ui->verticalLayout_MovingHeads->addWidget(&saveLoadHeads);

    posInit.name = "Pos"; posInit.overridePos = Qt::CheckState::Unchecked; posInit.enableShift = true; posInit.enableSpan = true; posInit.enableSpeed = true;
    posMovingHeads = tmpPos = new Position(this, posInit);
    ui->verticalLayout_MovingHeads->addWidget(posMovingHeads);
    saveLoadHeads.AddPositionUi(tmpPos);

    posInit.name = "Pan"; posInit.overridePos = Qt::CheckState::Checked; posInit.overridePos = Qt::CheckState::Unchecked; posInit.enableShift = true; posInit.enableSpan = true; posInit.enableSpeed = true;
    panMovingHeads = tmpPos = new Position(this, posInit);
    ui->verticalLayout_MovingHeads->addWidget(panMovingHeads);
    saveLoadHeads.AddPositionUi(tmpPos);

    posInit.name = "Tilt"; posInit.overridePos = Qt::CheckState::Checked; posInit.overridePos = Qt::CheckState::Checked; posInit.enableShift = true; posInit.enableSpan = true; posInit.enableSpeed = true;
    tiltMovingHeads = tmpPos = new Position(this, posInit);
    ui->verticalLayout_MovingHeads->addWidget(tiltMovingHeads);
    saveLoadHeads.AddPositionUi(tmpPos);

    posInit.name = "Dimm"; posInit.overridePos = Qt::CheckState::Checked; posInit.enableShift = true; posInit.enableSpan = true; posInit.enableSpeed = true;
    dimmMovingHeads = tmpPos = new Position(this, posInit);
    movingHeadsDimm.SetUi(dimmMovingHeads);
    ui->verticalLayout_MovingHeads->addWidget(dimmMovingHeads);
    saveLoadHeads.AddPositionUi(tmpPos);

    MovingHead_RGBWA_UV_t RGBW_Dimm_MovingHead_Init;

        RGBW_Dimm_MovingHead_Init.red = 3;
        RGBW_Dimm_MovingHead_Init.green = 4;
        RGBW_Dimm_MovingHead_Init.blue = 5;
        RGBW_Dimm_MovingHead_Init.white = 6;
        RGBW_Dimm_MovingHead_Init.dimm = 2;
        RGBW_Dimm_MovingHead_Init.amber = 7;
        RGBW_Dimm_MovingHead_Init.uv = 8;
        RGBW_Dimm_MovingHead_Init.x = 0;
        RGBW_Dimm_MovingHead_Init.y = 1;
        RGBW_Dimm_MovingHead_Init.xy = 9;

    cT.RegisterCLient(&(movingHeadsDimm));
    for(int device=0; device<AMT_MOVING_HEADS; device++)
    {
        masterBs.RegisterClient(&(movingHeadDevices[device]));
        movingHeadDevices[device].SetUi(posMovingHeads);
        movingHeadDevices[device].SetType(NEW_BS);
        movingHeadDevices[device].GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);

        movingHeadDevices[device].RegisterClient(&(movingHeadsRGBdevs[device]));
        movingHeadDevices[device].RegisterClient(&(movingHeadsPan[device]));
        movingHeadDevices[device].RegisterClient(&(movingHeadsTilt[device]));

        movingHeads[device] = new MovingHead_RGBWA_UV(universum);
        RGBW_Dimm_MovingHead_Init.adr = 1+ (AMT_CANS*8) +(device*10);
        movingHeads[device]->Init(RGBW_Dimm_MovingHead_Init);
        movingHeadsPan[device].RegisterClient(movingHeads[device]->GetPanMapper()); movingHeadsPan[device].GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);
        movingHeadsPan[device].SetUi(panMovingHeads);
        movingHeadsTilt[device].RegisterClient(movingHeads[device]->GetTiltMapper()); movingHeadsTilt[device].GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);
        movingHeadsTilt[device].SetUi(tiltMovingHeads);

        colorWheelMovingHeads[device].SetRgbDevice((I_RGB*)movingHeads[device]);
        colorWheelMovingHeads[device].GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);
        movingHeadsRGBdevs[device].RegisterClient(&(colorWheelMovingHeads[device]));
        movingHeadsRGBdevs[device].GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);

        movingHeadsDimm.RegisterClient(movingHeads[device]->GetDimmMapper()); movingHeadsDimm.GetFuncCont()->AddFunctionSectionByParams(1, 0, 0.5, 0.2);
    }


    posInit.name = "Pos"; posInit.overridePos = Qt::CheckState::Unchecked; posInit.enableShift = true; posInit.enableSpan = true; posInit.enableSpeed = true;
    posCans = new Position(this, posInit);
    ui->verticalLayout_Cans->addWidget(posCans);

    posInit.name = "DimmRgb"; posInit.overridePos = Qt::CheckState::Checked; posInit.enableShift = true; posInit.enableSpan = true; posInit.enableSpeed = true;
        dimmRgbCans = new Position(this, posInit);
        ui->verticalLayout_Cans->addWidget(dimmRgbCans);

        posInit.name = "Dimm White"; posInit.overridePos = Qt::CheckState::Checked; posInit.enableShift = true; posInit.enableSpan = true; posInit.enableSpeed = true;
        dimmWhiteCans = new Position(this, posInit);
        ui->verticalLayout_Cans->addWidget(dimmWhiteCans);

    Device_t canInit;
    canInit.red = 0;
    canInit.green = 2;
    canInit.blue = 4;
    canInit.white = 6;


        for(int device=0; device<AMT_CANS; device++)
        {
            cans[device] = new Device(universum);
            canInit.adr = 1+(device*8);
            cans[device]->Init(canInit);

            masterBs.RegisterClient(&(canDevices[device]));
            canDevices[device].SetUi(posCans);
            canDevices[device].SetType(NEW_BS);
            canDevices[device].GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);

            canDevices[device].RegisterClient(&(canRGBdevs[device]));
            canRGBdevs[device].RegisterClient(&(colorWheelCan[device]));
            colorWheelCan[device].SetRgbDevice((I_RGB*)cans[device]);
            canRGBdevs[device].GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);
            colorWheelCan[device].GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);

            canDevices[device].RegisterClient(&(canRgbDimm[device]));
            canRgbDimm[device].RegisterClient(cans[device]->GetRgbDimmMapper());
            canRgbDimm[device].SetUi(dimmRgbCans);
            canRgbDimm[device].GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);

            canWhiteDimm[device].SetUi(dimmWhiteCans);
            canWhiteDimm[device].RegisterClient(cans[device]->GetWhiteDimmMapper());
            canDevices[device].RegisterClient(&(canWhiteDimm[device]));
            canWhiteDimm[device].GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);
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
    }
    bsBeeEyesDimm.Consume(itteration, f);
    bsBeeEyesPan.Consume(itteration, f);
    bsBeeEyesTilt.Consume(itteration, f);

    for(int device=0; device<AMT_MOVING_HEADS; device++)
    {
        movingHeadDevices[device].Request(itteration);
    }
    movingHeadsDimm.Consume(itteration, f);

    for(int device=0; device<AMT_CANS; device++)
    {
        canDevices[device].Request(itteration);
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
