#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;

int *p, *r = NULL;

void make_set_dsu( int x ) { p[x] = x; }

int find_dsu( int x ) { return x == p[x] ? x : find_dsu( p[x] ); }

void union_dsu( int x, int y )
{
	x = find_dsu( x );
	y = find_dsu( y );
	if( r[x] < r[y] )
		p[x] = y;
	else
	{
		p[y] = x;
		if( r[x] == r[y] )
			r[x]++;
	}
}

bool cmp(int *a, int *b) { return a[0] < b[0]; }

int main()
{
	int n, m;
	cin >> n >> m;
	int **edges = new int* [m];
	for( int i = 0; i < m; i++ )
	{
		edges[i] = new int[3];
		cin >> edges[i][1] >> edges[i][2] >> edges[i][0];
		edges[i][1]--; edges[i][2]--;
	}

	sort(edges, edges + m, cmp);
	
	p = new int[n];
	r = new int[n];
	for( int i = 0; i < n; i++ ){
		p[i] = i;
	}

	int result = 0;
	for( int i = 0; i < m; i++ )
	{
		int *edge = edges[i];
		if( find_dsu(edge[1]) != find_dsu(edge[2]) )
		{
			result += edge[0];
			union_dsu( edge[1], edge[2] );
		}
	}
	cout << result << endl;
	
}
