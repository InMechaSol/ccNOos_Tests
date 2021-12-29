TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

DEFINES += \
    PLATFORM_QTCreatorC \
    __USINGCONSOLEMENU \
    __USINGFLOATPRINTF \
    COMPILE_TESTS \
    EXAMPLE_ATTEN_UI


SOURCES += \
    ../ccNOos/computeModule/compute_module.c \
    ../ccNOos/consoleMenu/console_menu.c \
    ../ccNOos/executionSystem/execution_system.c \
    ../ccNOos/ioDevice/io_device.c \
    ../ccNOos/tests/AttensUIExample.c \
    ../ccNOos/tests/SatComACSExample.c \
    ../ccNOos/tests/SysTickExample.c \
    ../ccNOos/tests/ccNOos_tests.c \
    QTCreator_C.c

HEADERS += \
    ../ccNOos/computeModule/compute_module.h \
    ../ccNOos/consoleMenu/console_menu.h \
    ../ccNOos/executionSystem/execution_system.h \
    ../ccNOos/executionSystem/version_config.h \
    ../ccNOos/ioDevice/io_device.h \
    ../ccNOos/tests/AttensUIExample.h \
    ../ccNOos/tests/SatComACSExample.h \
    ../ccNOos/tests/SysTickExample.h \
    ../ccNOos/tests/ccNOos_tests.h \
    Platform_QTCreatorC.h
