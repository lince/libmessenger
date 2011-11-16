/*
 * MessengerFactory.h
 *
 *   Created on: Nov 16, 2011
 *  Last Chance: 1:57:44 PM
 *       Author: caioviel
 *       E-mail: caio_viel@dc.ufscar.br
 */

#ifndef MESSENGERFACTORY_H_
#define MESSENGERFACTORY_H_

#include <libcpputil/logger/Loggable.h>

#include "IMessenger.h"

namespace messenger {

class MessengerFactory : public cpputil::logger::Loggable {

public:
	MessengerFactory();

	virtual ~MessengerFactory();

	IMessenger* CreateMessenger(
			const std::string& brokerURI,
			const std::string& destURI,
			const std::string& origURI,
			bool useTopic = true,
			bool clientAck = true,
			bool persistent = true);
};

} /* namespace messenger */
#endif /* MESSENGERFACTORY_H_ */
