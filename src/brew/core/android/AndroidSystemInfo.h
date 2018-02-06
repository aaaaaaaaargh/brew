/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2017 [insert fancy company name here]
 *
 *  Created on: 30.01.18
 *
 */

#ifndef BREW_ANDROIDSYSTEMINFO_H
#define BREW_ANDROIDSYSTEMINFO_H

#include <brew/core/SystemInfo.h>

namespace brew {
namespace detail {

/**
 * System query implementation for linux systems.
 */
class AndroidSystemQuery : public SystemQuery {
public:
    /**
     * @return The total number of logical processors on this system.
     */
    SizeT getNumLogicalProcessors() const override {
        // Stub.
        return 0;
    }

    /**
     * @return The total number of physical processors on this system.
     */
    SizeT getNumPhysicalProcessors() const override {
        // Stub.
        return 0;
    }

    /**
     * @return The total number of physical memory on this system.
     */
    SizeT getPhysicalMemory() const override {
        // Stub.
        return 0;
    }

    /**
     * @return The total number of unallocated physical memory on this system.
     */
    SizeT getPhysicalMemoryAvailable() const override {
        // Stub.
        return 0;
    }

    /**
     * @return The total number of virtual memory on this system.
     */
    SizeT getVirtualMemory() const override {
        // Stub.
        return 0;
    }

    /**
     * @return The platform name.
     */
    const String& getPlatformName() override {
        static const String platformName = "Android";
        return platformName;
    }

    /**
     * @return The current working directory.
     */
    const String& getCWD() override {
        static const String cwd = ".";
        return cwd;
    }
};

} /* namespace detail */
} /* namespace brew */

#endif //BREW_ANDROIDSYSTEMINFO_H
