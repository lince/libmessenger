/**
 * File: IMessengerListener.h
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

#ifndef IMESSENGERLISTENER_H_
#define IMESSENGERLISTENER_H_

#include <string>

namespace messenger {

/**
 * This interface must be implemented by all the class that wishes to be notified when messages arrives.
 * A instance of IMessengerListener must be registered into Messenger instances for receive text messages.
 */
class IMessengerListener {

public:
	/**
	 * Virtual Destructor
	 */
	virtual ~IMessengerListener() {}

	/**
	 * This method is a callback that will be called when the IMessenger receive a text message.
	 * @param messageStr The text message received.
	 */
	virtual void receiveMessage( const std::string& messageStr ) = 0;
};

} /* namespace messenger */
#endif /* IMESSENGERLISTENER_H_ */
