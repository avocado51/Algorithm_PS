#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
//SWEA Flatten [1208](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV139KOaABgCFAYh)

int height[101];
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 10;

    for (int tc = 1; tc <= t; tc++)
    {
        int dump;
        cin >> dump;

        for (int i = 0; i < 100; i++)
        {
            cin >> height[i];
        }

        //가장 높은 곳에서 가장 낮은 곳으로 블럭을 하나씩 보낸다.
        //dump 만큼
        sort(height, height + 100);

        while (dump--)
        {
            height[99]--;
            height[0]++;

            sort(height, height + 100);
        }
        sort(height, height + 100);
        cout << "#" << tc << " " << height[99] - height[0] << "\n";
    }
    return 0;
}