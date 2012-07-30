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

#ifndef IBROKERCONNECTION_H_
#define IBROKERCONNECTION_H_

namespace messenger {

class IBrokerConnection {
public:
	/**
	 * Virtual destructor
	 */
	virtual ~IBrokerConnection() {};

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
	 * This method disconnects the IMessenger from the broker.
	 * It should be called before closing the program.
	 */
	virtual bool isConnected() = 0;

};

}

#endif /* IBROKERCONNECTION_H_ */
