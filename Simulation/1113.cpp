#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
//BOJ 마피아 [1113](https://www.acmicpc.net/problem/1079)

int n;
typedef pair<int, int> pp;

int R[17][17];
int mapia;
bool chk[17];
int ans = 0;
int guilty[17];

void playGame(int m, int cnt)
{
    if (m == 1)
    {
        ans = max(ans, cnt);
        return;
    }

    //참가자의 수가 짝수이면 밤
    //홀수이면 낮

    if (m % 2 == 0)
    {
        int c_guilty[17];
        memcpy(c_guilty, guilty, sizeof(guilty));
        //밤 = 누가 죽을 지 확인한다.
        for (int j = 0; j < n; j++)
        {
            if (chk[j] || j == mapia)
                continue;

            chk[j] = true;
            for (int x = 0; x < n; x++)
            {
                //죽은 사람의 R만큼 더해준다.

                if (chk[x])
                    continue;
                if (x == j)
                {
                    guilty[x] = -10000;
                    continue;
                }

                guilty[x] += R[j][x];
            }
            playGame(m - 1, cnt + 1);
            for (int x = 0; x < n; x++)
            {
                //죽은 사람의 R만큼 더해준다.

                if (chk[x])
                    continue;
                if (x == j)
                {
                    guilty[x] = c_guilty[x];
                    continue;
                }

                guilty[x] -= R[j][x];
            }
            chk[j] = false;
        }
    }
    else
    {
        //낮 -> guilty가 제일 높은 사람이 죽는다.
    
        int maxx = 0, maxIdx = 0;
        for (int j = 0; j < n; j++)
        {
            if (chk[j])
                continue;
            //이미 죽은 사람
            if (guilty[j] > maxx)
            {
                maxx = guilty[j];
                maxIdx = j;
            }
        }

        if (maxIdx == mapia)
        {
            playGame(1, cnt);
        }
        else
        {
            chk[maxIdx] = true; //죽인다.
            playGame(m - 1, cnt);
            chk[maxIdx] = false;
        }
    }
}

int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> guilty[i];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> R[i][j];
        }
    }

    cin >> mapia;
    playGame(n, 0);

    cout << ans << '\n';
    return 0;
}