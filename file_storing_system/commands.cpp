#include "Commands.h"
#include "Heap.h"
#include "File.h"
#include <iostream>
#include <vector>
#include "Hash.h"

std::vector<File*> recent_files(Heap& modification_time_heap, 
    HashMap<File*, int>& file_loc_modification_time,
    HashMap<File*, int>& file_loc_most_versions, int k) {

    std::vector<File*> result;

    if (k > modification_time_heap.size() || k < 0) {
        k = modification_time_heap.size();
        std::cout << "Only " << k << " files available\n";
    }

    for (int i = 0; i < k; i++) {
        result.push_back(modification_time_heap.top());
        modification_time_heap.remove(0, file_loc_modification_time, 
            file_loc_most_versions);
    }

    for (int i = k - 1; i >= 0; i--) {
        modification_time_heap.add(result[i], file_loc_modification_time,
            file_loc_most_versions);
    }

    return result;
}

std::vector<File*> biggest_trees(Heap& version_number_heap, 
    HashMap<File*, int>& file_loc_modification_time,
    HashMap<File*, int>& file_loc_most_versions, int k) {

    std::vector<File*> result;
    
    if (k > version_number_heap.size() || k < 0) {
        k = version_number_heap.size();
        std::cout << "Only " << k << " files available\n";
    }
    
    for (int i = 0; i < k; i++) {
        result.push_back(version_number_heap.top());
        version_number_heap.remove(0, file_loc_modification_time, file_loc_most_versions);
    }
    
    for (int i = k - 1; i >= 0; i--) {
        version_number_heap.add(result[i], file_loc_modification_time, file_loc_most_versions);
    }
    
    return result;
}

void create(std::string filename, Heap& modification_time_heap, Heap& version_number_heap, 
    HashMap<std::string, File*>& file_name, 
    HashMap<File*, int>& file_loc_modification_time, 
    HashMap<File*, int>& file_loc_most_versions) {
    
        if (file_name.find(filename)) {
        std::cout << "File already exists\n";
        return;
    }
    
    File* new_file = new File(filename, file_name);
    modification_time_heap.add(new_file, file_loc_modification_time, file_loc_most_versions);
    version_number_heap.add(new_file, file_loc_modification_time, file_loc_most_versions);
}

std::string read(std::string filename, HashMap<std::string, File*>& file_name) {

    if (!file_name.find(filename)) {
        return "File does not exist\n";
    }

    return file_name[filename]->read();
}

std::string insert(std::string filename, std::string content, Heap& modification_time_heap, Heap& version_number_heap, 
    HashMap<std::string, File*>& file_name, 
    HashMap<File*, int>& file_loc_modification_time, 
    HashMap<File*, int>& file_loc_most_versions) {

    if (!file_name.find(filename)) {
        return "File does not exist\n";
    }

    file_name[filename]->insert(content, modification_time_heap, version_number_heap, 
                                    file_loc_modification_time, file_loc_most_versions);
    
    return "Inserted successfully\n";
}

std::string update(std::string filename, std::string content, Heap& modification_time_heap, Heap& version_number_heap, 
    HashMap<std::string, File*>& file_name,
    HashMap<File*, int>& file_loc_modification_time, 
    HashMap<File*, int>& file_loc_most_versions) {

    if (!file_name.find(filename)) {
        return "File does not exist\n";
    }
    
    file_name[filename]->update(content, modification_time_heap, version_number_heap, 
        file_loc_modification_time, file_loc_most_versions);
    
        return "Updated successfully\n";
}

std::string snapshot(std::string filename, std::string message, Heap& modification_time_heap, 
    HashMap<std::string, File*>& file_name, 
    HashMap<File*, int>& file_loc_modification_time, 
    HashMap<File*, int>& file_loc_most_versions) {
    
    if (!file_name.find(filename)) {
        return "File does not exist\n";
    }

    if (file_name[filename] -> snapshot(message, modification_time_heap, 
        file_loc_modification_time, 
        file_loc_most_versions)) {
        return "Snapshot created successfully\n";
    }

    return "Already Snapshotted\n";
}

std::string rollback(std::string filename, HashMap<std::string, File*>& file_name, int versionID) {
    
    if (!file_name.find(filename)) {
        return "File does not exist\n";
    }
    
    if (file_name[filename] -> rollback(versionID)) {
        return "Rollback successful\n";
    }
    
    return "";
}

std::vector<Version*> history(std::string filename, HashMap<std::string, File*>& file_name) {
    
    if (!file_name.find(filename)) {
        std::cout << "File does not exist\n";
        return {};
    }
    
    return file_name[filename] -> history();
}
