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
../src/RegexTools/regextools.cpp \
../src/path.cpp \
../src/main.cpp

AM_CXXFLAGS = -lpthread -std=c++0x -g -O0 $(DEPS_CFLAGS) -Wall -pedantic

OniboConverter2_LDADD = $(DEPS_LIBS)
