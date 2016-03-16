.. PNI Tools documentation master file, created by
   sphinx-quickstart on Mon Feb 15 11:51:27 2016.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Welcome to PNI Tools's documentation!
=====================================

Overview
--------

The **pnitools** distribution is a collection of programs (mainly for the
command line) which should make life at PNI beamlines easier. They are intended
to work with all kind of data files including Nexus files. Indeed providing
tools for dealing with Nexus files was the original motivation to start with
**pnitools** (see also the section below). **pnitools** is by far not the only
collection of programs available for this purpose. However, one of the design
goals of **pnitools** was to provide similar user interfaces and program
behavior for all programs making it easy for scientists to learn how to use
these tools. 

A few words on Nexus
--------------------

There are a lot of tools available on Unix terminals like :command:`grep`,
:command:`cat`, or :command:`awk` to manipulate and extract data from ASCII
files.  Nexus, as a binary data format cannot make use of these tools. The
**pnitools** distribution tries to fill this gap and provides command line
programs to interact with Nexus files in a similar way as the above tools do
with text files. In addition **pnitools** provides some more general purpose
programs for data analysis which already do or will support Nexus.
Currently, programs are available for 

* creating Nexus files from XML
* convert Nexus files to XML
* listing the content and extract data from Nexus files
* merging detector data stored in individual files into a Nexus file.

In future this list may become longer.

How to read
-----------

New users are strongly recommended to read @ref{Common
concepts} before anything else (including the rest of this chapter).
Understanding the concepts presented in @ref{Common concepts} is crucial to read
the documentation of the individual programs.

The rest of this chapter deals with building and installing of the
**pnitools**-distribution. It is thus for system administrators or experienced
users only who know how to build code on their systems. 

Users who have already experience with **pnitools** and want to use this manual
as a quick reference for a particular program can immediately
proceed to the appropriate section in the manual. However, as **pnitools**
evolves it is recommended to have a quick look through @ref{Common concepts}
from time to time to keep informed about new developments and possible changes.

Contents:

.. toctree::
   :maxdepth: 2
   
   installation
   general_concepts
   command_line_tools

.. toctree::
   :maxdepth: 2

   developer_documentation



Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`

