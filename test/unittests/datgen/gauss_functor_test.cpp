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
#include <datgen/functors/gauss.hpp>

using namespace pni::core;

static float64 tolerance = 1.e-8;

BOOST_AUTO_TEST_SUITE(gauss_functor_test)

BOOST_AUTO_TEST_CASE(test_gauss)
{
    gauss f(0.3,1.0,2.0);

    BOOST_CHECK_CLOSE(f(0),0.0102818599753,tolerance);
    BOOST_CHECK_CLOSE(f(1),2.65961520268,tolerance);
    BOOST_CHECK_CLOSE(f(-1.),5.9406001249e-10,tolerance);
}


BOOST_AUTO_TEST_SUITE_END()


