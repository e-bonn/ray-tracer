#!/bin/bash

# make any libs
cd ../..
premake4 gmake
make

# make source code
cd src 
premake4 gmake
make

if [ $# -eq 1 ] 
then 
    cd Assets
    ../RayTracer $1".lua"
    eog $1".png" &
fi