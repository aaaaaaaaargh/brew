/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: May 27, 2016
 *
 */

#ifndef BREW_RINGBUFFER_H
#define BREW_RINGBUFFER_H

#include <brew/core/Types.h>
#include <vector>

namespace brew {

/**
 * A generic ring buffer implementation.
 * @tparam T The type of the buffer contents.
 */
template<typename T>
class RingBuffer {
public:
	/**
	 * Constructs a new ring buffer.
	 * @param size The given maximum size of the buffer.
	 */
	RingBuffer(const SizeT& size)
	: offset(0) {
		elements.resize(size);
	}

    /**
     * Adds a new element to the buffer.
     * @param t The element to add.
     */
	void push(const T& t) {
		elements[offset] = t;
		if(++offset >= elements.size()) {
			offset = 0;
		}
	}

    /**
     * Iterator implementation for ring buffers.
     * @tparam U The element type.
     * @tparam RingBufferT The ring buffer type.
     */
	template<typename U=T, class RingBufferT=RingBuffer<T> >
	class IteratorType {
        typedef IteratorType<U, RingBufferT> type;
		friend RingBufferT;
		RingBufferT& buf;
		s32 cur;

	private:
        /**
         * Creates a new iteator. Use RingBuffer::begin() with iterator arithmetic instead.
         * @param buf The buffer.
         * @param cur The current index.
         */
		IteratorType(RingBufferT& buf, s32 cur) : buf(buf), cur(cur) {
		}

	public:
        /**
         * Increments the iterator
         * @return The iterator pointing to the next element or RingBuffer::end() if not available.
         */
		IteratorType<U, RingBufferT>& operator ++() {
			if(++cur >= buf.elements.size()) {
				cur = -1;
			}
			return *this;
		}

        /**
         * @return A reference to the associated object.
         */
		inline U& operator *() const {
			return buf.elements[cur];
		}

        /**
         * @return A raw pointer to the referenced object.
         */
		inline U* operator ->() const {
			return &buf.elements[cur];
		}

        /**
         * Performs a comparison with another iterator.
         * @param other The other iterator.
         * @return Whether both iterators are equal.
         */
		inline bool operator == (const type& other) const {
			return other.cur == cur;
		}

        /**
         * Performs a comparison with another iterator.
         * @param other The other iterator.
         * @return Whether both iterators are unequal.
         */
		inline bool operator != (const type& other) const {
			return other.cur != cur;
		}
	};

	typedef IteratorType<T, RingBuffer<T> > iterator;
	typedef IteratorType<const T, const RingBuffer<T> > const_iterator;

    /**
     * @return An iterator referencing the first element.
     */
	iterator begin() {
		return iterator(*this, 0);
	}

    /**
     * @return A const iterator referencing the first element.
     */
	const_iterator cbegin() const {
		return const_iterator(*this, 0);
	}

    /**
     * @return An iterator referencing the last element.
     */
	iterator end() {
		return iterator(*this, -1);
	}

    /**
     * @return A const iterator referencing the last element.
     */
	const_iterator end() const {
		return const_iterator(*this, -1);
	}

    /**
     * @return The current size of this buffer.
     */
	inline SizeT size() const {
		return elements.size();
	}

private:
	SizeT offset;
	std::vector<T> elements;
};

} /* namespace brew */

#endif /* BREW_RINGBUFFER_H */
