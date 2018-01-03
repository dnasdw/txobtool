# txobtool

A tool for exporting/importing cgfx file.

## History

- v1.1.0 @ 2018.01.03 - A new beginning

### v1.0

- v1.0.0 @ 2015.03.11 - First release
- v1.0.1 @ 2017.02.22 - Fix offset
- v1.0.2 @ 2017.03.25 - Refactoring
- v1.0.3 @ 2017.04.02 - Refactoring
- v1.0.4 @ 2017.04.04 - Commandline support unicode

## Platforms

- Windows
- Linux
- macOS

## Building

### Dependencies

- cmake
- zlib
- libpng

### Compiling

- make 64-bit version
~~~
mkdir project
cd project
cmake -DUSE_DEP=OFF ..
make
~~~

- make 32-bit version
~~~
mkdir project
cd project
cmake -DBUILD64=OFF -DUSE_DEP=OFF ..
make
~~~

### Installing

~~~
make install
~~~

## Usage

### Windows

~~~
txobtool [option...] [option]...
~~~

### Other

~~~
txobtool.sh [option...] [option]...
~~~

## Options

See `txobtool --help` messages.
