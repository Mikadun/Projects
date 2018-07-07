#include <iostream>
using namespace std;

const int INF = 1000000;

int main()
{
	int n, m;
	cin >> n >> m;
	int g[n][n];

	for( int i = 0; i < n; i++ )
	{
		for( int j = 0; j < n; j++ )
		{
			g[i][j] = INF;
		}
		g[i][i] = 0;
	}

	for( int i = 0; i < m; i++ )
	{
		int first, second, weight;
		cin >> first >> second >> weight;
		first--; second--;
		g[first][second] = weight;
		g[second][first] = weight;
	}

	for( int k = 0; k < n; k++ )
		for( int i = 0; i < n; i++ )
			for( int j = 0; j < n; j++ )
				g[i][j] = min( g[i][j], g[i][k] + g[k][j] );

	int result = 0;

	for( int i = 0; i < n; i++ )
	{
		for( int j = 0; j < n; j++ )
			if( g[i][j] != INF )
				result = max( result, g[i][j] );
	}

	if( result != INF )
		cout << result;
	else
		cout << 0;

}
