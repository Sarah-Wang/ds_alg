#include <stdio.h>

#define ARRAY_LEN 17



int sorted_search(int *arr, int len, int target)
{
	if (!arr || len < 1)
		return -1;

	int i;

	for (i = 0; i < len; i++) {
		if (arr[i] == target)
			return i;
	}
	return -1;
}

int __binary_search_recursive(int *arr, int left, int right, int target)
{
	if (left > right)
		return -1;

	int mid = left + (right - left) / 2;

	if (arr[mid] == target)
		return mid;
	if (arr[mid] < target)
		return __binary_search_recursive(arr, mid + 1, right, target);
	else
		return __binary_search_recursive(arr, left, mid - 1, target);
}

int binary_search_recursive(int *arr, int len, int target)
{
	if (!arr || len < 1)
		return -1;

	return __binary_search_recursive(arr, 0, len - 1, target);
}

int binary_search(int *arr, int len, int target)
{
	if (!arr || len < 1)
		return -1;

	int left = 0;
	int right = len - 1;
	int mid = 0;

	while (left <= right) {
		mid = (left + right) / 2;
		if (arr[mid] == target)
			return mid;
		if (arr[mid] < target)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return -1;
}

int __insert_search(int *arr, int l, int r, int target)
{
	if (l > r)
		return -1;

	int mid = 0;

	mid = l + (target - arr[l]) / (arr[r] - arr[l]) * (r - l);
	if (arr[mid] == target)
		return mid;
	if (arr[mid] > target)
		return __insert_search(arr, l, mid - 1, target);
	else
		return __insert_search(arr, mid + 1, r, target);
}

int insert_search(int *arr, int len, int target)
{
	if (!arr || len < 1)
		return -1;

	return __insert_search(arr, 0, len - 1, target);
}

int gen_sorted_array(int *arr, int len)
{
	if (!arr || len < 1)
		return -1;

	int i;

	printf("original array:\n");
	for (i = 0; i < len; i++) {
		arr[i] = i * 2;
		printf("%d ", arr[i]);
	}
	printf("\n");
	return 0;
}

int main(void)
{
	int arr[ARRAY_LEN] = {0};
	int idx = 0;
	int target = 0;
	int ret = 0;

	ret = gen_sorted_array(arr, ARRAY_LEN);
	if (ret)
		return -1;

	target = arr[9];
	idx = sorted_search(arr, ARRAY_LEN, target);
	printf("%d is in position %d\n", target, idx);

	target = 9;
	idx = sorted_search(arr, ARRAY_LEN, target);
	printf("%d is in position %d\n", target, idx);

	target = arr[9];
	idx = binary_search(arr, ARRAY_LEN, target);
	printf("%d is in position %d\n", target, idx);

	target = 9;
	idx = binary_search(arr, ARRAY_LEN, target);
	printf("%d is in position %d\n", target, idx);

	target = arr[9];
	idx = binary_search_recursive(arr, ARRAY_LEN, target);
	printf("%d is in position %d\n", target, idx);

	target = 9;
	idx = binary_search_recursive(arr, ARRAY_LEN, target);
	printf("%d is in position %d\n", target, idx);

	target = arr[9];
	idx = insert_search(arr, ARRAY_LEN, target);
	printf("%d is in position %d\n", target, idx);

	target = 9;
	idx = insert_search(arr, ARRAY_LEN, target);
	printf("%d is in position %d\n", target, idx);
}
