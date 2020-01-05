#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_LENGTH 10

//1、时间复杂度：O(n2)
//2、空间复杂度：O(1)
//3、非稳定排序
//4、原地排序
int sort_select(int *a, int size)
{
	int idx, i, j;
	int tmp = 0;

	if (!a)
		return -1;
	if (size == 1)
		return 0;

	for (i = 0; i < size - 1; i++) {
		idx = i;
		for (j = i + 1; j < size; j++) {
			if (a[j] < a[idx])
				idx = j;
		}
		tmp = a[i];
		a[i] = a[idx];
		a[idx] = tmp;
	}
	printf("%s after sort:\n", __func__);
	for (i = 0; i < size; i++)
		printf(" %d ", a[i]);
	printf("\n\n");
	return 0;
}

//1、时间复杂度：O(n2)
//2、空间复杂度：O(1)
//3、稳定排序
//4、原地排序

int sort_insert(int *a, int size)
{
	int idx, i, j, k;
	int tmp = 0;

	if (!a)
		return -1;
	if (size == 1)
		return 0;

	for (i = 1; i < size; i++) {
		for (j = i - 1; j >= 0; j--) {
			if (a[j] <= a[i])
				break;
		}
		tmp = a[i];
		for (k = i; k > j + 1; k--)
			a[k] = a[k - 1];
		a[j + 1] = tmp;
	}
	printf("%s after sort:\n", __func__);
	for (i = 0; i < size; i++)
		printf(" %d ", a[i]);
	printf("\n\n");
	return 0;
}

//1、时间复杂度：O(n2)
//2、空间复杂度：O(1)
//3、稳定排序
//4、原地排序
int sort_bubble(int *a, int size)
{
	int idx, i, j, k;
	int tmp = 0;

	if (!a)
		return -1;
	if (size == 1)
		return 0;

	for (i = 0; i < size - 1; i++) {
		for (j = 0; j < size - 1 - i; j++) {
			if (a[j] > a[j + 1]) {
				tmp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tmp;
			}
		}
	}
	printf("%s after sort:\n", __func__);
	for (i = 0; i < size; i++)
		printf(" %d ", a[i]);
	printf("\n\n");
	return 0;
}

int sort_bubble_optimize(int *a, int size)
{
	int idx, i, j, k;
	int tmp, swap;

	if (!a)
		return -1;
	if (size == 1)
		return 0;

	for (i = 0; i < size - 1; i++) {
		swap = 0;
		for (j = 0; j < size - 1 - i; j++) {
			if (a[j] > a[j + 1]) {
				tmp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tmp;
				swap = 1;
			}
		}
		if (swap == 0)
			break;
	}
	printf("%s after sort:\n", __func__);
	for (i = 0; i < size; i++)
		printf(" %d ", a[i]);
	printf("\n\n");
	return 0;
}


static void init_array(int *a, int size)
{
	int i;

	srand((unsigned int)time(NULL));
	for (i = 0; i < size; i++)
		a[i] = rand() % 100;

	printf("before sort:\n");
	for (i = 0; i < ARRAY_LENGTH; i++)
		printf(" %d ", a[i]);
	printf("\n\n");
}

int main(void)
{
	int a[ARRAY_LENGTH] = {0};
	int i;

	init_array(a, ARRAY_LENGTH);

	sort_select(a, ARRAY_LENGTH);
	sort_insert(a, ARRAY_LENGTH);
	sort_insert(a, ARRAY_LENGTH);
	sort_bubble(a, ARRAY_LENGTH);
	sort_bubble_optimize(a, ARRAY_LENGTH);

	return 0;
}
