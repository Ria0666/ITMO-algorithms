#include "iostream"
#include <math.h>

typedef long long ll;
using namespace std;

int main() {
    ll X, Y, start, end, i, j, z, md, a, b, count_steps, last, point;
    int cnt = 0;
    cin >> X >> Y;

    ll nums[60];
    for (i = 0; i < 60; i++) {
        nums[i] = pow(2, i + 1) - 1;
    }
    start = 0;
    end = 0;
    for (i = 0; i <= 60; i++) {
        if (nums[i] >= X) {
            start = i;
            break;
        }
    }
    for (i = 0; i < 60; i++) {
        if (nums[i] >= Y) {
            end = i;
            break;
        }
    }
    for (i = start; i <= end; i++) {
        a = nums[i];
        b = a + 1;
        md = nums[i] - nums[i - 1] + nums[i - 2];
        count_steps = b / 8;
        last = 0;
        for (j = i; j > 1; j--) {
            a = a - nums[j - 1] + nums[j - 2];
            if (a >= X && a <= Y) {
                cnt++;
            }
        }
        for (z = 0; z < int(log2(b/8)); z++) {
            for (j = 2; j <= count_steps; j *= 2) {
                last = j;
                point = j + md;
                if (point >= X && point <= Y)
                    cnt++;
            }
            count_steps = count_steps / 2;
            md = md + last;

        }

    }
    cout << cnt;
}

