#include <iostream>
#include <vector>
using namespace std;

int main() {
  int n, m;
  cin >> n >> m;
  vector<pair<int, int>> matrix[n];
  
  for( int i = 0; i < m; i++ )
  {
    int a, b, w;
    cin >> a >> b >> w;
    a--; b--;
    matrix[a].push_back( make_pair(b, w) );
    matrix[b].push_back( make_pair(a, w) );
  }
  
  bool used[n];
  for( int i = 0; i < n; i++ ) used[i] = false;
  used[0] = true;
  int result = 0;
  
  for( int i = 0; i < n - 1; i++ )
  {
    int temp[3];
    temp[2] = 1000000;
    for( int j = 0; j < n; j++ )
    {
      if( used[j] )
      {
        for( auto k = matrix[j].begin(); k != matrix[j].end(); k++ )
        {
          if( !used[k->first] && k->second < temp[2])
          {
            temp[2] = k->second;
            temp[0] = j;
            temp[1] = k->first;
          }
        }
      }
    }
    used[temp[1]] = true;
    result += temp[2];
  }
  cout << result;
  
}
