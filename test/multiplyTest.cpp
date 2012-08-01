/*
 * main.cpp
 *
 *  Created on: Aug 25, 2011
 *      Author: caioviel
 */

#include <iostream>
using namespace std;

#include "../include/MessengerFactory.h"
using namespace messenger;


class SimpleListener : public IMessengerListener {

public:
	SimpleListener(std::string id) {
		this->id = id;
	}

	virtual void receiveMessage( const string& messageStr ) {
		std::cout << "<" << id << ">:" << messageStr << std::endl;
	}

private:
	std::string id;

};

int main(int argc, char* argv[]) {
	std::string brokerURI =
			"failover:(tcp://localhost:61616?jms.watchTopicAdvisories=false"
			//        "&wireFormat=openwire"
			//        "&connection.useAsyncSend=true"
			//        "&transport.commandTracingEnabled=true"
			//        "&transport.tcpTracingEnabled=true"
			//        "&wireFormat.tightEncodingEnabled=true"
			")";

    std::string topic1 = "TEST.MULTIPLY_1";
    std::string topic2 = "TEST.MULTIPLY_3";


    cout << "This is a message before the constructor." << endl;

	string str = "{ \"notification\" : { \"channel\" : 6, \"id\" : 1, \"label\""
			" : \"Alguma coisa aconteceu?\", \"options\" : [ { \"id\" : 1, \"label\" "
			": \"Sim\" }, { \"id\" : 2, \"label\" : \"Nao\" } ], \"type\" : \"multiply\" } }";

	MessengerFactory factory;

	IBrokerConnection* conn = factory.CreateBrokerConnection(brokerURI);
	conn->connect();

	IMessenger* messenger1 = factory.CreateMessenger(conn, topic1, topic1);
	messenger1->setMessengerListener( new SimpleListener("Listener1") );
	messenger1->connect();

	IMessenger* messenger2 = factory.CreateMessenger(conn, topic2, topic2);
	messenger2->setMessengerListener( new SimpleListener("Listener2") );
	messenger2->connect();

	sleep(1);
	std::cout << "Vamos enviar a mensagem: " << std::endl;
	messenger1->sendMessage(str);
	messenger2->sendMessage(str);
	std::cout << "Mensagem enviada!" << std::endl;
	sleep(1);

	messenger1->disconnect();
	messenger2->disconnect();
	conn->disconnect();
	return 0;
}



