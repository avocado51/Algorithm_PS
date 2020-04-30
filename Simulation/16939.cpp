#include <iostream>
#include <vector>
#include <cstring>
#include <deque>
using namespace std;

//boj 2×2×2 큐브 https://www.acmicpc.net/problem/16939

int cube[25];
int rotateIdx[6][8] = {{1, 3, 5, 7, 9, 11, 24, 22}, {2, 4, 6, 8, 10, 12, 23, 21}, {3, 4, 17, 19, 10, 9, 16, 14}, {1, 2, 18, 20, 12, 11, 15, 13}, {7, 8, 19, 20, 23, 24, 15, 16}, {5, 6, 17, 18, 21, 22, 13, 14}};

bool check()
{
    //각 면이

    for (int i = 1; i <= 24; i += 4)
    {
        for (int j = i; j < i + 4; j++)
        {
            if (cube[i] != cube[j])
                return false;
        }
    }
    return true;
}
void rotate()
{
    //첫번째 방법으로 돌려본다.
    //왼쪽/오른쪽을 돌릴 것인지 확인한다.

    deque<int> q;
    bool flag = false;
    int c_cube[25];
    memcpy(c_cube, cube, sizeof(cube));

    for (int i = 0; i < 6; i++)
    {

        int j = 0;
        for (; j < 8; j++)
        {
            q.push_back(rotateIdx[i][j]);
        }

        int cnt = 2;
        while (cnt--)
        {
            q.push_back(q.front());
            q.pop_front();
        }

        j = 0;

        while (!q.empty())
        {
            int idx = q.front();
            q.pop_front();

            cube[rotateIdx[i][j++]] = c_cube[idx];
        }

        if (check())
        {
            flag = true;
            cout << 1 << '\n';
            break;
        }

        memcpy(cube, c_cube, sizeof(cube));

        j = 0;
        for (; j < 8; j++)
        {
            q.push_back(rotateIdx[i][j]);
        }

        cnt = 2;
        while (cnt--)
        {
            q.push_front(q.back());
            q.pop_back();
        }

        j = 0;

        while (!q.empty())
        {
            int idx = q.front();
            q.pop_front();

            cube[rotateIdx[i][j++]] = c_cube[idx];
        }

        if (check())
        {
            flag = true;
            cout << 1 << '\n';
            break;
        }

        memcpy(cube, c_cube, sizeof(cube));
    }

    if (!flag)
        cout << 0 << '\n';
}

int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    //총 여섯가지의 방향 전환이 나온다.
    //모든 경우를 해 보고 가능하면 1, 아니면 0

    for (int i = 1; i <= 24; i++)
    {
        cin >> cube[i];
    }

    rotate();
    //전체 검사

    return 0;
}
