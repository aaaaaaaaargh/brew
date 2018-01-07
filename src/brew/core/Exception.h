/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 random arts
 *
 *  Created on: 04.09.17
 *
 */

#ifndef BREW_EXCEPTION_H
#define BREW_EXCEPTION_H

#include <brew/core/Types.h>

#include <exception>

namespace brew {

/**
 * A basic exception class for BREW exceptions.
 */
class Exception : public std::exception {
public:
    explicit Exception(const String& what);
    explicit Exception(const char* what);
public:
    const char* what() const throw() override;

private:
    String message;
};

/**
 * A buffer overflow exception.
 */
class BufferOverflowException : public Exception {
public:
    using Exception::Exception;
};

/**
 * An exception for illegal access to a resource.
 */
class IllegalAccessException : public Exception {
public:
    using Exception::Exception;
};

/**
 * An exception for illegal transition of a resources state.
 */
class IllegalStateException : public Exception {
public:
    using Exception::Exception;
};

/**
 * An exception for runtime errors.
 */
class RuntimeException : public Exception {
public:
    using Exception::Exception;
};

/**
 * A special class for input/output exceptions.
 */
class IOException : public Exception {
public:
    using Exception::Exception;
};

/**
 * A special class for not found exceptions.
 */
class NotFoundException : public Exception {
public:
    using Exception::Exception;
};

/**
 * A special class for invalid argument exceptions.
 */
class InvalidArgumentException : public Exception {
public:
    using Exception::Exception;
};

/**
 * A special class for unsupported operations.
 */
class NotSupportedException : public Exception {
public:
    using Exception::Exception;
};

} /* namespace brew */

#endif //BREW_EXCEPTION_H
