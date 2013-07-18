#/bin/sh

TITLE="a test experiment"
#set some default program names
DETINFO=detinfo
DET2NX=det2nx
XML2NX=xml2nx

#read the basic template 
nxmain_template=$(cat basic.xml | sed 's/>/\\>/g' | sed 's/</\\</g')

final=$(eval echo  ${nxmain_template})
echo $final


