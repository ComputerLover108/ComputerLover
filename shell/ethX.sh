#!/bin/sh
ifup ethX1 ethX2 ethX3 ethX4 &&
ifconfig ethX1 192.168.0.123 netmask 255.255.255.0
ifconfig ethX2 192.168.0.124 netmask 255.255.255.0
ifconfig ethX3 192.168.0.125 netmask 255.255.255.0
ifconfig ethX4 192.168.0.126 netmask 255.255.255.0
#
brctl addbr br0
brctl addif br0 eth2
ifconfig br0 192.168.0.130 up
#OpenBSD
brctl addbr br1
brctl addif br1 ethX1
ifconfig br1 192.168.0.131 up
#NetBSD
brctl addbr br2
brctl addif br2 ethX2
ifconfig br2 192.168.0.132 up
#FreeBSD
brctl addbr br3
brctl addif br3 ethX3
ifconfig br3 192.168.0.133 up
#DragonflyBSD
brctl addbr br4
brctl addif br4 ethX4
ifconfig br4 192.168.0.134 up
