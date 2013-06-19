#!/bin/bash

REFPATH="$1:///:NXentry/:NXinstrument"
CNT="1"

while [ $CNT -lt 11 ]
do
    DATA="$REFPATH/channel_$CNT:NXdetector/data"
    POLAR="$REFPATH/channel_$CNT:NXdetector/polar_angle"
    nxcat $POLAR $DATA 
    CNT=$[$CNT+1]
done
