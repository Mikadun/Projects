#include <iostream>

using namespace std;

typedef unsigned long t_len;

t_len GCD( t_len a, t_len b ) // Maximum devider of two numbers
{
	if( a > b )
		swap( a, b );
	return a == 0 ? b : GCD( a, b % a );
}

t_len LCM( t_len a, t_len b ) // Minimum number, that divides by that numbers
{
	return (int) a * b / GCD( a, b );
}

t_len cycle_length( int* permutation, bool* used, int n )
{
	int i = 0;
	while( used[i] ) 
		i++;

	int length = 0;
	while( !used[i] )
	{
		used[i] = true;
		i = permutation[i];
		length++;
	}

	return length;
}

bool contain_not_used( bool* container, int size )
{
	for( int i = 0; i < size; i++ )
		if( !container[i] )
			return true;

	return false;
}

int main()
{
	int n;
	cin >> n;
	int *permutation = new int[n];
	bool *used = new bool[n]{false};
	for( int i = 0; i < n; i++ )
	{
		cin >> permutation[i];
		permutation[i]--;
	}

	t_len lcm = 1;
	while( contain_not_used( used, n ) )
		lcm = LCM( lcm, cycle_length( permutation, used, n ) );

	cout << lcm;
}