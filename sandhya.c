#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Convert a string representing a number in a given base to a long long integer
long long decode_base(const char *value_str, int base) {
    long long result = 0;
    while (*value_str) {
        char digit = *value_str;
        int val;
        if (digit >= '0' && digit <= '9')
            val = digit - '0';
        else if (digit >= 'a' && digit <= 'z')
            val = digit - 'a' + 10;
        else if (digit >= 'A' && digit <= 'Z')
            val = digit - 'A' + 10;
        else
            val = 0;
        result = result * base + val;
        value_str++;
    }
    return result;
}

// Perform Lagrange interpolation to find f(0)
long long lagrange_interpolation(int *x, long long *y, int k) {
    long double result = 0.0;

    for (int i = 0; i < k; i++) {
        long double term = (long double)y[i];
        for (int j = 0; j < k; j++) {
            if (i != j) {
                term *= ((long double)x[j]) / (x[j] - x[i]);
            }
        }
        result += term;
    }

    return llround(result);
}

int main() {
    // Example Test Case 1
    int k1 = 3;
    int x1[] = {1, 2, 3};
    const char *bases1[] = {"10", "2", "10"};
    const char *values1[] = {"4", "111", "12"};

    long long y1[3];
    for (int i = 0; i < k1; i++) {
        int base = atoi(bases1[i]);
        y1[i] = decode_base(values1[i], base);
    }

    long long secret1 = lagrange_interpolation(x1, y1, k1);
    printf("Secret from Test Case 1: %lld\n", secret1);

    // Example Test Case 2 (only 7 roots used here)
    int k2 = 7;
    int x2[] = {1, 2, 3, 4, 5, 6, 7};
    const char *bases2[] = {
        "6", "15", "15", "16", "8", "3", "3"
    };
    const char *values2[] = {
        "13444211440455345511",
        "aed7015a346d63",
        "6aeeb69631c227c",
        "e1b5e05623d881f",
        "316034514573652620673",
        "2122212201122002221120200210011020220200",
        "20120221122211000100210021102001201112121"
    };

    long long y2[7];
    for (int i = 0; i < k2; i++) {
        int base = atoi(bases2[i]);
        y2[i] = decode_base(values2[i], base);
    }

    long long secret2 = lagrange_interpolation(x2, y2, k2);
    printf("Secret from Test Case 2: %lld\n", secret2);

    return 0;
}
