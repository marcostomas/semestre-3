#include <stdio.h>
#include <stdlib.h>

union float_bytes
{
    float f;
    char b[sizeof(float)];
};

int float2bytes(float f)
{
    // https://stackoverflow.com/questions/41862038/get-raw-data-bytes-of-a-constant-float-value-using-define-in-c

    union float_bytes fb = {f};
    for (int i = 0; i < sizeof(float); i++)
        printf("%hhx\n", fb.b[i]);
}

float f1 = 1.2347e+39;
float f2 = 12347e+34;
float f11 = 1.2347e-38;
float f12 = 1.2347e-39;
float f13 = 1.2347e-42;
float f14 = 1.2347e-45;
float f15;

void main(void)
{
    puts("float1, float2");
    printf("%f, %f\n", f1, f2);
    printf("%X, %X\n", (int)f1, (int)f2);
    puts("float1");
    float2bytes(f1);
    puts("float2");
    float2bytes(f2);
    puts("f11, f12");
    printf("%f, %f\n", f11, f12);
    printf("%e, %e\n", f11, f12);
    printf("%X, %X\n", (int)f11, (int)f12);
    float2bytes(f11);
    puts("f13, f14");
    printf("%f, %f\n", f13, f14);
    printf("%e, %e\n", f13, f14);
    printf("%X, %X\n", (int)f13, (int)f14);
    float2bytes(f14);
    f15 = 2.0 * f14;
    puts("f15, f15");
    printf("%f, %f\n", f15, f15);
    printf("%e, %e\n", f15, f15);
    printf("%X, %X\n", (int)f15, (int)f15);
    float2bytes(f15);
}