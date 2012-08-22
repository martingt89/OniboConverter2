/*
 * findfmpegdialog.cpp
 *
 *  Created on: 22.8.2012
 *      Author: martint
 */

#include "findffmpegdialog.h"

namespace Gui {

FindFFmpegDialog::FindFFmpegDialog(const Glib::RefPtr<Gtk::Builder>& refGlade, Path& ffmpegPath) :
	ffmpegPath(ffmpegPath){
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

FindFFmpegDialog::~FindFFmpegDialog() {
	// TODO Auto-generated destructor stub
}

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
	//todo add file chooser dialog
}
} /* namespace Gui */
