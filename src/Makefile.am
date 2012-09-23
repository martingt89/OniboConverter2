bin_PROGRAMS=OniboConverter2

MediaElement= \
MediaElement/audiograde.cpp \
MediaElement/channel.cpp \
MediaElement/container.cpp \
MediaElement/samplerate.cpp \
MediaElement/bitrate.cpp \
MediaElement/encoder.cpp \
MediaElement/resolution.cpp \
MediaElement/format.cpp \
MediaElement/framerate.cpp \
MediaElement/ffpreset.cpp \
MediaElement/elementsdb.cpp \
MediaElement/elementsrelations.cpp

Profile= \
Profile/configuration.cpp \
Profile/profile.cpp \
Profile/profiles.cpp

Xml= \
Xml/profileloader.cpp \
Xml/xmlparser.cpp \
Xml/xmlgenerator.cpp \
Xml/settingsloader.cpp \
Xml/settingsgenerator.cpp \
xmlfilesdefinitions.cpp \
Xml/optionsloaderxml.cpp \
Xml/profilegenerator.cpp

MediaFile= \
MediaFile/mediafile.cpp \
MediaFile/mediainfo.cpp \
MediaFile/mediaconvert.cpp \
MediaFile/mediascanner.cpp \
MediaFile/audiostream.cpp \
MediaFile/stream.cpp \
MediaFile/videostream.cpp

Gui= \
Gui/Settings/general.cpp \
Gui/Settings/threading.cpp \
Gui/Settings/usersettingsdialog.cpp \
Gui/findffmpegdialog.cpp \
Gui/convertwindow.cpp \
Gui/mainwindow.cpp \
Gui/convertergui.cpp \
Gui/destinationcontrol.cpp \
Gui/filecontrol.cpp \
Gui/infocontrol.cpp \
Gui/overwritedialog.cpp \
Gui/avcontrol.cpp \
Gui/manualsettingscontrol.cpp \
Gui/profilenamedialog.cpp \
Gui/Audio/audiocontrol.cpp \
Gui/Audio/encodercontrola.cpp \
Gui/Video/videocontrol.cpp \
Gui/Video/resolutiondialog.cpp \
Gui/Video/bitratedialog.cpp \
Gui/Video/encodercontrolv.cpp \
Gui/unencodersdialog.cpp \
Gui/importexport.cpp

ProcessExecutor= \
ProcessExecutor/process.cpp \
ProcessExecutor/safestream.cpp \
ProcessExecutor/safeinputstream.cpp \
ProcessExecutor/safeoutputstream.cpp

Converter= \
Converter/convertparser.cpp \
Converter/dispenser.cpp \
Converter/argumentsgenerator.cpp \
Converter/unsupportedencoders.cpp

Top= \
userpreferences.cpp \
systemsettings.cpp \
helper.cpp \
main.cpp

Other= \
CppExtension/path.cpp \
CppExtension/logger.cpp \
RegexTools/regextools.cpp \
ConverterOptions/supportedencoders.cpp \
ExternalTools/supportedencodersloader.cpp \
System/cpu.cpp

OniboConverter2_SOURCES= \
$(MediaElement) \
$(Profile) \
$(Xml) \
$(MediaFile) \
$(Gui) \
$(ProcessExecutor) \
$(Converter) \
$(Top) \
$(Other)

if DEBUG
AM_CXXFLAGS = -lpthread -std=c++0x -O0 -g -Wall -W -Wextra -Werror -pedantic -DDATADIR=\"$(datadir)\" $(DEPS_CFLAGS) 
else
AM_CXXFLAGS = -lpthread -std=c++0x -O0 -DDATADIR=\"$(datadir)\" -DPROGDIR=\"@PACKAGE@\" $(DEPS_CFLAGS) 
endif

OniboConverter2_LDADD = $(DEPS_LIBS)
