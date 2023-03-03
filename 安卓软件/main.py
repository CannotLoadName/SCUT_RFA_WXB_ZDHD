from os.path import dirname
from threading import Thread
from socket import socket,AF_INET,SOCK_STREAM
from bottle import static_file,route,run
server=socket(AF_INET,SOCK_STREAM)
server.bind(("0.0.0.0",2000))
server.listen(1)
client=None
pump=-1
loc=True
def init():
    global loc,server,client,pump
    if loc:
        loc=False
        if client!=None:
            client.close()
            client=None
        pump=-1
        client=server.accept()[0]
        loc=True
def comm(byt):
    global client
    if client==None:
        return -1
    else:
        byt=byt.encode("utf-8")
        try:
            client.send(byt)
        except:
            return -1
        else:
            byr=client.recv(65536)
            if byr==b"":
                return -1
            else:
                if byt==b"V":
                    return (int.from_bytes(byr,byteorder="little",signed=False))/819.2
                else:
                    return int.from_bytes(byr,byteorder="little",signed=False)
@route("/index.html")
def deal():
    return static_file("index.html",root=dirname(__file__),download=False)
@route("/styles.css")
def deal():
    return static_file("styles.css",root=dirname(__file__),download=False)
@route("/scripts.js")
def deal():
    return static_file("scripts.js",root=dirname(__file__),download=False)
@route("/favicon.ico")
def deal():
    return static_file("favicon.ico",root=dirname(__file__),download=False)
@route("/start")
def deal():
    global pump,client
    if client==None:
        pump=-1
    else:
        try:
            client.send(b"B")
        except:
            pump=-1
        else:
            pump=1
    return ""
@route("/stop")
def deal():
    global pump,client
    if client==None:
        pump=-1
    else:
        try:
            client.send(b"E")
        except:
            pump=-1
        else:
            pump=0
    return ""
@route("/reset")
def deal():
    Thread(target=init).start()
@route("/data")
def deal():
    global client,pump
    return {
        "wifi":0 if client==None else 1,
        "helec":comm("H"),
        "melec":comm("M"),
        "lelec":comm("L"),
        "voltage":comm("V"),
        "temper":-1,
        "pump":pump
    }
run(host="0.0.0.0",port=8080)