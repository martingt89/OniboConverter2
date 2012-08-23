/*
 * findffmpegdialog.h
 *
 *  Created on: 22.8.2012
 *      Author: martint
 */

#ifndef FINDFFMPEGDIALOG_H_
#define FINDFFMPEGDIALOG_H_

#include<gtkmm/window.h>
#include <gtkmm/builder.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include <gtkmm/filechooserdialog.h>
#include "../CppExtension/path.h"
namespace Gui {

class FindFFmpegDialog {
public:
	FindFFmpegDialog(const Glib::RefPtr<Gtk::Builder>& refGlade, Path& ffmpegPath);
	virtual ~FindFFmpegDialog();
	Gtk::Window& getWindow();
	bool isNewStart();
private:
	void findOkClicked();
	void findQuitClicked();
	void findChooseFileClicked();
	Path& ffmpegPath;
	Gtk::FileChooserDialog fileChooser;
	Gtk::Window* findFFmpegWindow;
	Gtk::Button* findChooseFile;
	Gtk::Button* findOk;
	Gtk::Button* findQuit;
	Gtk::Entry* findFFmpegPath;
	Gtk::Label* findErrorMessage;
	bool restart;
};

} /* namespace Gui */
#endif /* FINDFFMPEGDIALOG_H_ */
