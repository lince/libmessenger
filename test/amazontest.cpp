/*
 * main.cpp
 *
 *  Created on: Aug 25, 2011
 *      Author: caioviel
 */

#include "../include/Messenger.h"
using namespace messenger;

#include <iostream>
using namespace std;

class SimpleListener : public MsgListener {

	virtual void receiveMsg( const string& messageStr ) {
		std::cout << messageStr << std::endl;
	}

};

int main(int argc, char* argv[]) {
    std::string brokerURI =
          "failover:(tcp://demoiselle.i-brasil.com:61616"
//        "?wireFormat=openwire"
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
	messenger->setMsgListener( new SimpleListener() );
	messenger->connect();

	//sleep(1);
	std::cout << "Vamos enviar a mensagem: " << std::endl;
	messenger->sendMessage(str);
	std::cout << "Mensgem enviada!" << std::endl;
	sleep(1);

	messenger->disconnect();
	activemq::library::ActiveMQCPP::shutdownLibrary();
	return 0;
}



