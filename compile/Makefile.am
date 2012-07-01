bin_PROGRAMS=OniboConverter2

OniboConverter2_SOURCES=../src/AVBox/audioformat.cpp \
../src/AVBox/formattoencoders.cpp \
../src/AVBox/videoformat.cpp \
../src/AVBox/encoder.cpp \
../src/AVBox/avbox.cpp \
../src/AVBox/container.cpp \
../src/Process/processexecutor.cpp \
../src/Process/safeinputstream.cpp \
../src/Process/safeoutputstream.cpp \
../src/Process/safestream.cpp \
../src/settings.cpp \
../src/regextools.cpp \
../src/FFTools/imagecreator.cpp \
../src/FFTools/suportedencoders.cpp \
../src/MediaInfo/infoloader.cpp \
../src/MediaInfo/stream.cpp \
../src/MediaInfo/videostream.cpp \
../src/MediaInfo/mediafile.cpp \
../src/MediaInfo/audiostream.cpp \
../src/helper.cpp \
../src/XML/encodersparser.cpp \
../src/XML/containersparser.cpp \
../src/main.cpp

AM_CXXFLAGS = -lpthread -std=c++0x -g -O0 $(DEPS_CFLAGS) 

OniboConverter2_LDADD = $(DEPS_LIBS)
