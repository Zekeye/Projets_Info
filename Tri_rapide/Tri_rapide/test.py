#!/usr/bin/env python3


import subprocess
import sys


NULL = open("/dev/null", "w")

def say(m):
	sys.stdout.write(m)
	sys.stdout.flush()


def noter():
    note=0
    rc_base = subprocess.call("gcc -o rapide_rec pile.c tri_rapide.c test_rapide_rec.c",shell = True, stdout = NULL, stderr = NULL)

    if rc_base == 0:
        say("Version recursive compilee")
    else:
        say("Echec de compilation tri rapide recursif\nNote provisoire : 0\n")
        sys.exit(1)
    process=subprocess.Popen("./rapide_rec",shell=True,stdout=subprocess.PIPE,stderr=subprocess.PIPE, bufsize=-1)
    (out,err)=process.communicate()
    if(process.returncode==0):
        print(out.decode('utf-8'))
        note+=(int(err.decode('utf-8')))
        #print(err.decode('utf-8'))
    say("\tTri rapide recursif: "+ str(note)+ "/50\n")
    rc_base = subprocess.call("gcc -o rapide_iter pile.c tri_rapide.c test_rapide.c",shell = True, stdout = NULL, stderr = NULL)

    if rc_base == 0:
        say("Version iterative compilee")
    else:
        say("Echec de compilation tri rapide iteratif\nNote provisoire : "+ str(note) + "\n")
        sys.exit(1)
    process=subprocess.Popen("./rapide_iter",shell=True,stdout=subprocess.PIPE,stderr=subprocess.PIPE, bufsize=-1)
    (out,err)=process.communicate()
    if(process.returncode==0):
        print(out.decode('utf-8'))
        note+=(int(err.decode('utf-8')))
        #print(err.decode('utf-8'))
    
    
    print("\n\tNote provisoire : "+str(note)+"/100")
noter()
