/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2017 [insert fancy company name here]
 *
 *  Created on: 17.05.17
 *
 */

#ifndef BREW_LINUXSYSTEMINFO_H
#define BREW_LINUXSYSTEMINFO_H

#include <brew/core/SystemInfo.h>

#include <fstream>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

namespace brew {
namespace detail {

/**
 * Reads a file from the local file system.
 * @param filename The filename.
 * @return The file contents.
 */
std::vector<String> readFile(const String& filename) {
    std::ifstream f(filename);
    std::vector<String> lines;
    while(f.good() && !f.eof() && f.is_open()) {
        String line;
        std::getline(f, line);
        lines.push_back(line);
    }
    return lines;
}

const std::vector<String> cpuInfo = readFile("/proc/cpuinfo");

const std::vector<String> memInfo = readFile("/proc/meminfo");

/**
 * System query implementation for linux systems.
 */
class LinuxSystemQuery : public SystemQuery {
public:
    /**
     * @return The total number of logical processors on this system.
     */
    SizeT getNumLogicalProcessors() const override {
        SizeT result = 0;
        for(const String& line : cpuInfo) {
            if(line.find("processor") == 0) {
                result++;
            }
        }
        return result;
    }

    /**
     * @return The total number of physical processors on this system.
     */
    SizeT getNumPhysicalProcessors() const override {
        for(const String& line : cpuInfo) {
            if(line.find("cpu cores") == 0) {
                SizeT value = std::stoul(
                        line.substr(line.find_last_of(":")+1)
                );

                if(value > 0) {
                    return value;
                }
            }
        }
    }

    /**
     * @return The total number of physical memory on this system.
     */
    SizeT getPhysicalMemory() const override {
        for(const String& line : memInfo) {
            if(line.find("MemTotal") == 0) {
                SizeT value = std::stoul(
                        line.substr(line.find_last_of(":")+1)
                );

                if(value > 0) {
                    return value * 1000;
                }
            }
        }
    }

    /**
     * @return The total number of unallocated physical memory on this system.
     */
    SizeT getPhysicalMemoryAvailable() const override {
        for(const String& line : memInfo) {
            if(line.find("MemAvailable") == 0) {
                SizeT value = std::stoul(
                        line.substr(line.find_last_of(":")+1)
                );

                if(value > 0) {
                    return value * 1000;
                }
            }
        }
    }

    /**
     * @return The total number of virtual memory on this system.
     */
    SizeT getVirtualMemory() const override {
        for(const String& line : memInfo) {
            if(line.find("SwapTotal") == 0) {
                SizeT value = std::stoul(
                        line.substr(line.find_last_of(":")+1)
                );

                if(value > 0) {
                    return value * 1000;
                }
            }
        }
    }

    /**
     * @return The platform name.
     */
    const String& getPlatformName() override {
        static const String platformName = "Linux";
        return platformName;
    }

    /**
     * @return The current working directory.
     */
    const String& getCWD() override {
        char szTmp[1024];
        char pBuf[1024];
        ssize_t len = 1024;
        sprintf(szTmp, "/proc/%d/exe", getpid());

        int bytes = std::min(readlink(szTmp, pBuf, len), len - 1);
        if(bytes >= 0)
            pBuf[bytes] = '\0';

        static String result = pBuf;
        result = result.substr(0, result.find_last_of("/"));

        return result;
    }
};

} /* namespace detail */
} /* namespace brew */

#endif //BREW_LINUXSYSTEMINFO_H
