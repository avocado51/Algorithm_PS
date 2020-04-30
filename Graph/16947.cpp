#include <iostream>
#include <vector>
#include <algorithm>

#include <queue>
#define MAXX 3001
using namespace std;
// BOJ 여행가자 https://www.acmicpc.net/problem/1976

int n, m;

int parent[MAXX];

int find(int a)
{
    if (parent[a] == -1)
        return a;
    return find(parent[a]);
}
void unionFind(int a, int b)
{
    int pa = find(a);
    int pb = find(b);

    if (pa == pb)
        return;

    parent[pa] = pb;
}
bool isSameSet(int a, int b)
{
    int pa = find(a);
    int pb = find(b);

    if (pa == pb)
        return true;
    return false;
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    for (int i = 1; i <= n; i++)
    {
        parent[i] = -1;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            int tmp;
            cin >> tmp;
            if (tmp)
                unionFind(i, j);
        }
    }

    int plan[1001] = {0};
    for (int i = 0; i < m; i++)
    {
        cin >> plan[i];
    }

    bool flag = true;
    int start = plan[0];
    for (int i = 1; i < m; i++)
    {
        if (isSameSet(start, plan[i]))
        {
            start = plan[i];
        }
        else
        {
            flag = false;
            break;
        }
    }
    if (flag)
        cout << "YES" << '\n';
    else
        cout << "NO" << '\n';
    return 0;
}