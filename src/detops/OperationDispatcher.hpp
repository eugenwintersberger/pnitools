/*
 * OperationDispatcher.hpp
 *
 *  Created on: Jun 9, 2011
 *      Author: eugen
 */

#ifndef OPERATIONDISPATCHER_HPP_
#define OPERATIONDISPATCHER_HPP_

#include <map>
#include <string>

#include <pni/utils/PNITypes.hpp>

#include "Operation.hpp"
#include "Exceptions.hpp"
#include "SumOperation.hpp"
#include "MinOperation.hpp"
#include "MaxOperation.hpp"
#include "AverageOperation.hpp"

using namespace pni::utils;


class OperationDispatcher {
protected:
	typedef std::map<TypeID,Operation *> _TypeOperatorMap;
	typedef std::map<String,_TypeOperatorMap > _OperatorMap;
	_OperatorMap _omap;
	//class not copyable
	OperationDispatcher(const OperationDispatcher &){}
public:
	OperationDispatcher();
	virtual ~OperationDispatcher();


	//virtual void addOperation(pni::utils::String name,Operation *op);
	virtual Operation *getOperation(String name,TypeID tid){
		EXCEPTION_SETUP("Operation *OperationDispatcher::getOperation(String name,PNITypeID tid)");

		if(!_omap.count(name)){
			EXCEPTION_INIT(UnsupportedCommandError,"Command "+name+" not supported!");
			EXCEPTION_THROW();
		}

		if(!_omap[name].count(tid)){
			EXCEPTION_INIT(UnsupportedDataTypeError,"Data type not supported!");
			EXCEPTION_THROW();
		}
		return _omap[name][tid];
	}



};

#endif /* OPERATIONDISPATCHER_HPP_ */
