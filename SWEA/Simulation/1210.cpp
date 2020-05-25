#include <iostream>
#include <vector>
#define DOWN 1
#define LEFT 2
#define RIGHT 3
using namespace std;
//SWEA Ladder1 [1210](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV14ABYKADACFAYh)

int map[102][102];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t = 10;

    for (int tc = 1; tc <= t; tc++)
    {

        int n;
        cin >> n;
        int dest = 0;
        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 100; j++)
            {
                cin >> map[i][j];
                if (map[i][j] == 2)
                    dest = j;
            }
        }

        int ans = 0;
        int start = 0;
        for (int i = 0; i < 100; i++)
        {
            //시작 좌표
            int x = 0, y = i;
            start = y;
            int dir = DOWN;
            while (x < 100)
            {
                bool flag = false;
                // cout << x << " " << y << '\n';
                if (dir == DOWN || dir == RIGHT)
                {
                    if (y + 1 < 100 && map[x][y + 1])
                    {
                        y++;
                        flag = true;
                        dir = RIGHT;
                    }
                }
                if (dir == DOWN || dir == LEFT)
                {
                    if (y - 1 >= 0 && map[x][y - 1])
                    {
                        y--;
                        flag = true;
                        dir = LEFT;
                    }
                }
                if (!flag)
                {
                    x++;
                    dir = DOWN;
                }
            }
            if (y == dest)
            {
                ans = start + 1;
                break;
            }
        }
        cout << "#" << n << " " << ans << '\n';
    }
    return 0;
}