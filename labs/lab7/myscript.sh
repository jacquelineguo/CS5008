#!/bin/bash
## This file is for git pull and copy specific file to own folder.

cd ~/resources
git pull
ls
echo "Which folder you want to copy?"
read to_copy
cd /jacquelineguo_CS5008
mkdir newCopy
cp -r ~/resources/$to_copy ~/jacquelineguo_CS5008/newCopy
cd ~/jacquelineguo_CS5008/newCopy
ls
