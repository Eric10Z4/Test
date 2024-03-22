#include <bits/stdc++.h>
using namespace std;
int main()
{
    string a, b;
    getline(cin,a);
    getline(cin,b);
    
    // 1. 布尔数组必须初始化为 false（0），否则里面是脏数据
    // 大小开到 256 是为了安全覆盖所有的 ASCII 码
    bool y[256] = {false}; 
    
    for(int i = 0; i < b.size(); i ++)
    {
        // 强转最好加上 unsigned char，防止碰到扩充 ASCII 码变成负数越界
        y[(unsigned char)b[i]] = true;
    }
    
    // 2. 对于“删除”文字，最安全的逻辑不是在原有的 a 里面 erase，
    // 而是把不需要删除的挑出来，装进新的杯子。
    string result = "";
    for(int i = 0; i < a.size(); i ++)
    {
        if(y[(unsigned char)a[i]] == false) 
        {
            result += a[i]; // 只有不在黑名单里的，才拼接到答案里
        }
    }
    
    cout << result << endl;
    return 0;
}