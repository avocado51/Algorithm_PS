#include <iostream>
#include <vector>

using namespace std;
//BOJ LCD Test https://www.acmicpc.net/problem/2290

int s;
int ssize;
char printArr[230][120];
void print()
{
    for (int i = 0; i < 2 * s + 3; i++)
    {
        for (int j = 0; j < (2 + s) * ssize;)
        {
            if (printArr[i][j] == '\0')
                cout << ' ';
            else
                cout << printArr[i][j];
            if (++j % (2 + s) == 0)
                cout << ' ';
        }
        cout << '\n';
    }
}
void drawDigit(int digit, int x, int y)
{
    //총 6군데로 나누어져있다.
    //0의 경우 6군데 모두 포함이 된다.
    //0 <- 제일 윗 부분
    if (digit == 2 || digit == 3 || digit == 5 || digit == 6 || digit == 7 || digit == 8 || digit == 9 || digit == 0)
    {
        //- 를 그려줘야 한다.
        int cnt = s;
        int sy = y + 1;
        while (cnt--)
        {
            printArr[0][sy++] = '-';
        }
    }
    //1
    if (digit == 4 || digit == 5 || digit == 6 || digit == 8 || digit == 9 || digit == 0)
    {
        //|
        int cnt = s;
        int sx = 1;
        while (cnt--)
        {
            printArr[sx++][y] = '|';
        }
    }

    //2
    if (digit == 1 || digit == 2 || digit == 3 || digit == 4 || digit == 7 || digit == 8 || digit == 9 || digit == 0)
    {
        int cnt = s;
        int sx = 1;
        while (cnt--)
        {
            printArr[sx++][y + s + 1] = '|';
        }
    }
    //3
    if (digit == 2 || digit == 3 || digit == 4 || digit == 5 || digit == 6 || digit == 8 || digit == 9)
    {
        int cnt = s;
        int sy = y + 1;
        while (cnt--)
        {
            printArr[s + 1][sy++] = '-';
        }
    }
    //4
    if (digit == 2 || digit == 6 || digit == 8 || digit == 0)
    {
        int cnt = s;
        int sx = s + 2;
        while (cnt--)
        {
            printArr[sx++][y] = '|';
        }
    }
    //5
    if (digit == 1 || digit == 3 || digit == 4 || digit == 5 || digit == 7 || digit == 6 || digit == 8 || digit == 9 || digit == 0)
    {
        int cnt = s;
        int sx = s + 2;
        while (cnt--)
        {
            printArr[sx++][y + s + 1] = '|';
        }
    }
    //6
    if (digit == 2 || digit == 3 || digit == 5 || digit == 6 || digit == 8 || digit == 9 || digit == 0)
    {
        int cnt = s;
        int sy = y + 1;
        while (cnt--)
        {
            printArr[2 * s + 2][sy++] = '-';
        }
    }
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string n;
    cin >> s >> n;
    ssize = n.size();
    for (int i = 0; i < n.size(); i++)
    {
        int digit = n[i] - '0';

        int sx = 0;
        int sy = (s + 2) * i;

        drawDigit(digit, sx, sy);
        // cout << digit << '\n';
        // print();
    }
    print();
    return 0;
}