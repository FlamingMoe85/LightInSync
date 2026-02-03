QT       += core gui serialport multimedia


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../share/BrokerClientServer/Base_Client.cpp \
    ../../share/BrokerClientServer/Base_Server.cpp \
    ../../share/BrokerClientServer/ClientServerBase.cpp \
    ../../share/EffectStructureBlocks/BundleSeries.cpp \
    ../../share/EffectStructureBlocks/BundleSeriesManager.cpp \
    ../../share/EffectStructureBlocks/Positioner.cpp \
    ../../share/Functions/FunctionContainer.cpp \
    ../../share/Functions/FunctionContainerSpan.cpp \
    ../../share/Functions/FunctionSection_Base.cpp \
    ../../share/Functions/FunctionSection_Linear.cpp \
    ../../share/Mapper/ColorWheelMapper.cpp \
    ../../share/Mapper/HandTroughMapper.cpp \
    ../../share/Mapper/Mapper_Channel.cpp \
    ../../share/Mapper/Mapper_Channel_16b.cpp \
    ../../share/Mapper/Mapper_InternalValue.cpp \
    ../../share/Mapper/OneChannelMapper.cpp \
    ../Experiment/Audio/AudioPlayer.cpp \
    ../Experiment/Audio/AudioPlayerFrontend.cpp \
    ../Experiment/ClientServer_Top.cpp \
    ../Experiment/ControlInputs/NameButton.cpp \
    ../Experiment/ControlInputs/Position.cpp \
    ../Experiment/ControlInputs/SaveLoadScene.cpp \
    ../Experiment/ControlInputs/SceneLoadButtons.cpp \
    ../Experiment/ControlInputs/ScrollAreaWithVertLayout.cpp \
    ../Experiment/ControlInputs/Span.cpp \
    ../Experiment/PlaylistManagement/FileBrowser/window.cpp \
    ../Experiment/PlaylistManagement/PlaylistManager.cpp \
    ../Experiment/SequenceUis/SequenceEditor.cpp \
    ../Experiment/SequenceUis/SequenceItem.cpp \
    ../Experiment/SequenceUis/SequencePlayer.cpp \
    ../Experiment/UI/CustomScrollArea.cpp \
    ../Experiment/UI/EditorItem.cpp \
    ../Experiment/UI/EffectEditor.cpp \
    ../Experiment/UI/HorSliderSelfCentering.cpp \
    ../Experiment/UI/ShadeWidget.cpp \
    ../Experiment/UI/hoverpoints.cpp \
    main.cpp \
    widget.cpp

