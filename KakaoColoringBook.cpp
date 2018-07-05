#include <vector>
#include <iostream>
using namespace std;

vector<vector<int>> arr(100, vector<int>(100, 0));//picture 대신 사용하는 전역배열.(picture값복사)
int number_of_area = 0;
int max_size_of_one_area = 0;

int recur(int i, int j, int m, int n) {
	int tmp = arr[i][j], flag = 0, x = 1;
	arr[i][j] = 0;//색깔을 지움.
	if (i>0 && tmp == arr[i - 1][j]) {
		x += recur(i - 1, j, m, n);
		flag = 1;
	}
	if (j>0 && tmp == arr[i][j - 1]) {
		x += recur(i, j - 1, m, n);
		flag = 1;
	}
	if (i<m-1 && tmp == arr[i + 1][j]) {
		x += recur(i + 1, j, m, n);
		flag = 1;
	}
	if (j<n-1 && tmp == arr[i][j + 1]) {
		x += recur(i, j + 1, m, n);
		flag = 1;
	}
	if (flag == 0) return 1;
	else return x;
}

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
vector<int> solution(int m, int n, vector<vector<int>> picture) {
	vector<int> answer(2);
	int i, j, flag = 0, x = 0;
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			arr[i][j] = picture[i][j];
		}
	}

	for (i = 0 ; i<m ; i++) {
		for (j = 0 ; j<n ; j++) {
			if (arr[i][j] != 0) {
				x = recur(i, j, m, n);
				number_of_area++;
				if (x>max_size_of_one_area) max_size_of_one_area = x;//최댓값.
			}
		}
	}
	answer[0] = number_of_area;
	answer[1] = max_size_of_one_area;
	return answer;
}

int main() {
	int m, n,i,j,x;
	vector<int> answer(2);
	cin >> m >> n;
	vector<vector<int>> v(m, vector<int>(n, 0));
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			cin >> v[i][j];
		}
	}
	answer = solution(m, n, v);
	cout << answer[0] << " " << answer[1] << endl;
	cin >> x;
	return 0;
}