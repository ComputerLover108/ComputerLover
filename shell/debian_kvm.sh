#!/bin/sh
apt install qemu-kvm libvirt-clients libvirt-daemon-system virtinst virt-viewer
# adduser <youruser> libvirt
# adduser <youruser> libvirt-qemu

# Huge Page Memory support
# Huge Page Counts = Total VM Guest Memory In MB / 2
# 大内存支持，公式 大分页数=全部虚拟机内存/2
# 准备建四个虚拟机，每个内存为8G
echo 16384 > /proc/sys/vm/nr_hugepages
mkdir -p /mnt/hugetlbfs
mount -t hugetlbfs hugetlbfs /mnt/hugetlbfs
mkdir -p /mnt/hugetlbfs/libvirt/bin
systemctl restart libvirtd

# 安装OpenBSD
virt-install \
--virt-type kvm \
-n openbsd1 \
-r 8192 \
--vcpus=8 \
--accelerate \
--location https://fastly.cdn.openbsd.org/pub/OpenBSD/6.3/amd64/ \
-w bridge:br0 \
--disk path=/VirtualMachine/kvm/openbsd1.img,size=8