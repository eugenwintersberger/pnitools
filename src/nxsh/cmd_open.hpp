#include "command.hpp"

#include <pni/utils/Types.hpp>
#include <pni/nx/NX.hpp>

using namespace pni::utils;
using namespace pni::nx::h5;

class cmd_open : public command
{
    private:
        String _file_name;
        String _current_group;
    public:
        virtual void setup(const std::vector<String> &cargs);
        virtual void execute(std::unique_ptr<environment> &env);
};
