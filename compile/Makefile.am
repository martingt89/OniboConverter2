bin_PROGRAMS=OniboConverter2

SRCPATH=../src

OniboConverter2_SOURCES= \
$(SRCPATH)/ConverterOptions/optionsdatabase.cpp \
$(SRCPATH)/ConverterOptions/bitrate.cpp \
$(SRCPATH)/ConverterOptions/resolution.cpp \
$(SRCPATH)/ConverterOptions/encoder.cpp \
$(SRCPATH)/ConverterOptions/samplerate.cpp \
$(SRCPATH)/ConverterOptions/framerate.cpp \
$(SRCPATH)/ConverterOptions/format.cpp \
$(SRCPATH)/ConverterOptions/container.cpp \
$(SRCPATH)/ConverterOptions/optionsloaderxml.cpp \
$(SRCPATH)/ConverterOptions/ffpreset.cpp \
$(SRCPATH)/ConverterOptions/supportedencoders.cpp \
$(SRCPATH)/RegexTools/regextools.cpp \
$(SRCPATH)/CppExtension/path.cpp \
$(SRCPATH)/Profile/profile.cpp \
$(SRCPATH)/Gui/convertergui.cpp \
$(SRCPATH)/Gui/mainsettings.cpp \
$(SRCPATH)/Gui/Video/videosettingsgui.cpp \
$(SRCPATH)/Gui/Video/videoencodergui.cpp \
$(SRCPATH)/Gui/Video/videoresolutiongui.cpp \
$(SRCPATH)/helper.cpp \
$(SRCPATH)/main.cpp 

AM_CXXFLAGS = -lpthread -std=c++0x -g -O0 $(DEPS_CFLAGS) -Wall -pedantic

OniboConverter2_LDADD = $(DEPS_LIBS)
