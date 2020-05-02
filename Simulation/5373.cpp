#include <iostream>
#include <vector>
#include <cstring>
#include <deque>
using namespace std;
//BOJ 큐빙 https://www.acmicpc.net/problem/5373

/*            U
          0  1  2
          3  4  5
          6  7  8
L        __________    R            B
36 37 38|F18 19 20 | 45 46 47 | 27 28 29
39 40 41| 21 22 23 | 48 49 50 | 30 31 32
42 43 44| 24 25 26 | 51 52 53 | 33 34 35
        -----------
          9  10 11
          12 13 14
          15 16 17
          D
*/

int dirs[6][12] = {
    {36, 37, 38, 18, 19, 20, 45, 46, 47, 27, 28, 29}, //U
    {33, 34, 35, 51, 52, 53, 24, 25, 26, 42, 43, 44}, //D
    {6, 7, 8, 44, 41, 38, 11, 10, 9, 45, 48, 51},     //F
    {2, 1, 0, 53, 50, 47, 15, 16, 17, 36, 39, 42},    //B
    {0, 3, 6, 35, 32, 29, 9, 12, 15, 18, 21, 24},     //L
    {8, 5, 2, 26, 23, 20, 17, 14, 11, 27, 30, 33}     //R
};

//B D F L R U
char sides[6] = {'U', 'D', 'F', 'B', 'L', 'R'};
char color[6] = {'w', 'y', 'r', 'o', 'g', 'b'};
int cubeIdx[6][3][3];
char cubeColor[55];

void rotate(int idx, int cnt)
{

    //시계방향 회전
    //idx
    //일단 기준 면을 회전한다.
    //인덱스를 변한해야 한다.
    char q[12];
    char tmp[3][3];
    int n = 3;

    while (cnt--)
    {

        for (int i = 0; i < 12; i++)
        {
            q[i] = cubeColor[dirs[idx][i]];
        }

        for (int i = 0; i < 12; i++)
        {
            cubeColor[dirs[idx][i]] = q[(i + 3) % 12];
        }

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                tmp[j][n - i - 1] = cubeColor[cubeIdx[idx][i][j]];
            }
        }

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cubeColor[cubeIdx[idx][i][j]] = tmp[i][j];
            }
        }
    }
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    while (t--)
    {
        int n;
        cin >> n;

        int s = 0;
        for (int i = 0; i < 6; i++)
        {
            char c = color[i];
            for (int j = 0; j < 3; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    cubeIdx[i][j][k] = s++;
                }
            }
        }

        int cnt = 0;
        s = 0;
        for (int i = 0; i < 54; i++)
        {
            cubeColor[i] = color[cnt];
            if ((i + 1) % 9 == 0)
                cnt++;
        }

        while (n--)
        {

            char side, dir;
            cin >> side >> dir;

            int idx = 0;
            for (int i = 0; i < 6; i++)
            {
                if (sides[i] == side)
                {
                    idx = i;
                }
            }
            int cnt = 1;
            if (dir == '-')
            {
                cnt = 3;
            }

            rotate(idx, cnt);
        }
        //debyggggg

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cout << cubeColor[cubeIdx[0][i][j]];
            }
            cout << '\n';
        }
    }
    return 0;
}