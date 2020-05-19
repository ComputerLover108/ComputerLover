#!/bin/sh
VERSION=$1
JOBS=$2
if [ ! $JOBS ]; then
	JOBS=`cat /proc/cpuinfo | grep processor | wc -l`
fi
wget -c ftp://gcc.gnu.org/pub/gcc/releases/gcc-$VERSION/gcc-$VERSION.tar.gz &&
tar xfz gcc-$VERSION.tar.gz &&
cd gcc-$VERSION &&
./contrib/download_prerequisites &&
VERSION=${VERSION%.*} && 
#CC=clang ./configure --disable-multilib --prefix=/opt/gcc6.3 &&
CC=clang ./configure --prefix=/opt/gcc$VERSION --enable-checking=release --enable-languages=c,c++ --disable-multilib --disable-bootstrap 1>../gccBuild.log 2>../gccBuildError.log &&
make -s -j $JOBS 1>>../gccBuild.log 2>>../gccBuildError.log &&
make -s -j $JOBS install  1>>../gccBuild.log 2>>../gccBuildError.log 
