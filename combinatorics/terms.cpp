#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct t_container
{
	int* data;
	int size;
	t_container( int _size ) { size = _size; data = new int[size]{0}; }
};

vector<t_container> result;

void term( int left, int high, int depth, t_container* used )
{
	if( left == 0 )
	{
		t_container temp( depth );
		for( int i = 0; i < depth; i++ )
			temp.data[i] = used->data[i];
		sort( temp.data, temp.data + depth );
		result.push_back( temp );
		return;
	}

	high = min( left, high );
	for( int i = 1; i <= high; i++ )
	{
		used->data[depth] = i;
		term( left - i, i, depth + 1, used );
	}
	used->data[depth] = 0;
}

bool cmp_function( t_container a, t_container b )
{
  int min_size = min( a.size, b.size );
  int i = 0;
  while( a.data[i] == b.data[i] )
    i++;
  
  return a.data[i] > b.data[i];
}

int main()
{
	int n;
	cin >> n;
	
	t_container used(n);

	term( n, n, 0, &used );
	sort( result.begin(), result.end(), cmp_function );
	//cout << result.size();
	for( int i = 0; i < result.size(); i++ )
	{
	  for( int j = 0; j < result[i].size; j++ )
	    cout << result[i].data[j] << " ";
    cout << endl;
	}
}