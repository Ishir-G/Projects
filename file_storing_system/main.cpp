#include "Parser.h"
#include "Heap.h"
#include <iostream>
#include "Hash.h"
#include <string>
#include "File.h"

int main() {
    bool flag = true;
    Heap modification_time_heap(true);
    Heap version_number_heap(false);

    HashMap<std::string, File*> file_name;
    HashMap<File*, int> file_loc_most_versions;
    HashMap<File*, int> file_loc_modification_time;

    while (flag) {
        std::cout << "> ";
        parser(flag, modification_time_heap, version_number_heap, 
            file_name, file_loc_modification_time, file_loc_most_versions);
    }
    return 0;
}
