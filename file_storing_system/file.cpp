#include "File.h"
#include "Heap.h"
#include <ctime>
#include <iostream>

File::File(std::string name, HashMap<std::string, File*>& file_name) {
    root = new Version(0, "", "Creating File");
    active_version = root;
    total_versions = 1;
    version_map[0] = root;
    file_name[name] = this;
    filename = name;
    last_modified = time(nullptr);
}

File::~File() {}

std::string File::read() {
    return active_version->content;
}

void File::insert(std::string new_content, Heap& modification_time_heap, Heap& version_number_heap, 
    HashMap<File*, int>& file_loc_modification_time, 
    HashMap<File*, int>& file_loc_most_versions) {

    if (active_version->snapshot_timestamp == -1) {
        active_version->content.append(new_content);
    } else {
        Version* temp = new Version(total_versions++, (active_version->content + new_content), "", active_version);
        active_version->children.push_back(temp);
        active_version = temp;
        version_map[total_versions - 1] = temp;
        version_number_heap.remove(file_loc_most_versions[this], file_loc_modification_time, file_loc_most_versions);
        version_number_heap.add(this, file_loc_modification_time, file_loc_most_versions);
    }

    last_modified = time(nullptr);
    modification_time_heap.remove(file_loc_modification_time[this], file_loc_modification_time, file_loc_most_versions);
    modification_time_heap.add(this, file_loc_modification_time, file_loc_most_versions);
}

void File::update(std::string new_content, Heap& modification_time_heap, Heap& version_number_heap, 
    HashMap<File*, int>& file_loc_modification_time, 
    HashMap<File*, int>& file_loc_most_versions) {

    if (active_version->snapshot_timestamp == -1) {
        active_version->content = new_content;
    } else {
        Version* temp = new Version(total_versions++, (new_content), "", active_version);
        active_version->children.push_back(temp);
        active_version = temp;
        version_map[total_versions - 1] = temp;
        version_number_heap.remove(file_loc_most_versions[this], file_loc_modification_time, file_loc_most_versions);
        version_number_heap.add(this, file_loc_modification_time, file_loc_most_versions);
    }

    last_modified = time(nullptr);
    modification_time_heap.remove(file_loc_modification_time[this], file_loc_modification_time, file_loc_most_versions);
    modification_time_heap.add(this, file_loc_modification_time, file_loc_most_versions);
}

bool File::snapshot(std::string message, Heap& modification_time_heap, 
    HashMap<File*, int>& file_loc_modification_time, 
    HashMap<File*, int>& file_loc_most_versions) {

    if (active_version->snapshot_timestamp != -1) return false;
    active_version->snapshot_timestamp = time(nullptr);
    active_version->message = message;
    last_modified = time(nullptr);
    modification_time_heap.remove(file_loc_modification_time[this], file_loc_modification_time, file_loc_most_versions);
    modification_time_heap.add(this, file_loc_modification_time, file_loc_most_versions);

    return true;
}

bool File::rollback(int version_id) {

    if (version_id == -1) {
        if (active_version->parent != nullptr) {
            active_version = active_version->parent;
        } else {
            std::cout << "Already at root\n";
            return false;
        }
    } else if (version_id > total_versions - 1 || version_id < 0) { 
        std::cout << "Invalid versionID\n";
        return false;
    } else {
        active_version = version_map[version_id];
    }

    return true;
}

std::vector<Version*> File::history() {

    std::vector<Version*> history_vec;
    Version* curr = active_version;
    
    while (curr != nullptr) {
        history_vec.push_back(curr);
        curr = curr->parent;
    }
    
    for (int i = 0; i < history_vec.size() / 2; i++) {
        std::swap(history_vec[i], history_vec[history_vec.size() - i - 1]);
    }
    
    return history_vec;
}
