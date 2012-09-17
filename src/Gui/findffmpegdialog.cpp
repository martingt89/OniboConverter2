/* ---------------------------------------------------------------------------
** Author: Martin Geier
** findffmpegdialog.cpp is part of OniboConverter2.
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

#include "findffmpegdialog.h"
#include <gtkmm/stock.h>

namespace Gui {

FindFFmpegDialog::FindFFmpegDialog(const Glib::RefPtr<Gtk::Builder>& refGlade, Path& ffmpegPath) :
	ffmpegPath(ffmpegPath), fileChooser("Please choose a executable file", Gtk::FILE_CHOOSER_ACTION_OPEN){
	fileChooser.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	fileChooser.add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);

	refGlade->get_widget("findFFmpegWindow",findFFmpegWindow);
	refGlade->get_widget("findChooseFile",findChooseFile);
	refGlade->get_widget("findOk",findOk);
	refGlade->get_widget("findQuit",findQuit);
	refGlade->get_widget("findFFmpegPath",findFFmpegPath);
	refGlade->get_widget("findErrorMessage",findErrorMessage);

	findFFmpegPath->set_text(ffmpegPath.getPath());
	restart = false;

	findOk->signal_clicked().connect(sigc::mem_fun(*this, &FindFFmpegDialog::findOkClicked));
	findQuit->signal_clicked().connect(sigc::mem_fun(*this, &FindFFmpegDialog::findQuitClicked));
	findChooseFile->signal_clicked().connect(sigc::mem_fun(*this, &FindFFmpegDialog::findChooseFileClicked));
}

FindFFmpegDialog::~FindFFmpegDialog() {}

Gtk::Window& FindFFmpegDialog::getWindow(){
	return *findFFmpegWindow;
}
bool FindFFmpegDialog::isNewStart(){
	return restart;
}
void FindFFmpegDialog::findOkClicked(){
	ffmpegPath = Path(findFFmpegPath->get_text());
	restart = true;
	findFFmpegWindow->hide();
}
void FindFFmpegDialog::findQuitClicked(){
	restart = false;
	findFFmpegWindow->hide();
}
void FindFFmpegDialog::findChooseFileClicked(){
	int res = fileChooser.run();
	fileChooser.hide();
	if(res == Gtk::RESPONSE_OK){
		Glib::RefPtr< Gio::File > file = fileChooser.get_file ();
		findFFmpegPath->set_text(file->get_path());
	}
}
} /* namespace Gui */
