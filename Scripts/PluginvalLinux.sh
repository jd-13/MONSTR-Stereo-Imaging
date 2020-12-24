#!/bin/bash

set -e

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" > /dev/null 2>&1 && pwd )"

# Exclude tests that don't work on Linux
cat << EOF >> $SCRIPT_DIR/disabled-tests.txt
Basic bus
EOF

$PLUGINVAL --validate $SCRIPT_DIR/../Builds/LinuxMakefile/build/MONSTR.vst3 \
           --strictness-level 10 \
           --skip-gui-tests \
           --disabled-tests $SCRIPT_DIR/disabled-tests.txt
