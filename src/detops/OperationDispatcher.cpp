/*
 * OperationDispatcher.cpp
 *
 *  Created on: Jun 9, 2011
 *      Author: eugen
 */

#include <pni/utils/Array.hpp>

#include "OperationDispatcher.hpp"

OperationDispatcher::OperationDispatcher() {
	//assemble the maps for the array operations
	_omap["sum"] = _TypeOperatorMap();
	//summation
	_omap["sum"][INT32] = (Operation *)(new SumOperation<Int32Array>());
	_omap["sum"][INT8]  = (Operation *)(new SumOperation<Int8Array>());
	_omap["sum"][INT16] = (Operation *)(new SumOperation<Int16Array>());
	_omap["sum"][UINT8] = (Operation *)(new SumOperation<UInt8Array>());
	_omap["sum"][UINT16]= (Operation *)(new SumOperation<UInt16Array>());
	_omap["sum"][UINT32]= (Operation *)(new SumOperation<UInt32Array>());

	//average
	_omap["av"] = _TypeOperatorMap();
	_omap["av"][INT32] = (Operation *)(new AverageOperation<Int32Array>());
	_omap["av"][INT8]  = (Operation *)(new AverageOperation<Int8Array>());
	_omap["av"][INT16] = (Operation *)(new AverageOperation<Int16Array>());
	_omap["av"][UINT8] = (Operation *)(new AverageOperation<UInt8Array>());
	_omap["av"][UINT16]= (Operation *)(new AverageOperation<UInt16Array>());
	_omap["av"][UINT32]= (Operation *)(new AverageOperation<UInt32Array>());

	//minimum operation
	_omap["min"] = _TypeOperatorMap();
	_omap["min"][INT32] = (Operation *)(new MinOperation<Int32Array>());
	_omap["min"][INT8]  = (Operation *)(new MinOperation<Int8Array>());
	_omap["min"][INT16] = (Operation *)(new MinOperation<Int16Array>());
	_omap["min"][UINT8] = (Operation *)(new MinOperation<UInt8Array>());
	_omap["min"][UINT16]= (Operation *)(new MinOperation<UInt16Array>());
	_omap["min"][UINT32]= (Operation *)(new MinOperation<UInt32Array>());

	//maximum operation
	_omap["max"] = _TypeOperatorMap();
	_omap["max"][INT32] = (Operation *)(new MaxOperation<Int32Array>());
	_omap["max"][INT8]  = (Operation *)(new MaxOperation<Int8Array>());
	_omap["max"][INT16] = (Operation *)(new MaxOperation<Int16Array>());
	_omap["max"][UINT8] = (Operation *)(new MaxOperation<UInt8Array>());
	_omap["max"][UINT16]= (Operation *)(new MaxOperation<UInt16Array>());
	_omap["max"][UINT32]= (Operation *)(new MaxOperation<UInt32Array>());

}

OperationDispatcher::~OperationDispatcher() {
	//we need to free here all memory

	if(_omap["sum"][INT32] != NULL) delete _omap["sum"][INT32];
	if(_omap["sum"][INT8]  != NULL) delete _omap["sum"][INT8];
	if(_omap["sum"][INT16] != NULL) delete _omap["sum"][INT16];
	if(_omap["sum"][UINT8] != NULL) delete _omap["sum"][UINT8];
	if(_omap["sum"][UINT16]!= NULL) delete _omap["sum"][UINT16];
	if(_omap["sum"][UINT32]!= NULL) delete _omap["sum"][UINT32];

	if(_omap["av"][INT32] != NULL) delete _omap["av"][INT32];
	if(_omap["av"][INT8]  != NULL) delete _omap["av"][INT8];
	if(_omap["av"][INT16] != NULL) delete _omap["av"][INT16];
	if(_omap["av"][UINT8] != NULL) delete _omap["av"][UINT8];
	if(_omap["av"][UINT16]!= NULL) delete _omap["av"][UINT16];
	if(_omap["av"][UINT32]!= NULL) delete _omap["av"][UINT32];


	if(_omap["min"][INT32] != NULL) delete _omap["min"][INT32];
	if(_omap["min"][INT8]  != NULL) delete _omap["min"][INT8];
	if(_omap["min"][INT16] != NULL) delete _omap["min"][INT16];
	if(_omap["min"][UINT8] != NULL) delete _omap["min"][UINT8];
	if(_omap["min"][UINT16]!= NULL) delete _omap["min"][UINT16];
	if(_omap["min"][UINT32]!= NULL) delete _omap["min"][UINT32];

	if(_omap["max"][INT32] != NULL) delete _omap["max"][INT32];
	if(_omap["max"][INT8]  != NULL) delete _omap["max"][INT8];
	if(_omap["max"][INT16] != NULL) delete _omap["max"][INT16];
	if(_omap["max"][UINT8] != NULL) delete _omap["max"][UINT8];
	if(_omap["max"][UINT16]!= NULL) delete _omap["max"][UINT16];
	if(_omap["max"][UINT32]!= NULL) delete _omap["max"][UINT32];

}

