#include <iostream>
#include <mutex>

class Data {
public:
	int int_data;
	std::mutex mu;
	Data() = delete;


	Data(int a) {
		int_data = a;
	}

};

//c помощью lock
void swap_by_lock(Data& a, Data& b) {
	std::lock(a.mu, b.mu);
	std::lock_guard<std::mutex>lock_a(a.mu, std::adopt_lock);
	std::lock_guard<std::mutex>lock_b(b.mu, std::adopt_lock);

	std::swap(a.int_data, b.int_data);
}

//c помощью юник лок
void swap_by_unique_lock(Data& a, Data& b) {
	std::unique_lock<std::mutex> ulock_a(a.mu, std::defer_lock);
	std::unique_lock<std::mutex> ulock_b(b.mu, std::defer_lock);

	std::swap(a.int_data, b.int_data);
}

//скопед лок
void swap_by_scoped_lock(Data& a, Data& b) {
	std::scoped_lock lock(a.mu, b.mu);

	std::swap(a.int_data, b.int_data);
}

int main() {
	Data a(50);
	Data b(10);
	swap_by_scoped_lock(a, b);
	std::cout << "a.int_data = " << a.int_data << std::endl;
	std::cout << "b.int_data = " << b.int_data << std::endl;

	return 0;
}