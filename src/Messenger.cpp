/**
 * File: Messenger.cpp
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

#include "../include/Messenger.h"
using namespace cpputil::logger;
using namespace std;

using namespace activemq;
using namespace activemq::core;
using namespace activemq::transport;
using namespace decaf::lang;
using namespace decaf::util;
using namespace decaf::util::concurrent;
using namespace cms;

#include <cassert>
#include <string>

namespace messenger {

Messenger::Messenger(
		const std::string& brokerURI,
		const std::string& destURI,
		const std::string& origURI,
		bool useTopic,
		bool clientAck,
		bool persistent) : Loggable("messenger::Messenger") {

	trace(" begin constructor");

	static bool isInitialized = false;
	//TODO: sincronizacao
	if (!isInitialized) {
		activemq::library::ActiveMQCPP::initializeLibrary();
		isInitialized =  true;
	}

	connection = NULL;
	session = NULL;
	destinationConsumer = NULL;
	destinationProducer = NULL;
	consumer = NULL;
    producer = NULL;
    msgListener = NULL;

	this->brokerURI = brokerURI;
	this->destURI = destURI;
	this->origURI = origURI;

	this->useTopic = useTopic;
	this->clientAck = clientAck;
	this->persistent = persistent;
}

Messenger::~Messenger() throw() {
	trace("begin destructor");

	this->cleanup();
}

void Messenger::connect() {
	trace("begin connect()");

	if (!msgListener) {
		throw cpputil::InitializationException(
				"Trying to connect without informing the MsgListener",
				"messenger::Messenger",
				"connect()");
	}

	try {

		// Create a ConnectionFactory
		std::auto_ptr<activemq::core::ActiveMQConnectionFactory>
		connectionFactory(
				new activemq::core::ActiveMQConnectionFactory(brokerURI));

		// Create a Connection
		try {
			connection = connectionFactory->createConnection();
			connection->start();
		} catch (cms::CMSException& e) {
			e.printStackTrace();
			throw e;
		}

		// Create a Session
		if (clientAck) {
			session = connection->createSession(
					cms::Session::CLIENT_ACKNOWLEDGE);
		} else {
			session = connection->createSession(cms::Session::AUTO_ACKNOWLEDGE);
		}

		// Create the destination (Topic or Queue)
		if (useTopic) {
			destinationConsumer = session->createTopic(origURI);
			destinationProducer = session->createTopic(destURI);
		} else {
			destinationConsumer = session->createQueue(origURI);
			destinationProducer = session->createQueue(destURI);
		}
		// Create a MessageProducer from the Session to the Topic or Queue

		if (persistent) {
			producer = session->createProducer(destinationProducer);
			producer->setDeliveryMode(cms::DeliveryMode::NON_PERSISTENT);
		} else {
			producer = session->createProducer(destinationProducer);
			producer->setDeliveryMode(cms::DeliveryMode::PERSISTENT);
		}
		consumer = session->createConsumer( destinationConsumer );
		consumer->setMessageListener( this );

	} catch (cms::CMSException& e) {
		ostringstream ostr;
		e.printStackTrace(ostr);
		error(ostr.str());
		throw cpputil::InitializationException(
				e.what(),
				"messenger::Messenger",
				"connect()");
	}
}

void Messenger::disconnect() {
	trace("begin disconnect()");

	this->cleanup();
}

void Messenger::sendMessage(const std::string& strMessage) {
	trace("sendMessage(cons string&)");

	try {
	    TextMessage* message = session->createTextMessage( strMessage );
	    producer->send( message );
		delete message;
	} catch (cms::CMSException& e) {
		ostringstream ostr;
		e.printStackTrace(ostr);
		error(ostr.str());
		throw cpputil::IllegalParameterException(
				e.what(),
				"messenger::Messenger",
				"connect()");
	}
}

void Messenger::setMessengerListener(IMessengerListener* msgListener) {
	trace("setMessengerListener(IMessengerListener*)");
	assert(msgListener);
	this->msgListener = msgListener;
}

// Called from the consumer since this class is a registered MessageListener.
void Messenger::onMessage( const Message* message ) throw() {
	trace(" begin onMessage(const Message* )");

	static int count = 0;

	try
	{
		count++;
		const TextMessage* textMessage =
				dynamic_cast< const TextMessage* >( message );
		string text = "";

		if( textMessage != NULL ) {
			text = textMessage->getText();
		} else {
			warning("A Non-Text message was received.");
			return;
		}

		message->acknowledge();
		debug("Message Received: " + text);
		msgListener->receiveMessage(text);

	} catch (CMSException& e) {
		//e.printStackTrace();
		ostringstream ostr;
		e.printStackTrace(ostr);
		error(ostr.str());
	}
}

// If something bad happens you see it here as this class is also been
// registered as an ExceptionListener with the connection.
void Messenger::onException( const CMSException& ex AMQCPP_UNUSED ) {
	error("CMS Exception occurred");
	throw ex;
}

void Messenger::transportInterrupted() {
	info("The Connection's Transport has been Interrupted.");
}

void Messenger::transportResumed() {
	info("The Connection's Transport has been Restored.");
}

void Messenger::cleanup(){
	trace("begin cleanup()");

	try{
		if( destinationProducer != NULL ) delete destinationProducer;
	}catch (CMSException& e) {}
	destinationProducer = NULL;

	try{
		if( destinationConsumer != NULL ) delete destinationConsumer;
	}catch (CMSException& e) {}
	destinationConsumer = NULL;

	try{
		if( consumer != NULL ) delete consumer;
	} catch (CMSException& e) {}
	consumer = NULL;

	try{
		if( producer != NULL ) delete producer;
	} catch (CMSException& e) {}
	producer = NULL;

	// Close open resources.
	try{
		if( session != NULL ) session->close();
		if( connection != NULL ) connection->close();
	}catch (CMSException& e) {}

	// Now Destroy them
	try{
		if( session != NULL ) delete session;
	}catch (CMSException& e) {}
	session = NULL;

	try{
		if( connection != NULL ) delete connection;
	}catch (CMSException& e) {}
	connection = NULL;

}

} /* namespace messenger */
