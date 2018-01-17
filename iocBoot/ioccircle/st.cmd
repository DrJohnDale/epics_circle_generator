#!../../bin/linux-x86_64/circle

#- You may have to change circle to something else
#- everywhere it appears in this file

#< envPaths

## Register all support components
dbLoadDatabase("../../dbd/circle.dbd",0,0)
circle_registerRecordDeviceDriver(pdbbase) 

## Load record instances
#dbLoadRecords("../../db/circle.db","user=dale")
dbLoadRecords("../../db/phaseGen.db","user=dale")

iocInit()

## Start any sequence programs
#seq snccircle,"user=dale"
