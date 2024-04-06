#!/usr/bin/env python3


import subprocess
import sys


NULL = open("/dev/null", "w")

def say(m):
	sys.stdout.write(m)
	sys.stdout.flush()


def noter():
    note=0
    rc_base = subprocess.call("gcc -o notation_sy pile.c polonaise.c test_sy.c",shell = True, stdout = NULL, stderr = NULL)

    if rc_base == 0:
        say("notation_sy compilee\n")
    else:
        say("Echec de compilation notation_sy\nNote provisoire : 0\n")
        sys.exit(1)
    process=subprocess.Popen("./notation_sy < test_sy/test0.txt",shell=True,stdout=subprocess.PIPE,stderr=subprocess.PIPE, bufsize=1)
    (out,err)=process.communicate()
    if(process.returncode==0):
        say('test0: ')
        print(out.decode('utf-8'))
        note+=(int(err.decode('utf-8')))
        #print(err.decode('utf-8'))
    process=subprocess.Popen("./notation_sy < test_sy/test1.txt",shell=True,stdout=subprocess.PIPE,stderr=subprocess.PIPE, bufsize=1)
    (out,err)=process.communicate()
    if(process.returncode==0):
        say('test1: ')
        print(out.decode('utf-8'))
        note+=(int(err.decode('utf-8')))
        #print(err.decode('utf-8'))
    process=subprocess.Popen("./notation_sy < test_sy/test2.txt",shell=True,stdout=subprocess.PIPE,stderr=subprocess.PIPE, bufsize=1)
    (out,err)=process.communicate()
    if(process.returncode==0):
        say('test2: ')
        print(out.decode('utf-8'))
        note+=(int(err.decode('utf-8')))
        #print(err.decode('utf-8'))
    process=subprocess.Popen("./notation_sy < test_sy/test3.txt",shell=True,stdout=subprocess.PIPE,stderr=subprocess.PIPE, bufsize=1)
    (out,err)=process.communicate()
    if(process.returncode==0):
        say('test3: ')
        print(out.decode('utf-8'))
        note+=(int(err.decode('utf-8')))
        #print(err.decode('utf-8'))
    process=subprocess.Popen("./notation_sy < test_sy/test4.txt",shell=True,stdout=subprocess.PIPE,stderr=subprocess.PIPE, bufsize=1)
    (out,err)=process.communicate()
    if(process.returncode==0):
        say('test4: ')
        print(out.decode('utf-8'))
        note+=(int(err.decode('utf-8')))
        #print(err.decode('utf-8'))
    
    print("\nNote provisoire : "+str(note)+"/5")
noter()
