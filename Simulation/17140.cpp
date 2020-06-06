#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

//BOJ 이차원 배열의 연산 [17140](https://www.acmicpc.net/problem/17140)

int A[102][102];

int R = 3, C = 3;
typedef pair<int, int> pp;
int res[102];

void print()
{
    for (int i = 1; i <= R; i++)
    {
        for (int j = 1; j <= C; j++)
        {
            cout << A[i][j] << ' ';
        }
        cout << '\n';
    }
}
void calcC()
{
    //C연산
    //C 연산: 배열 A의 모든 행에 대해서 정렬을 수행한다. 행의 개수 ≥ 열의 개수인 경우에 적용된다.
    //행에 대한 정렬
    //수의 최대는 100까지이다.
    int nR = R * 2 > 100 ? 100 : R * 2; //6
    int maxx = 1;
    for (int i = 1; i <= C; i++)
    {
        memset(res, 0, sizeof(res));
        for (int j = 1; j <= R; j++)
        {
            //나온 수에 횟수를 저장한다.
            if (A[j][i])
                res[A[j][i]]++;
        }

        vector<pp> v;
        for (int j = 1; j <= 100; j++)
        {
            //횟수가 0보다 크면 그 수들을 모아 정렬한다.
            if (res[j])
            {
                v.push_back({res[j], j});
            }
        }

        sort(v.begin(), v.end());

        for (int j = 1; j <= R; j++)
        {
            A[j][i] = 0;
        }

        int idx = 0;
        for (int j = 0; j < v.size() && idx <= 100; j++)
        {
            A[++idx][i] = v[j].second;
            A[++idx][i] = v[j].first;
        }

        maxx = max(maxx, idx);
    }
    R = min(nR, maxx);
}
void calcR()
{
    //R연산
    //R 연산: 배열 A의 모든 행에 대해서 정렬을 수행한다. 행의 개수 ≥ 열의 개수인 경우에 적용된다.
    //행에 대한 정렬
    int res[101];                       //수의 최대는 100까지이다.
    int nC = C * 2 > 100 ? 100 : C * 2; //6
    int maxx = 1;
    for (int i = 1; i <= R; i++)
    {
        memset(res, 0, sizeof(res));
        for (int j = 1; j <= C; j++)
        {
            //나온 수에 횟수를 저장한다.
            if (A[i][j])
                res[A[i][j]]++;
        }

        vector<pp> v;
        for (int j = 1; j <= 100; j++)
        {
            //횟수가 0보다 크면 그 수들을 모아 정렬한다.
            if (res[j])
            {
                v.push_back({res[j], j});
            }
        }

        sort(v.begin(), v.end());

        for (int j = 1; j <= C; j++)
        {
            A[i][j] = 0;
        }

        int idx = 0;
        for (int j = 0; j < v.size() && idx <= 100; j++)
        {
            A[i][++idx] = v[j].second;
            A[i][++idx] = v[j].first;
        }

        maxx = max(maxx, idx);
    }
    C = min(nC, maxx);
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie();

    int r, c, k;
    cin >> r >> c >> k;
    for (int i = 1; i <= 3; i++)
    {
        for (int j = 1; j <= 3; j++)
        {
            cin >> A[i][j];
        }
    }

    if (A[r][c] == k)
    {
        cout << 0 << '\n';
        return 0;
    }

    int time = 0;
    while (1)
    {
        time++;
        if (R >= C)
        {
            //R연산
            calcR();
        }
        else
        {
            calcC();
        }

        if (A[r][c] == k)
        {
            break;
        }
        if (time >= 100)
        {
            time = -1;
            break;
        }
    }
    cout << time << '\n';
    return 0;
}