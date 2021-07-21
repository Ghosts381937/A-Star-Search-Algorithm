// A C++ Program to implement A* Search Algorithm
#include <bits/stdc++.h>
using namespace std;

#define ROW 9
#define COL 10

//存放座標
typedef pair<int, int> Pair;
//存放座標即對應的F
typedef pair<double, pair<int, int> > pPair;
//存放最短路徑
struct cell {
	int parent_i, parent_j;
	double f, g, h;
};
//判斷該座標是否合法(可能會超出界線或小於0)
bool isValid(int row, int col) {
	return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
}
//判斷該座標是否有被阻擋
bool isUnBlocked(int grid[][COL], int row, int col) {
	return grid[row][col] != 1;
}
//是否為終點
bool isDestination(int row, int col, Pair dest) {
	return row == dest.first && col == dest.second;
}
//算出2點間的距離即計算H
double calculateValue(int row, int col, Pair dest) {
	return sqrt(pow(dest.first - row, 2) + pow(dest.second - col, 2));
}
//從路徑即cellDetails裡從終點以堆疊的形式取出路徑即可求得完整起點至終點的路徑
void tracePath(cell cellDetails[][COL], Pair dest) {
	printf("The path is ");
	stack <Pair> path;
	int row = dest.first;
	int col = dest.second;

	//暫存row,col(因為直接使用row,col取得下一個節點時，row更新完後就會失去原先的row，因此無法取得正確的col)
	int tmp_row;
	int tmp_col;

	while (!(cellDetails[row][col].parent_i == row && cellDetails[row][col].parent_j == col)) {
		path.push(make_pair(row, col));
		tmp_row = cellDetails[row][col].parent_i;
		tmp_col = cellDetails[row][col].parent_j;	
		row = tmp_row;
		col = tmp_col;
	}
	path.push(make_pair(row, col));
	while (!path.empty()) {
		Pair output = path.top();
		printf("-> (%d,%d) ",output.first,output.second);
		path.pop();
	}
	return;
}
void ASSA(int grid[][COL],Pair src,Pair dest) {
	//初始化open list
	list <Pair> openlist;
	openlist.push_back(src);

	//初始化close list
	bool closelist[ROW][COL];
	memset(closelist, false, sizeof(closelist));

	//初始化cellDetails
	cell cellDetails[ROW][COL];
	for (int i = 0; i < ROW;i++) {
		for (int j = 0; j < COL; j++) {
			cellDetails[i][j].parent_i = -1;
			cellDetails[i][j].parent_j = -1;
			cellDetails[i][j].f = FLT_MAX;
			cellDetails[i][j].g = FLT_MAX;
			cellDetails[i][j].h = FLT_MAX;
		}
	}
	cellDetails[src.first][src.second].parent_i = src.first;
	cellDetails[src.first][src.second].parent_j = src.second;
	cellDetails[src.first][src.second].f = 0;
	cellDetails[src.first][src.second].g = 0;
	cellDetails[src.first][src.second].h = 0;

	while (!openlist.empty()) {
		//從open list取出最前端節點且刪除，然後將該節點於close list中設為已走訪
		Pair q = openlist.front();
		openlist.pop_front();
		int i = q.first;
		int j = q.second;
		closelist[i][j] = true;

		//將8個方向列出並以陣列儲存
		Pair successsor[8] = {make_pair(i,j + 1),make_pair(i,j - 1),make_pair(i + 1,j + 1), make_pair(i - 1,j + 1), 
			make_pair(i + 1,j - 1),make_pair(i - 1,j - 1),make_pair(i + 1,j),make_pair(i - 1,j)};

		for (int x = 0; x < 8; x++) {
			//確保該方向節點為正常節點
			if (!isValid(successsor[x].first, successsor[x].second)) {
				continue;
			}

			//判斷是否為終點
			if (isDestination(successsor[x].first, successsor[x].second, dest)) {
				cellDetails[successsor[x].first][successsor[x].second].parent_i = i;
				cellDetails[successsor[x].first][successsor[x].second].parent_j = j;
				tracePath(cellDetails, dest);
				return;
			}

			//若未阻隔且未走訪
			else if (isUnBlocked(grid, successsor[x].first, successsor[x].second) && !closelist[successsor[x].first][successsor[x].second]) {
				double Ftmp = 0.0;
				double Gtmp = 0.0;
				double Htmp = 0.0;
				Gtmp = cellDetails[i][j].g + calculateValue(successsor[x].first, successsor[x].second, q);
				Htmp = calculateValue(successsor[x].first, successsor[x].second, dest);
				Ftmp = Gtmp + Htmp;
				//若新路徑較短或是仍處於初始值
				if (cellDetails[successsor[x].first][successsor[x].second].f == FLT_MAX || cellDetails[successsor[x].first][successsor[x].second].f > Ftmp) {
					cellDetails[successsor[x].first][successsor[x].second].parent_i = i;
					cellDetails[successsor[x].first][successsor[x].second].parent_j = j;
					cellDetails[successsor[x].first][successsor[x].second].f = Ftmp;
					cellDetails[successsor[x].first][successsor[x].second].g = Gtmp;
					cellDetails[successsor[x].first][successsor[x].second].h = Htmp;
					openlist.push_back(successsor[x]);
				}
			}
		}
	}
	return;
}


int main() {
	//初始化含有阻隔的陣列(1阻隔,0可行走)
	int grid[ROW][COL] = {
		{0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
		{0, 0, 1, 1, 0, 0, 1, 1, 0, 0},
		{0, 0, 1, 1, 0, 0, 1, 1, 0, 0},
		{0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
		{0, 0, 1, 1, 0, 0, 1, 1, 0, 0},
		{0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
		{0, 0, 1, 1, 0, 0, 1, 1, 0, 0},
		{1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
	};
	Pair src = make_pair(8, 0);
	Pair dest = make_pair(0, 9);
	ASSA(grid, src, dest);
}
