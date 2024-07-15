#include <windows.h>
#include <iostream>
#include <vector>

struct DiskInfo {
    std::string name;
    ULONGLONG totalSize;
    ULONGLONG freeSpace;
};

void GetDiskInfo(std::vector<DiskInfo>& disks) {
    char driveLetter = 'A';
    while (driveLetter <= 'Z') {
        char rootPath[4] = { driveLetter, ':', '\\', '\0' };
        ULARGE_INTEGER freeBytesAvailable, totalNumberOfBytes, totalNumberOfFreeBytes;

        if (GetDiskFreeSpaceEx(rootPath, &freeBytesAvailable, &totalNumberOfBytes, &totalNumberOfFreeBytes)) {
            DiskInfo disk;
            disk.name = rootPath;
            disk.totalSize = totalNumberOfBytes.QuadPart;
            disk.freeSpace = totalNumberOfFreeBytes.QuadPart;
            disks.push_back(disk);
        }
        ++driveLetter;
    }
}

void PrintDiskInfo(const std::vector<DiskInfo>& disks) {
    for (const auto& disk : disks) {
        std::cout << "Drive: " << disk.name << std::endl;
        std::cout << "Total Size: " << disk.totalSize / (1024 * 1024) << " MB" << std::endl;
        std::cout << "Free Space: " << disk.freeSpace / (1024 * 1024) << " MB" << std::endl;
        std::cout << "-------------------------------" << std::endl;
    }
}

int main() {
    std::vector<DiskInfo> disks;
    GetDiskInfo(disks);
    PrintDiskInfo(disks);

    return 0;
}
