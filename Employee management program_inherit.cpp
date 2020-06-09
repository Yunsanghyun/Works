#include <iostream>
#include <string>

class employee {
private:
	std::string name;
	int age;
	std::string position;
	int rank;

public:
	employee(std::string _name, int _age, std::string _position, int _rank)
		: name(_name), age(_age), position(_position), rank(_rank) {}
	
	employee(employee& _employee) {
		name = _employee.name;
		age = _employee.age;
		position = _employee.position;
		rank = _employee.rank;
	}
	
	void salary_print() {
		int salary = calculate_salary();
		std::cout << name << "의 월급은 " << salary << std::endl;
	}

	int calculate_salary() {
		return 200 + rank * 50;
	}
};

class manager : public employee {
private:
	int year_of_service;

public:
	manager(std::string _name, int _age, std::string _position, int _rank, int _year_of_service)
		: year_of_service(_year_of_service), employee(_name, _age, _position, _rank) {}

	manager(manager& _manager) :employee(_manager.name, _manager.age, _manager.position, _manager.rank) {
		year_of_service = _manager.year_of_service;
	}

	void salary_print() {
		int salary = calculate_salary();
		std::cout << name << "의 월급은 " << salary << std::endl;
	}

	int calculate_salary() {
		return 200 + rank * 50 + year_of_service * 5;
	}
};

class employeelist {
private:
	int alloc_employee;
	int curr_employee;
	int curr_manager;
	employee** employee_list;
	manager** manager_list;

public:
	employeelist(int _alloc_employee) : alloc_employee(_alloc_employee){
		employee_list = new employee * [alloc_employee];
		manager_list = new manager * [alloc_employee];
		curr_employee = 0;
		curr_manager = 0;
	}
	employeelist(employeelist& _employeelist) {
		alloc_employee = _employeelist.alloc_employee;
		curr_employee = _employeelist.curr_employee;
		employee_list = _employeelist.employee_list;
		manager_list = _employeelist.manager_list;
	}
	~employeelist() {
		for (int i = 0; i < curr_employee; i++) {
			delete employee_list[i];
		}
		for (int i = 0; i < curr_manager; i++) {
			delete manager_list[i];
		}
		delete[] employee_list;
		delete[] manager_list;
}

	void add_employee(employee* _employee) {
		employee_list[curr_employee] = _employee;
		curr_employee++;
	}

	void add_manager(manager* _manager) {
		manager_list[curr_manager] = _manager;
		curr_manager++;
	}

	void print_total_salary() {
		int total_salary = 0;
		for (int i = 0; i < curr_employee; i++) {
			employee_list[i]->salary_print();
			total_salary += employee_list[i]->calculate_salary();
		}
		for (int i = 0; i < curr_manager; i++) {
			manager_list[i]->salary_print();
			total_salary += manager_list[i]->calculate_salary();
		}

	}
};

int main() {
	int alloc_employee_num = 0;
	std::cout << "할당할 직원수를 입력하시오 " << std::endl;
	std::cin >> alloc_employee_num;

	employeelist employeelist(alloc_employee_num);
	
	employeelist.add_employee(new employee("노홍철", 34, "평사원", 1));
	employeelist.add_employee(new employee("하하", 34, "평사원", 1));
	employeelist.add_manager(new manager("유재석", 41, "부장", 7, 10));
	employeelist.add_manager(new manager("정준하", 43, "과장", 4, 6));
	employeelist.add_mamager(new manager("박명수", 43, "차장", 5, 8));
	employeelist.add_employee(new employee("정형돈", 36, "대리", 2));
	employeelist.add_employee(new employee("길", 36, "인턴", -1));

	employeelist.print_total_salary();

	return 0;
}