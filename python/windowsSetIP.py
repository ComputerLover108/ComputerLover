'''
Win32_NetworkAdapterConfiguration类: https://docs.microsoft.com/zh-cn/windows/desktop/CIMWin32Prov/win32-networkadapterconfiguration#properties
'''
 
import wmi
 
objNicConfig = None
arrIPAddresses =['192.168.70.120', '192.168.1.56'] # IP地址列表
arrSubnetMasks =['255.255.255.0', '255.255.255.0'] # 子网掩码列表
arrDefaultGateways =['192.168.70.253'] # 默认网关列表
arrGatewayCostMetrics =[1] #默认网关跳跃点
arrDNSServers =['192.168.70.15', '61.134.1.4'] #DNS服务器列表
intReboot = 0
 
 
def GetNicConfig():
    wmiService = wmi.WMI()
    colNicConfigs = wmiService.Win32_NetworkAdapterConfiguration(IPEnabled=True)
    # 根据需要过滤出指定网卡，本只有一个网卡，不做过滤直接获取第一个
    '''
    for obj in colNicConfigs:
        print(obj.Index)
        print(obj.Description)
        print(obj.SettingID)
    '''
    if len(colNicConfigs) < 1:
        print('没有找到可用的网络适配器')
        return False
    else:
        global objNicConfig
        objNicConfig = colNicConfigs[0]
        return True
 
def SetIP():
    returnValue = objNicConfig.EnableStatic(IPAddress = arrIPAddresses, SubnetMask = arrSubnetMasks)
    if returnValue[0]==0:
        print('设置IP成功')
    elif returnValue[0]==1:
        print('设置IP成功')
        intReboot += 1
    else:
        print('ERROR: IP设置发生错误')
        return False
    return True
 
def SetGateways():
    returnValue = objNicConfig.SetGateways(DefaultIPGateway = arrDefaultGateways, GatewayCostMetric = arrGatewayCostMetrics)
    if returnValue[0]==0:
        print('设置网关成功')
    elif returnValue[0]==1:
        print('设置网关成功')
        intReboot += 1
    else:
        print('ERROR: 网关设置发生错误')
        return False
    return True
 
def SetDNS():
    returnValue = objNicConfig.SetDNSServerSearchOrder(DNSServerSearchOrder = arrDNSServers)
    if returnValue[0]==0:
        print('设置DNS成功')
    elif returnValue[0]==1:
        print('设置DNS成功')
        intReboot += 1
    else:
        print('ERROR: DNS设置发生错误')
        return False
    return True
 
def SetAutoDNS():
    returnValue = objNicConfig.SetDNSServerSearchOrder()
    if returnValue[0]==0:
        print('设置自动获取DNS成功')
    elif returnValue[0]==1:
        print('设置自动获取DNS成功')
        intReboot += 1
    else:
        print('ERROR: DNS设置发生错误')
        return False
    return True
 
def SetAutoIP():
    returnValue = objNicConfig.EnableDHCP()
    if returnValue[0]==0:
        print('设置自动获取IP成功')
    elif returnValue[0]==1:
        print('设置自动获取IP成功')
        intReboot += 1
    else:
        print('ERROR: IP设置发生错误')
        return False
    return True
 
 
# 切换为静态IP
def EnableStatic():
    return SetIP() and SetGateways() and SetDNS()
 
# 切换为自动获取IP、DNS
def EnableDHCP():
    return SetAutoDNS() and SetAutoIP()
    
 
def main():
    if not GetNicConfig():
        return False
    
    if objNicConfig.DHCPEnabled:
        print('正在切换为静态IP...')
        if EnableStatic():
            if intReboot > 0:
                print('需要重新启动计算机')
            else:
                print('修改后的配置为：')
                print('IP: ',', '.join(objNicConfig.IPAddress))
                print('掩码: ',', '.join(objNicConfig.IPSubnet))
                print('网关: ',', '.join(objNicConfig.DefaultIPGateway))
                print('DNS: ',', '.join(objNicConfig.DNSServerSearchOrder))
                print('修改IP结束')
        else:
            print('请关闭控制面板、以管理员权限运行重试')
    else:
        print('正在切换为动态IP...')
        if EnableDHCP():
            if intReboot > 0:
                print('需要重新启动计算机')
            else:
                print('切换为动态DHCP成功!')
        else:
            print('请关闭控制面板、以管理员权限运行重试')
 
if __name__ == "__main__":
    main()
