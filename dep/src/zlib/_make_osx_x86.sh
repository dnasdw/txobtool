#!/bin/sh

rootdir=`dirname $0`
cd $rootdir
rootdir=`pwd`
target=OSX_x86
zlib_version=`cat $rootdir/zlib.txt`
rm -rf "$rootdir/$zlib_version"
mkdir "$rootdir/$zlib_version"
cp -rf "$rootdir/../$zlib_version/"* "$rootdir/$zlib_version"
cd "$rootdir/$zlib_version"
mkdir project
cd project
cmake -DBUILD64=ON -C "$rootdir/CMakeLists.txt" -DCMAKE_INSTALL_PREFIX="$rootdir/../.." -DINSTALL_BIN_DIR="$rootdir/$zlib_version/bin" -DINSTALL_INC_DIR="$rootdir/../../include/$target" -DINSTALL_LIB_DIR="$rootdir/../../lib/$target" -DINSTALL_MAN_DIR="$rootdir/$zlib_version/share/man" -DINSTALL_PKGCONFIG_DIR="$rootdir/$zlib_version/share/pkgconfig" ..
cmake -DBUILD64=ON -C "$rootdir/CMakeLists.txt" -DCMAKE_INSTALL_PREFIX="$rootdir/../.." -DINSTALL_BIN_DIR="$rootdir/$zlib_version/bin" -DINSTALL_INC_DIR="$rootdir/../../include/$target" -DINSTALL_LIB_DIR="$rootdir/../../lib/$target" -DINSTALL_MAN_DIR="$rootdir/$zlib_version/share/man" -DINSTALL_PKGCONFIG_DIR="$rootdir/$zlib_version/share/pkgconfig" ..
cmake --build . --target install --config Release --clean-first
rm -rf "$rootdir/../../lib/$target/libz"*".dylib"
cd $rootdir
rm -rf "$rootdir/$zlib_version"
