import requests,json,serial.tools.list_ports
from datetime import*
import time
import bs4
def JL_GR():
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
    return a-b-c

def Date():
    t = datetime.today()
    y = t.year
    m = t.month
    d = t.day
    second = t.second + t.microsecond * 0.000001
    minute = t.minute + second / 60.0
    hour = t.hour + minute / 60.0
    return "%s"%y+" "+"%d"%m+" "+"%d"%d+" "+"%d"%hour+" "+"%d"%minute+" "

o = {
    'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8',
    'Accept-Encoding': 'gzip, deflate, sdch',
    'Accept-Language': 'zh-CN,zh;q=0.8',
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/53.0.2785.104 Safari/537.36 Core/1.53.3226.400 QQBrowser/9.6.11681.400'
}
def Weather():
    dongguan = requests.get('http://www.weather.com.cn/weather/101281601.shtml', headers=o, timeout=80) 
    dongguan.encoding = 'utf-8'
    dongguan1 = bs4.BeautifulSoup(dongguan.text,'html.parser')
    tianqi = dongguan1.find('ul', 't clearfix')
    jintian = tianqi.find('li')
    jintian.find('p', 'wea').string
    return jintian.find('p', 'wea').string
dk = list(serial.tools.list_ports.comports())
if len(dk) > 0:
    for i in range(len(dk)):
        print(dk[i])
    cki = int(input("串口------]"))
    jnd = list(dk[cki-1])
    omg = jnd[0]
    CK = serial.Serial(omg, 9600)
    while(1):
        CK.write(str(JL_GR()).encode())
        CK.write(str(";").encode())
        print(str(JL_GR()))
        time.sleep(0.5)
        CK.write(str(Date()).encode())
        CK.write(str(";").encode())
        print(str(Date()))
#        time.sleep(0.5)
#        CK.write(str(Weather()).encode())
#        print(str(Weather()))
        time.sleep(3)
        
else:
    print("ERR")
