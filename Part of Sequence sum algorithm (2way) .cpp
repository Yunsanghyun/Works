#include <iostream>
#include <vector>

class find_partsum {
private:
	std::vector<int> arr;
	int arr_len;
	int max_sum;

public:
	find_partsum(std::vector<int> v, int v_len) {
		arr = v;
		arr_len = v_len;
		max_sum = 0;
	}
	find_partsum(find_partsum& a) {
		arr = a.arr;
		arr_len = a.arr_len;
		max_sum = a.max_sum;
	}
	void first_algorithm();
	int second_algorithm(int left, int right);
	void print_maxsum();
};

void find_partsum::first_algorithm() {
	int sum = 0;
	for (int i = 0; i < arr_len; i++) {
		sum += arr[i];

		if (sum > max_sum)
			max_sum = sum;
		if (sum < 0)
			sum = 0;
	}
}

void find_partsum::print_maxsum() {
	std::cout << "최대 부분수열 합은 " << max_sum << std::endl;
}

//앞쪽 절반에 최대 수열이 있는 경우
//뒤쪽 절반에 최대 수열이 있는 경우
//중간에 걸쳐져있는 경우

int find_partsum::second_algorithm(int left, int right) {
	if (left == right) {
		if (arr[left] > 0)
			return arr[left];
		else
			return 0;
	}

	int center = (left + right) / 2;
	int maxLeftSum = second_algorithm(left, center);
	int maxRightSum = second_algorithm(center + 1, right);

	int maxLeftBorderSum = 0, leftBorderSum = 0;
	for (int i = center; i >= left; i--) {
		leftBorderSum += arr[i];
		if (leftBorderSum > maxLeftBorderSum)
			maxLeftBorderSum = leftBorderSum;
	}

	int maxRightBorderSum = 0, rightBorderSum = 0;
	for (int i = center + 1; i <= right; i++) {
		rightBorderSum += arr[i];
		if (rightBorderSum > maxRightBorderSum)
			maxRightBorderSum = rightBorderSum;
	}

	int maxBorderSum = maxLeftBorderSum + maxRightBorderSum;

	if (maxLeftSum > maxRightSum) {
		if (maxLeftSum > maxBorderSum)
			max_sum = maxLeftSum;
		else
			max_sum = maxBorderSum;
	}
	else {
		if (maxRightSum > maxBorderSum)
			max_sum = maxRightSum;
		else
			max_sum = maxBorderSum;
	}

	return max_sum;
}

int main() {
	std::vector<int> v;
	int x;

	std::cout << "배열을 입력하시오" << std::endl;
	for (int i = 0; i < 10; i++) {
		std::cin >> x;
		v.push_back(x);
	}
	
	find_partsum first_algorithm(v, v.size());
	find_partsum second_algorithm(v, v.size());
	
	first_algorithm.first_algorithm();
	first_algorithm.print_maxsum();
	
	second_algorithm.second_algorithm(0, v.size() - 1);
	second_algorithm.print_maxsum();

	return 0;
}