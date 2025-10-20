#include "Parser.h"
#include "Commands.h"
#include "Heap.h"
#include "File.h"
#include <iostream>
#include <sstream>

void parser(bool& flag, Heap& modification_time_heap, Heap& version_number_heap, 
    HashMap<std::string, File*>& file_name, 
    HashMap<File*, int>& file_loc_modification_time, 
    HashMap<File*, int>& file_loc_most_versions) {

    std::string command;
    std::getline(std::cin, command);

    std::istringstream iss(command);
    std::vector<std::string> words;
    std::string word;

    while (iss >> word) {
        words.push_back(word);
    }

    if (words.size() != 0 && words[0] == "EXIT") {
        std::cout << "Exiting Terminal\n";
        flag = false;
        return;
    }

    if (words.size() < 1) {
        std::cout << "Incorrect Input\n";
        return;
    }

    if (words[0] == "CREATE") {
        if (words.size() != 2) {
            std::cout << "Incorrect Input\n";
            return;
        }
        create(words[1], modification_time_heap, version_number_heap, 
            file_name, file_loc_modification_time, file_loc_most_versions);
        return;
    }

    if (words[0] == "READ") {
        if (words.size() != 2) {
            std::cout << "Incorrect Input\n";
            return;
        }
        std::cout << read(words[1], file_name) << '\n';
        return;
    }

    if (words[0] == "INSERT") {
        if (words.size() < 3) {
            std::cout << "Incorrect Input\n";
            return;
        }
        std::string content = "";
        for (int i = 2; i < words.size(); i++) {
            content += words[i] + " ";
        }
        content.pop_back();
        std::cout << insert(words[1], content, modification_time_heap, version_number_heap, 
            file_name, file_loc_modification_time, file_loc_most_versions);
        return;
    }

    if (words[0] == "UPDATE") {
        if (words.size() < 3) {
            std::cout << "Incorrect Input\n";
            return;
        }
        std::string content = "";
        for (int i = 2; i < words.size(); i++) {
            content += words[i] + " ";
        }
        content.pop_back();
        std::cout << update(words[1], content, modification_time_heap, version_number_heap, 
            file_name, file_loc_modification_time, file_loc_most_versions);
        return;
    }

    if (words[0] == "SNAPSHOT") {
        if (words.size() < 3) {
            std::cout << "Incorrect Input\n";
            return;
        }
        std::string content = "";
        for (int i = 2; i < words.size(); i++) {
            content += words[i] + " ";
        }
        content.pop_back();
        std::cout << snapshot(words[1], content, modification_time_heap, 
            file_name, file_loc_modification_time, file_loc_most_versions);
        return;
    }

    if (words[0] == "ROLLBACK") {
        if (words.size() == 2) {
            std::cout << rollback(words[1], file_name);
            return;
        } else if (words.size() == 3) {
            int versionID;
            try {
                versionID = std::stoi(words[2]);
            } catch (...) {
                std::cout << "Incorrect Input\n";
                return;
            }
            std::cout << rollback(words[1], file_name, versionID);
            return;
        }
        else std::cout << "Incorrect Input\n";
        return;
    }

    if (words[0] == "HISTORY") {
        if (words.size() != 2) {
            std::cout << "Incorrect Input\n";
            return;
        }
        std::vector<Version*> history_vec = history(words[1], file_name);
        for (Version* version : history_vec) {
            if (version->snapshot_timestamp != -1)
                std::cout << version->version_id << " " << std::ctime(&version->snapshot_timestamp) << " " << version -> message << '\n';
        }
        return;
    }

    if (words[0] == "RECENT_FILES") {

        if (words.size() == 1) {
            std::vector<File*> recent_files_vec = recent_files(modification_time_heap, file_loc_modification_time, 
                file_loc_most_versions);
            for (File* file : recent_files_vec) {
                std::cout << file->filename << '\n';
            }
        }
        
        else if (words.size() == 2) {
            int n;
            try {
                n = std::stoi(words[1]);
            }
            catch (...) {
                std::cout << "Incorrect Input\n";
                return;
            }
            std::vector<File*> recent_files_vec = recent_files(modification_time_heap, file_loc_modification_time,
                file_loc_most_versions, n);
            for (File* file : recent_files_vec) {
                std::cout << file->filename << '\n';
            }
        }
        
        else std::cout << "Incorrect Input\n";
        
        return;
    }

    if (words[0] == "BIGGEST_TREES") {
        
        if (words.size() == 1) {
            std::vector<File*> biggest_trees_vec = biggest_trees(version_number_heap, file_loc_modification_time,
                file_loc_most_versions);
            for (File* file : biggest_trees_vec) {
                std::cout << file->filename << ", Number of Versions: " << file -> total_versions << '\n';
            }
        }
        
        else if (words.size() == 2) {
            int n;
            try {
                n = std::stoi(words[1]);
            }
            catch (...) {
                std::cout << "Incorrect Input\n";
                return;
            }
            std::vector<File*> biggest_trees_vec = biggest_trees(version_number_heap, file_loc_modification_time,
                file_loc_most_versions, n);
            for (File* file : biggest_trees_vec) {
                std::cout << file->filename << ", Number of Versions: " << file -> total_versions << '\n';
            }
        }
        
        else std::cout << "Incorrect Input\n";
        
        return;
    }

    std::cout << "Invalid Input\n";
    return;
}
