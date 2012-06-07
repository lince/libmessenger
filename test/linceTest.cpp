/*
 * main.cpp
 *
 *  Created on: Aug 25, 2011
 *      Author: caioviel
 */

#include <iostream>
using namespace std;

#include "../include/Messenger.h"
using namespace messenger;


class SimpleListener : public IMessengerListener {

	virtual void receiveMessage( const string& messageStr ) {
		std::cout << messageStr << std::endl;
	}

};

int main(int argc, char* argv[]) {
	std::string brokerURI =
			"failover:(tcp://200.18.98.23:61616?jms.watchTopicAdvisories=false"
			//        "&wireFormat=openwire"
			//        "&connection.useAsyncSend=true"
			//        "&transport.commandTracingEnabled=true"
			//        "&transport.tcpTracingEnabled=true"
			//        "&wireFormat.tightEncodingEnabled=true"
			")";

    std::string destURI = "TVMONITOR.TUNER0.C";
    std::string origURI = "TVMONITOR.TUNER0.P";

    cout << "This is a message before the constructor." << endl;

	string str = "{ \"notification\" : { \"channel\" : 6, \"id\" : 1, \"label\""
			" : \"Alguma coisa aconteceu?\", \"options\" : [ { \"id\" : 1, \"label\" "
			": \"Sim\" }, { \"id\" : 2, \"label\" : \"Nao\" } ], \"type\" : \"multiply\" } }";

	Messenger* messenger = new Messenger(brokerURI, destURI, destURI);
	messenger->setMessengerListener( new SimpleListener() );
	messenger->connect();

	//sleep(1);
	std::cout << "Vamos enviar a mensagem: " << std::endl;
	messenger->sendMessage(str);
	std::cout << "Mensgem enviada!" << std::endl;
	sleep(1);

	messenger->disconnect();
	return 0;
}



