/* ---------------------------------------------------------------------------
** Author: Martin Geier
** findffmpegdialog.h is part of OniboConverter2.
**
** OniboConverter2 is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
** -------------------------------------------------------------------------*/

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
