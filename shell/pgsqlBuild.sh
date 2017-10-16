#1/bin/sh
# sudo apt-get install libreadline-dev zlib1g-dev libxslt-dev libxml2-dev libssl-dev libsystemd-dev
VERSION=10.0
SRCDIR=http://ftp.postgresql.org/pub/source/v$VERSION/postgresql-$VERSION.tar.bz2
SOURCE=postgresql-$VERSION.tar.bz2
cd /tmp &&
wget -c $SRCDIR/$SOURCE &&
tar xfj $SOURCE -C /tmp &&
cd  /tmp/postgresql-$VERSION &&
CC=/opt/clang5.0/bin/clang CFLAGS="-O2 -fstrict-enums -fno-signed-zeros"  ./configure --prefix=/opt/pgsql$VERSION --with-libxml --with-libxslt --with-openssl --with-systemd &&
make -j 8 world &&
make -j 8 install-world 