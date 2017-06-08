#include <iostream>
#include <fstream>
using namespace std;
int main()
{ 
  ifstream fin("diploma.in");
  ofstream fout("diploma.out");
  unsigned long long int x;
  unsigned long int W, H, N;
  fin >> W >> H >> N;
  unsigned long long int a = 1;
  unsigned long long int b = 10e13;
  while(b - a >= 1) {
    x = (a + b) / 2;  
    if((x / W) * (x / H) < N){
      a = x + 1;
    }
    else{
      b = x;
    }
  }
  fout << a;
  fin.close();
  fout.close();
}
