#include <iostream>
#include <algorithm>
using namespace std;

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
  
	int trees[n];
	for( int i = 0; i < n; i++ )
		trees[i] = i;

	int result = 0;
	for( int i = 0; i < m; i++ )
	{
		int *edge = edges[i];
		if( trees[ edge[1] ] != trees[ edge[2] ] )
		{
			int new_tree = trees[ edge[1] ],
				old_tree = trees[ edge[2] ];
			result += edge[0];
			for ( int j = 0; j < n; j++ )
				if( trees[j] == old_tree )
					trees[j] = new_tree;
		}
	}
	cout << result << endl;

}
