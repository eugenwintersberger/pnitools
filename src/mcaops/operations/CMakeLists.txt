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
           average.cpp
           scale.cpp
           )

       add_library(mcaops_ops STATIC  ${SOURCE})
