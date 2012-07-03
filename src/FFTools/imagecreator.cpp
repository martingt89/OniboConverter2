/*
 * imagecreator.cpp
 *
 *  Created on: 28.6.2012
 *      Author: martint
 */

#include "imagecreator.h"
#include "../settings.h"
#include "../Process/processexecutor.h"
#include "../helper.h"

namespace FFTools {

std::string ImageCreator::createImage(MediaInfo::MediaFile file, double time){
	//todo try catch
	std::string path = Settings::getSettings()->getValue(Settings::FFPATH);

	std::list<std::string> args;
	args.push_back("-ss");

	if(time < file.getDuration()){
		args.push_back(toS(time));
	}else{
		args.push_back(toS(file.getDuration() / 10));
	}

	args.push_back("-vframes");
	args.push_back("1");

	args.push_back("-i");
	args.push_back(file.getFilePath());

	std::cout<<"file path: "<<file.getFilePath()<<std::endl;

	args.push_back("-f");
	args.push_back("image2");

	args.push_back("/tmp/filename.png");	//todo dinamicky nazov

	Process::Executor exec(path, args);

	if(exec.waitForRunChild()){
		std::cout<<"error"<<std::endl; //todo exception
		return "";
	}

	std::cout<<"status: "<<exec.waitForEndChild()<<std::endl;

	return "/tmp/filename.png";
}
} /* namespace FFTools */
