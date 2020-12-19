#include <iostream>

using namespace std;

long long int fib(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    long long int f[n + 1];
    f[0] = 0;
    f[1] = 1;

    for (int i = 2; i <= n; i++) {
        f[i] = f[i - 1] + f[i - 2];
    }

    return f[n];

}

int main() {

    cout << fib(5) << endl;

    return 0;
}
