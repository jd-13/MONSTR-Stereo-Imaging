#!/bin/bash

set -e

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" > /dev/null 2>&1 && pwd )"

echo "=== Cloning WE-Core ==="
WECORE_HOME=$SCRIPT_DIR/../WECore
git clone --recurse-submodules https://github.com/jd-13/WE-Core $WECORE_HOME

cd $WECORE_HOME
echo "=== Using WE-Core $(git log --pretty=format:'%h' -n 1) ==="
cd -

echo "=== Downloading fonts ==="
wget https://github.com/JulietaUla/Montserrat/raw/master/fonts/ttf/Montserrat-Regular.ttf \
     -P $SCRIPT_DIR/../Source/Graphics

echo "=== Downloading JUCE ==="
JUCE_VERSION=7.0.5
wget https://github.com/juce-framework/JUCE/releases/download/$JUCE_VERSION/juce-$JUCE_VERSION-osx.zip \
     -P $SCRIPT_DIR/..
unzip $SCRIPT_DIR/../juce-$JUCE_VERSION-osx.zip

echo "=== Setting module paths ==="
sed -i '' -e 's#../../../../../SDKs/JUCE/modules#JUCE/modules#g' $SCRIPT_DIR/../MONSTR.jucer

echo "=== Updating include paths ==="
sed -i '' -e 's#../../../WECore/WECore#../../WECore/WECore#g' $SCRIPT_DIR/../MONSTR.jucer

echo "=== Setting DSPFilters path ==="
sed -i '' -e 's#../../../WECore/DSPFilters#../../WECore/DSPFilters#g' $SCRIPT_DIR/../MONSTR.jucer
sed -i '' -e 's#../WECore/DSPFilters/shared/DSPFilters/source#WECore/DSPFilters/shared/DSPFilters/source#g' $SCRIPT_DIR/../MONSTR.jucer

echo "=== Generating project ==="
$SCRIPT_DIR/../JUCE/Projucer.app/Contents/MacOS/Projucer --resave $SCRIPT_DIR/../MONSTR.jucer

echo "=== Starting build ==="
cd $SCRIPT_DIR/../Builds/MacOSX
xcodebuild -version
xcodebuild -project MONSTR.xcodeproj -scheme "MONSTR - All" -configuration Debug

echo "=== Collecting artefacts ==="
mkdir -p $SCRIPT_DIR/dist
cp -r ~/Library/Audio/Plug-Ins/VST3/MONSTR.vst3 $SCRIPT_DIR/dist
cp -r ~/Library/Audio/Plug-Ins/Components/MONSTR.component $SCRIPT_DIR/dist
