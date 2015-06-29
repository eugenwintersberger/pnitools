set(SOURCE operation.cpp
           operation_factory.cpp
           sum.cpp
           dump.cpp 
           max.cpp
           maxpos.cpp
           min.cpp
           minpos.cpp
           rebin.cpp
           output_config.cpp
           )

add_library(mcaops_ops_objects OBJECT ${SOURCE})
