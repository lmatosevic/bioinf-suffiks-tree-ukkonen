#include <iostream>
#include <stdio.h>

using namespace std;

int main() {
    char name[50];
    cout << "Enter your name: ";
    scanf("%s", name);
    cout << "Hello " << name << endl;
    return 0;
}