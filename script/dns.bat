netsh interface 192.168.16.211 set dns name="无线局域网适配器 WLAN" source=static addr=8.8.8.8
netsh interface ip add dns \"本地连接\" addr=8.8.8.8
netsh interface ip add dns \"本地连接\" addr=202.96.69.38
