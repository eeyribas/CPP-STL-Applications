#include <QCoreApplication>
#include <iostream>
#include <assert.h>
#include <thread>
#include <chrono>
#include <future>

using namespace std;

bool state = false;

void Foo1(future<void> future_obj, int value)
{
    cout << "Start Foo-1..." << endl;
    while (future_obj.wait_for(chrono::milliseconds(1)) == future_status::timeout) {
        if (!state) {
            cout << "Foo-1 Value = " << value << endl;
            this_thread::sleep_for(chrono::milliseconds(1000));
        } else {
            cout << "Foo-1 finished..." << endl;
            break;
        }
    }
    cout << "Finished Foo-1..." << endl;
}

void Foo2(int value)
{
    cout << "Start Foo-2..." << endl;
    for (;;) {
        if (!state) {
            cout << "Foo-2 Value = " << value << endl;
            this_thread::sleep_for(chrono::milliseconds(1000));
        } else {
            cout << "Foo-2 finished..." << endl;
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    promise<void> exit_signal;
    future<void> future_obj = exit_signal.get_future();
    state = false;

    thread th_1(&Foo1, move(future_obj), 7);
    thread th_2(Foo2, 5);
    thread th_3(Foo2, 10);

    this_thread::sleep_for(chrono::milliseconds(10000));
    state = true;
    this_thread::sleep_for(chrono::milliseconds(2000));
    exit_signal.set_value();

    th_1.join();
    th_2.join();
    th_3.join();

    return a.exec();
}
