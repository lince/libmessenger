#ifndef IMESSENGER_H_
#define IMESSENGER_H_

#include "IMessengerListener.h"

namespace messenger {

class IMessenger {

public:
	~IMessenger() {};

	virtual void connect() = 0;

	virtual void disconnect() = 0;

	virtual void sendMessage(const std::string& text) = 0;

	virtual void setMessengerListener(IMessengerListener* msgListener) = 0;

};

}

#endif /* IMESSENGER_H_ */
