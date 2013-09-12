/*
 * (c) Copyright 2013 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
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
 *
 *  Created on: Sep 12, 2013
 *      Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */

#include <boost/current_function.hpp>
#include<cppunit/extensions/HelperMacros.h>

#include <vector>
#include <list>

#include "column_test.hpp"

typedef std::vector<scalar<double> > vector_scalar_cell_t;
typedef std::vector<darray<double> > vector_array_cell_t;

typedef std::list<scalar<double> > list_scalar_cell_t;
typedef std::list<darray<double> > list_array_cell_t;

CPPUNIT_TEST_SUITE_REGISTRATION(column_test<vector_scalar_cell_t>);
//CPPUNIT_TEST_SUITE_REGISTRATION(column_test<vector_array_cell_t>);
//CPPUNIT_TEST_SUITE_REGISTRATION(column_test<list_scalar_cell_t>);
//CPPUNIT_TEST_SUITE_REGISTRATION(column_test<list_array_cell_t>);

