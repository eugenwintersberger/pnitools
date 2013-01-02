/*
 * (c) Copyright 2012 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of pnitools.
 *
 * pnitools is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * pnitools is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with pnitools.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 * Created on: Sep 27, 2011
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#pragma once

#include <pni/utils/PNITypes.hpp>
#include <pni/utils/ArrayObject.hpp>

#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;
using namespace pni::utils;

class DetectorReader 
{
    private:
        ArrayObject::sptr _data;
        fs::path _input_file;

        void _ext_to_lower(String &e);
    public:
        DetectorReader();
        DetectorReader(const DetectorReader &r);
        virtual ~DetectorReader();

        virtual void setInputFile(const fs::path &ifile);
        void operator()();
        ArrayObject::sptr getData(){
            return _data;
        }
};

