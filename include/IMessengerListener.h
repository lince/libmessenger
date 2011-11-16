/*
 * IMessengerListener.h
 *
 *  Created on: Sep 15, 2011
 *      Author: caioviel
 */

#ifndef IMESSENGERLISTENER_H_
#define IMESSENGERLISTENER_H_

#include <string>

namespace messenger {

class IMessengerListener {

public:
	virtual ~IMessengerListener() {}

	virtual void receiveMessage( const std::string& messageStr ) = 0;
};

} /* namespace messenger */
#endif /* IMESSENGERLISTENER_H_ */
