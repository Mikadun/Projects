#include <iostream>

using namespace std;

int main(){
	int n;
	cin >> n;
	int row[n] = {0};
	for(int i = 0; i < n; i++){
		int flag = 0;
		for(int j = 0; j < n; j++){
			int temp;
			cin >> temp;
			if(temp != 0)
				row[j] = j + 1;
		}
		for(int j = 0; j < n; j++)
			if(row[j] != 0){
				cout << row[j] << " ";
				row[j] = 0;
				flag = 1;
			}
		if(!flag)
			cout << 0;
		cout << endl;
	}
	return 0;
}
