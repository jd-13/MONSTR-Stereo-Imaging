#!/bin/bash

set -e

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" > /dev/null 2>&1 && pwd )"

# Download WE-Core
WECORE_HOME="$(cd $SCRIPT_DIR/.. > /dev/null 2>&1 && pwd)"
WECORE_SRC="$WECORE_HOME/WECore"
git clone --recurse-submodules https://github.com/jd-13/WE-Core $SCRIPT_DIR/../WECore

# Set JUCE module paths
sed -i 's#../JUCE/modules#/home/JUCE/modules#g' $SCRIPT_DIR/../MONSTR.jucer

# Generate the makefile
$JUCE_PATH/Projucer --resave $SCRIPT_DIR/../MONSTR.jucer

# Update the include paths
sed -i 's#-I$(HOME)/WEA/WECore/WECore#-I../../WECore/WECore#g' $SCRIPT_DIR/../Builds/LinuxMakefile/Makefile
sed -i 's#-I$(HOME)/WEA/WECore/DSPFilters#-I../../WECore/DSPFilters#g' $SCRIPT_DIR/../Builds/LinuxMakefile/Makefile

# Run the build
cd $SCRIPT_DIR/../Builds/LinuxMakefile
make
