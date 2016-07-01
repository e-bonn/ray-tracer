#!/bin/bash

# make any libs
cd ../..
premake4 gmake
make

# make source code
cd src 
premake4 gmake
make

cd Assets
../RayTracer $1".lua"

eog $1".png" &
