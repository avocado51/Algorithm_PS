#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int init(vector<int> &tree, vector<int> &num, int node, int start, int end)
{
    if (start == end)
        return tree[node] = num[start];
    else
        return tree[node] = init(tree, num, node * 2, start, (start + end) / 2) + init(tree, num, node * 2 + 1, (start + end) / 2 + 1, end);
}
int query(vector<int> &tree, int node, int start, int end, int left, int right)
{
    if (right < start || end < left)
        return 0;
    else if (left <= start && end <= right)
        return tree[node];
    else
    {
        int res = query(tree, node * 2, start, (start + end) / 2, left, right) + query(tree, node * 2 + 1, (start + end) / 2 + 1, end, left, right);
        cout << start << " " << end << " " << res << '\n';
        return 0;
    }
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n;

    int h = (int)ceil(log2(n));
    int size = 1 << (h + 1);

    vector<int> tree(size);
    vector<int> num(n);

    for (int i = 0; i < n; i++)
    {
        cin >> num[i];
    }
    init(tree, num, 1, 0, n - 1);

    for (int i = 0; i < size; i++)
        cout << tree[i] << ' ';
    cout << '\n';

    cin >> m;

    while (m--)
    {
        int a, b;
        cin >> a >> b;

        a--;
        b--;

        cout << "ans " << query(tree, 1, 0, n - 1, a, b) << '\n';
    }
    return 0;
}