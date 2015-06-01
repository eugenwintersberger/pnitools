set(SOURCE data_provider.cpp
           data_provider_factory.cpp
           index_generator.cpp
           stdin_provider.cpp
           fio_provider.cpp
           )

add_library(mcaops_io OBJECT ${SOURCE})
