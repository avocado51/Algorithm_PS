#include <iostream>
#include <vector>

using namespace std;

int n, m, K;
int sticker[101][4][11][11];
int map[41][41];
typedef pair<int, int> pp;

pp ssize[101][4];

bool check(int sx, int sy, int ex, int ey, int idx, int dir)
{
    //이 자리에 해당 스티커가 들어갈 수 있는지 확인
    for (int i = sx; i < ex; i++)
    {
        for (int j = sy; j < ey; j++)
        {
            if (sticker[idx][dir][i - sx][j - sy] && map[i][j])
                return false;
        }
    }
    return true;
}
void rotate(int idx, int dir, int r, int c)
{
    for (int j = 0; j < r; j++)
    {
        for (int k = 0; k < c; k++)
        {
            sticker[idx][dir][j][k] = sticker[idx][dir - 1][c - k - 1][j];
        }
    }
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> K;

    int r, c;

    for (int i = 0; i < K; i++)
    {
        cin >> r >> c;
        ssize[i][0] = pp(r, c);

        for (int j = 0; j < r; j++)
        {
            for (int k = 0; k < c; k++)
            {
                cin >> sticker[i][0][j][k];
            }
        }

        for (int j = 1; j < 4; j++)
        {
            swap(r, c);
            ssize[i][j] = pp(r, c);
            rotate(i, j, r, c);
        }
    }

    // for (int i = 0; i < k; i++)
    // {
    //     for (int d = 0; d < 4; d++)
    //     {
    //         int h = ssize[i][d].first;
    //         int w = ssize[i][d].second;
    //         for (int j = 0; j < h; j++)
    //         {
    //             for (int k = 0; k < w; k++)
    //             {
    //                 cout << sticker[i][d][j][k] << ' ';
    //             }
    //             cout << '\n';
    //         }
    //         cout << '\n';
    //     }
    //     cout << '\n';
    // }

    //스티커 붙이기
    for (int s = 0; s < K; s++)
    {
        bool flag = false;
        for (int d = 0; d < 4; d++)
        {
            int h = ssize[s][d].first;
            int w = ssize[s][d].second;

            for (int i = 0; i <= n - h; i++)
            {
                for (int j = 0; j <= m - w; j++)
                {
                    if (check(i, j, i + h, j + w, s, d))
                    {
                        // cout << "DEEE " << s << " " << d << '\n';
                        //붙일 수 있다.
                        for (int k = i; k < i + h; k++)
                        {
                            for (int q = j; q < j + w; q++)
                            {
                                if (!map[k][q] && sticker[s][d][k - i][q - j])
                                    map[k][q] = sticker[s][d][k - i][q - j];
                            }
                        }
                        flag = true;
                        break;
                    }
                }
                if (flag)
                    break;
            }
            if (flag)
                break;
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (map[i][j])
                ans++;
        }
    }

    cout << ans << '\n';
    return 0;
}