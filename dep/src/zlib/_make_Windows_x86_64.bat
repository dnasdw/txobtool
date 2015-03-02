IF DEFINED VS120COMNTOOLS (
  SET GENERATOR="Visual Studio 12 Win64"
) ELSE IF DEFINED VS110COMNTOOLS (
  SET GENERATOR="Visual Studio 11 Win64"
) ELSE IF DEFINED VS100COMNTOOLS (
  SET GENERATOR="Visual Studio 10 Win64"
)
IF NOT DEFINED GENERATOR (
  ECHO Can not find VC2010 or VC2012 or VC2013 installed!
  GOTO ERROR
)
SET rootdir=%~dp0
SET target=Windows_x86_64
SET /P zlib_version=<"%rootdir%zlib.txt"
RD /S /Q "%rootdir%%zlib_version%"
MD "%rootdir%%zlib_version%"
XCOPY "%rootdir%..\%zlib_version%" "%rootdir%%zlib_version%" /S /Y
CD /D "%rootdir%%zlib_version%"
MD project
CD project
cmake -C "%rootdir%CMakeLists.txt" -DCMAKE_INSTALL_PREFIX="%rootdir%..\.." -DINSTALL_BIN_DIR="%rootdir%%zlib_version%\bin" -DINSTALL_INC_DIR="%rootdir%..\..\include\%target%" -DINSTALL_LIB_DIR="%rootdir%..\..\lib\%target%" -DINSTALL_MAN_DIR="%rootdir%%zlib_version%\share\man" -DINSTALL_PKGCONFIG_DIR="%rootdir%%zlib_version%\share\pkgconfig" -G %GENERATOR% ..
cmake -C "%rootdir%CMakeLists.txt" -DCMAKE_INSTALL_PREFIX="%rootdir%..\.." -DINSTALL_BIN_DIR="%rootdir%%zlib_version%\bin" -DINSTALL_INC_DIR="%rootdir%..\..\include\%target%" -DINSTALL_LIB_DIR="%rootdir%..\..\lib\%target%" -DINSTALL_MAN_DIR="%rootdir%%zlib_version%\share\man" -DINSTALL_PKGCONFIG_DIR="%rootdir%%zlib_version%\share\pkgconfig" -G %GENERATOR% ..
cmake --build . --target install --config Release --clean-first
DEL "%rootdir%..\..\lib\%target%\zlib.lib"
CD /D "%rootdir%"
RD /S /Q "%rootdir%%zlib_version%"
GOTO EOF

:ERROR
PAUSE

:EOF
