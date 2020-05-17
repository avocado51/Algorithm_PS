#include <iostream>
#include <vector>
#define N 10
//BOJ 색종이 붙이기 

using namespace std;
int map[N][N];
int paperCnt[6] = {0,5,5,5,5,5};
bool visited[N][N];
int ans = 26;
int fillCnt = 0;
typedef pair<int, int> pp;
vector<pp> fillPos;
void dfs(int res, int cnt) {

	if (cnt == fillPos.size()) {
		ans = ans > res ? res : ans;
		return;
	}

	if (ans <= res) return;
	//모든 색종이를 다썼으면 

	for (pp pos : fillPos){
		int i = pos.first;
		int j = pos.second;
		if (visited[i][j]) continue;

		int k = 5; 
		for (; k >= 1; k--) {
			if (!paperCnt[k]) continue;

			bool flag = true;
			if (i + k > N || j + k > N) continue;

			for (int x = i; x < i+k; x++) {
				for (int y = j; y < j + k; y++) {
					if (!map[x][y] || visited[x][y]) {
						flag = false;
						break;
					}
				}
				if (!flag) break;
			}

			if (flag) {

				for (int x = i; x < i+k; x++) {
					for (int y = j; y < j + k; y++) {
						visited[x][y] = true;
					}

				}
				// cout << k << '\n';
				// print();
				paperCnt[k]--;
				dfs(res+1, cnt+k*k);
				paperCnt[k]++;
				for (int x = i; x < i+k; x++) {
					for (int y = j; y < j + k; y++) {
						visited[x][y] = false;
					}

				}
			}

		}
		return;

	}
}
int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0);

	for (int i = 0; i < N; i++) 
	{
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];

			if (map[i][j]) {

				fillPos.push_back(pp(i, j));
			}
		}
	}

	dfs(0, 0);
	if (ans == 26) ans = -1;
	cout << ans << '\n';
	return 0;
}
