set(SOURCE operation.cpp
           operation_factory.cpp
           sum.cpp
           dump.cpp 
           max.cpp
           )

add_library(mcaops_ops OBJECT ${SOURCE})
