#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
//BOJ 전국시대 [15809](https://www.acmicpc.net/problem/15809)
int n, m;

int A[100001];
int parent[100001];

int find(int a)
{
    int pa = parent[a];
    if (pa == a)
        return a;
    return parent[a] = find(parent[a]);
}

void unionSet(int a, int b, int flag)
{
    int pa = find(a);
    int pb = find(b);

    if (pa == pb)
        return;

    parent[pb] = pa;

    if (flag == 1)
    {
        //동맹
        A[pa] += A[pb];
    }
    else
    {
        A[pa] = A[pa] - A[pb];
        A[pb] = 0;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    for (int i = 1; i <= n; i++)
    {
        cin >> A[i];
        parent[i] = i;
        //자기 자신을 가르키면 동맹, 속국 없이 자신의 값을 가지고 있다는 것이다.
    }

    int o, p, q;
    while (m--)
    {
        cin >> o >> p >> q;

        if (o == 1)
        {
            //동맹
            //두 나라의 병력이 하나로 합쳐진다.
            unionSet(p, q, 1);
        }
        else
        {
            int pp = find(p);
            int pq = find(q);
            //전쟁
            if (A[pp] > A[pq])
            {
                unionSet(p, q, 2);
            }
            else if (A[pp] == A[pq])
            {
                A[pp] = A[pq] = 0;
            }
            else
            {
                //pp가 pq의 속국
                unionSet(q, p, 2);
            }
        }
    }

    int size = 0;
    vector<int> res;

    for (int i = 1; i <= n; i++)
    {
        if (parent[i] == i && A[i])
        {
            size++;
            res.push_back(A[i]);
        }
    }
    sort(res.begin(), res.end());

    cout << size << '\n';
    for (int j = 0; j < res.size(); j++)
        cout << res[j] << ' ';
    return 0;
}