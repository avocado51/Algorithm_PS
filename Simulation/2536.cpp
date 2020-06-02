#include <iostream>
#include <vector>

using namespace std;

int m, n, k;
int sx, sy, dx, dy;
typedef struct Bus {
    int sx, sy, dx, dy, dir;
};
Bus bus[5001];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >>m >> n >> k;

    int idx, sx, sy, dx, dy;
    //dir == 1 : 세로 
    //dir == 0 : 가로
    while(k--) {
        cin >> idx >> sx >> sy >> dx >> dy;
        int dir;
        if (sx > dx) {
            //x로 움직임 
            dir = 0;
        }
        else dir = 1;
        bus[idx] = {sx, sy, dx, dy, dir};
        
    }

    cin >> sx >> sy >> dx >> dy;
    
    return 0;
}