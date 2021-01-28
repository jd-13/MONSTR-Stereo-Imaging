#!/bin/bash

set -e

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" > /dev/null 2>&1 && pwd )"

echo "=== Cloning WE-Core ==="
WECORE_HOME=$SCRIPT_DIR/../WECore
git clone --recurse-submodules https://github.com/jd-13/WE-Core $SCRIPT_DIR/../WECore

cd $WECORE_HOME
echo "=== Using WE-Core $(git log --pretty=format:'%h' -n 1) ==="
cd -

echo "=== Downloading fonts ==="
wget https://github.com/JulietaUla/Montserrat/raw/master/fonts/ttf/Montserrat-Regular.ttf \
     -P $SCRIPT_DIR/../Source/Graphics

echo "=== Setting module paths ==="
sed -i 's#../JUCE/modules#/home/JUCE/modules#g' $SCRIPT_DIR/../MONSTR.jucer

echo "=== Setting DSPFilters path ==="
sed -i 's#../WECore/DSPFilters#WECore/DSPFilters#g' $SCRIPT_DIR/../MONSTR.jucer

echo "=== Generating makefile ==="
$JUCE_PATH/Projucer --resave $SCRIPT_DIR/../MONSTR.jucer

echo "=== Updating include paths ==="
sed -i 's#-I$(HOME)/WEA/WECore/WECore#-I../../WECore/WECore#g' $SCRIPT_DIR/../Builds/LinuxMakefile/Makefile

# TODO: this path gets set wrong, not sure why
sed -i 's#-I$(HOME)/WWECore/DSPFilters/shared/DSPFilters/include#-I../../WECore/DSPFilters/shared/DSPFilters/include#g' $SCRIPT_DIR/../Builds/LinuxMakefile/Makefile

echo "=== Starting build ==="
cd $SCRIPT_DIR/../Builds/LinuxMakefile
make
