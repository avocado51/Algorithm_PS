#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
//BOJ 나무재태크 [16235](https://www.acmicpc.net/problem/16235)

int n, m, k;
int nutri[11][11];
int A[11][11];
vector<int> trees[11][11];
int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1}, dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

bool checkRange(int x, int y)
{
    if (x < 0 || x >= n || y < 0 || y >= n)
        return false;
    return true;
}
void winter()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            nutri[i][j] += A[i][j];
        }
    }
}
void fall()
{
    /*
    가을에는 나무가 번식한다. 번식하는 나무는 나이가 5의 배수이어야 하며, 인접한 8개의 칸에 나이가 1인 나무가 생긴다. 어떤 칸 (r, c)와 인접한 칸은 
    (r-1, c-1), (r-1, c), (r-1, c+1), (r, c-1), (r, c+1), (r+1, c-1), (r+1, c), (r+1, c+1) 이다. 
    상도의 땅을 벗어나는 칸에는 나무가 생기지 않는다.
    */
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (trees[i][j].size())
            {
                for (int age : trees[i][j])
                {
                    if (age % 5 == 0)
                    {
                        //5의 배수이면 번식
                        for (int d = 0; d < 8; d++)
                        {
                            int nx = i + dx[d];
                            int ny = j + dy[d];

                            if (checkRange(nx, ny))
                            {
                                //범위를 벗어나지 않으먄
                                trees[nx][ny].push_back(1);
                            }
                        }
                    }
                }
            }
        }
    }
}
void springAndSummer()
{
    /*
    봄에는 나무가 자신의 나이만큼 양분을 먹고, 나이가 1 증가한다. 각각의 나무는 나무가 있는 1×1 크기의 칸에 있는 양분만 먹을 수 있다. 
    하나의 칸에 여러 개의 나무가 있다면, 나이가 어린 나무부터 양분을 먹는다. 만약, 땅에 양분이 부족해 자신의 나이만큼 양분을 먹을 수 없는 나무는 양분을 먹지 못하고 즉시 죽는다.

    여름에는 봄에 죽은 나무가 양분으로 변하게 된다. 각각의 죽은 나무마다 나이를 2로 나눈 값이 나무가 있던 칸에 양분으로 추가된다. 소수점 아래는 버린다.
    */
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (trees[i][j].size())
            {
                //나무가 잇으면
                vector<int> liveTree;
                //살아남은 나무만 저장
                sort(trees[i][j].begin(), trees[i][j].end());

                int sum = 0;

                //나이가 가장 적은 순으로 정렬되낟.
                for (int d = 0; d < trees[i][j].size(); d++)
                {
                    if (nutri[i][j] - trees[i][j][d] >= 0)
                    {
                        liveTree.push_back(trees[i][j][d] + 1);
                        nutri[i][j] -= trees[i][j][d];
                    }
                    else
                    {
                        //죽는다.-> 양분이 된다.
                        sum += (trees[i][j][d] / 2);
                    }
                }
                trees[i][j] = liveTree;
                nutri[i][j] += sum;
            }
        }
    }
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie();

    cin >> n >> m >> k;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> A[i][j];
            nutri[i][j] = 5; //기본 5씩 들어있다.
        }
    }
    int x, y, z;

    while (m--)
    {
        //상도가 심은 나무
        cin >> x >> y >> z;
        trees[x - 1][y - 1].push_back(z);
    }

    while (k--)
    {
        springAndSummer();
        fall();
        winter();
    }

    int ans = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            ans += trees[i][j].size();
        }
    }

    cout << ans << '\n';
    return 0;
}