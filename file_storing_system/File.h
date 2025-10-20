#ifndef FILE_H
#define FILE_H

#include <string>
#include "Hash.h"
#include <vector>
#include "Version.h"
#include "Heap.h"

class File {
private:
    Version* root;
    Version* active_version;
    HashMap<int, Version*> version_map;

public:
    std::string filename;
    int total_versions;
    time_t last_modified;

    File(std::string name, HashMap<std::string, File*>& file_name);
    ~File();
    std::string read();
    void insert(std::string new_content, Heap& modification_time_heap, Heap& version_number_heap, 
        HashMap<File*, int>& file_loc_modification_time, 
        HashMap<File*, int>& file_loc_most_versions);

    void update(std::string new_content, Heap& modification_time_heap, Heap& version_number_heap, 
        HashMap<File*, int>& file_loc_modification_time, 
        HashMap<File*, int>& file_loc_most_versions);

    bool snapshot(std::string message, Heap& modification_time_heap, 
        HashMap<File*, int>& file_loc_modification_time, 
        HashMap<File*, int>& file_loc_most_versions);
        
    bool rollback(int version_id = -1);
    std::vector<Version*> history();
};

#endif
