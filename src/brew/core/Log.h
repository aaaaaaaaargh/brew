/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2017 random arts
 *
 *  Created on: Dec 9, 2015
 *
 */

#ifndef BREW_LOG_H
#define BREW_LOG_H

#include <brew/core/Types.h>
#include <brew/core/String.h>

#include <ostream>
#include <iostream>
#include <functional>
#include <mutex>

namespace brew
{

class AbstractLog;
class LogStream;

/**
 * A log tag describes the current 'topic' of the log stream.
 * In most cases this is the name of the class currently writing into the log.
 */
class LogTag
{
public:
    /**
     * Creates a new log tag.
     * @param tag The display name of the log tag.
     */
	LogTag(const String& tag);

private:
	friend class LogStream;
	String tag;
};

/**
 * Log levels describe how important the current message is (from lowest to highest).
 * Depending on how the application is configured, only messages above a certain log level willl be displayed.
 * In a productive build you most likely don't want to set the log level to 'Debug'.
 */
enum class LogLevel
{
	Debug,
	Info,
	Warning,
	Error
};

/**
 * A log stream is a stream that logs messages (duh!).
 * It is compatible to any structure that can be streamed into a regular std::ostream and therefore
 * doesn't require much work to make your data structures work with it once you've made them to work
 * with the STL streams.
 *
 * Normally you would not want to  create a LogStream instance manually, but use AbstractLog::stream() instead.
 */
class LogStream
{
public:
    /**
     * Creates a new log stream.
     * @param log The log instance.
     */
	LogStream(AbstractLog& log);
	~LogStream();

private:
	friend LogStream logStream(const String&);
	friend class AbstractLog;

    /**
     * Copy constructs a log stream.
     * @param other The log stream to copy from.
     */
	LogStream(const LogStream& other);

	LogStream& operator =(const LogStream&) = delete;

public:
    /**
     * Sets the current log tag.
     * @param tag The new log tag.
     * @return This log stream for chaining.
     */
	LogStream& operator << (const LogTag& tag);

    /**
     * Sets the current log level.
     * @param level The new log level.
     * @return This log stream for chaining.
     */
	LogStream& operator << (const LogLevel& level);

    /**
     * Logs an object to the stream.
     * @tparam T The type of the object to log. Must support std::ostreams.
     * @param value The object to log.
     * @return This log stream for chaining.
     */
	template<typename T>
	LogStream& operator << (const T& value)
	{
		buffer << value;
		return *this;
	}

    /**
     * Manually flushes the stream.
     */
	void flush();

private:
	String currentTag;
	StringStream buffer;
	std::reference_wrapper<AbstractLog> log;

};

/**
 * Base class for logging.
 * There are various logging classes derived from AbstractLog that can be used depending on
 * your requirements.
 * Go with a StreamLog if you just want to display some text in the console or flush the output
 * into a std::fstream.
 */
class AbstractLog
{
public:
	/**
	 * Creates a new log stream.
	 * @param tag The tag name of the log stream.
	 * @return The new log stream instance.
	 */
	LogStream stream(const String& tag="");

	/**
	 * Records a new message to this log.
	 * @param tag The tag name of the message.
	 * @param message The message body.
	 */
	void record(const String& tag, const String& message);

protected:
	/**
	 * Records a new message to this log.
	 * @param tag The tag name of the message.
	 * @param message The message body.
	 */
	virtual void _record(const String& tag, const String& message) = 0;

private:
	std::mutex mutex;

};

/**
 * This class logs messages into a stream. This is the default log implementation.
 */
class StreamLog : public AbstractLog
{
public:
	/**
	 * Creates a new stream log.
	 * @param os The output stream to use for this log.
	 */
	StreamLog(std::ostream& os = std::cout);

protected:
	/**
	 * Records a new message to this log.
	 * @param tag The tag name of the message.
	 * @param message The message body.
	 */
	void _record(const String& tag, const String& message) override;

private:
	std::ostream& ostream;
};

/**
 * NullLog implementation. Logs nowhere.
 */
class NullLog : public AbstractLog
{
protected:
	/**
	 * Records a new message to this log.
	 * @param tag The tag name of the message.
	 * @param message The message body.
	 */
	void _record(const String& tag, const String& message) override;
};

} /* namespace brew */

#endif /* BREW_LOG_H */
