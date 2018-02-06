/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: 17.05.17
 *
 */

#ifndef BREW_SYSTEMINFO_H
#define BREW_SYSTEMINFO_H

#include <brew/core/Types.h>

#include <memory>

namespace brew {

namespace detail {
    /**
     * A system query. Implementation is platform specific.
     */
    class SystemQuery {
    public:
        /**
         * @return The total number of logical processors on this system.
         */
        virtual SizeT getNumLogicalProcessors() const = 0;

        /**
         * @return The total number of physical processors on this system.
         */
        virtual SizeT getNumPhysicalProcessors() const = 0;

        /**
         * @return The total number of physical memory on this system.
         */
        virtual SizeT getPhysicalMemory() const = 0;

        /**
         * @return The total number of virtual memory on this system.
         */
        virtual SizeT getVirtualMemory() const = 0;

        /**
         * @return The total number of unallocated physical memory on this system.
         */
        virtual SizeT getPhysicalMemoryAvailable() const = 0;

        /**
         * @return The platform name.
         */
        virtual const String& getPlatformName() = 0;

        /**
         * @return The current working directory.
         */
        virtual const String& getCWD() = 0;
    };
}

/**
 * A static class providing access to system relevant information.
 */
class SystemInfo {
public:
    SystemInfo() = delete;

public:
    /**
     * @return The total number of logical processors on this system.
     */
    static SizeT getNumLogicalProcessors();

    /**
     * @return The total number of physical processors on this system.
     */
    static SizeT getNumPhysicalProcessors();

    /**
     * @return The total number of physical memory on this system.
     */
    static SizeT getPhysicalMemory();

    /**
     * @return The total number of virtual memory on this system.
     */
    static SizeT getVirtualMemory();

    /**
     * @return The total number of unallocated physical memory on this system.
     */
    static SizeT getPhysicalMemoryAvailable();

    /**
     * @return The total number of memory available on this system.
     */
    static SizeT getTotalMemory();

    /**
     * @return The platform name.
     */
    static const String& getPlatformName();

    /**
     * @return The current working directory.
     */
    static const String& getCWD();

private:
    std::unique_ptr<detail::SystemQuery> query;
};

} /* namespace brew */

#endif //BREW_SYSTEMINFO_H
