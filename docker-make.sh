#!/bin/bash

MOUNT_DIR=$PWD:/home/project
WORKING_DIR=/home/project

docker run -it  -v $MOUNT_DIR -w $WORKING_DIR simpletron_gcc make
