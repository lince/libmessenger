/**
 * File: Messenger.h
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

#ifndef MESSENGER_H_
#define MESSENGER_H_

#include <decaf/lang/Thread.h>
#include <decaf/lang/Runnable.h>
#include <decaf/util/concurrent/CountDownLatch.h>
#include <activemq/core/ActiveMQConnectionFactory.h>
#include <activemq/core/ActiveMQConnection.h>
#include <activemq/transport/DefaultTransportListener.h>
#include <activemq/library/ActiveMQCPP.h>
#include <decaf/lang/Integer.h>
#include <activemq/util/Config.h>
#include <decaf/util/Date.h>
#include <cms/Connection.h>
#include <cms/Session.h>
#include <cms/TextMessage.h>
#include <cms/BytesMessage.h>
#include <cms/MapMessage.h>
#include <cms/ExceptionListener.h>
#include <cms/MessageListener.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

#include <libcpputil/logger/Logger.h>
#include <libcpputil/InitializationException.h>

#include "IMessenger.h"
#include "IBrokerConnection.h"

namespace messenger {

/**
 * This class is Messenger that communicate with the Broker via text messages.
 * You can create an instance of this class by the MessengerFactory
 * and access its methods via IMessenger interface.
 * This class is hidden from the users of libmessenger due
 * its cms includes that can be complicated to handle by the library users.
 * This class is notified when Exception occurs in the broker.
 */
class Messenger : 	public cms::ExceptionListener,
					public cms::MessageListener,
					public activemq::transport::DefaultTransportListener,
					public IMessenger,
					public cpputil::logger::Loggable {

public:

	/**
	 * Complete Constructor
	 * @param brokerURI The URI of the broker that the Messenger will be connected.
	 * @param destURI The URI of the topic/queue to where the messages will be sent.
	 * @param origURI The URI of the topic/queu from where the nessages will be received.
	 * @param useTopic if true, the communication will be proceed using topic, false it will use queue
	 * @param clientAck if true, clients will receive ack for each message they send.
	 * @param persistent if true, the messages will be persistent on the broker.
	 */
	Messenger(
			IBrokerConnection* brokerConnection,
			const std::string& destURI,
			const std::string& origURI,
			bool useTopic = true,
			bool persistent = true);

	Messenger(
			const std::string& brokerURI,
			const std::string& destURI,
			const std::string& origURI,
			bool useTopic = true,
			bool clientAck = true,
			bool persistent = true);

	/**
	 * Destructor
	 * Realize the clean-up and delete all the agregade instances.
	 */
	virtual ~Messenger() throw();

	virtual void connect();

	virtual void disconnect();

	virtual void sendMessage(const std::string& text);

	virtual void setMessengerListener(IMessengerListener* msgListener);


	/* CMS Listeners */
	/**
	 * This method is a callback that will be called when new messages arrive from the broker
	 * @param message The message that just arrives.
	 */
	virtual void onMessage( const cms::Message* message ) throw();

	/**
	 * This method is a callback that will be called whwn Exceptions arrive from the broker.
	 */
	virtual void onException( const cms::CMSException& ex AMQCPP_UNUSED );

	/**
	 * This method is callback that wil be called when the transport stream is interrupted.
	 */
	virtual void transportInterrupted();

	/**
	 * This method is callback that wil be called when the transport stream is resumed.
	 */
	virtual void transportResumed();

private:

	void cleanup();

private:
	//cms::Connection* connection;
	cms::Session* session;
	cms::Destination* destinationConsumer;
	cms::Destination* destinationProducer;
	cms::MessageConsumer* consumer;
	cms::MessageProducer* producer;

	std::string brokerURI;
	std::string destURI;
	std::string origURI;

	bool useTopic;
	bool persistent;
	IMessengerListener* msgListener;
	IBrokerConnection* brokerConnection;

};

} /* namespace messenger */
#endif /* MESSENGE_H_ */
