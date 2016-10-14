T=int(input())
for Testcase in range(T):
    alen=int(input())
    a=[int(i) for i in input().split()]
    if len(a)%2==1:
        print("lolanv")
    else:
        a.sort()
        cnt=0
        for i in range(0,alen-1,2):
            if a[i]==a[i+1]:
                cnt+=1
        if cnt==alen/2:
            print("Wind")
        else:
            print("lolanv")

