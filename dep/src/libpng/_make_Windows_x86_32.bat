IF DEFINED VS120COMNTOOLS (
  SET GENERATOR="Visual Studio 12"
) ELSE IF DEFINED VS110COMNTOOLS (
  SET GENERATOR="Visual Studio 11"
) ELSE IF DEFINED VS100COMNTOOLS (
  SET GENERATOR="Visual Studio 10"
)
IF NOT DEFINED GENERATOR (
  ECHO Can not find VC2010 or VC2012 or VC2013 installed!
  GOTO ERROR
)
SET rootdir=%~dp0
SET target=Windows_x86_32
SET /P libpng_version=<"%rootdir%libpng.txt"
RD /S /Q "%rootdir%%libpng_version%"
MD "%rootdir%%libpng_version%"
XCOPY "%rootdir%..\%libpng_version%" "%rootdir%%libpng_version%" /S /Y
CD /D "%rootdir%%libpng_version%"
MD project
CD project
cmake -C "%rootdir%CMakeLists.txt" -DCMAKE_INSTALL_PREFIX="%rootdir%%target%" -DZLIB_INCLUDE_DIR="%rootdir%..\..\include\%target%" -DZLIB_LIBRARY="%rootdir%..\..\lib\%target%\zlibstatic.lib" -G %GENERATOR% ..
cmake -C "%rootdir%CMakeLists.txt" -DCMAKE_INSTALL_PREFIX="%rootdir%%target%" -DZLIB_INCLUDE_DIR="%rootdir%..\..\include\%target%" -DZLIB_LIBRARY="%rootdir%..\..\lib\%target%\zlibstatic.lib" -G %GENERATOR% ..
cmake --build . --target install --config Release --clean-first
RD /S /Q "%rootdir%%target%\include\libpng16"
MD "%rootdir%..\..\include\%target%"
XCOPY "%rootdir%%target%\include" "%rootdir%..\..\include\%target%" /S /Y
MD "%rootdir%..\..\lib\%target%"
COPY /Y "%rootdir%%target%\lib\*.lib" "%rootdir%..\..\lib\%target%"
CD /D "%rootdir%"
RD /S /Q "%rootdir%%libpng_version%"
GOTO EOF

:ERROR
PAUSE

:EOF
