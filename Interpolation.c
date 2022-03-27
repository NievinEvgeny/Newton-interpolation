#include <stdio.h>
#define RFACTOR (1.24733)

// 4 3 0 0 2 4 3 9 4 16 1 2.5 3.5

void comb_sort(double* x, double* y, int size)
{
    int gap = size;
    int swaps = 1;
    int i, j;

    while (gap > 1 || swaps)
    {
        gap = (int)(gap / RFACTOR);
        if (gap < 1)
            gap = 1;
        swaps = 0;
        for (i = 0; i < size - gap; ++i)
        {
            j = i + gap;
            if (x[i] > x[j])
            {
                double tmp = x[i];
                x[i] = x[j];
                x[j] = tmp;
                tmp = y[i];
                y[i] = y[j];
                y[j] = tmp;
                swaps = 1;
            }
        }
    }
}

void newton(int numOfKnownPoints, double* x, double* y, int i)
{
    // CalcDivDiff - To calculate required DivDiffs
    // PolyDivDiff - To save required DivDiffs for polynomial
    double temp1, temp2;
    double CalcDivDiff[numOfKnownPoints], PolyDivDiff[numOfKnownPoints];

    PolyDivDiff[0] = y[0];

    for (int j = 0; j < numOfKnownPoints; j++) // Fill in the array for polynomial values
    {
        CalcDivDiff[j] = y[j];
    }

    for (int j = 0; j < numOfKnownPoints - 1; j++) // calculation of divided differences
    {
        temp2 = CalcDivDiff[0];
        for (int k = j + 1; k < numOfKnownPoints; k++)
        {
            temp1 = (CalcDivDiff[k - j] - temp2) / (x[k] - x[k - j - 1]);
            temp2 = CalcDivDiff[k - j];
            CalcDivDiff[k - j - 1] = temp1;
            if (k == j + 1) // first iteration (value required for polynomial)
            {
                PolyDivDiff[j + 1] = temp1;
            }
        }
    }

    y[i] = PolyDivDiff[0];

    for (int j = 1; j < numOfKnownPoints; j++)
    {
        double calc = PolyDivDiff[j];
        for (int k = j; k > 0; k--)
        {
            calc *= (x[i] - x[k - 1]);
        }
        y[i] += calc;
    }
}

int main()
{
    FILE* out;
    out = fopen("output.txt", "w");

    int numOfKnownPoints, numOfUnknownPoints, numOfPoints;
    printf("Введите количество узлов интерполяции:\n");
    scanf("%d", &numOfKnownPoints);

    printf("Введите количество неизвестных точек:\n");
    scanf("%d", &numOfUnknownPoints);

    numOfPoints = numOfKnownPoints + numOfUnknownPoints;

    double x[numOfPoints], y[numOfPoints];

    for (int i = 0; i < numOfKnownPoints; i++)
    {
        printf("Введите значения узла (x%d y%d):\n", i + 1, i + 1);
        scanf("%lf %lf", &x[i], &y[i]);
    }
    for (int i = numOfKnownPoints; i < numOfPoints; i++)
    {
        printf("Введите неизвестный x:\n");
        scanf("%lf", &x[i]);
        y[i] = 0;
    }

    for (int i = numOfKnownPoints; i < numOfPoints; i++) // number of unknown y
    {
        newton(numOfKnownPoints, x, y, i);
    }

    comb_sort(x, y, numOfPoints);

    for (int i = 0; i < numOfPoints; i++)
    {
        fprintf(out, "%.6lf %.6lf\n", x[i], y[i]);
    }
}