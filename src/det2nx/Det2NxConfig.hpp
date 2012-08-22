/*
 * Det2NxConfig.hpp
 *
 *  Created on: Sep 26, 2011
 *      Author: eugen
 */

#ifndef DET2NXCONFIG_HPP_
#define DET2NXCONFIG_HPP_

#include <pni/utils/PNITypes.hpp>

#include "../common/ProgramConfig.hpp"
#include "../common/Exceptions.hpp"

using namespace pni::utils;

class Det2NxConfig:public ProgramConfig {
public:
	Det2NxConfig();
	virtual ~Det2NxConfig();

	virtual String getEntryName() const;
	virtual String getInstrumentName() const;
	virtual String getDetectorName() const;
	virtual String getCompression() const;
	virtual String getOutputFile() const;
	virtual bool getOverwrite() const;
	virtual bool getAppend() const;
	virtual bool getReplace() const;
	virtual UInt64 getSplitSize() const;
};

#endif /* DET2NXCONFIG_HPP_ */
