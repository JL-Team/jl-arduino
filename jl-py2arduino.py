import requests,json,serial.tools.list_ports
from datetime import*
import time
import bs4
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

def Date(t):
    y = t.year
    m = t.month
    d = t.day
    second = t.second + t.microsecond * 0.000001
    minute = t.minute + second / 60.0
    hour = t.hour + minute / 60.0
    return "%s"%y+"年"+"%d"%m+"月"+"%d"%d+"日"+"%d"%hour+"时"+"%d"%minute+"分"+"%d"%second+"秒"
t = datetime.today()


o = {
    'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8',
    'Accept-Encoding': 'gzip, deflate, sdch',
    'Accept-Language': 'zh-CN,zh;q=0.8',
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/53.0.2785.104 Safari/537.36 Core/1.53.3226.400 QQBrowser/9.6.11681.400'
}
dongguan = requests.get('http://www.weather.com.cn/weather/101281601.shtml', headers=o, timeout=80) 
dongguan.encoding = 'utf-8'
dongguan1 = bs4.BeautifulSoup(dongguan.text,'html.parser')
tianqi = dongguan1.find('ul', 't clearfix')
jintian = tianqi.find('li')


print(jintian.find('p', 'wea').string)
print(str(a-b-c))
print(str(Date(t)))

if len(plist) <= 0:
        print("没有发现端口!")
else:
    plist_0 = list(plist[0])
    serialName = plist_0[0]
    serialFd = serial.Serial(serialName, 9600)
    print("可用端口名>>>", serialFd.name)
    serialFd.write(str(a-b-c).encode())
    time.sleep(0.1)
    serialFd.write(str(Date(t)).encode())

