set(SOURCE functor.cpp 
           functor_factory.cpp
           linear.cpp
           gauss.cpp
           uniform.cpp
           executor.cpp
           )

add_library(datgen_functor_objects OBJECT ${SOURCE})
