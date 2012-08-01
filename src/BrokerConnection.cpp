/**
 * File: IMessenger.h
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

#include "../include/BrokerConnection.h"

namespace messenger {


BrokerConnection::BrokerConnection(const std::string& brokerURI,
		bool clientAck) : cpputil::logger::Loggable("messenger::BrokerConnection") {

	this->brokerURI = brokerURI;
	this->clientAck = false;
	this->connected = false;
	this->connection = NULL;
	this->session = NULL;

	trace("constructor");


}

BrokerConnection::~BrokerConnection() {
	trace("destructor");

	if (connected) {
		disconnect();
	}
}

void BrokerConnection::connect() {
	trace("connect()");

	if (connected) {
		throw cpputil::InitializationException(
				"Trying to connect the same instance twice.",
				"messenger::BrokerConnection",
				"connect()");
	}

	// Create a ConnectionFactory
	std::auto_ptr<activemq::core::ActiveMQConnectionFactory>
	connectionFactory(
			new activemq::core::ActiveMQConnectionFactory(brokerURI));

	try {

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

	} catch(cms::CMSException& e) {
		std::ostringstream ostr;
		e.printStackTrace(ostr);
		error(ostr.str());
		throw cpputil::InitializationException(
				e.what(),
				"messenger::BrokerConnection",
				"connect()");

	}

	connected = true;
}

void BrokerConnection::disconnect() {
	trace("disconnect()");

	if (!connected) {
		throw cpputil::InitializationException(
				"Trying to disconnect a unconnected instance.",
				"messenger::BrokerConnection",
				"disconnect()");
	}

	// Close open resources.
	try{
		if( session != NULL ) session->close();
		if( connection != NULL ) connection->close();
	}catch (cms::CMSException& e) {}

	// Now Destroy them
	try{
		if( session != NULL ) delete session;
	}catch (cms::CMSException& e) {}
	session = NULL;

	try{
		if( connection != NULL ) delete connection;
	}catch (cms::CMSException& e) {}
	connection = NULL;

	connected = false;
}

bool BrokerConnection::isConnected() {
	return this->connected;

}

cms::Connection* BrokerConnection::getCMSConnection() {
	trace("getCMSConnection()");

	if (!connected) {
		error("Trying to get a cms::Connection from a a unconnected instance.");

		throw cpputil::InitializationException(
				"Trying to get a cms::Connection from a a unconnected instance",
				"messenger::BrokerConnection",
				"getCMSConnection()");
	}

	return this->connection;

}

cms::Session* BrokerConnection::getCMSSession() {
	trace("getCMSSession()");

	if (!connected) {
		error("Trying to get a cms::Session from a a unconnected instance.");

		throw cpputil::InitializationException(
				"Trying to get a cms::Session from a a unconnected instance",
				"messenger::BrokerConnection",
				"getCMSSession()");
	}
	return this->session;

}

std::string BrokerConnection::getBrokerURI() {
	trace("getBrokerURI()");

	return this->brokerURI;
}

bool BrokerConnection::isClientAck() {
	return this->clientAck;
}


}
