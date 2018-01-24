/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2017 r.acc
 *
 *  TimeMeasure.h
 *
 *  Created on: May 27, 2016
 *      Author: void
 */

#ifndef BREW_COUNTER_H
#define BREW_COUNTER_H

#include <brew/core/Types.h>
#include <brew/core/RingBuffer.h>

#include <chrono>

namespace brew {

/**
 * A simple class to count stuff.
 */
class Counter {

public:
	enum class MeasureFormat {
		PerSecond,
		MicroSeconds
	};

public:
	/**
	 * Creates a new counter.
	 * @param sampleSize The maximum number of samples to use.
	 */
	explicit Counter(const SizeT& sampleSize = 5);

	/**
	 * @return The average delta time between the measured samples.
	 */
	inline Real getAverage() const {
		return average;
	}

	/**
	 * @return The best delta time between the measured samples.
	 */
	inline Real getBest() const {
		return best;
	}

	/**
	 * @return The worst delta time between the measured samples.
	 */
	inline Real getWorst() const {
		return worst;
	}

	/**
	 * Clears the buffered samples.
	 */
	void clear();

	/**
	 * Records a new sample.
	 */
	void measure();

private:
	void updateCachedValues();

private:
	RingBuffer<Real> buffer;
	Real average, best, worst;
	std::chrono::high_resolution_clock::time_point last;

};

} /* namespace brew */

#endif /* BREW_COUNTER_H */
