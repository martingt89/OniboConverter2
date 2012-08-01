bin_PROGRAMS=OniboConverter2

OniboConverter2_SOURCES= \
../src/ConverterOptions/optionsdatabase.cpp \
../src/ConverterOptions/bitrate.cpp \
../src/ConverterOptions/resolution.cpp \
../src/ConverterOptions/encoder.cpp \
../src/ConverterOptions/samplerate.cpp \
../src/ConverterOptions/framerate.cpp \
../src/ConverterOptions/format.cpp \
../src/ConverterOptions/container.cpp \
../src/ConverterOptions/optionsloaderxml.cpp \
../src/ConverterOptions/ffpreset.cpp \
../src/ConverterOptions/supportedencoders.cpp \
../src/RegexTools/regextools.cpp \
../src/CppExtension/path.cpp \
../src/Gui/guicontrols.cpp \
../src/Gui/filecontrols.cpp \
../src/Gui/Video/globalvideosettings.cpp \
../src/Gui/Video/encodersettings.cpp \
../src/Gui/settingsdialog.cpp \
../src/profil.cpp \
../src/main.cpp 

AM_CXXFLAGS = -lpthread -std=c++0x -g -O0 $(DEPS_CFLAGS) -Wall -pedantic

OniboConverter2_LDADD = $(DEPS_LIBS)
