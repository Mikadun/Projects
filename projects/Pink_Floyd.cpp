#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int n, m, count;
	cin >> n >> m >> count;

	int g[n][n], g_next[n][n], time[n][n], flight[count];

	const int INF = -1000000000;

	for( int i = 0; i < n; i++ ) // Initialization
	{
		for( int j = 0; j < n; j++ )
		{
			g[i][j] = INF;
			g_next[i][j] = i;
			time[i][j] = 0;
		}
		g[i][i] = 0;
	}

	for( int i = 0; i < m; i++ ) // Reading graph
	{
		int from, to, w;
		cin >> from >> to >> w;
		g[ from - 1 ][ to - 1 ] = w;
		time[ from - 1 ][ to - 1 ] = i + 1;
	}

	for( int i = 0; i < count; i++ )
		cin >> flight[i];

	for( int k = 0; k < n; k++ ) // Floyd-Warshall
		for( int i = 0; i < n; i++ )
			for( int j = 0; j < n; j++ )
				if( g[i][k] != INF && g[k][j] != INF)
					if( g[i][j] < g[i][k] + g[k][j] )
					{
						g[i][j] = g[i][k] + g[k][j];
						g_next[i][j] = k;
					}


	for( int i = 0; i < n; i++ ) // Check for infinity cycle
		for( int j = 0; j < n; j++ )
			for( int k = 0; k < n; k++ )
				if( g[i][k] != INF && g[k][j] != INF && g[k][k] > 0 )
					g[i][j] = -INF;


	vector<int> result;

	bool is_infinity = false;

	for( int i = 0; i < count - 1; i++ ) // Print result
	{
		vector<int> path;
		int u = flight[i] - 1, v = flight[i + 1] - 1;
		if( g[u][v] != INF )
		{
			while( v != u ) 
			{
				if( g[u][v] == -INF ) // If any infinity cycle on the path found
				{
					cout << "infinitely kind";
					return 0;
				}
				path.push_back( v );
				v = g_next[u][v];
			}
			path.push_back( u );
		}

		for( int j = path.size() - 1; j > 0; j-- )
		{
			result.push_back( time[ path[j] ][ path[j - 1] ] );
		}
	}

	cout << result.size() << endl;
	for( int i = 0; i < result.size(); i++ )
		cout << result[i] << " ";
}
