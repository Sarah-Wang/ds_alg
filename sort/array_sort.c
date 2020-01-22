#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_LENGTH 20
//#define DEBUG

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
	int i, j, k;
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

static int insert_for_shell(int *a, int size, int idx, int gap)
{
	int i, j, k, tmp;

	for (i = idx; i < size; i += gap) {
		for (j = i - gap; j >= 0; j -= gap) {
			if (a[j] <= a[i])
				break;
		}
		tmp = a[i];
		for (k = i; k > j + gap; k -= gap)
			a[k] = a[k - gap];
		a[j + gap] = tmp;
	}
	return 0;
}

//1. 时间复杂度：O(nlogn)
//2. 空间复杂度：O(1)
//3. 非稳定排序
//4. 原地排序
int sort_shell(int *a, int size)
{
	int i, j, k;
	int gap;

	if (!a)
		return -1;
	if (size == 1)
		return 0;

	for (gap = size / 2; gap > 0; gap /= 2) {
		for (i = 0; i < gap; i++)
			insert_for_shell(a, size, i + gap, gap);
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
	int i, j, k;
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
	int i, j, k;
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

static int merge(int *a1, int l1, int *a2, int l2, int *b)
{
	int *p1 = a1, *p2 = a2;
	int len = l1 + l2;
	int i = 0, j = 0, k = 0;

	while (i < l1 && j < l2) {
		if (a1[i] < a2[j])
			b[k++] = a1[i++];
		else
			b[k++] = a2[j++];
	}
	while (i < l1)
		b[k++] = a1[i++];
	while (j < l2)
		b[k++] = a2[j++];

#ifdef DEBUG
	printf("a1:\n");
	for (i = 0; i < l1; i++)
		printf("%d ", a1[i]);
	printf("\n");

	printf("a2:\n");
	for (i = 0; i < l2; i++)
		printf("%d ", a2[i]);
	printf("\n");

	printf("b:\n");
	for (i = 0; i < l1 + l2; i++)
		printf("%d ", b[i]);
	printf("\n");
#endif
	return 0;
}

static void test_merge(void)
{
	int a1[6] = {1, 3, 4, 5, 7, 10};
	int a2[3] = {4, 6, 9};
	int a3[9] = {0};

	merge(a1, 6, a2, 3, a3);
}

static int __merge_sort(int *a, int len, int *b)
{
	int mid = len / 2;
	int i;

	if (len == 1)
		return 0;

	__merge_sort(a, mid, b);
	__merge_sort(a + mid, len - mid, b);
	merge(a, mid, a + mid, len - mid, b);
	for (i = 0; i < len; i++)
		a[i] = b[i];

	return 0;
}

//1、时间复杂度：O(nlogn)
//2、空间复杂度：O(n)
//3、稳定排序
//4、非原地排序
static int sort_merge_recursive(int *a, int size)
{
	int i;
	int *b = NULL;

	b = calloc(1, sizeof(int) * size);
	if (!b) {
		printf("memory lack\n");
		return -1;
	}

	__merge_sort(a, size, b);

	free(b);
	b = NULL;

	printf("%s after sort:\n", __func__);
	for (i = 0; i < size; i++)
		printf(" %d ", a[i]);
	printf("\n\n");
	return 0;
}

static int sort_merge_non_recursive(int *a, int size)
{

}

static int __quick_end(int *a, int size)
{
	int i, j, tmp;

	if (!a)
		return -1;
	if (size == 1)
		return 0;

	for (i = 0, j = 0; j < size; j++) {
		if (a[j] < a[size - 1]) {
			tmp = a[i];
			a[i] = a[j];
			a[j] = tmp;
			i++;
		}
	}
	tmp = a[i];
	a[i] = a[size - 1];
	a[size - 1] = tmp;
	if (i > 0)
		__quick_end(&a[0], i);
	if (i + 1 < size)
		__quick_end(&a[i + 1], size - i - 1);
}

static int __quick_start(int *a, int size)
{
	int i, j, tmp, istop, jstop;

	if (!a)
		return -1;
	if (size == 1)
		return 0;

	istop = 0;
	jstop = 0;
	for (i = 0, j = size - 1; i <= j;) {
		if (a[i] <= a[0])
			i++;
		else
			istop = 1;

		if (a[j] >= a[0])
			j--;
		else
			jstop = 1;
		if ((istop == 1) && (jstop == 1)) {
			tmp = a[i];
			a[i] = a[j];
			a[j] = tmp;
			i++;
			j--;
			istop = 0;
			jstop = 0;
		}
	}

	tmp = a[j];
	a[j] = a[0];
	a[0] = tmp;
	if (j > 0)
		__quick_start(&a[0], j);
	if (j + 1 < size)
		__quick_start(&a[j + 1], size - j - 1);
}

/* //not correct */
/* static int __quick_rand(int *a, int size) */
/* { */
/* 	int i, j, tmp, istop, jstop; */
/* 	int k, base; */


/* 	if (!a) */
/* 		return -1; */
/* 	if (size == 1) */
/* 		return 0; */

/* 	/1* srand(time(NULL)); *1/ */
/* 	k = rand() % size; */
/* 	base = a[k]; */
/* 	printf("k: %d\n", k); */

/* 	istop = 0; */
/* 	jstop = 0; */
/* 	for (i = 0, j = size - 1; i <= j;) { */
/* 		if (a[i] <= base) */
/* 			i++; */
/* 		else */
/* 			istop = 1; */

/* 		if (a[j] >= base) */
/* 			j--; */
/* 		else */
/* 			jstop = 1; */
/* 		if ((istop == 1) && (jstop == 1)) { */
/* 			tmp = a[i]; */
/* 			a[i] = a[j]; */
/* 			a[j] = tmp; */
/* 			i++; */
/* 			j--; */
/* 			istop = 0; */
/* 			jstop = 0; */
/* 		} */
/* 	} */

/* 	tmp = a[j]; */
/* 	a[j] = base; */
/* 	a[k] = tmp; */
/* 	if (j > 0) */
/* 		__quick_rand(&a[0], j); */
/* 	if (j + 1 < size) */
/* 		__quick_rand(&a[j + 1], size - j - 1); */
/* } */


/* 1、时间复杂度：O(nlogn) */
/* 2、空间复杂度：O(logn) */
/* 3、非稳定排序 */
/* 4、原地排序 */
static int sort_quick(int *a, int size)
{
	int i;

	/* __quick_end(a, size); */
	__quick_start(a, size);
	/* __quick_rand(a, size); */

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
	for (i = 0; i < size; i++)
		printf(" %d ", a[i]);
	printf("\n");
}

int main(void)
{
	int a[ARRAY_LENGTH] = {0};
	int i;

	init_array(a, ARRAY_LENGTH);
	sort_select(a, ARRAY_LENGTH);

	init_array(a, ARRAY_LENGTH);
	sort_insert(a, ARRAY_LENGTH);

	init_array(a, ARRAY_LENGTH);
	sort_shell(a, ARRAY_LENGTH);

	init_array(a, ARRAY_LENGTH);
	sort_bubble(a, ARRAY_LENGTH);

	init_array(a, ARRAY_LENGTH);
	sort_bubble_optimize(a, ARRAY_LENGTH);

	/* test_merge(); */
	init_array(a, ARRAY_LENGTH);
	sort_merge_recursive(a, ARRAY_LENGTH);

	init_array(a, ARRAY_LENGTH);
	sort_quick(a, ARRAY_LENGTH);

	return 0;
}
