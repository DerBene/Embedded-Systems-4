#include <iostream>
#include "../include/PoolAllocator.h"

using namespace std;

int main() {

    cout << "### Testing basic allocation of int* with PoolAllocator with BLOCK_COUNT = 5 and BLOCK_SIZE = 10 ###" << endl;
    Allocator<5, 10> poolAllocator1;
    cout << "    Available bytes before allocation of int[3]: [" << poolAllocator1.Available() << "]" << endl;
    int * array1 = static_cast<int *>(poolAllocator1.Allocate(sizeof(int) * 3));
    cout << "    Available bytes after allocation of int[3]: [" << poolAllocator1.Available() << "]" << endl;
    for (int i = 0; i < 3; i++) {
        array1[i] = i + 1;
    }
    cout << "    Allocated Array: [";
    for (int i = 0; i < 3; i++) {
        cout << array1[i];
        if (i < 2) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
    cout << "    Deallocating Array" << endl;
    poolAllocator1.Deallocate(array1);
    cout << "    Available bytes after deallocation of int[3]: [" << poolAllocator1.Available() << "]" << endl;


    cout << "### Testing basic allocation of char* with PoolAllocator with BLOCK_COUNT = 100 and BLOCK_SIZE = 1 ###" << endl;
    Allocator<100, 1> poolAllocator2;
    cout << "    Available bytes before allocation of char[5]: [" << poolAllocator2.Available() << "]" << endl;
    char * array2 = static_cast<char *>(poolAllocator2.Allocate(sizeof(char) * 5));
    cout << "    Available bytes after allocation of char[5]: [" << poolAllocator2.Available() << "]" << endl;
    for (int i = 0; i < 4; i++) {
        array2[i] = static_cast<char>('a' + i);
    }
    array2[4] = '\0';
    cout << "    Allocated Array: [";
    for (int i = 0; i < 5; i++) {
        cout << array2[i];
        if (i < 4) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
    cout << "    Deallocating Array" << endl;
    poolAllocator2.Deallocate(array2);
    cout << "    Available bytes after deallocation of char[5]: [" << poolAllocator2.Available() << "]" << endl;


    cout << "### Testing allocation when no fitting chunk but enough bytes available with PoolAllocator with BLOCK_COUNT = 100 and BLOCK_SIZE = 1 ###" << endl;
    Allocator<100, 1> poolAllocator3;
    cout << "    Available bytes before allocation of char[25] (1): [" << poolAllocator3.Available() << "]" << endl;
    char * array3_1 = static_cast<char *>(poolAllocator3.Allocate(sizeof(char) * 25));
    cout << "    Available bytes after allocation of char[25] (1): [" << poolAllocator3.Available() << "]" << endl;
    cout << "    Available bytes before allocation of char[25] (2): [" << poolAllocator3.Available() << "]" << endl;
    char * array3_2 = static_cast<char *>(poolAllocator3.Allocate(sizeof(char) * 25));
    cout << "    Available bytes after allocation of char[25] (2): [" << poolAllocator3.Available() << "]" << endl;
    cout << "    Available bytes before allocation of char[25] (3): [" << poolAllocator3.Available() << "]" << endl;
    char * array3_3 = static_cast<char *>(poolAllocator3.Allocate(sizeof(char) * 25));
    cout << "    Available bytes after allocation of char[25] (3): [" << poolAllocator3.Available() << "]" << endl;
    cout << "    Available bytes before allocation of char[25] (4): [" << poolAllocator3.Available() << "]" << endl;
    char * array3_4 = static_cast<char *>(poolAllocator3.Allocate(sizeof(char) * 25));
    cout << "    Available bytes after allocation of char[25] (4): [" << poolAllocator3.Available() << "]" << endl;
    cout << "    Deallocating Array 2" << endl;
    poolAllocator3.Deallocate(array3_2);
    cout << "    Available bytes after deallocation of char[25] (2): [" << poolAllocator3.Available() << "]" << endl;
    cout << "    Deallocating Array 4" << endl;
    poolAllocator3.Deallocate(array3_4);
    cout << "    Available bytes after deallocation of char[25] (4): [" << poolAllocator3.Available() << "]" << endl;
    cout << "    Trying to allocate char[60]" << endl;
    char * array3_5 = static_cast<char *>(poolAllocator3.Allocate(sizeof(char) * 60));
    cout << "    Pool should not have a large enough chunk available and return nullptr" << endl;
    cout << "    Pool has returned nullptr: [" << (array3_5 == nullptr ? "true" : "false") << "]" << endl;
    cout << "    Deallocating Array 1" << endl;
    poolAllocator3.Deallocate(array3_1);
    cout << "    Available bytes after deallocation of char[25] (1): [" << poolAllocator3.Available() << "]" << endl;
    cout << "    Deallocating Array 3" << endl;
    poolAllocator3.Deallocate(array3_3);
    cout << "    Available bytes after deallocation of char[25] (3): [" << poolAllocator3.Available() << "]" << endl;

    return 0;
}