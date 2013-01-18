#include "command.hpp"

#include <pni/core/Types.hpp>
#include <pni/io/nx/NX.hpp>

using namespace pni::core;
using namespace pni::io::nx::h5;

class cmd_open : public command
{
    private:
        String _file_name;
        String _current_group;
    public:
        virtual void setup(const std::vector<String> &cargs);
        virtual void execute(std::unique_ptr<environment> &env);
        virtual void help() const {}
};
