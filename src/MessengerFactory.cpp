/*
 * MessengerFactory.cpp
 *
 *   Created on: Nov 16, 2011
 *  Last Chance: 1:57:45 PM
 *       Author: caioviel
 *       E-mail: caio_viel@dc.ufscar.br
 */

#include "../include/MessengerFactory.h"

#include "../include/Messenger.h"

namespace messenger {

MessengerFactory::MessengerFactory()
		: cpputil::logger::Loggable("messenger::MessengerFactory") {

	// TODO Auto-generated constructor stub
}

MessengerFactory::~MessengerFactory() {
	// TODO Auto-generated destructor stub
}

IMessenger *MessengerFactory::CreateMessenger(
		const std::string & brokerURI,
		const std::string & destURI,
		const std::string & origURI,
		bool useTopic, bool clientAck, bool persistent) {

	return new Messenger(brokerURI, destURI, origURI, useTopic, clientAck, persistent);
}

} /* namespace messenger */
