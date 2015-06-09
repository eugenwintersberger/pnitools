//
// (c) Copyright 2015 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
//
// This file is part of pnitools.
//
// pnitools is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// pnitools is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with pnitools.  If not, see <http://www.gnu.org/licenses/>.
//************************************************************************
//
//  Created on: Jun 9, 2015
//      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
//

#include <boost/test/unit_test.hpp>
#include <datgen/options_splitter.hpp>

static args_vector keywords = {"uniform","gauss","linear"};

struct fixture
{
    options_splitter splitter;
    
    fixture():
        splitter(keywords)
    {
        
    }
};


BOOST_FIXTURE_TEST_SUITE(options_splitter_test,fixture)

//----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_only_global)
{
    args_vector args{"-f","-ohello.dat","-x"};
    args_map m = splitter(args);

    BOOST_CHECK_EQUAL(m.size(),1);
    BOOST_CHECK_EQUAL(m.find("global")->second.size(),3);

}

//----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_no_args)
{
    args_vector args;
    args_map m = splitter(args);
    BOOST_CHECK_EQUAL(m.size(),0);
}

//----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_different_keys)
{
    args_vector args{"-f","-x","linear","-s12","-o3","uniform","-l-1."};
    args_map m = splitter(args);
    BOOST_CHECK_EQUAL(m.size(),3);
    BOOST_CHECK_EQUAL(m.find("global")->second.size(),2);
    BOOST_CHECK_EQUAL(m.find("linear")->second.size(),2);
    BOOST_CHECK_EQUAL(m.find("uniform")->second.size(),1);
}

//----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_no_global)
{
    args_vector args{"linear","-s12","-o3","uniform","-l-1."};
    args_map m = splitter(args);
    BOOST_CHECK_EQUAL(m.size(),3);
    BOOST_CHECK_EQUAL(m.find("global")->second.size(),0);
    BOOST_CHECK_EQUAL(m.find("linear")->second.size(),2);
    BOOST_CHECK_EQUAL(m.find("uniform")->second.size(),1);
}

//----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_multiple_equal_keys)
{
    args_vector args{"-f","-x","linear","-s12","-o3","linear","-s34.12"};
    args_map m = splitter(args);
    BOOST_CHECK_EQUAL(m.size(),3);

    auto iter = m.find("linear");
    BOOST_CHECK_EQUAL(iter->second.size(),2);
    ++iter;
    BOOST_CHECK_EQUAL(iter->second.size(),1);
    ++iter;
    BOOST_CHECK(iter==m.end());

}


BOOST_AUTO_TEST_SUITE_END()
