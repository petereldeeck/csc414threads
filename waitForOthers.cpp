#include <iostream>
#include <condition_variable>
#include <random>
#include <mutex>
#include <chrono>
#include <string>


int num_threads = 10;
std::default_random_engine e;
std::uniform_int_distribution<> id(1, 2000);
std::condition_variable CVariable;
bool Phase1Complete = false;
std::mutex m;



void thread(std::string s) {

	std::this_thread::sleep_for(std::chrono::milliseconds(id(e)));
	std::cout << "phase 1 for thread " << s << std::endl;
	std::unique_lock<std::mutex> lock(m);


	if (s == std::to_string(num_threads - 1)) {
		Phase1Complete = true;
		CVariable.notify_all();
	}

	while (!phase1Complete) CVariable.wait(lock);
	std::this_thread::sleep_for(std::chrono::milliseconds(id(e)));
	std::cout << s << " is done" << std::endl;
}
int main()
{
	std::vector<std::thread> mythreads;
	for (int i = 0; i < num_threads; i++) {
		std::this_thread::sleep_for(std::chrono::milliseconds(2000)); //line5 on slack you asked to add this line
		mythreads.push_back(std::thread(thread, std::to_string(i)));
	}

	for (auto& t : mythreads) {

		t.join();

	}

}
