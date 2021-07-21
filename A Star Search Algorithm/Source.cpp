// A C++ Program to implement A* Search Algorithm
#include <bits/stdc++.h>
using namespace std;

#define ROW 9
#define COL 10

//�s��y��
typedef pair<int, int> Pair;
//�s��y�ЧY������F
typedef pair<double, pair<int, int> > pPair;
//�s��̵u���|
struct cell {
	int parent_i, parent_j;
	double f, g, h;
};
//�P�_�Ӯy�ЬO�_�X�k(�i��|�W�X�ɽu�Τp��0)
bool isValid(int row, int col) {
	return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
}
//�P�_�Ӯy�ЬO�_���Q����
bool isUnBlocked(int grid[][COL], int row, int col) {
	return grid[row][col] != 1;
}
//�O�_�����I
bool isDestination(int row, int col, Pair dest) {
	return row == dest.first && col == dest.second;
}
//��X2�I�����Z���Y�p��H
double calculateValue(int row, int col, Pair dest) {
	return sqrt(pow(dest.first - row, 2) + pow(dest.second - col, 2));
}
//�q���|�YcellDetails�̱q���I�H���|���Φ����X���|�Y�i�D�o����_�I�ܲ��I�����|
void tracePath(cell cellDetails[][COL], Pair dest) {
	printf("The path is ");
	stack <Pair> path;
	int row = dest.first;
	int col = dest.second;

	//�Ȧsrow,col(�]�������ϥ�row,col���o�U�@�Ӹ`�I�ɡArow��s����N�|���h�����row�A�]���L�k���o���T��col)
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
	//��l��open list
	list <Pair> openlist;
	openlist.push_back(src);

	//��l��close list
	bool closelist[ROW][COL];
	memset(closelist, false, sizeof(closelist));

	//��l��cellDetails
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
		//�qopen list���X�̫e�ݸ`�I�B�R���A�M��N�Ӹ`�I��close list���]���w���X
		Pair q = openlist.front();
		openlist.pop_front();
		int i = q.first;
		int j = q.second;
		closelist[i][j] = true;

		//�N8�Ӥ�V�C�X�åH�}�C�x�s
		Pair successsor[8] = {make_pair(i,j + 1),make_pair(i,j - 1),make_pair(i + 1,j + 1), make_pair(i - 1,j + 1), 
			make_pair(i + 1,j - 1),make_pair(i - 1,j - 1),make_pair(i + 1,j),make_pair(i - 1,j)};

		for (int x = 0; x < 8; x++) {
			//�T�O�Ӥ�V�`�I�����`�`�I
			if (!isValid(successsor[x].first, successsor[x].second)) {
				continue;
			}

			//�P�_�O�_�����I
			if (isDestination(successsor[x].first, successsor[x].second, dest)) {
				cellDetails[successsor[x].first][successsor[x].second].parent_i = i;
				cellDetails[successsor[x].first][successsor[x].second].parent_j = j;
				tracePath(cellDetails, dest);
				return;
			}

			//�Y�����j�B�����X
			else if (isUnBlocked(grid, successsor[x].first, successsor[x].second) && !closelist[successsor[x].first][successsor[x].second]) {
				double Ftmp = 0.0;
				double Gtmp = 0.0;
				double Htmp = 0.0;
				Gtmp = cellDetails[i][j].g + calculateValue(successsor[x].first, successsor[x].second, q);
				Htmp = calculateValue(successsor[x].first, successsor[x].second, dest);
				Ftmp = Gtmp + Htmp;
				//�Y�s���|���u�άO���B���l��
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
	//��l�Ƨt�����j���}�C(1���j,0�i�樫)
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
