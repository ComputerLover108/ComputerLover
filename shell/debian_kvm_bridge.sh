#!/bin/sh
# modprobe dummy
# ip link add dummy0 type dummy
# ip link add link dummy0 macvlan0 type macvlan mode bridge
# ifconfig dummy0 up
# ifconfig macvlan0 192.168.1.2 broadcast 192.168.1.255 netmask 255.255.255.0 up