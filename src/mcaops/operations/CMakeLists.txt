set(SOURCE operation.cpp
           operation_factory.cpp
           sum.cpp
           dump.cpp 
           max.cpp
           maxpos.cpp
           min.cpp
           )

add_library(mcaops_ops OBJECT ${SOURCE})
