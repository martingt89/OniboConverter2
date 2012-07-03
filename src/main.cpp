/*
 * main.cpp
 *
 *  Created on: 20.6.2012
 *  Author: Martin Geier
 *
 *  Testing MediaInfo library
 */

#include <iostream>
#include "settings.h"
#include "Process/safestream.h"
#include "Process/safeinputstream.h"
#include "Process/processexecutor.h"

#include "MediaInfo/infoloader.h"
#include "regextools.h"

#include "FFTools/suportedencoders.h"
#include "FFTools/imagecreator.h"

#include "XML/containersparser.h"
#include "XML/encodersparser.h"

#include "AVBox/formattoencoders.h"


template<class T>
std::ostream& operator<<(std::ostream& stream, const std::list<T>& list){
	typename std::list<T>::const_iterator iter;
	for(iter = list.begin(); iter != list.end(); ++iter){
		stream << (std::string)*iter << " ";
	}
	return stream;
}
template<class T1, class T2>
std::ostream& operator<<(std::ostream& stream, const std::list<std::pair<T1, T2> >& list){
	typename std::list<std::pair<T1, T2> >::const_iterator iter;
	for(iter = list.begin(); iter != list.end(); ++iter){
		stream << iter->first << " " << iter->second;
	}
	return stream;
}

std::ostream& operator<<(std::ostream& stream, const std::list<AVBox::Encoder>& list){
	typename std::list<AVBox::Encoder>::const_iterator iter;
	for(iter = list.begin(); iter != list.end(); ++iter){
		stream << "Encoder: "<<iter->getEncoder() <<std::endl;
		stream << "Comment: "<<iter->getDescription()<<std::endl;
		stream << "Options: "<<iter->getOptions()<<std::endl;
	}
	return stream;
}
int main(int argc, char *argv[]){

	Settings *set = Settings::getSettings();
	set->setValue(Settings::FFPATH, "ffmpeg");
	set->setValue(Settings::ENCODERS, "encoders_table.xml");
	set->setValue(Settings::CONTAINERS, "container_settings.xml");

	//	MediaInfo::InfoLoader info("/media/data_int/shared/Filmy/HD filmy/28.Days.Later/dmt-28dl.avi");

//	std::string path = FFTools::ImageCreator::createImage(info.getMediaInfo(), 100);
//	std::cout<<"path: "<<path<<std::endl;

	FFTools::SuportedEncoders encs;

	AVBox::AVBox box;
	XML::ContainersParser parser;
	parser.parse(box);

	AVBox::FormatToEncoders convert;
	XML::EncodersParser encodersParser;
	encodersParser.parse(convert);

	std::cout<<box.getContainerList()<<std::endl;
	std::cout<<box.getContainer("3gp").getVideoFormats()<<std::endl;

	std::list<AVBox::Encoder> listEnc = box.getContainer("mkv").
			getVideoFormat("H264").getAvailableEncoders(encs, convert);

	std::cout<<listEnc<<std::endl;

//
//	//std::cout<<"ret: "<<ret<<std::endl;
//
//	std::cout<< "Containers: "<<box.getContainerList()<<std::endl;
//
//	std::cout<< "mkv: "<<box.getContainer("mkv").getVideoFormats()<<std::endl;
//	std::cout<< "avi: "<<box.getContainer("avi").getVideoFormats()<<std::endl;

//	AVBox::Encoders convert;
//
//	XML::EncodersParser encodersParser;
//
//	encodersParser.parse(convert);

//	std::cout<< "mkv: "<<box.getContainer("mkv").getVideoFormat("MPEG4").getAvailableCodecs()<<std::endl;
//	std::list<std::string>::iterator it;
//	std::list<std::string> list = box.getContainerList();
//	for(it = list.begin(); it != list.end(); ++it){
//		std::cout<<"Container: "<<*it<<std::endl;
//	}

//	std::cout<<info.getMediaInfo().getState()<<std::endl;

//	FFTools::SuportedEncoders encs;

//	MediaInfo::InfoLoader info("/home/martint/Obrázky/telapathy.jpg");
//	MediaInfo::InfoLoader info("/home/martint/Obrázky/thumbsup.png");
//	MediaInfo::InfoLoader info("/home/martint/cv.od");



	return 0;
}
