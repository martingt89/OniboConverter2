/*
 * overwritedialog.h
 *
 *  Created on: 30.8.2012
 *      Author: martint
 */

#ifndef OVERWRITEDIALOG_H_
#define OVERWRITEDIALOG_H_

#include <list>
#include <gtkmm/window.h>
#include <gtkmm/entry.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/builder.h>
#include "../MediaFile/mediafile.h"
#include "convertwindow.h"

namespace Gui {

class OverwriteDialog {
public:
	OverwriteDialog(const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~OverwriteDialog();
	void addFile(MediaFile::MediaFile*& file);
private:
	void loadWidgets(const Glib::RefPtr<Gtk::Builder>& refGlade);
	void showFile(MediaFile::MediaFile*& file);
	void overwriteClicked();
	void cancelClicked();
	void renameClicked();
	void getNext();
	void hide();

	std::list<MediaFile::MediaFile*> files;
	MediaFile::MediaFile* actualFile;
	Gtk::Window* overwriteWindow;
	Gtk::Entry* filePath;
	Gtk::Entry* newName;
	Gtk::Button* overwrite;
	Gtk::Button* rename;
	Gtk::Button* cancel;
	Gtk::Label* suffix;
};

} /* namespace Gui */
#endif /* OVERWRITEDIALOG_H_ */
