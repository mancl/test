// 递归实现
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

void Merge(int* SR, int* TR1, int s, int m, int t)
{
	int i, j, k;
	for (i = s, j = m + 1; s <= m && j <= t; ++i)
	{
		if (SR[s] < SR[j])
			TR1[i] = SR[s++];
		else
			TR1[i] = SR[j++];
	}
	if (s <= m)
	{
		for (k = 0; k <= m - s; ++k)
			TR1[i + k] = SR[s + k];
	}
	if (j <= t)
	{
		for (k = 0; k <= t - j; ++k)
			TR1[i + k] = SR[j + k];
	}
}

void MSort(int* SR, int* TR1, int s, int t)
{
	int m;
	int TR2[MAXSIZE];
	if (s == t)
		TR1[s] = SR[s];
	else
	{
		m = (s + t) / 2;
		MSort(SR, TR2, s, m);
		MSort(SR, TR2, m + 1, t);
		Merge(TR2, TR1, s, m, t);
	}
}

void MergeSort(int* array, int n)
{
	MSort(array, array, 0, n - 1);
}

// 非递归实现
void Merge_(int SR[], int TR[], int s, int m, int t)
{
	int i, j, k;
	for (i = s, j = m + 1; s <= m && j <= t; ++i)
	{
		if (SR[s] < SR[j])
			TR[i] = SR[s++];
		else
			TR[i] = SR[j++];
	}
	if (s <= m)
	{
		for (k = 0; k <= m - s; ++k)
			TR[i + k] = SR[s + k];
	}
	if (j <= t)
	{
		for (k = 0; k <= t - j; ++k)
			TR[i + k] = SR[j + k];
	}
}

void MergePass(int SR[], int TR[], int s, int t)
{
	int i = 0;
	int j;
	// while (i <= t - 2 * s - 1)
	while (i+2*s-1<= t)
	{
		Merge_(SR, TR, i, i + s -1, i + 2 * s - 1);
		i = i + 2 *s;
	}
	if (i +s -1 < t)
		Merge_(SR, TR, i, i + s-1, t);
	else
		for (j = i; j <= t; ++j)
			TR[j] = SR[j];
}

void MergeSort_(int array[], int n)
{
	int * TR = (int *)malloc(n * sizeof(int));
	int k = 1;
	while (k < n - 1)
	{
		MergePass(array, TR, k, n - 1);
		k = 2 * k;
		MergePass(TR, array, k, n - 1);
		k = 2 * k;
	}
	free(TR);
}

int main(int argc, char const *argv[])
{
	int a[9]={5,1,3,9,7,4,8,6,2};
	MergeSort_(a,9);
	int i;
	for (i = 0; i < 9; ++i)
	{
		printf("%d\t",a[i]);
	}
	return 0;
}