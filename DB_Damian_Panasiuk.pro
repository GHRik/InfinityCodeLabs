TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle Wall
CONFIG -= qt

SOURCES += \
        DatabaseManager.cpp \
        Helper/FileManager.cpp \
        Helper/Logger.cpp \
        Helper/Splitter.cpp \
        Helper/Translator.cpp \
        Helper/Validator.cpp \
        Interface/iFileManager.cpp \
        Interface/iLogger.cpp \
        Interface/iSplitter.cpp \
        Interface/iTranslator.cpp \
        Interface/iValidate.cpp \
        main.cpp

HEADERS += \
    DatabaseManager.hpp \
    Helper/FileManager.hpp \
    Helper/Logger.hpp \
    Helper/Splitter.hpp \
    Helper/Translator.hpp \
    Helper/Validator.hpp \
    Interface/iFileManager.hpp \
    Interface/iLogger.hpp \
    Interface/iSplitter.hpp \
    Interface/iTranslator.hpp \
    Interface/iValidate.hpp \
    Utils/DataBaseCommand.hpp \
    Utils/ErrorsCode.hpp
