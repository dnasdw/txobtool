#!/bin/sh

rootdir=`dirname $0`
cd $rootdir
rootdir=`pwd`
target=Linux_x86_64
libpng_version=`cat $rootdir/libpng.txt`
rm -rf "$rootdir/$libpng_version"
mkdir "$rootdir/$libpng_version"
cp -rf "$rootdir/../$libpng_version/"* "$rootdir/$libpng_version"
cd "$rootdir/$libpng_version"
mkdir project
cd project
cmake -DBUILD64=ON -C "$rootdir/CMakeLists.txt" -DCMAKE_INSTALL_PREFIX="$rootdir/$target" -DZLIB_INCLUDE_DIR="$rootdir/../../include/$target" -DZLIB_LIBRARY="$rootdir/../../lib/$target/libz.a" ..
cmake -DBUILD64=ON -C "$rootdir/CMakeLists.txt" -DCMAKE_INSTALL_PREFIX="$rootdir/$target" -DZLIB_INCLUDE_DIR="$rootdir/../../include/$target" -DZLIB_LIBRARY="$rootdir/../../lib/$target/libz.a" ..
cmake --build . --target install --config Release --clean-first
rm -rf "$rootdir/$target/include/libpng16"
mkdir "$rootdir/../../include/$target"
cp -rf "$rootdir/$target/include/"* "$rootdir/../../include/$target"
mkdir "$rootdir/../../lib/$target"
cp -rf "$rootdir/$target/lib/"* "$rootdir/../../lib/$target"
cd $rootdir
rm -rf "$rootdir/$libpng_version"
