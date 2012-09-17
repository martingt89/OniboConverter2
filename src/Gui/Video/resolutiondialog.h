/* ---------------------------------------------------------------------------
** Author: Martin Geier
** resolutiondialog.h is part of OniboConverter2.
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

#ifndef RESOLUTIONCONTROL_H_
#define RESOLUTIONCONTROL_H_

#include <gtkmm/builder.h>
#include <gtkmm/dialog.h>
#include <gtkmm/entry.h>
#include <gtkmm/treeview.h>
#include <gtkmm/liststore.h>
#include "../WidgetAdapter/comboboxext.h"
#include "../../MediaElement/elementsdb.h"

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
		Gtk::TreeModelColumn<MediaElement::Resolution> resolution;
	};
public:
	ResolutionControl(MediaElement::ElementsDB& elementsDB,
			const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~ResolutionControl();
	bool start(MediaElement::Resolution& resolution);
private:
	void doubleClickOnBoard(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn*);
	void clickOnBoard();
	void changedX();
	void changedY();
	void aspectChanged();
	void initAspectRatio(ComboBoxExt<MediaElement::AspectRatio>& aspectRatio);
	void fillCanavas(Glib::RefPtr<Gtk::ListStore>& treeModel);
	void setResolutiontoEntry(const MediaElement::Resolution& resolution);
	std::pair<int, int> calcAspect(const int& x, const int& y);
	MediaElement::ElementsDB& elementsDB;
	Gtk::Dialog* resolutionDialog;
	Gtk::Entry* resolutionEntryX;
	Gtk::Entry* resolutionEntryY;
	Gtk::Label* resolutionError;
	ComboBoxExt<MediaElement::AspectRatio> aspectRatio;
	ModelColumns model;
	Gtk::TreeView* resolutionCanavas;
	Glib::RefPtr<Gtk::ListStore> treeModel;
	Glib::RefPtr<Gtk::TreeSelection> treeSelection;

	bool isEnableSignal;
};

}
} /* namespace Gui */
#endif /* RESOLUTIONCONTROL_H_ */
