#!/bin/bash

set -e

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" > /dev/null 2>&1 && pwd )"

# Download WE-Core
WECORE_HOME="$(cd $SCRIPT_DIR/.. > /dev/null 2>&1 && pwd)"
WECORE_SRC="$WECORE_HOME/WECore"
git clone --recurse-submodules https://github.com/jd-13/WE-Core $SCRIPT_DIR/../WECore

# Set JUCE module paths
sed -i 's#../JUCE/modules#/home/JUCE/modules#g' $SCRIPT_DIR/../MONSTR.jucer

# Set include paths
sed -i 's#../WECore/DSPFilters#WECore/DSPFilters#g' $SCRIPT_DIR/../MONSTR.jucer
sed -i 's#~/WEA/WECore#../../WECore#g' $SCRIPT_DIR/../MONSTR.jucer

# Generate the makefile
$JUCE_PATH/Projucer --resave $SCRIPT_DIR/../MONSTR.jucer

cat $SCRIPT_DIR/../Builds/LinuxMakefile/Makefile

# Run the build
cd $SCRIPT_DIR/../Builds/LinuxMakefile
make
