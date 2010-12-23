/*
 * wake.h
 *
 *  Created on: 23.12.2010
 *      Author: Felix Jung <felix.jung@wilhelm-gym.net>
 */
#include <string>

#ifndef _WAKE_H_
#define _WAKE_H_

using namespace std;

class Wake {
private:
	bool wake_enabled;
public:
	Wake(bool enabled);
	void wake_mac(string mac);
};


#endif /* _WAKE_H_ */
