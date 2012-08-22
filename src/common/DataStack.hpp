/*
 * DataStack.hpp
 *
 *  Created on: Sep 27, 2011
 *      Author: eugen
 */

#ifndef DATASTACK_HPP_
#define DATASTACK_HPP_

class DataStack {
public:
	DataStack();
	virtual ~DataStack();

	void lock();
	bool try_lock();
	void unlock();
};

#endif /* DATASTACK_HPP_ */
