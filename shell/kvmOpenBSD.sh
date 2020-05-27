#!/bin/sh
# -n --name= 客户端虚拟机名称
# -r --ram= 客户端虚拟机分配的内存
# -u --uuid= 客户端UUID 默认不写时，系统会自动生成
# --vcpus= 客户端的vcpu个数
# -v --hvm 全虚拟化
# -p --paravirt 半虚拟化
# -l --location=localdir 安装源，有本地、nfs、http、ftp几种，多用于ks网络安装
# --vnc 使用vnc ，另有--vnclient＝监听的IP  --vncport ＝VNC监听的端口
# -c --cdrom= 光驱 安装途径
# --disk= 使用不同选项作为磁盘使用安装介质
# -w NETWORK, --network=NETWORK 连接客户机到主机网络 
# -s --file-size= 使用磁盘映像的大小 单位为GB
# -f --file= 作为磁盘映像使用的文件
# --cpuset=设置哪个物理CPU能够被虚拟机使用
# --os-type=OS_TYPE 针对一类操作系统优化虚拟机配置（例如：‘linux’，‘windows’）
# --os-variant=OS_VARIANT 针对特定操作系统变体（例如’rhel6’, ’winxp’,'win2k3'）进一步优化虚拟机配置
# --host-device=HOSTDEV 附加一个物理主机设备到客户机。HOSTDEV是随着libvirt使用的一个节点设备名（具体设备如’virsh nodedev-list’的显示的结果）
# --accelerate KVM或KQEMU内核加速,这个选项是推荐最好加上。如果KVM和KQEMU都支持，KVM加速器优先使用。
# -x EXTRA, --extra-args=EXTRA 当执行从"--location"选项指定位置的客户机安装时，附加内核命令行参数到安装程序
# --nographics "virt-install" 将默认使用--vnc选项，使用nographics指定没有控制台被分配给客户机

virt-install \
--name=myOpenBSD \
--ram=4096 \
--vcpus=4 \
--location=http://ftp.jaist.ac.jp/pub/OpenBSD/6.1/amd64/ \
--file=OpenBSD.img \
--file-size=4 \
--network=bridge:br0