/* ---------------------------------------------------------------------------
** Author: Martin Geier
** resolutiondialog.cpp is part of OniboConverter2.
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

#include "resolutiondialog.h"

#include <gtkmm/stock.h>
#include "../../helper.h"
#include <vector>

namespace Gui {
namespace Video {
static const std::string INVALID_RESOLUTION = "Invalid final resolution";
static const std::string CUSTOM_MODE = "--- custom ---";

ResolutionControl::ResolutionControl(MediaElement::ElementsDB& elementsDB,
		const Glib::RefPtr<Gtk::Builder>& refGlade) : elementsDB(elementsDB),
				aspectRatio(refGlade, "aspectRatio"){

	refGlade->get_widget("resolutionDialog", resolutionDialog);
	refGlade->get_widget("resolutionEntryX", resolutionEntryX);
	refGlade->get_widget("resolutionEntryY", resolutionEntryY);
	refGlade->get_widget("resolutionCanavas", resolutionCanavas);
	refGlade->get_widget("resolutionError", resolutionError);

	isEnableSignal = true;

	resolutionDialog->add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	resolutionDialog->add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);

	treeModel = Gtk::ListStore::create(model);
	resolutionCanavas->set_model(treeModel);

	treeSelection = resolutionCanavas->get_selection();

	initAspectRatio(aspectRatio);
	fillCanavas(treeModel);

	resolutionCanavas->append_column("Aspect ratio", model.colAspect);
	resolutionCanavas->append_column("Resolution name", model.colResolName);
	resolutionCanavas->append_column("Resolution", model.colResolution);

	Gtk::TreeView::Column* pColumn;
	pColumn = resolutionCanavas->get_column(0);
	if(pColumn)
	  pColumn->set_sort_column(model.colAspect);
	pColumn = resolutionCanavas->get_column(1);
	if(pColumn)
	  pColumn->set_sort_column(model.colResolName);
	pColumn = resolutionCanavas->get_column(2);
	if(pColumn)
	  pColumn->set_sort_column(model.colResolution);

	resolutionCanavas->signal_row_activated().connect(
			sigc::mem_fun(this, &ResolutionControl::doubleClickOnBoard));
	treeSelection->signal_changed().connect(
		    sigc::mem_fun(*this, &ResolutionControl::clickOnBoard));
	resolutionEntryX->signal_changed().connect(
		    sigc::mem_fun(*this, &ResolutionControl::changedX));
	resolutionEntryY->signal_changed().connect(
		    sigc::mem_fun(*this, &ResolutionControl::changedY));
	aspectRatio.signal_changed().connect(
		    sigc::mem_fun(*this, &ResolutionControl::aspectChanged));
}

ResolutionControl::~ResolutionControl() {
	delete resolutionDialog;
	delete resolutionEntryX;
	delete resolutionEntryY;
	delete resolutionCanavas;
	delete resolutionError;
}

bool ResolutionControl::start(MediaElement::Resolution& resolution){
	resolutionError->set_text("");
	aspectRatio.remove_all();
	treeModel->clear();

	initAspectRatio(aspectRatio);
	fillCanavas(treeModel);

	while(1){
		int res = resolutionDialog->run();

		if(res == Gtk::RESPONSE_OK){
			int x = toN(resolutionEntryX->get_text(), int());
			int y = toN(resolutionEntryY->get_text(), int());
			if(x == 0 || y == 0){
				resolutionError->set_markup("<span color='red'>"+INVALID_RESOLUTION+"</span>");
				continue;
			}
			auto aspectRatio = calcAspect(x, y);
			MediaElement::AspectRatio aspect(aspectRatio.first, aspectRatio.second);
			std::string name = "";
			bool found = false;
			MediaElement::Resolution res = elementsDB.getResolutions().getResolutionBySize(x, y, found);
			if(found){
				aspect = res.getAspectRatio();
				name = res.getName();
			}
			resolution = MediaElement::Resolution(name, aspect, x, y, false);
			resolutionDialog->hide();
			return true;
		}
		break;
	}
	resolutionDialog->hide();
	return false;
}
void ResolutionControl::initAspectRatio(ComboBoxExt<MediaElement::AspectRatio>& aspectRatio){
	aspectRatio.append(CUSTOM_MODE);
	aspectRatio.set_active_row_number(0);

	auto aspectRatioList = elementsDB.getResolutions().getAspectRatios();
	for(auto aspectIter = aspectRatioList.begin(); aspectIter!= aspectRatioList.end(); ++aspectIter){
		aspectRatio.append(aspectIter->readableForm(), *aspectIter);
	}
}
void ResolutionControl::fillCanavas(Glib::RefPtr<Gtk::ListStore>& treeModel){
	treeModel->clear();
	std::set<MediaElement::Resolution> uniqueResol;
	if(aspectRatio.is_set_first()){	//custom mode
		auto resolutionList = elementsDB.getResolutions().getResolutions();
		std::for_each(resolutionList.begin(), resolutionList.end(),
				[&](const MediaElement::Resolution& resolution){
			if(uniqueResol.count(resolution) == 0){
				Gtk::TreeModel::Row row = *(treeModel->append());
				row[model.colAspect] = resolution.getAspectRatio().readableForm();
				std::string resol = toS(resolution.getValue().first) + "x" + toS(resolution.getValue().second);
				row[model.colResolution] = resol;
				row[model.colResolName] = resolution.getName();
				row[model.resolution] = resolution;
				uniqueResol.insert(resolution);
			}
		});
	}else{
		auto resol = elementsDB.getResolutions().getResolutionsByAspectRatio(aspectRatio.get_active_row_item());
		std::for_each(resol.begin(), resol.end(),
						[&](const MediaElement::Resolution& resolution){
			if(uniqueResol.count(resolution) == 0){
				Gtk::TreeModel::Row row = *(treeModel->append());
				row[model.colAspect] = resolution.getAspectRatio().readableForm();
				std::string resol = toS(resolution.getValue().first) + "x" + toS(resolution.getValue().second);
				row[model.colResolution] = resol;
				row[model.colResolName] = resolution.getName();
				row[model.resolution] = resolution;
				uniqueResol.insert(resolution);
			}
		});
	}
}
void ResolutionControl::changedX(){
	if(isEnableSignal){
		isEnableSignal = false;
		if(!aspectRatio.is_set_first()){
			int x = toN(resolutionEntryX->get_text(), int());
			int y = aspectRatio.get_active_row_item().convertXtoY(x);
			resolutionEntryY->set_text(toS(y));
		}
		isEnableSignal = true;
	}
}
void ResolutionControl::changedY(){
	if(isEnableSignal){
		isEnableSignal = false;
		if(!aspectRatio.is_set_first()){
			int y = toN(resolutionEntryY->get_text(), int());
			int x = aspectRatio.get_active_row_item().convertYtoX(y);
			resolutionEntryX->set_text(toS(x));
		}
		isEnableSignal = true;
	}
}
void ResolutionControl::doubleClickOnBoard(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn*){
	Gtk::TreeModel::Row row = *(treeModel->get_iter(path));
	if(row){
		MediaElement::Resolution resol = row[model.resolution];
		setResolutiontoEntry(resol);
		resolutionDialog->response(Gtk::RESPONSE_OK);
	}
}
void ResolutionControl::clickOnBoard(){
	std::vector<Gtk::TreeModel::Path> rows = treeSelection->get_selected_rows();
	if(rows.size() > 0){
		Gtk::TreeModel::Row row = *(treeModel->get_iter(rows[0]));
		MediaElement::Resolution resol = row[model.resolution];
		setResolutiontoEntry(resol);
	}
}
void ResolutionControl::aspectChanged(){
	fillCanavas(treeModel);
}
void ResolutionControl::setResolutiontoEntry(const MediaElement::Resolution& resolution){
	isEnableSignal = false;
	resolutionEntryX->set_text(toS(resolution.getValue().first));
	resolutionEntryY->set_text(toS(resolution.getValue().second));
	isEnableSignal = true;
}
std::pair<int, int> ResolutionControl::calcAspect(const int& x, const int& y){
	int nsd = NSD(x, y);
	int tx = x / nsd;
	int ty = y / nsd;
	return std::make_pair(tx, ty);
}

}
} /* namespace Gui */
