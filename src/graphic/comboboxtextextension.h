/*
 * comboboxtextextension.h
 *
 *  Created on: 23.7.2012
 *      Author: martint
 */

#ifndef COMBOBOXTEXTEXTENSION_H_
#define COMBOBOXTEXTEXTENSION_H_

#include <gtkmm/comboboxtext.h>
#include "../helper.h"

template<class T>
class ComboBoxTextExtension{
	ComboBoxTextExtension(){
		comboBoxText = 0;
		isActivable = true;
		saveActiveRow = -1;
	}
	void set_comboboxtext_widget(Gtk::ComboBoxText* _comboBoxText){
		comboBoxText = _comboBoxText;
	}
	void append(const std::string& text, const T &item = T()){
		bool wasSensitive = comboBoxText->get_sensitive();
		comboBoxText->set_sensitive(true);
		comboBoxText->append(text, toS(items.size()));
		items.push_back(item);
		if(! (wasSensitive && isActivable)){
			comboBoxText->set_sensitive(false);
		}
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
			selectedItem = items[comboBoxText->get_active_row_number()];
		}else{
			isSelected = false;
			selectedItem = T();
		}
		return selectedItem;
	}
	void remove_all(){
		comboBoxText->remove_all();
		items.clear();
		items.resize(0);
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
	void unset_sctive(){
		comboBoxText->unset_active();
	}
	int count_of_rows(){
		return items.size();
	}
	void save_actual_row(){
		saveActiveRow = comboBoxText->get_active_id();
	}
	bool was_changed_saved_row(){
		return saveActiveRow == comboBoxText->get_active_id();
	}
	void set_activable(bool activable){
		this->isActivable = activable;
	}
	bool is_activable(){
		return isActivable;
	}
	bool is_set_last(){
		return comboBoxText->get_active_row_number() == (items.size()-1);
	}
	bool is_set_first(){
		return comboBoxText->get_active_row_number() == 0;
	}
private:
	Gtk::ComboBoxText* comboBoxText;
	std::vector<T> items;
	bool isActivable;
	int saveActiveRow;
};


#endif /* COMBOBOXTEXTEXTENSION_H_ */
