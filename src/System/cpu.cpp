/*
 * cpu.cpp
 *
 *  Created on: 10.9.2012
 *      Author: martin
 */

#include "cpu.h"
#include <unistd.h>

namespace System {

int CPU::getNumerOfThreads(){
	int cpus = sysconf(_SC_NPROCESSORS_ONLN);
	if(cpus <= 0){
		cpus = 1;
	}
	return cpus;
}

} /* namespace System */
