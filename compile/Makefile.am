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
$(SRCPATH)/ConverterOptions/channel.cpp \
$(SRCPATH)/ConverterOptions/optionsloaderxml.cpp \
$(SRCPATH)/ConverterOptions/ffpreset.cpp \
$(SRCPATH)/ConverterOptions/supportedencoders.cpp \
$(SRCPATH)/RegexTools/regextools.cpp \
$(SRCPATH)/CppExtension/path.cpp \
$(SRCPATH)/Profile/profile.cpp \
$(SRCPATH)/Profile/profileloader.cpp \
$(SRCPATH)/Xml/xmlprofileparser.cpp \
$(SRCPATH)/Xml/xmlgenerator.cpp \
$(SRCPATH)/Xml/xmlprofiletable.cpp \
$(SRCPATH)/Xml/profiletoxmlconverter.cpp \
$(SRCPATH)/Gui/convertergui.cpp \
$(SRCPATH)/Gui/avcontrol.cpp \
$(SRCPATH)/Gui/filecontrol.cpp \
$(SRCPATH)/Gui/convertwindow.cpp \
$(SRCPATH)/Gui/findffmpegdialog.cpp \
$(SRCPATH)/Gui/manualsettingscontrol.cpp \
$(SRCPATH)/Gui/destinationcontrol.cpp \
$(SRCPATH)/Gui/Video/videocontrol.cpp \
$(SRCPATH)/Gui/Video/encodercontrol.cpp \
$(SRCPATH)/Gui/Video/resolutiondialog.cpp \
$(SRCPATH)/Gui/Video/bitratedialog.cpp \
$(SRCPATH)/Gui/Audio/audiocontrol.cpp \
$(SRCPATH)/Gui/Audio/encodercontrola.cpp \
$(SRCPATH)/ExternalTools/supportedencodersloader.cpp \
$(SRCPATH)/ProcessExecutor/process.cpp \
$(SRCPATH)/ProcessExecutor/safestream.cpp \
$(SRCPATH)/ProcessExecutor/safeinputstream.cpp \
$(SRCPATH)/ProcessExecutor/safeoutputstream.cpp \
$(SRCPATH)/Converter/convertsettings.cpp \
$(SRCPATH)/Converter/dispenser.cpp \
$(SRCPATH)/MediaFile/mediafile.cpp \
$(SRCPATH)/MediaFile/mediafilescanner.cpp \
$(SRCPATH)/MediaFile/audiostream.cpp \
$(SRCPATH)/MediaFile/stream.cpp \
$(SRCPATH)/MediaFile/videostream.cpp \
$(SRCPATH)/helper.cpp \
$(SRCPATH)/main.cpp 

AM_CXXFLAGS = -lpthread -std=c++0x -O0 -g -Wall -pedantic $(DEPS_CFLAGS)

OniboConverter2_LDADD = $(DEPS_LIBS)
