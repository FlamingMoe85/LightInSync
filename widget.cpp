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
        ui(new Ui::Widget),
        saveLoadBeeEyes(this, "_BeeEyes")
{
    ui->setupUi(this);

    //ui->verticalLayout_Player->addWidget(&audioPlayerFrontEnd);

    for(int i=0; i<UNIV_LENGTH; i++)
    {
        universum.push_back(&(buf[i]));
        buf[i] = 0;
    }

PositionInit_t posInit;

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
pos[0] = tmpPos = new Position(this, posInit);
ui->verticalLayout->addWidget(pos[0]);
saveLoadBeeEyes.AddPositionUi(tmpPos);

posInit.name = "Pan"; posInit.enableShift = true; posInit.enableSpan = true; posInit.enableSpeed = true;
pan[0] = tmpPos = new Position(this, posInit);
ui->verticalLayout->addWidget(pan[0]);
saveLoadBeeEyes.AddPositionUi(tmpPos);

posInit.name = "Tilt"; posInit.overridePos = Qt::CheckState::Checked; posInit.enableShift = true; posInit.enableSpan = true; posInit.enableSpeed = true;
tilt[0] = tmpPos = new Position(this, posInit);
ui->verticalLayout->addWidget(tilt[0]);
saveLoadBeeEyes.AddPositionUi(tmpPos);

posInit.name = "Dimm"; posInit.overridePos = Qt::CheckState::Checked; posInit.enableShift = true; posInit.enableSpan = true; posInit.enableSpeed = true;
dimm[0] = tmpPos = new Position(this, posInit);
bsBeeEyesDimm[0].SetUi(dimm[0]);
ui->verticalLayout->addWidget(dimm[0]);
saveLoadBeeEyes.AddPositionUi(tmpPos);

posInit.name = "Zoom"; posInit.overridePos = Qt::CheckState::Checked; posInit.enableShift = true; posInit.enableSpan = true; posInit.enableSpeed = true;
zoom[0] = tmpPos = new Position(this, posInit);
ui->verticalLayout->addWidget(zoom[0]);
saveLoadBeeEyes.AddPositionUi(tmpPos);

posInit.name = "Rotate"; posInit.overridePos = Qt::CheckState::Checked; posInit.enableShift = true; posInit.enableSpan = true; posInit.enableSpeed = true;
rotate[0] = tmpPos = new Position(this, posInit);
ui->verticalLayout->addWidget(rotate[0]);
saveLoadBeeEyes.AddPositionUi(tmpPos);


posInit.name = "RGB Device Shift"; posInit.overridePos = Qt::CheckState::Checked; posInit.enableShift = true; posInit.enableSpan = true; posInit.enableSpeed = true;
shift[0] = tmpPos = new Position(this, posInit);
ui->verticalLayout->addWidget(shift[0]);
saveLoadBeeEyes.AddPositionUi(tmpPos);

posInit.name = "RGB Dimm Ring"; posInit.overridePos = Qt::CheckState::Checked; posInit.enableShift = true; posInit.enableSpan = true; posInit.enableSpeed = true;
rgbDimm[0] = tmpPos = new Position(this, posInit);
ui->verticalLayout->addWidget(rgbDimm[0]);
saveLoadBeeEyes.AddPositionUi(tmpPos);

posInit.name = "RGB Dimm Inner"; posInit.overridePos = Qt::CheckState::Checked; posInit.enableShift = false; posInit.enableSpan = false; posInit.enableSpeed = false;
rgbInnDimm[0] = tmpPos = new Position(this, posInit);
ui->verticalLayout->addWidget(rgbInnDimm[0]);
saveLoadBeeEyes.AddPositionUi(tmpPos);


posInit.name = "White Ring Dimm"; posInit.overridePos = Qt::CheckState::Checked; posInit.enableShift = true; posInit.enableSpan = true; posInit.enableSpeed = true;
shiftWhite[0] = tmpPos = new Position(this, posInit);
ui->verticalLayout->addWidget(shiftWhite[0]);
saveLoadBeeEyes.AddPositionUi(tmpPos);

posInit.name = "Inner White"; posInit.overridePos = Qt::CheckState::Checked; posInit.enableShift = true; posInit.enableSpan = true; posInit.enableSpeed = true;
innerWhite[0] = tmpPos = new Position(this, posInit);
ui->verticalLayout->addWidget(innerWhite[0]);
saveLoadBeeEyes.AddPositionUi(tmpPos);



cT.RegisterCLient(&(bsBeeEyesDimm[0]));

    for(int device=0; device<AMT_BEE_EYES; device++)
    {

        beeEye[device] = new MovingHead_RGBW_7x40_BeeEye_51Ch(universum);
        beeEye[device]->Init(1+ (AMT_CANS*8) +(AMT_MOVING_HEADS*10)+(device*51));

        masterBs.RegisterClient(&(bsBeeEyeDevices[device]));
        bsBeeEyeDevices[device].SetUi(pos[0]);
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
        bsBeeEyeDevices[device].RegisterClient(&(bsBeeEyesPan[0]));
        bsBeeEyeDevices[device].RegisterClient(&(bsBeeEyesTilt[device]));

        bsBeeEyesInnerWhite[device].GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);
        bsBeeEyesInnerWhite[device].RegisterClient(beeEye[device]->GetMapperWhite_1());
        bsBeeEyesInnerWhite[device].SetUi(innerWhite[0]);

        bsBeeEyesPan[0].GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);
        bsBeeEyesPan[0].RegisterClient(beeEye[device]->GetMapperPan());
        bsBeeEyesPan[0].SetUi(pan[0]);
        bsBeeEyesPan[0].SetType(NEW_BS);
        beeEye[device]->GetMapperPan()->GetFuncCont()->ClearSections();
        beeEye[device]->GetMapperPan()->GetFuncCont()->AddFunctionSectionByParams(1, 0, 0.25, 0.75);
        //if(device & 1)beeEye[device]->GetMapperPan()->GetFuncCont()->AddFunctionSectionByParams(1, 0, 0.25, 0.75);
        //else beeEye[device]->GetMapperPan()->GetFuncCont()->AddFunctionSectionByParams(1, 0, 0.75, 0.25);

        bsBeeEyesTilt[device].GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);
        bsBeeEyesTilt[device].RegisterClient(beeEye[device]->GetMapperTilt());
        bsBeeEyesTilt[device].SetUi(tilt[0]);

        colorWheelInnerDev[device].SetRgbDevice(beeEye[device]->GetRgbDevice(0));
        colorWheelInnerDev[device].GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);
        bsBeeEyesInnerRgbDevDimm[device].GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);
        bsBeeEyesInnerRgbDevDimm[device].RegisterClient(colorWheelInnerDev[device].GetDimm());
        bsBeeEyesInnerRgbDevDimm[device].SetType(NEW_BS);
        bsBeeEyesInnerRgbDevDimm[device].SetUi(rgbInnDimm[0]);

        bsBeeEyesOuter6RGBdevs[device].GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);
        bsBeeEyesOuter6RGBdevs[device].SetType(NEW_BS);
        bsBeeEyesOuter6RGBdevs[device].SetUi(shift[0]);
        bsBeeEyesOuter6RGBdevsDimm[device].GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);
        bsBeeEyesOuter6RGBdevsDimm[device].SetType(NEW_BS);
        bsBeeEyesOuter6RGBdevsDimm[device].SetUi(rgbDimm[0]);

        bsBeeEyesZoom[device].RegisterClient(beeEye[device]->GetMapperZoom()); bsBeeEyesZoom[device].GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);
        bsBeeEyesZoom[device].SetUi(zoom[0]);
        bsBeeEyesRotate[device].RegisterClient(beeEye[device]->GetMapperRotate()); bsBeeEyesRotate[device].GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);
        bsBeeEyesRotate[device].SetUi(rotate[0]);

        bsBeeEyesOuter6White[device].SetUi(shiftWhite[0]);
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
        bsBeeEyesDimm[0].RegisterClient(beeEye[device]->GetMapperDimmer()); bsBeeEyesDimm[0].GetFuncCont()->AddFunctionSectionByParams(1, 0, 1, 0);
    }



    QObject::connect(ui->pushButton_ConCOM, &QPushButton::clicked, this, &Widget::Slot_ConnectCom);
    QObject::connect(&timer, &QTimer::timeout, this, &Widget::Slot_TimerExpired);
    QObject::connect(&cT, &ClientServer_Top::RequestValue, this, &Widget::Slot_GetMasterPosition);


    timer.setInterval(100);
    timer.start();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::Slot_ConnectCom()
{
    serial.close();
    QString com = "COM" + QString::number(ui->spinBox_ComPort->value());
    qDebug() << "Slot_ConnectCom " << com;
    serial.setPortName(com);
    serial.setBaudRate(QSerialPort::Baud115200);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.open(QIODevice::ReadWrite);
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
    bsBeeEyesDimm[0].Consume(itteration, f);

    /*
    if(AMT_BEE_EYES > 0)*universum[137] += ui->horizontalSlider->value();
    if(AMT_BEE_EYES > 1)*universum[137+51] += ui->horizontalSlider_2->value();
    if(AMT_BEE_EYES > 2)*universum[137+102] += ui->horizontalSlider_3->value();
    if(AMT_BEE_EYES > 3)*universum[137+153] += ui->horizontalSlider_4->value();

    ui->lcdNumber->display(ui->horizontalSlider->value());
    ui->lcdNumber_2->display(ui->horizontalSlider_2->value());
    ui->lcdNumber_3->display(ui->horizontalSlider_3->value());
    ui->lcdNumber_4->display(ui->horizontalSlider_4->value());
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
    //qDebug() << " ";
    //qDebug() << debugMsg.toLatin1();
    if(serial.isOpen())
    {
      serial.write(sendMsg.toLatin1());
    }
    //
}

void Widget::Slot_GetMasterPosition(ClientServer_Top *b, int itterration)
{
    static float position = 0;
    if(position >= 1.0)position = 0.0;
    position += ((1.0/50000.0) * ((float)ui->horizontalSlider_PositonSpeed->value()));
    /*
    if(ui->checkBox->isChecked())
    {
        int v = ui->horizontalSlider_MasterPosition->value();
        v -= v%(ui->horizontalSlider_PositonSpeed->value());
        v += (ui->horizontalSlider_PositonSpeed->value());
        qDebug() << v;
        if(v > ui->horizontalSlider_MasterPosition->maximum())
        {
            v=0;
        }
        ui->horizontalSlider_MasterPosition->setSliderPosition(v);
    }
    */

    float tmpF = (float)ui->horizontalSlider_MasterPosition->value() / (float)ui->horizontalSlider_MasterPosition->maximum();
    b->Serve(itterration,position);
}
