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

#ifndef IMESSENGER_H_
#define IMESSENGER_H_

#include <string>

#include <libcpputil/InitializationException.h>
#include <libcpputil/IllegalParameterException.h>
#include "IMessengerListener.h"

namespace messenger {

/**
 * This interface is used for gain access to the Messenger services.
 * Using this interface you can send to and receive from texts messages to the broker.
 */
class IMessenger {

public:
	/**
	 * Virtual destructor
	 */
	~IMessenger() {};

	/**
	 * This method connects the current instance to the broker.
	 * Call this method is a necessary condition to gain access to
	 * all the services provide by Messenger.
	 * @throw InitializationException if the IMessengerListener isn't setted or some error occur.
	 */
	virtual void connect() = 0;

	/**
	 * This method disconnects the IMessnger from the broker.
	 * It should be called before closing the program.
	 */
	virtual void disconnect() = 0;

	/**
	 * This method is used to send message to the broker
	 * @param text the message to be sended
	 * @throw IllegalParameterException When errors occurs sending messages.
	 */
	virtual void sendMessage(const std::string& text) = 0;

	/**
	 * Allows set the instance of IMessengerListener that will be notified when the Messenger receive a message
	 * from the broker.
	 * @param msgListener The instance to be notified.
	 */
	virtual void setMessengerListener(IMessengerListener* msgListener) = 0;

};

}

#endif /* IMESSENGER_H_ */
