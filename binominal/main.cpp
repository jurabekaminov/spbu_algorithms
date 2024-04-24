#include <bits/stdc++.h>
using namespace std;


double binom(int n,int k)
{
  if (k>n/2) k=n-k;
  if (k==1)  return n;
  if (k==0)  return 1;
  double r=1;
  for (int i=1; i<=k;++i) {
    r*=n-k+i;
    r/=i;
  }
  return ceil(r-0.2);
}


int main()
{
    int n, k;
    cin >> n >> k;
       cout << binom(n,k) << endl;
       return 0;
}

