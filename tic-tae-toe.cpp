#include <bits/stdc++.h>
#define DEBUG 0
using namespace std;
const int MAXN = 3;
char gra[MAXN][MAXN];
const int ME = 0;
const int YOU = 1;
int judge_full(int level) {
	for (int i = 0; i<3; i++)
	{
		int j = 0;
		while (j<3 && gra[i][j] == gra[i][0])j++;
		if (j == 3) {
			if (gra[i][0] == 'x')return 10 - level;
			else if (gra[i][0] == 'o')return level - 10;
		}
	}
	for (int j = 0; j<3; j++) {
		int i = 0;
		while (i<3 && gra[i][j] == gra[0][j])i++;
		if (i == 3) {
			if (gra[0][j] == 'x')return 10 - level;
			else if (gra[0][j] == 'o')return level - 10;
		}
	}
	int r, c;
	r = 0; c = 0;
	while (r<3 && c<3 && gra[r][c] == gra[0][0]) { r++; c++; }
	if (r == 3) {
		if (gra[0][0] == 'x')return 10 - level;
		else if (gra[0][0] == 'o')return level - 10;
	}
	r = 0; c = 2;
	while (r<3 && c >= 0 && gra[r][c] == gra[0][2]) { r++; c--; }
	if (r == 3) {
		if (gra[0][2] == 'x')return 10 - level;
		else if (gra[0][2] == 'o')return level - 10;
	}
	int suc = 1;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (gra[i][j] == '-')suc = 0;
	if (suc)return 0;

	return -1;
	
}
int dfs(int level) {
	int ret = judge_full(level);
	if (ret != -1)return ret;

	int xlevel = -100;
	int olevel = 100;
	for (int i = 0; i<3; i++)
		for (int j = 0; j<3; j++) {
			if (gra[i][j] != '-')continue;
			if (level % 2 == 1) {
				gra[i][j] = 'x';
				int ret = dfs(level + 1);
				xlevel = max(ret, xlevel);
				gra[i][j] = '-';
			}
			else {
				gra[i][j] = 'o';
				int ret = dfs(level + 1);
				olevel = min(ret, olevel);
				gra[i][j] = '-';
			}
		}
	if (level % 2 == 0)return olevel;
	else return xlevel;
}
void display(int round = -1) {
	if (round != -1)
		cout << "round " << round << endl;
	for (int i = 0; i<3; i++) {
		for (int j = 0; j<3; j++)
			cout << gra[i][j];
		cout << endl;
	}
}
void win() {
	cout << "game over" << endl;
	display();
	cout << "X win you can not beat me :)" << endl;
	exit(0);
}
void draw() {
	cout << "game over" << endl;
	display();
	cout << "Draw! quit now!" << endl;
	exit(0);
}
void lose() {
	cout << "game over" << endl;
	display();
	cout << "Something impossible happens please report it!" << endl;
	exit(0);
}
char disgra[4][4];
void dis_disgra() {
	for (int i = 0; i<4; i++) {
		for (int j = 0; j<4; j++)
			cout << disgra[i][j];
		cout << endl;
	}
}
int main() {
	srand((int)time(0));  // 产生随机种子  把0换成NULL也行
	for (int i = 0; i<3; i++)
		for (int j = 0; j<3; j++)
			gra[i][j] = '-';
	cout << "tic tae toe! chinese: jing zi guo san guan" << endl;

	for (int i = 0; i<4; i++) {
		for (int j = 0; j<4; j++)disgra[i][j] = '-';
	}
	disgra[0][0] = ' ';
	for (int i = 1; i<4; i++)disgra[i][0] = i - 1 + '0';
	for (int j = 1; j<4; j++)disgra[0][j] = j - 1 + '0';
	cout << "When we have 3x or 3o in a line or diagnoal, game is over" << endl;

	dis_disgra();
	cout << "type coordinate xy to input (eg.00); 00 is the top left" << endl;
	cout << "type q to quit the game" << endl;
	cout << "Now presss Y if you want to be the first move or press another key so that i will make the first move " << endl;
	string st;
	getline(cin, st);
	int cur;
	int round = 0;
	if (st[0] == 'Y' || st[0] == 'y') {
		cur = ME;
	}
	else cur = YOU;
	cout << "Now Begin Have Fun" << endl;
	
#if DEBUG	
	freopen("in.txt", "r", stdin);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)cin >> gra[i][j];
#endif
	display();
	while (1) {
		cur = !cur;
		round++;
		if (cur == ME) {
			cout << "My turn" << endl;
			int tmpans = -100;
			int pr, pc;
			vector<pair<int, int>> moves;
			for (int i = 0; i<3; i++)
				for (int j = 0; j<3; j++) {

					if (gra[i][j] == '-') {
						gra[i][j] = 'x';
						int ret = dfs(0);
						if (ret>=tmpans) {
							
							if (ret > tmpans) {
								moves = vector<pair<int, int>>();
								moves.push_back(make_pair(i, j));
							}
							else moves.push_back(make_pair(i, j));

							tmpans = ret;
						}
						gra[i][j] = '-';
					}
				}
			if (tmpans != -100) {
				int rd = rand() % (int)moves.size();
				gra[moves[rd].first][moves[rd].second] = 'x';
			}
			display(round);
			if (tmpans == -100) {
				draw();
			}
			if (tmpans == 10) {
				win();
			}
			else {
				if (tmpans == -10)lose();
				else continue;
			}
		}
		else {
			cout << "YOUR turn please input" << endl;
			string str;
			while (getline(cin, str)) {
				if (str[0] == 'q')exit(0);
				if ((int)str.size() == 2) {
					if (str[0] >= '0' && str[0] <= '2' && str[1] >= '0' && str[1] <= '2') {
						int r = str[0] - '0';
						int c = str[1] - '0';
						if (gra[r][c] != '-') {
							cout << "already place a chess! input again!" << endl;
							continue;
						}
						gra[r][c] = 'o';
						display(round);
						break;
					}
				}
				cout << "Unknown command! or coordinate format is not correct! input again" << endl;

			}

		}

	}
	return 0;
}