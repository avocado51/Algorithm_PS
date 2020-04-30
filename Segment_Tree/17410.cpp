#include <iostream>
#include <vector>
#include <algorithm>
#define MAXX 1000001
using namespace std;
//BOJ https://www.acmicpc.net/problem/17410
//unsolved

int num[MAXX];
vector<int> tree[MAXX];
vector<int> merge(vector<int> &v1, vector<int> &v2)
{
    vector<int> ret;

    for (int i = 0; i < v1.size(); i++)
    {
        ret.push_back(v1[i]);
    }
    for (int i = 0; i < v2.size(); i++)
    {
        ret.push_back(v2[i]);
    }
    sort(ret.begin(), ret.end());
    return ret;
}
void init(vector<int> *tree, int *arr, int node, int start, int end)
{
    if (start == end)
    {
        tree[node].push_back(arr[start]);
        return;
    }
    init(tree, arr, node * 2, start, (start + end) / 2);
    init(tree, arr, node * 2 + 1, (start + end) / 2 + 1, end);

    tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
}
void update(vector<int> *tree, int node, int start, int end, int idx, int diff)
{
    if (idx < start || end < idx)
        return;

    for (int i = 0; i < tree[node].size(); i++)
    {
        tree[node][i] += diff;
    }
    if (start != end)
    {
        update(tree, node * 2, start, (start + end) / 2, idx, diff);
        update(tree, node * 2 + 1, (start + end) / 2 + 1, end, idx, diff);
    }
}
int query(vector<int> *tree, int node, int start, int end, int left, int right, int k)
{
    if (right < start || end < left)
        return 0;
    else if (left <= start && end <= right)
    {
        return tree[node].size() - (upper_bound(tree[node].begin(), tree[node].end(), k) - tree[node].begin());
    }
    else
    {
        return query(tree, node * 2, start, (start + end) / 2, left, right, k) + query(tree, node * 2 + 1, (start + end) / 2 + 1, end, left, right, k);
    }
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n;

    for (int i = 0; i < n; i++)
        cin >> num[i];

    init(tree, num, 1, 0, n - 1);

    cin >> m;

    while (m--)
    {
        int q, i, j, k;
        cin >> q;

        switch (q)
        {
        case 1:
        {
            cin >> i >> k;

            i--;
            int diff = k - num[i];
            num[i] = k;
            update(tree, 1, 0, n - 1, i, diff);
        }
        break;
        case 2:
        {
            cin >> i >> j >> k;
            i--;
            j--;

            cout << query(tree, 1, 0, n - 1, i, j, k) << '\n';
        }
        break;
        default:
            break;
        }
    }
    return 0;
}