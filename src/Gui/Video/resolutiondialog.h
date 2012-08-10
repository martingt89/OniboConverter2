/*
 * videoresolutiongui.h
 *
 *  Created on: 9.8.2012
 *      Author: martint
 */

#ifndef RESOLUTIONCONTROL_H_
#define RESOLUTIONCONTROL_H_

#include <gtkmm/builder.h>
#include <gtkmm/dialog.h>
#include <gtkmm/entry.h>
#include <gtkmm/treeview.h>
#include <gtkmm/liststore.h>
#include "../WidgetAdapter/comboboxext.h"
#include "../../ConverterOptions/optionsdatabase.h"

namespace Gui {
namespace Video {

class ResolutionControl {
private:
	class ModelColumns : public Gtk::TreeModel::ColumnRecord{
	public:
		ModelColumns(){
			add(colAspect);
			add(colResolution);
			add(colResolName);
			add(resolution);
		}
		Gtk::TreeModelColumn<std::string> colAspect;
		Gtk::TreeModelColumn<std::string> colResolution;
		Gtk::TreeModelColumn<std::string> colResolName;
		Gtk::TreeModelColumn<ConverterOptions::Resolution> resolution;
	};
public:
	ResolutionControl(ConverterOptions::OptionsDatabase &database,
			const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~ResolutionControl();
	bool start(ConverterOptions::Resolution& resolution);
private:
	void doubleClickOnBoard(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn*);
	void clickOnBoard();
	void changedX();
	void changedY();
	void aspectChanged();
	void initAspectRatio(ComboBoxExt<ConverterOptions::AspectRatio>& aspectRatio);
	void fillCanavas(Glib::RefPtr<Gtk::ListStore>& treeModel);
	void setResolutiontoEntry(const ConverterOptions::Resolution& resolution);
	std::string calcAspect(const int& x, const int& y);
	ConverterOptions::OptionsDatabase &database;
	Gtk::Dialog* resolutionDialog;
	Gtk::Entry* resolutionEntryX;
	Gtk::Entry* resolutionEntryY;
	Gtk::Label* resolutionError;
	ComboBoxExt<ConverterOptions::AspectRatio> aspectRatio;
	ModelColumns model;
	Gtk::TreeView* resolutionCanavas;
	Glib::RefPtr<Gtk::ListStore> treeModel;
	Glib::RefPtr<Gtk::TreeSelection> treeSelection;

	bool isEnableSignal;
};

}
} /* namespace Gui */
#endif /* RESOLUTIONCONTROL_H_ */
