/*
 * ffpresets.cpp
 *
 *  Created on: 12.7.2012
 *      Author: martint
 */

#include "ffpresets.h"
#include "../Tools/settings.h"
#include <giomm/file.h>
#include <iostream>
#include "../Tools/regextools.h"

namespace FFTools {

FFpresets::FFpresets() {
	std::string ffpresentsFolder = Settings::getSettings()->getValue(Settings::FFPRESENTSFOLDER);

	try{
		Glib::RefPtr< Gio::File > directory = Gio::File::create_for_path(ffpresentsFolder);

		if(!directory){
			std::cout<<"folder not found"<<std::endl;
		}
		Glib::RefPtr<Gio::FileEnumerator> enumerator = directory->enumerate_children();
		if(!enumerator)
			std::cerr << "Gio::File::enumerate_children() returned an empty RefPtr." << std::endl;

		RegexTools::Regex reg("^([^-]+)-(.*)\\.ffpreset");

		Glib::RefPtr<Gio::FileInfo> file_info = enumerator->next_file();
		while(file_info){
			if(file_info->get_file_type() == Gio::FILE_TYPE_REGULAR ){
				RegexTools::Matcher match = reg.getMatcher(file_info->get_name());
				if(match.find()){
					FFfile file;
					file.path = Glib::build_filename(directory->get_path (), file_info->get_name());
					file.fullName = file_info->get_name();
					file.prefix = match.getGroup(1);
					file.shortName = match.getGroup(2);
					prefixToFiles[file.prefix].push_back(file);
				}
			}
			file_info = enumerator->next_file();
		}
	}catch(const Glib::Exception& ex){
		std::cerr<<ex.what()<<std::endl;
	}
}

FFpresets::~FFpresets() {
	// TODO Auto-generated destructor stub
}

void FFpresets::copyPartOfListToList(
		const std::map<std::string, std::list<FFfile> >::const_iterator& it,
		std::list<std::pair<std::string, std::string> >& ret) const {
	std::list<FFfile>::const_iterator iter;
	for (iter = it->second.begin(); iter != it->second.end(); ++iter) {
		std::pair<std::string, std::string> tmp(iter->shortName, iter->path);
		ret.push_back(tmp);
	}
}

std::list<std::pair<std::string, std::string> > FFpresets::getShortnamesWithPaths(
		const std::string &prefix) const {
	std::list<std::pair<std::string, std::string> > ret;
	std::map<std::string, std::list<FFfile> >::const_iterator it;
	it = prefixToFiles.find(prefix);
	if(it != prefixToFiles.end()){
		copyPartOfListToList(it, ret);
	}
	it = userDefined.find(prefix);
	if(it != userDefined.end()){
		copyPartOfListToList(it, ret);
	}
	return ret;
}
void FFpresets::addUserDefinedFile(std::string prefix, const Glib::RefPtr< Gio::File >& file){
	FFfile ff;
	ff.path = file->get_path();
	ff.fullName = file->get_basename();
	ff.prefix = prefix;
	ff.shortName = file->get_basename();
	userDefined[ff.prefix].push_back(ff);
}
} /* namespace FFTools */
