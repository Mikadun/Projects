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
 
int main()
{
    int n;
    std::cin >> n;
    int *permut = new int[n];
    for( int i = 0; i < n; i++ )
        std::cin >> permut[i];
 
    next_permut( permut, n );
    for( int i = 0; i < n; i++ )
        std::cout << permut[i] << " ";
    return 0;
}