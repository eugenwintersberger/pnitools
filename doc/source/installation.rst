
Installation
============

Build requirements
------------------

To build and install the **pnitools** distribution the following additional
software packages must be available

* a full installation of the  `pnicore`_ and `pniio`_ libraries
* :program:`pkg-config` for library configuration
* :program:`cmake` version 2.6 and higher
* :program:`pdftex` and  :program:`makeinfo` for building the user
  documentation
* :program:`doxygen` for developer documentation
* :program:`sphinx` to build all the documentation from RST files.

A working setup for :program:`pkg-config` is recommended as it would be
difficult to get the configuration for **pnicore** and **pniio** right. Both
libraries provide configuration files for :program:`pkg-config` with the
default installation. If the libraries cannot be found you may have to set the
:envvar:`PKG_CONFIG_PATH` environment variable according to the installation
directories of **pniio** and **pnicore**.

Building and installing pnitools
--------------------------------

You can obtain the **pnitools** code either directly from the `GIT repository`_. 
Stable releases are available as tarballs from the `releases site`_ on GitHub. 

I strongly recommend to use the code directly from the GIT repository. The
@emph{stable} branch always provides the latest release with all the bugfixes
and is guaranteed to build. To get the code from GIT use 

.. code-block:: bash

    $ git clone https://code.google.com/p/pnitools pnitools-code

As we use :program:`cmake` for building the distribution create an extra build
directory somewhere on your filesystem and run cmake there

.. code-block:: bash

    $ mkdir pnitools-build
    $ cd pnitools-build
    $ cmake /PATH/TO/pnitools-code

Once :program:`cmake` finished the configuration successfully simply run
:program:`make` and :program:`make install` form within the build directory

.. code-block:: bash

    $ make
    $ make install

By default :program:`make` the default installation prefix is :file:`/usr`. You
can change this during the configuration run by setting the
:envvar:`CMAKE_INSTALL_REPFIX` variable with 

.. code-block:: bash

    $ cmake -DCMAKE_INSTALL_PREFIX=/opt/pnitools /PATH/TO/pnitools-code

During :program:`make install` files will be copied to the following directories

+-------------------------------------------------+---------------------------+
| Directory                                       | files                     |
+=================================================+===========================+
|:file:`CMAKE_INSTALL_PREFIX/bin`                 | all the program binaries  |
+-------------------------------------------------+---------------------------+
|:file:`CMAKE_INSTALL_PREFIX/share/man`           | manpages for the programs |
|                                                 | (you may need to add this |
|                                                 | to your :envvar:`MANPATH` |
|                                                 | environment variable)     |
+-------------------------------------------------+---------------------------+
|:file:`CMAKE_INSTALL_PREFIX/share/info`          | info pages                |
+-------------------------------------------------+---------------------------+
| :file:`CMAKE_INSTALL_PREFIX/share/pnitools-doc` | all the other             |
|                                                 | documentation including   |
|                                                 | the pdf documents         |
+-------------------------------------------------+---------------------------+


.. _GIT repository: https://github.com/eugenwintersberger/pnitools
.. _releases site: https://github.com/eugenwintersberger/pnitools/releases
.. _pnicore: https://github.com/pni-libraries/libpnicore 
.. _pniio: https://github.com/pni-libraries/libpniio
