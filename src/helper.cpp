/*
 * helper.cpp
 *
 *  Created on: 9.8.2012
 *      Author: martint
 */

#include "helper.h"

int NSD(const int& x, const int& y){
	int nsd = 0;
	int b = y;
	int a = x;
	if (b == 0){
		nsd = a;
	}else{
		nsd = NSD(b, a % b);
	}
	return nsd;
}

