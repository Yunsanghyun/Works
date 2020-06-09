#include <iostream>

class bubble {
private:
	int index;
	int str_len;
	char* str;

public:
	bubble(char* _str, int _str_len);
	~bubble();

	void bubble_func();
	void print_str();
};

bubble::bubble(char* _str, int _str_len) {
	index = 0;
	str_len = _str_len;
	str = new char[str_len + 1];
	for (int i = 0; i < str_len; i++) {
		str[i] = _str[i];
	}
}

bubble::~bubble() {
	delete str;
}

void bubble::bubble_func() {
	for (int i = 0; i < str_len; i++) {
		for (int j = i; j < str_len; j++) {
			if (str[i] > str[j]) {
				char temp_i,temp_j = 0;
				temp_i = str[i];
				temp_j = str[j];
				str[i] = temp_j;
				str[j] = temp_i;
			}
		}
	}
	str[str_len] = '\0';
}

void bubble::print_str() {

	std::cout << "버블정렬된 문자열은 " << str << std::endl;
}

int main() {
	
	int string_len = 0;
	char* string;
	std::cout << "입력할 문자열 길이는? " << std::endl;
	std::cin >> string_len;

	string = new char[string_len + 1];

	std::cout << "문자열을 입력하시오 " << std::endl;
	for (int i = 0; i < string_len; i++) {
		std::cin >> string[i];
	}

	bubble test(string,string_len);
	test.bubble_func();
	test.print_str();
	
	delete[] string;

	return 0;
}