/* ---------------------------------------------------------------------------
** Author: Martin Geier
** safestream.cpp is part of ProcessExecutor.
**
** ProcessExecutor is free software: you can redistribute it and/or modify
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

#include "safestream.h"
#include <iostream>
namespace ProcessExecutor {

SafeStream::SafeStream() {
	open = true;
}

SafeStream::~SafeStream() {
	open = false;
}
bool SafeStream::operator<<(const std::string& text){
	std::unique_lock<std::mutex> m(mutex);
	if(open){
		buffer.push_back(text);
		cond.notify_all();
	}
	return open;
}
int SafeStream::operator>>=(std::string& text){
	std::unique_lock<std::mutex> m(mutex);
	if(!buffer.empty()){
		text = buffer.front();
		buffer.pop_front();
		return 1;
	}
	if(open){
		return -1;		//nothing read
	}
	return 0;			//buffer is close
}
bool SafeStream::operator>>(std::string& text){
	std::unique_lock<std::mutex> m(mutex);
	while(open && buffer.empty()){
		cond.wait(m);
	}
	if(!buffer.empty()){
		text = buffer.front();
		buffer.pop_front();
		return true;
	}
	return open;
}
bool SafeStream::isOpen(){
	std::unique_lock<std::mutex> m(mutex);
	return open;
}
void SafeStream::close(){
	std::unique_lock<std::mutex> m(mutex);
	open = false;
	cond.notify_all();
}
} /* namespace ProcessExecutor */
