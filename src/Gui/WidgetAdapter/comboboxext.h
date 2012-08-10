/*
 * comboboxext.h
 *
 *  Created on: 23.7.2012
 *      Author: martint
 */

#ifndef COMBOBOXEXT_H_
#define COMBOBOXEXT_H_

#include <gtkmm/comboboxtext.h>
#include <gtkmm/builder.h>
#include "../../helper.h"

template<class T>
class ComboBoxExt{
public:
	ComboBoxExt(const Glib::RefPtr<Gtk::Builder>& refGlade, const std::string& name){
		comboBoxText = 0;
		saveSelectedRow = -1;
		sensitive = false;
		refGlade->get_widget(name, comboBoxText);
	}
	~ComboBoxExt(){
		if(comboBoxText != 0){
			delete comboBoxText;
		}
	}
	void append(const std::string& text, const T &item = T()){
		bool wasSensitive = comboBoxText->get_sensitive();
		comboBoxText->set_sensitive(true);
		comboBoxText->append(text, toS(items.size()));
		items.push_back(std::make_pair(text, item));
		if(! (wasSensitive)){
			comboBoxText->set_sensitive(false);
		}
	}
	void insertAfterLast(const std::string& text, const T &item = T()){
		const int lastIndex = items.size()-1;
		if(lastIndex >= 0){

			const std::string lastText = items[lastIndex].first;
			const T lastItem = items[lastIndex].second;

			comboBoxText->remove_text(lastIndex);
			items.pop_back();

			this->append(text, item);
			this->append(lastText, lastItem);
		}else{
			this->append(text, item);
		}
	}
	//
	bool containes(const std::string& text){
		auto iter = std::find_if(items.begin(), items.end(),
				[text](const std::pair<std::string, T>& pair) -> bool {
			return pair.first == text;
		});
		return iter != items.end();
	}
	bool isSelectedIfActivable(){
		if(/*isActivable &&*/ is_sensitive()){
			return is_selected();
		}else{
			return true; //isActivable
		}
	}

	bool isSelectedActivableRow(){
		return is_sensitive() && is_selected();
	}

	std::string getValue(){
		return comboBoxText->get_entry_text();
	}

	void set_active_row_number(int index){
		comboBoxText->set_active(index);
	}
	int get_active_row_number(){
		return comboBoxText->get_active_row_number();
	}
	std::string get_active_text(){
		return comboBoxText->get_active_text();
	}
	T get_active_row_item(bool& isSelected){
		T selectedItem;
		if(comboBoxText->get_active_row_number() >= 0){
			isSelected = true;
			selectedItem = items[comboBoxText->get_active_row_number()].second;
		}else{
			isSelected = false;
			selectedItem = T();
		}
		return selectedItem;
	}
	T get_active_row_item(){
		T selectedItem;
		if(comboBoxText->get_active_row_number() >= 0){
			selectedItem = items[comboBoxText->get_active_row_number()].second;
		}else{
			selectedItem = T();
		}
		return selectedItem;
	}
	void remove_all(){
		comboBoxText->remove_all();
		items.clear();
		items.resize(0);
	}
	void set_sensitive(bool sensitive){
		comboBoxText->set_sensitive(sensitive);
	}
	void set_active_text(const std::string& text){
		comboBoxText->set_active_text(text);
	}

	bool is_sensitive(){
		return comboBoxText->get_sensitive();
	}

	bool is_selected(){
		return comboBoxText->get_active_row_number() >= 0;
	}
	Glib::SignalProxy0< void > signal_changed(){
		return comboBoxText->signal_changed();
	}
	void unset_active(){
		comboBoxText->unset_active();
	}
	int count_of_rows(){
		return items.size();
	}
//	void set_activable(bool activable){
//		this->isActivable = activable;
//	}
//	bool is_activable(){
//		return isActivable;
//	}
	void save_actual_state(){
		sensitive = comboBoxText->is_sensitive();
		saveSelectedRow = comboBoxText->get_active_row_number();
		saveItems.clear();
		saveItems.resize(items.size());
		std::copy(items.begin(), items.end(), saveItems.begin());
	}
	void restor_saved_state(){
		this->remove_all();
		std::for_each(saveItems.begin(), saveItems.end(), [&](std::pair<std::string, T> item) {
			this->append(item.first, item.second);
		});
		this->set_sensitive(sensitive);
		if(saveSelectedRow >= 0){
			this->set_active_row_number(saveSelectedRow);
		}
	}
	bool is_set_last(){
		return comboBoxText->get_active_row_number() == (int)(items.size()-1);
	}
	bool is_set_first(){
		return comboBoxText->get_active_row_number() == 0;
	}
private:
	Gtk::ComboBoxText* comboBoxText;
	std::vector<std::pair<std::string, T> > items;

	std::vector<std::pair<std::string, T> > saveItems;
	int saveSelectedRow;
	bool sensitive;
};


#endif /* COMBOBOXEXT_H_ */
