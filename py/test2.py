import os
import re

def isgoal(name):
    if len(re.findall(r'\b.*cpp\b',name))>0:
           if(os.path.getsize(name)<8192):
               print(name)
           
path=r'F:\charlotte_code'
check=dict()

for nowdir in os.walk(path):
    for name in nowdir[2]:
        li=re.findall(r'\bp.\d+.*cpp\b',name)
#        compname=os.path.join(nowdir[0],name)
        if len(li)>0:
            print(nowdir[0]+os.sep+name)
            newname=name[1:]
            check[nowdir[0]+os.sep+name]=nowdir[0]+os.sep+newname
#            os.rename(nowdir[0]+os.sep+name,nowdir[0]+os.sep+newname)
inp=input('enter 1 to rename previous files\n')
if inp.isdigit():
    if int(inp)==1:
        for item in check:
            os.rename(item,check[item])
        print('completed')

