import requests,json,serial.tools.list_ports
response = requests.get(
    'https://voice.baidu.com/newpneumonia/get',
    data = json.dumps({
        'target': 'trend',
        'isCaseIn': '0',
        'stage': 'publish',
        'callback': 'jsonp_1601895127118_65535'
    })
)
data = response.json()['data'][6]['trend']['list']
a = data[0]['data'][-1]
b = data[1]['data'][-1]
c = data[2]['data'][-1]
plist = list(serial.tools.list_ports.comports())
if len(plist) <= 0:
        print("没有发现端口!")
else:
    
    plist_0 = list(plist[0])
    serialName = plist_0[0]
    serialFd = serial.Serial(serialName, 9600)
    print("可用端口名>>>", serialFd.name)
    serialFd.write(str(a-b-c).encode())

