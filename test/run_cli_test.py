#!/usr/bin/env python

#this is the master script running all the CLI tests for pnitools

from unittest import main
from unittest import TestLoader
from unittest import TestSuite
from nxtee import nxtee_test
from detinfo import detinfo_test
from datgen import datgen_uniform_test
from datgen import datgen_global_test
#from det2nx_test  import det2nx_test
#from nxcat_test   import nxcat_test
#from nxls_test    import nxls_test
#from xml2nx_test  import xml2nx_test
#from mcaops_test  import mcaops_test

suite = TestSuite()
suite.addTest(TestLoader().loadTestsFromTestCase(nxtee_test))
suite.addTest(TestLoader().loadTestsFromTestCase(detinfo_test))
suite.addTest(TestLoader().loadTestsFromTestCase(datgen_global_test))
suite.addTest(TestLoader().loadTestsFromTestCase(datgen_uniform_test))
#suite.addTest(TestLoader().loadTestsFromTestCase(det2nx_test))
#suite.addTest(TestLoader().loadTestsFromTestCase(nxcat_test))
#suite.addTest(TestLoader().loadTestsFromTestCase(nxls_test))
#suite.addTest(TestLoader().loadTestsFromTestCase(xml2nx_test))
#suite.addTest(TestLoader().loadTestsFromTestCase(mcaops_test))

main()
