#include <iostream>
#include <algorithm>
 
using namespace std;
 
void next_permut( int* permutation, int n )
{
  if( n == 1 )
    return;
  int i = n - 2;
  while( permutation[i] > permutation[i + 1] && i > 0 )
    i--;
   
  int idx = -1;
  for( int j = i + 1; j < n; j++ )
    if( ( permutation[idx] > permutation[j] || idx == -1 ) && permutation[j] > permutation[i] )
      idx = j;
  
  int temp = permutation[idx];
  permutation[idx] = permutation[i];
  permutation[i] = temp;
 
  std::sort( permutation + i + 1, permutation + n );
}

int factorial( int n ) // Below 10 is ok
{
  if( n == 1 )
    return 1;
  return n * factorial( n - 1 );
}
 
int main()
{
    int n;
    std::cin >> n;
    int *permut = new int[n];
    for( int i = 0; i < n; i++ )
        permut[i] = i + 1;
 
    for( int i = 0; i < factorial(n); i++ )
    {
      for( int j = 0; j < n; j++ )
        cout << permut[j];
      cout << endl;
      next_permut( permut, n );
    }
    return 0;
}