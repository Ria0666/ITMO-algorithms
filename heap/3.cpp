#include <iostream>
using namespace std;

void heapf(long long int a[], int n, int i) {
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;
    if (l < n && a[l] > a[largest])
        largest = l;
    if (r < n && a[r] > a[largest])
        largest = r;
    if (largest != i) {
        long long int c = a[i];
        a[i]=a[largest];
        a[largest]=c;
        heapf(a, n, largest);
    }
}
void heap(long long int a[], long long int n)
{
    for (long long int i = n / 2 - 1; i >= 0; i--)
        heapf(a, n, i);
    for (int i=n-1; i>=0; i--)
    {
        long long int c = a[i];
        a[i]=a[0];
        a[0]=c;
        heapf(a, i, 0);
    }
}
int main() {
    long long int n;
    cin>>n;
    long long int a[n];
    for (int i=0;i<n;++i) {
      cin>>a[i];
    }
    heap(a, n);
    for (int i=0;i<n;++i) {
        cout<<a[i]<<" ";
    }
}
