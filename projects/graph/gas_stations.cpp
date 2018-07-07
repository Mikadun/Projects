#include <iostream>

using namespace std;

const int MAX_SIZE = 100;
const int INF = 100000;

bool used[ MAX_SIZE ];
int g[ MAX_SIZE ][ MAX_SIZE ];
int weights[ MAX_SIZE ];
int d[ MAX_SIZE ];

void dijkstra( int start, int n )
{
	d[ start ] = 0;

	for( int i = 0; i < n; i++ )
	{
		int v = -1;
		for( int j = 0; j < n; j++ )
		{
			if( !used[ j ] && ( v == -1 || d[ j ] < d[ v ] ) )
				v = j;
		}

		if( d[ v ] == INF )
			return;

		used[ v ] = true;

		for( int j = 0; j < n; j++ )
		{
			if( g[ v ][ j ] != -1 && d[ j ] > d[ v ] + g[ v ][ j ] )
			{
				d[ j ] = d[ v ] + g[ v ][ j ];
			}
		}
	}

}

int main()
{
	int n, m;
	cin >> n;

	for( int i = 0; i < n; i++ )
	{
		cin >> weights[ i ];
		d[ i ] = INF;
		for( int j = 0; j < n; j++ )
			g[ i ][ j ] = -1;
	}

	cin >> m;
	for( int i = 0; i < m; i++ )
	{
		int first, second;
		cin >> first >> second;
		first--; second-- ;
		g[ first ][ second ] = weights[ first ];
		g[ second ][ first ] = weights[ second ];
	}

	dijkstra( 0, n );

	if( d[ n - 1 ] != INF )
		cout << d[ n - 1 ];
	else
		cout << -1;

	return 0;
}