import random
x = random.randint(1,100)
print("请猜猜数是多少:")
a = int(input())
while(a != x):
    if(a > x):print("太大了")
    if(a < x):print("太小了")
    a = int(input("请重新猜一个吧："))
if(a == x):print("恭喜你猜对啦！")