HEADERS += \
    ../../share/BrokerClientServer/Base_Client.h \
    ../../share/BrokerClientServer/Base_Server.h \
    ../../share/BrokerClientServer/ClientServerBase.hpp \
    ../../share/BrokerClientServer/I_Client.hpp \
    ../../share/BrokerClientServer/I_Server.hpp \
    ../../share/Devices/Channel/ChannelTypes.hpp \
    ../../share/Devices/Channel/Channel_16Bit.hpp \
    ../../share/Devices/Channel/Channel_8Bit.hpp \
    ../../share/Devices/Channel/Channel_8BitValue_8BitDimm.hpp \
    ../../share/Devices/Channel/DmxChannel_8Bit.hpp \
    ../../share/Devices/DmxDevices/Device.hpp \
    ../../share/Devices/DmxDevices/Device_RGBW.hpp \
    ../../share/Devices/DmxDevices/MovingHead_RGBWA_UV.hpp \
    ../../share/Devices/DmxDevices/MovingHead_RGBW_7x40_BeeEye_51Ch.hpp \
    ../../share/Devices/DmxDevices/Par_RGBWAUV_10Ch.hpp \
    ../../share/Devices/DmxDevices/PinSpotRGBW_7Ch.hpp \
    ../../share/Devices/DmxDevices/RGBWA_UV_MiniMovingHead.hpp \
    ../../share/Devices/DmxDevices/RGBWA_UV_Stationary.hpp \
    ../../share/Devices/DmxDevices/RGBW_Dimm.h \
    ../../share/Devices/Interfaces/I_Channel_16Bit.hpp \
    ../../share/Devices/Interfaces/I_Channel_8Bit.hpp \
    ../../share/Devices/Interfaces/I_DmxChannelBlue_8Bit.hpp \
    ../../share/Devices/Interfaces/I_DmxChannelDimm_8Bit.hpp \
    ../../share/Devices/Interfaces/I_DmxChannelGreen_8Bit.hpp \
    ../../share/Devices/Interfaces/I_DmxChannelPan_8Bit.hpp \
    ../../share/Devices/Interfaces/I_DmxChannelRandom.hpp \
    ../../share/Devices/Interfaces/I_DmxChannelRed_8Bit.hpp \
    ../../share/Devices/Interfaces/I_DmxChannelTilt_8Bit.hpp \
    ../../share/Devices/Interfaces/I_DmxChannelWhite_8Bit.hpp \
    ../../share/Devices/Interfaces/I_HowMany.hpp \
    ../../share/Devices/Interfaces/I_PositionConsumer.h \
    ../../share/Devices/Interfaces/I_RGB.hpp \
    ../../share/Devices/Interfaces/I_RGBW.hpp \
    ../../share/Devices/Interfaces/I_RGBW_Dimm.hpp \
    ../../share/Devices/Interfaces/I_White.hpp \
    ../../share/EffectStructureBlocks/BundleSeries.h \
    ../../share/EffectStructureBlocks/BundleSeriesManager.h \
    ../../share/EffectStructureBlocks/I_AlternateServer.hpp \
    ../../share/EffectStructureBlocks/I_BundleSeries_UI.hpp \
    ../../share/EffectStructureBlocks/Positioner.h \
    ../../share/FunctionOwners.hpp \
    ../../share/Functions/FunctionContainer.h \
    ../../share/Functions/FunctionContainerSpan.h \
    ../../share/Functions/FunctionSection_Base.h \
    ../../share/Functions/FunctionSection_Linear.h \
    ../../share/Functions/I_FunctionSection.hpp \
    ../../share/GlobalDefines_Shared.h \
    ../../share/Helper.hpp \
    ../../share/Mapper/ColorWheelMapper.h \
    ../../share/Mapper/HandTroughMapper.h \
    ../../share/Mapper/Mapper_Base.hpp \
    ../../share/Mapper/Mapper_Channel.h \
    ../../share/Mapper/Mapper_Channel_16b.h \
    ../../share/Mapper/Mapper_InternalValue.h \
    ../../share/Mapper/OneChannelMapper.h \
    ../Experiment/Audio/AudioPlayer.h \
    ../Experiment/Audio/AudioPlayerFrontend.h \
    ../Experiment/ClientServer_Top.h \
    ../Experiment/ControlInputs/ChangeSliderAtRate.h \
    ../Experiment/ControlInputs/I_Ping.hpp \
    ../Experiment/ControlInputs/NameButton.h \
    ../Experiment/ControlInputs/Position.h \
    ../Experiment/ControlInputs/SaveLoadScene.h \
    ../Experiment/ControlInputs/SceneLoadButtons.h \
    ../Experiment/ControlInputs/ScrollAreaWithVertLayout.h \
    ../Experiment/ControlInputs/Span.h \
    ../Experiment/PlaylistManagement/FileBrowser/window.h \
    ../Experiment/PlaylistManagement/PlaylistManager.h \
    ../Experiment/SequenceUis/SequenceEditor.h \
    ../Experiment/SequenceUis/SequenceItem.h \
    ../Experiment/SequenceUis/SequencePlayer.h \
    ../Experiment/UI/CustomScrollArea.h \
    ../Experiment/UI/EditorItem.h \
    ../Experiment/UI/EffectEditor.h \
    ../Experiment/UI/HorSliderSelfCentering.h \
    ../Experiment/UI/ShadeWidget.h \
    ../Experiment/UI/hoverpoints.h \
    ../Experiment/Utilities.hpp \
    widget.h

FORMS += \
    ../Experiment/Audio/AudioPlayerFrontend.ui \
    ../Experiment/ControlInputs/NameButton.ui \
    ../Experiment/ControlInputs/SaveLoadScene.ui \
    ../Experiment/ControlInputs/ScrollAreaWithVertLayout.ui \
    ../Experiment/ControlInputs/Span.ui \
    ../Experiment/PlaylistManagement/PlaylistManager.ui \
    ../Experiment/SequenceUis/SequenceEditor.ui \
    ../Experiment/SequenceUis/SequenceItem.ui \
    ../Experiment/UI/CustomScrollArea.ui \
    ../Experiment/UI/EditorItem.ui \
    ../Experiment/UI/EffectEditor.ui \
    ../Experiment/UI/HorSliderSelfCentering.ui \
    ../Experiment/ControlInputs/Position.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
