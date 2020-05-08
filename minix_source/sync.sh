#!/bin/bash

cd "$(dirname "$0")" # set current working directory to the directory of the script

rsync -avz -e 'ssh -p 10022' --exclude=".git" ./usr/include/ root@localhost:/usr/include/
rsync -avz -e 'ssh -p 10022' --exclude=".git" ./usr/src/ root@localhost:/usr/src/
