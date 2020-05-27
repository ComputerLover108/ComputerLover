docker pull primiano/docker-webvirtmgr
sudo groupadd -g 1010 webvirtmgr
sudo useradd -u 1010 -g webvirtmgr -s /sbin/nologin -d /data/vm webvirtmgr
sudo chown -R webvirtmgr:webvirtmgr /data/vm