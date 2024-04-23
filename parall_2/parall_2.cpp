// parall_2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <condition_variable>

using namespace std;
condition_variable cv;
int next_thread = 0;

mutex mut;

void print_num(const int& start, const int& end, vector<string> nums,const int& index) {
    unique_lock<mutex> lock(mut);
    cv.wait(lock, [&index]() { return index == next_thread; });
        for (int i = start; i <= end; i++)
            cout << nums[i] << " ";
    next_thread ++;
    lock.unlock();
    cv.notify_all();
}



int main()
{
    vector<thread> threads;
    vector<string> nums = { "first", "second","third","fourth","fifth" ,"sixth" ,"seventh" ,"eighth" ,"ninth" };
    int measurements = 9;
    int num_treads, start, end;
    for (int i = 0; i < measurements; i++) {
        next_thread = 0;
        num_treads = i + 1;
        start = 0;
        end = 8 % num_treads + 8 / num_treads;
        cout << "threads [" << num_treads << "] ";
        for (int j = 0; j < num_treads; j++) {
            threads.emplace_back(print_num, start, end, nums,j);
            start = 1 + end;
            end += 8 / num_treads;
        }
        for (auto& thread : threads) {
            thread.join();
        }
        cout << endl;
        threads.clear();
    }

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
