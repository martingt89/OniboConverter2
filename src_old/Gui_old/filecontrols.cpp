/*
 * filecontrols.cpp
 *
 *  Created on: 29.7.2012
 *      Author: martint
 */

#include "filecontrols.h"

namespace Gui {

FileControls::FileControls() {
	// TODO Auto-generated constructor stub

}

FileControls::~FileControls() {
	// TODO Auto-generated destructor stub
}

sigc::signal<void, std::list<Path> >& FileControls::signalAddFilterToFiles(){
	return addFilterToFile;
}
sigc::signal<void, std::list<Path> >& FileControls::signalRemoveFiles(){
	return removeFiles;
}

std::list<Path> FileControls::getAllFiles(){
	return std::list<Path>(); //todo implement
}

} /* namespace Gui */
