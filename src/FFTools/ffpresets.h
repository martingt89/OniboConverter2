/*
 * ffpresets.h
 *
 *  Created on: 12.7.2012
 *      Author: martint
 */

#ifndef FFPRESETS_H_
#define FFPRESETS_H_
#include <string>
#include <map>
#include <list>
#include <giomm/file.h>

namespace FFTools {

class FFpresets {
private:
	struct FFfile{
		std::string path;
		std::string prefix;
		std::string fullName;
		std::string shortName;
	};
public:
	FFpresets();
	std::list<std::pair<std::string, std::string> > getShortnamesWithPaths(const std::string &prefix) const;
	void addUserDefinedFile(std::string prefix, const Glib::RefPtr< Gio::File >& file);
private:
	std::map<std::string, std::list<FFfile> > prefixToFiles;
	std::map<std::string, std::list<FFfile> > userDefined;

	void appendMapToList(
			const std::map<std::string, std::list<FFfile> >::const_iterator& it,
			std::list<std::pair<std::string, std::string> >& ret) const;
};

} /* namespace FFTools */
#endif /* FFPRESETS_H_ */
