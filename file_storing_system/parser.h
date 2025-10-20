#ifndef PARSER_H
#define PARSER_H

#include<string>
#include "Hash.h"
#include "Heap.h"
class File;

void parser(bool& flag, Heap& modification_time_heap, Heap& version_number_heap, 
    HashMap<std::string, File*>& file_name, 
    HashMap<File*, int>& file_loc_modification_time,
    HashMap<File*, int>& file_loc_most_versions);

#endif
