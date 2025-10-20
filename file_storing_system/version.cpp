#include "Version.h"

Version::Version(int version_id, std::string content, std::string message, Version* parent_version)
    : version_id(version_id), content(content), message(message), parent(parent_version) {
    created_timestamp = time(nullptr);
    snapshot_timestamp = (version_id == 0 ? created_timestamp : -1);
}
