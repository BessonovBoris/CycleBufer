#include <iostream>
#include <algorithm>
#include "cycle_buff.h"

using std::cout, std::cin;

int main() {
    CBuff<int> cb(5, 43);

    cb[0] = 2;
    cb[1] = 1;
    cb[2] = -4;

    for(auto i = cb.begin(); i != cb.end(); i++) {
        cout << *i << " ";
    }

    cb.resize(4);
    cout << "\nAfter capacity change\n";
    for(auto i = cb.begin(); i != cb.end(); i++) {
        cout << *i << " ";
    }

    cout << "\nFirst element: " << cb.front() << "\n";
    cout << "Last element: " << cb.last() << "\n";

    cout << "\nEraze and put to any place\n";
    cb.put(cb.begin()+1, -10);
    cb.eraze(cb.begin()+2, cb.end());

    for(auto i = cb.begin(); i != cb.end(); i++) {
        cout << *i << " ";
    }

    cout << "\nPush begin and end\n";

    cb.push_end(4);
    cb.push_end(5);
    cb.push(6);
    cb.push(7);

    for(auto i = cb.begin(); i != cb.end(); i++) {
        cout << *i << " ";
    }

    cout << "\nDelete first and last\n";

    cb.delete_first();
    cb.delete_last();

    for(auto i = cb.begin(); i != cb.end(); i++) {
        cout << *i << " ";
    }

    cb.push_end(4);
    cb.push_end(-2);

    cout << "\n\n";
    std::fill(cb.begin(), cb.end(), 10);
    for(auto i = cb.begin(); i != cb.end(); i++) {
        cout << *i << " ";
    }

    std::sort(cb.begin(), cb.end());


    return 0;
}
