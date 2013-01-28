#include "command.hpp"

#include <pni/core/types.hpp>
#include <pni/io/nx/nx.hpp>

using namespace pni::core;
using namespace pni::io::nx::h5;

class cmd_open : public command
{
    private:
        string _file_name;
        string _current_group;
    public:
        virtual void setup(const std::vector<string> &cargs);
        virtual void execute(std::unique_ptr<environment> &env);
        virtual void help() const {}
};
