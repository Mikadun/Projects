#include <iostream>
#include <algorithm>
using namespace std;

bool cmp(int *a, int *b) { return a[0] < b[0]; }

int main()
{
	int n, m;
	cin >> n >> m;
	int times[n][n];
	int **edges = new int* [m];
	for( int i = 0; i < m; i++ )
	{
		edges[i] = new int[3];
		cin >> edges[i][1] >> edges[i][2];
		edges[i][1]--; edges[i][2]--; edges[i][0] = 1;
	}

	sort(edges, edges + m, cmp);
  
	int trees[n];
	for( int i = 0; i < n; i++ )
		trees[i] = i;

	int result[n - 1][2];
	int idx = 0;
	for( int i = 0; i < m; i++ )
	{
		int *edge = edges[i];
		if( trees[ edge[1] ] != trees[ edge[2] ] )
		{
			int new_tree = trees[ edge[1] ],
				old_tree = trees[ edge[2] ];
			result[idx][0] = edge[1];
			result[idx][1] = edge[2];
			idx++;
			for ( int j = 0; j < n; j++ )
				if( trees[j] == old_tree )
					trees[j] = new_tree;
		}
	}
	for( int i = 0; i < n - 1; i++ )
	{
		cout << result[i][0] + 1 << " " << result[i][1] + 1 << endl;
	}

}
