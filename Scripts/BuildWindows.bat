set SCRIPT_DIR=%~dp0

ECHO "=== Cloning WE-Core ==="
set WECORE_HOME=%SCRIPT_DIR%..\WECore
git clone --recurse-submodules https://github.com/jd-13/WE-Core %WECORE_HOME%

pushd
cd %WECORE_HOME%
for /f %%i in ('git log --pretty^=format:'%%h' -n 1') do set WECORE_COMMIT=%%i
ECHO "=== Using WE-Core %WECORE_COMMIT% ==="
popd

ECHO "=== Downloading fonts ==="
powershell -Command "& {[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12; Invoke-WebRequest https://github.com/JulietaUla/Montserrat/raw/master/fonts/ttf/Montserrat-Regular.ttf -OutFile %SCRIPT_DIR%..\Source\Graphics\Montserrat-Regular.ttf}"

ECHO "=== Downloading JUCE ==="
set JUCE_VERSION=7.0.9
powershell -Command "& {[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12; Invoke-WebRequest https://github.com/juce-framework/JUCE/releases/download/%JUCE_VERSION%/juce-%JUCE_VERSION%-windows.zip -OutFile %SCRIPT_DIR%..\juce-%JUCE_VERSION%-windows.zip}"
powershell -Command "& {Expand-Archive -LiteralPath %SCRIPT_DIR%..\juce-%JUCE_VERSION%-windows.zip -DestinationPath %SCRIPT_DIR%..}"

ECHO "=== Setting module paths ==="
powershell -Command "& {$PSDefaultParameterValues['Out-File:Encoding'] = 'utf8'; (get-content %SCRIPT_DIR%..\MONSTR.jucer).replace(\"..\JUCE\modules\",\"JUCE\modules\") | out-file -filepath %SCRIPT_DIR%..\MONSTR.jucer}"

ECHO "=== Updating include paths ==="
powershell -Command "& {$PSDefaultParameterValues['Out-File:Encoding'] = 'utf8'; (get-content %SCRIPT_DIR%..\MONSTR.jucer).replace(\"%%USERPROFILE%%\WEA\WECore\WECore\",\"..\..\WECore\WECore\") | out-file -filepath %SCRIPT_DIR%..\MONSTR.jucer}"

ECHO "=== Generating project ==="
%SCRIPT_DIR%..\JUCE\Projucer --resave %SCRIPT_DIR%..\MONSTR.jucer

ECHO "=== Starting build ==="
cd %SCRIPT_DIR%..\Builds\VisualStudio2019
msbuild -version
msbuild MONSTR.sln /p:Configuration=Debug /p:Platform=x64
