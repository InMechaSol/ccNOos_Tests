TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

DEFINES += \
    PLATFORM_QTCreatorC \
    __USINGCONSOLEMENU \
    __USINGFLOATPRINTF \
    EXAMPLE_POWER_METER

INCLUDEPATH += ../ccNOos/tests/

SOURCES += \
    ../ccNOos/ccLibs/acs/satComControl.c \
    ../ccNOos/ccLibs/mcs/motionControl.c \
    ../ccNOos/computeModule/compute_module.c \
    ../ccNOos/consoleMenu/console_menu.c \
    ../ccNOos/executionSystem/execution_system.c \
    ../ccNOos/ioDevice/io_device.c \
    ../ccNOos/tests/AttensUIExample.c \
    ../ccNOos/tests/SatComACSExample.c \
    ../ccNOos/tests/SatComPowerMeterExample.c \
    ../ccNOos/tests/SysTickExample.c \
    ../ccNOos/tests/ccNOos_tests.c \
    QTCreator_C.c

HEADERS += \
    ../ccNOos/ccLibs/acs/satComControl.h \
    ../ccNOos/ccLibs/mcs/motionControl.h \
    ../ccNOos/computeModule/compute_module.h \
    ../ccNOos/consoleMenu/console_menu.h \
    ../ccNOos/executionSystem/execution_system.h \
    ../ccNOos/executionSystem/version_config.h \
    ../ccNOos/ioDevice/io_device.h \
    ../ccNOos/tests/AttensUIExample.h \
    ../ccNOos/tests/Platform_QTCreatorC.h \
    ../ccNOos/tests/SatComACSExample.h \
    ../ccNOos/tests/SatComPowerMeterExample.h \
    ../ccNOos/tests/SysTickExample.h \
    ../ccNOos/tests/ccNOos_tests.h
