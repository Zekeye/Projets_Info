#!/usr/bin/env python3


import subprocess
import sys


NULL = open("/dev/null", "w")

def say(m):
	sys.stdout.write(m)
	sys.stdout.flush()


def noter():
    note=0
    rc_base = subprocess.call("gcc -lm -o notation_pol pile.c polonaise.c test_polonaise.c",shell = True, stdout = NULL, stderr = NULL)

    if rc_base == 0:
        say("notation_pol 0 compilee\n")
    else:
        say("Echec de compilation notation_pol\nNote provisoire : 0\n")
        sys.exit(1)
    process=subprocess.Popen("./notation_pol < test/test_add.txt",shell=True,stdout=subprocess.PIPE,stderr=subprocess.PIPE, bufsize=1)
    (out,err)=process.communicate()
    if(process.returncode==0):
        say('add: ')
        print(out.decode('utf-8'))
        note+=(int(err.decode('utf-8')))
        #print(err.decode('utf-8'))
    process=subprocess.Popen("./notation_pol < test/test_sous.txt",shell=True,stdout=subprocess.PIPE,stderr=subprocess.PIPE, bufsize=1)
    (out,err)=process.communicate()
    if(process.returncode==0):
        say('sous: ')
        print(out.decode('utf-8'))
        note+=(int(err.decode('utf-8')))
        #print(err.decode('utf-8'))
    process=subprocess.Popen("./notation_pol < test/test_mul.txt",shell=True,stdout=subprocess.PIPE,stderr=subprocess.PIPE, bufsize=1)
    (out,err)=process.communicate()
    if(process.returncode==0):
        say('mul: ')
        print(out.decode('utf-8'))
        note+=(int(err.decode('utf-8')))
        #print(err.decode('utf-8'))
    process=subprocess.Popen("./notation_pol < test/test_div.txt",shell=True,stdout=subprocess.PIPE,stderr=subprocess.PIPE, bufsize=1)
    (out,err)=process.communicate()
    if(process.returncode==0):
        say('div: ')
        print(out.decode('utf-8'))
        note+=(int(err.decode('utf-8')))
        #print(err.decode('utf-8'))
    process=subprocess.Popen("./notation_pol < test/test_puiss.txt",shell=True,stdout=subprocess.PIPE,stderr=subprocess.PIPE, bufsize=1)
    (out,err)=process.communicate()
    if(process.returncode==0):
        say('puiss: ')
        print(out.decode('utf-8'))
        note+=(int(err.decode('utf-8')))
        #print(err.decode('utf-8'))

    process=subprocess.Popen("./notation_pol < test/test_facto.txt",shell=True,stdout=subprocess.PIPE,stderr=subprocess.PIPE, bufsize=1)
    (out,err)=process.communicate()
    if(process.returncode==0):
        say('facto: ')
        print(out.decode('utf-8'))
        note+=(int(err.decode('utf-8')))
        #print(err.decode('utf-8'))

    process=subprocess.Popen("./notation_pol < test/test_neg.txt",shell=True,stdout=subprocess.PIPE,stderr=subprocess.PIPE, bufsize=1)
    (out,err)=process.communicate()
    if(process.returncode==0):
        say('neg: ')
        print(out.decode('utf-8'))
        note+=(int(err.decode('utf-8')))
        #print(err.decode('utf-8'))

    print("\nNote provisoire : "+str(note)+"/7")
noter()
