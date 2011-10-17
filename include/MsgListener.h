/*
 * MessengerReceiver.h
 *
 *  Created on: Sep 15, 2011
 *      Author: caioviel
 */

#ifndef MSGLISTENER_H_
#define MSGLISTENER_H_

#include <cpputil/logger/Logger.h>

namespace messenger {

class MsgListener {

public:
	virtual ~MsgListener() {}

	virtual void receiveMsg( const std::string& messageStr ) = 0;

private:

	void cleanup();
};

} /* namespace messenger */
#endif /* MSGLISTENER_H_ */
