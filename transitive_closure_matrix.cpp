#include <iostream>
using namespace std;

int main()
{
	int n;
	cin >> n;
	bool g[n][n], res[n][n];
	for( int i = 0; i < n; i++ )
		for( int j = 0; j < n; j++ )
		{
			cin >> g[i][j];
			res[i][j] = g[i][j];
		}

	for( int m = 0; m < n; m++ )
		for( int i = 0; i < n; i++ )
			for( int j = 0; j < n; j++ )
				for( int k = 0; k < n; k++ )
					res[i][j] |= res[i][k] & g[k][j];

	for( int i = 0; i < n; i++ )
	{
		for( int j = 0; j < n; j++ )
			cout << (int) res[i][j] << " ";
		cout << endl;
	}


}
