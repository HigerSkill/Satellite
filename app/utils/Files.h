#ifndef SATELLITE_FILES_H
#define SATELLITE_FILES_H

#include <string>

/**
 * Get file extension.
 *
 * @param filename Path of file.
 * @return string with extension of file.
 */
std::string getFileExtension(std::string filename) {
    return filename.substr(filename.find_last_of('.') + 1);
}

#endif //SATELLITE_FILES_H
