
#ifndef VERSION_H
#define VERSION_H

#include <string>
#include <vector>
#include <ctime>

struct Version {
public:
    int version_id;
    std::string content;
    std::string message;
    std::time_t created_timestamp;
    std::time_t snapshot_timestamp;
    Version* parent;
    std::vector<Version*> children;

    Version(int version_id, std::string content, std::string message, Version* parent_version = nullptr);
};

#endif
