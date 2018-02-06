/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2017 r.acc
 *
 *  TimeMeasure.cpp
 *
 *  Created on: May 27, 2016
 *      Author: void
 */

#include <brew/core/Counter.h>
#include <iostream>
#include <brew/math/Math.h>

namespace brew {

const SizeT Counter::DefaultSampleSize = 15;

Counter::Counter(SizeT sampleSize) :
		buffer(sampleSize),
		average(0), best(std::numeric_limits<u32>::max()),
		worst(0) {
	last = std::chrono::high_resolution_clock::now();
}

void Counter::measure() {
	auto now = std::chrono::high_resolution_clock::now();
	Real v = std::chrono::duration_cast<std::chrono::milliseconds>(now - last).count() * 0.001f;

	if (v >= math::EPSILON) {
		// Only record relevant delta values.
		last = now;
		buffer.push(v);
		updateCachedValues();
	}
}

void Counter::clear() {

	last = std::chrono::high_resolution_clock::now();
	best = average = worst = 0;
	for (auto& i : buffer) {
		i = 0;
	}

}

void Counter::updateCachedValues() {
	average = 0;
	SizeT n = 0;

	for (auto& i : buffer) {
		if (i == 0)
			continue;
		n++;

		best = std::min(best, i);
		worst = std::max(worst, i);

		average += i;
	}

	average /= n;
}

} /* namespace brew */
