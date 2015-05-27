set(SOURCE operation.cpp
           operation_factory.cpp
           sum_operation.cpp
           dump_operation.cpp 
           )

add_library(mcaops_ops OBJECT ${SOURCE})
