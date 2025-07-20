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
        head(universum)
{
    ui->setupUi(this);

    //ui->verticalLayout_Player->addWidget(&audioPlayerFrontEnd);

    for(int i=0; i<UNIV_LENGTH; i++)
    {
        universum.push_back(&(buf[i]));
        buf[i] = 0;
    }

    head.Init(1);

    pos[0]=new Position(this, head.GetMapperPan(), channelNames[0]);
     pos[1]=new Position(this, head.GetMapperPanFine(), channelNames[1]);
     pos[2]=new Position(this, head.GetMapperTilt(), channelNames[2]);
     pos[3]=new Position(this, head.GetMapper(), channelNames[3]);
     pos[4]=new Position(this, head.GetMapperPanTiltSpeed(), channelNames[4]);
     pos[5]=new Position(this, head.GetMapperZoom(), channelNames[5]);
     pos[6]=new Position(this, head.GetMapperRotate(), channelNames[6]);
     pos[7]=new Position(this, head.GetMapperDimmer(), channelNames[7]);
     pos[8]=new Position(this, head.GetMapperStrobe(), channelNames[8]);
     pos[9]=new Position(this, head.GetMapperRedDimm(), channelNames[9]);
     pos[10]=new Position(this, head.GetMapperGreenDimm(), channelNames[10]);
     pos[11]=new Position(this, head.GetMapperBlueDimm(), channelNames[11]);
     pos[12]=new Position(this, head.GetMapperWhiteDimm(), channelNames[12]);
     pos[13]=new Position(this, head.GetMapperCT(), channelNames[13]);
     pos[14]=new Position(this, head.GetMapperWash(), channelNames[14]);
     pos[15]=new Position(this, head.GetMapperStaticEff(), channelNames[15]);
     pos[16]=new Position(this, head.GetMapperDynEff(), channelNames[16]);
     pos[17]=new Position(this, head.GetMapperDynEffSpeed(), channelNames[17]);
     pos[18]=new Position(this, head.GetMapperBkGrndRed(), channelNames[18]);
     pos[19]=new Position(this, head.GetMapperBkGrndGreen(), channelNames[19]);
     pos[20]=new Position(this, head.GetMapperBkGrndBlue(), channelNames[20]);
     pos[21]=new Position(this, head.GetMapperBkGrndWhite(), channelNames[21]);
     pos[22]=new Position(this, head.GetMapperReset(), channelNames[22]);
     pos[23]=new Position(this, head.GetMapperRed_1(), channelNames[23]);
     pos[24]=new Position(this, head.GetMapperGreen_1(), channelNames[24]);
     pos[25]=new Position(this, head.GetMapperBlue_1(), channelNames[25]);
     pos[26]=new Position(this, head.GetMapperWhite_1(), channelNames[26]);
     pos[27]=new Position(this, head.GetMapperRed_2(), channelNames[27]);
     pos[28]=new Position(this, head.GetMapperGreen_2(), channelNames[28]);
     pos[29]=new Position(this, head.GetMapperBlue_2(), channelNames[29]);
     pos[30]=new Position(this, head.GetMapperWhite_2(), channelNames[30]);
     pos[31]=new Position(this, head.GetMapperRed_3(), channelNames[31]);
     pos[32]=new Position(this, head.GetMapperGreen_3(), channelNames[32]);
     pos[33]=new Position(this, head.GetMapperBlue_3(), channelNames[33]);
     pos[34]=new Position(this, head.GetMapperWhite_3(), channelNames[34]);
     pos[35]=new Position(this, head.GetMapperRed_4(), channelNames[35]);
     pos[36]=new Position(this, head.GetMapperGreen_4(), channelNames[36]);
     pos[37]=new Position(this, head.GetMapperBlue_4(), channelNames[37]);
     pos[38]=new Position(this, head.GetMapperWhite_4(), channelNames[38]);
     pos[39]=new Position(this, head.GetMapperRed_5(), channelNames[39]);
     pos[40]=new Position(this, head.GetMapperGreen_5(), channelNames[40]);
     pos[41]=new Position(this, head.GetMapperBlue_5(), channelNames[41]);
     pos[42]=new Position(this, head.GetMapperWhite_5(), channelNames[42]);
     pos[43]=new Position(this, head.GetMapperRed_6(), channelNames[43]);
     pos[44]=new Position(this, head.GetMapperGreen_6(), channelNames[44]);
     pos[45]=new Position(this, head.GetMapperBlue_6(), channelNames[45]);
     pos[46]=new Position(this, head.GetMapperWhite_6(), channelNames[46]);
     pos[47]=new Position(this, head.GetMapperRed_7(), channelNames[47]);
     pos[48]=new Position(this, head.GetMapperGreen_7(), channelNames[48]);
     pos[49]=new Position(this, head.GetMapperBlue_7(), channelNames[49]);
     pos[50]=new Position(this, head.GetMapperWhite_7(), channelNames[50]);

    int abs = 0;
    for(int c=0; c<4; c++)
    {
        for(int r=0; r<13; r++)
        {
            ui->gridLayout->addWidget(pos[abs], r, c);
            abs++;
            if(abs == 51)break;
        }
    }

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

    for(int i=0; i<51; i++)pos[i]->Ping(itteration);

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

