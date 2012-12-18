#include <iostream>

#include <pni/utils/Types.hpp>
#include <pni/nx/NX.hpp>

#include "interpreter.hpp"

using namespace pni::utils;
using namespace pni::nx::h5;


int main(int argc,char **argv)
{

    interpreter interp;
    interp.run();

    return 0;
}

