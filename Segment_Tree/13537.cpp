#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#define MAXX 1000001
using namespace std;
vector<int> tree[MAXX];
int arr[MAXX];
vector<int> merge(vector<int> &v1, vector<int> &v2)
{
    vector<int> ret;

    //두 백터 배열을 정렬해서 합친다.

    for (int k = 0; k < v1.size(); k++)
    {
        ret.push_back(v1[k]);
    }
    for (int k = 0; k < v2.size(); k++)
    {
        ret.push_back(v2[k]);
    }
    // int i = 0, j = 0;
    // while (i < v1.size() && j < v2.size())
    // {
    //     if (v1[i] <= v2[j])
    //     {
    //         ret.push_back(v1[i]);
    //         i++;
    //     }
    //     else
    //     {
    //         ret.push_back(v2[j]);
    //         j++;
    //     }
    // }
    // for (int k = i; k < v1.size(); k++)
    // {
    //     ret.push_back(v1[k]);
    // }
    // for (int k = j; k < v2.size(); k++)
    // {
    //     ret.push_back(v2[k]);
    // }
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
    cout << node << " " << node * 2 + 1 << '\n';
    tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    // for (int i = 0; i < tree[node].size(); i++)
    //     cout << tree[node][i] << ' ';
    // cout << '\n';
}
int query(vector<int> *tree, int node, int start, int end, int left, int right, int k)
{
    if (right < start || end < left)
        return 0;
    else if (left <= start && end <= right)
    {
        //lowerbound를 통해 k보다 큰 값을 반환한다.
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
    {
        cin >> arr[i];
    }

    init(tree, arr, 1, 0, n - 1);

    cin >> m;
    while (m--)
    {
        int i, j, k;
        cin >> i >> j >> k;
        i--;
        j--;

        cout << query(tree, 1, 0, n - 1, i, j, k) << '\n';
    }
    return 0;
}