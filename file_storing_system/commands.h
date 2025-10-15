#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>
#include <vector>
#include "Hash.h"
#include "Heap.h"
#include "Version.h"

class File;

void create(std::string filename, Heap& modification_time_heap, Heap& version_number_heap, 
    HashMap<std::string, File*>& file_name, 
    HashMap<File*, int>& file_loc_modification_time, 
    HashMap<File*, int>& file_loc_most_versions);

std::string read(std::string filename, HashMap<std::string, File*>& file_name);

std::string insert(std::string filename, std::string content, Heap& modification_time_heap, Heap& version_number_heap, 
    HashMap<std::string, File*>& file_name,
    HashMap<File*, int>& file_loc_modification_time, 
    HashMap<File*, int>& file_loc_most_versions);

std::string update(std::string filename, std::string content, Heap& modification_time_heap, Heap& version_number_heap, 
    HashMap<std::string, File*>& file_name,
    HashMap<File*, int>& file_loc_modification_time, 
    HashMap<File*, int>& file_loc_most_versions);

std::string snapshot(std::string filename, std::string message, Heap& modification_time_heap, 
    HashMap<std::string, File*>& file_name, 
    HashMap<File*, int>& file_loc_modification_time, 
    HashMap<File*, int>& file_loc_most_versions);
    
std::string rollback(std::string filename, HashMap<std::string, File*>& file_name, int version_id = -1);

std::vector<Version*> history(std::string filename, HashMap<std::string, File*>& file_name);

std::vector<File*> recent_files(Heap& modification_time_heap, HashMap<File*, int>& file_loc_modification_time,
    HashMap<File*, int>& file_loc_most_versions, int k = -1);

std::vector<File*> biggest_trees(Heap& version_number_heap, HashMap<File*, int>& file_loc_modification_time,
    HashMap<File*, int>& file_loc_most_versions, int k = -1);

#endif
