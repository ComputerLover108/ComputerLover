#!/bin/sh
VERSION=7.1.0
wget -c ftp://gcc.gnu.org/pub/gcc/releases/gcc-$VERSION/gcc-$VERSION.tar.bz2 &&
wget -c ftp://gcc.gnu.org/pub/gcc/releases/gcc-$VERSION/md5.sum &&
tar xfj gcc-$VERSION.tar.bz2 &&
cd gcc-$VERSION &&
./contrib/download_prerequisites &&
#CC=clang ./configure --disable-multilib --prefix=/opt/gcc6.3 &&
CC=clang ./configure --prefix=/opt/gcc$VERSION --enable-checking=release --enable-languages=c,c++ --disable-multilib --disable-bootstrap >../gccBuild.log && 
make -s -j 16 >>../gccBuild.log 2>&1 
make -s -j 16 install >>../gccBuild.log 2>&1 
