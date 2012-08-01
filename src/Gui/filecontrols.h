/*
 * filecontrols.h
 *
 *  Created on: 29.7.2012
 *      Author: martint
 */

#ifndef FILECONTROLS_H_
#define FILECONTROLS_H_

#include "../CppExtension/path.h"
#include <list>
#include <sigc++/sigc++.h>

namespace Gui {

class FileControls {
public:
	FileControls();
	virtual ~FileControls();
	sigc::signal<void, std::list<Path> >& signalAddFilterToFiles();
	sigc::signal<void, std::list<Path> >& signalRemoveFiles();
	std::list<Path> getAllFiles();
private:
	sigc::signal<void, std::list<Path> > addFilterToFile;
	sigc::signal<void, std::list<Path> > removeFiles;
};

} /* namespace Gui */
#endif /* FILECONTROLS_H_ */
