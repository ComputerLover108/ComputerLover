#!/bin/sh
#apt-get -y install build-essential
#apt-get -y install libz-dev
#apt-get -y install libreadline-dev
#apt-get -y install libncursesw5-dev
#apt-get -y install libssl-dev
#apt-get -y install libgdbm-dev
#apt-get -y install libsqlite3-dev
#apt-get -y install libbz2-dev
#apt-get -y install liblzma-dev
#apt-get -y install tk-dev
#apt-get -y install libdb-dev
#apt-get -y install libc6-dev
#apt-get -y install zlib
VERSION=$1
JOBS=$2
if [ ! $JOBS ]; then
	JOBS=`cat /proc/cpuinfo | grep processor | wc -l`
fi
cd /tmp
wget -c https://www.python.org/ftp/python/$VERSION/Python-$VERSION.tar.xz
tar xfJ Python-$VERSION.tar.xz
cd Python-$VERSION
VERSION=${VERSION%.*}
CC=clang ./configure  --enable-loadable-sqlite-extensions --enable-optimizations --disable-shared --prefix=/opt/python$VERSION >>/tmp/buildPython.log 2>&1 
make -j $JOBS >>/tmp/buildPython.log 2>&1 
make -j $JOBS test >>/tmp/buildPython.log 2>&1 
make -j $JOBS install >>/tmp/buildPython.log 2>&1 
