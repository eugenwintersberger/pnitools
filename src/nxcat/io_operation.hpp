#pragma once

class io_operation
{
    private:
    public:
        virtual void operator()();
};

template<typename TTYPE> class read_operation:public io_operation
{
    private:
    public:
        virtual void operator()()
        {

        }
};
