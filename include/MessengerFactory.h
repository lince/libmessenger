/**
 * File: MessengerFactory.h
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

#ifndef MESSENGERFACTORY_H_
#define MESSENGERFACTORY_H_

#include <libcpputil/logger/Loggable.h>

#include "IMessenger.h"
#include "IBrokerConnection.h"

namespace messenger {

/**
 * This class is used to create instances of Messeger.
 */
class MessengerFactory : public cpputil::logger::Loggable {

public:
	/**
	 * Constructor
	 */
	MessengerFactory();

	/**
	 * Destructor
	 */
	virtual ~MessengerFactory();

	/**
	 * This method creates a new instance of Messenger.
	 * @param brokerURI The URI of the broker that the Messenger will be connected.
	 * @param destURI The URI of the topic/queue to where the messages will be sent.
	 * @param origURI The URI of the topic/queu from where the nessages will be received.
	 * @param useTopic if true, the communication will be proceed using topic, false it will use queue
	 * @param clientAck if true, clients will receive ack for each message they send.
	 * @param persistent if true, the messages will be persistent on the broker.
	 * @return The Messenger instance created.
	 */
	IMessenger* CreateMessenger(
			const std::string& brokerURI,
			const std::string& destURI,
			const std::string& origURI,
			bool useTopic = true,
			bool clientAck = true,
			bool persistent = true);

	IMessenger* CreateMessenger(
				IBrokerConnection* connection,
				const std::string& destURI,
				const std::string& origURI,
				bool useTopic = true,
				bool persistent = true);

	IBrokerConnection* CreateBrokerConnection(
				const std::string& brokerURI,
				bool clientAck = true);
};

} /* namespace messenger */
#endif /* MESSENGERFACTORY_H_ */
