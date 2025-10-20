#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include "Hash.h"

class File;

class Heap {
private:
    std::vector<File*> heap;
    bool modification_time;
    bool compare(File* a, File* b) const;

    void heapify_up(int idx, HashMap<File*, int>& file_loc_modification_time, 
        HashMap<File*, int>& file_loc_most_versions);

    void heapify_down(int idx, HashMap<File*, int>& file_loc_modification_time,
        HashMap<File*, int>& file_loc_most_versions);

public:
    Heap(bool by_version);
    File* top();

    void add(File* file, HashMap<File*, int>& file_loc_modification_time,
        HashMap<File*, int>& file_loc_most_versions);

    void remove(int idx, HashMap<File*, int>& file_loc_modification_time,
        HashMap<File*, int>& file_loc_most_versions);

    File* operator[](int idx);

    int size() const;
};

#endif
