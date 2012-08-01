/**
 * File: MessengerFactory.cpp
 * Created by: Caio César Viel
 * Contact: caioviel@gmail.com
 * Last Modification: 02-16-2012
 *
 * Copyright (c) 2012 LINCE-UFSCar
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this
 * software and associated documentation files (the "Software"), to deal in the Software
 * without restriction, including without limitation the rights to use, copy, modify,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
 * FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include <activemq/library/ActiveMQCPP.h>

#include "../include/MessengerFactory.h"

#include "../include/Messenger.h"
#include "../include/BrokerConnection.h"

namespace messenger {

bool MessengerFactory::initialized = false;

MessengerFactory::MessengerFactory()
		: cpputil::logger::Loggable("messenger::MessengerFactory") {

	if (!initialized) {
		info("Initializing the Activemq Library");
		activemq::library::ActiveMQCPP::initializeLibrary();
		initialized = true;
	}

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

IMessenger* CreateMessenger(
			IBrokerConnection* connection,
			const std::string& destURI,
			const std::string& origURI,
			bool useTopic,
			bool persistent) {

	return new Messenger(connection, destURI, origURI, useTopic, persistent);

}

IBrokerConnection* CreateBrokerConnection(
			const std::string& brokerURI,
			bool clientAck) {

	return new BrokerConnection(brokerURI, clientAck);

}

} /* namespace messenger */
