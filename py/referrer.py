def init(n):
    global li
    li.append(1)
    li.append(1)
    for i in range(2,n):
        li.append(li[i-1]*i)
li=list()
init(1000)
print(li)
