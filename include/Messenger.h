/*
 * MessengerReceiver.h
 *
 *  Created on: Sep 15, 2011
 *      Author: caioviel
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

using namespace activemq;
using namespace activemq::core;
using namespace activemq::transport;
using namespace decaf::lang;
using namespace decaf::util;
using namespace decaf::util::concurrent;
using namespace cms;

namespace messenger {

class Messenger : 	public ExceptionListener,
					public MessageListener,
					public DefaultTransportListener,
					public IMessenger,
					public cpputil::logger::Loggable {

public:
	Messenger(
			const std::string& brokerURI,
			const std::string& destURI,
			const std::string& origURI,
			bool useTopic = true,
			bool clientAck = true,
			bool persistent = true);

	virtual ~Messenger() throw();

	virtual void connect();

	virtual void disconnect();

	virtual void sendMessage(const std::string& text);

	virtual void setMessengerListener(IMessengerListener* msgListener);


	/* CMS Listeners */
	virtual void onMessage( const Message* message ) throw();

	virtual void onException( const CMSException& ex AMQCPP_UNUSED );

	virtual void transportInterrupted();

	virtual void transportResumed();

private:

	void cleanup();

private:
	Connection* connection;
	Session* session;
	Destination* destinationConsumer;
	Destination* destinationProducer;
	MessageConsumer* consumer;
    MessageProducer* producer;

	std::string brokerURI;
	std::string destURI;
	std::string origURI;

	bool useTopic;
	bool clientAck;
	bool persistent;
	IMessengerListener* msgListener;
	cpputil::logger::Logger* logger;

};

} /* namespace messenger */
#endif /* MESSENGE_H_ */
