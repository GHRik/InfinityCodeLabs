TEMPLATE = app
CONFIG += console
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= Wall
CONFIG -= qt

SOURCES += \
        DatabaseManager.cpp \
        Helper/FileManager.cpp \
        Helper/Logger.cpp \
        Helper/Printer.cpp \
        Helper/Translator.cpp \
        Helper/Validator.cpp \
        Interface/iFileManager.cpp \
        Interface/iLogger.cpp \
        Interface/iPrinter.cpp \
        Interface/iTranslator.cpp \
        Interface/iValidate.cpp \
        main.cpp

HEADERS += \
    DatabaseManager.hpp \
    Helper/FileManager.hpp \
    Helper/Logger.hpp \
    Helper/Printer.hpp \
    Helper/Translator.hpp \
    Helper/Validator.hpp \
    Interface/iFileManager.hpp \
    Interface/iLogger.hpp \
    Interface/iPrinter.hpp \
    Interface/iTranslator.hpp \
    Interface/iValidate.hpp \
    Utils/DataBaseCommand.hpp \
    Utils/ErrorsCode.hpp \
    Utils/FileConfig.hpp \
    Utils/UsedType.hpp
