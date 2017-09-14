/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2017 random arts
 *
 *  Created on: Dec 14, 2015
 *
 */

#ifndef BREW_ABSTRACTBUFFER_H
#define BREW_ABSTRACTBUFFER_H

#include <ios>
#include <stdexcept>
#include <type_traits>

#include "Types.h"

namespace brew {

/**
 * This class represents a generic interface for buffer-like objects.
 * Hereby, any object is considered as 'buffer' that has a finite size and
 * supports random write and read access.
 */
class AbstractBuffer {
 public:
  explicit AbstractBuffer(SizeT numBytes) : size(numBytes) {}
  virtual ~AbstractBuffer() = default;

 protected:
  /**
   * AbstractBuffer interface
   */

  /**
   * Writes data into the buffer.
   * @param data A pointer to the data to write.
   * @param offset The offset to write the data to.
   * @param len The size of the data.
   */
  virtual void onWrite(const Byte* data, SizeT offset, SizeT len) = 0;

  /**
   * Reads data from the buffer.
   * @param dest A raw pointer to the destination.
   * @param offset The offset to read from.
   * @param len The size of the data.
   * @return The number of bytes read.
   */
  virtual SizeT onRead(Byte* dest, SizeT offset, SizeT len) const = 0;

 public:
  /**
   * Writes data into the buffer.
   * @param data A pointer to the data to write.
   * @param offset The offset to write the data to.
   * @param len The size of the data.
   */
  void write(const Byte* data, SizeT offset, SizeT len);

  /**
   * Reads data from the buffer.
   * @param dest A raw pointer to the destination.
   * @param offset The offset to read from.
   * @param len The size of the data.
   * @return The number of bytes read.
   */
  SizeT read(Byte* dest, SizeT offset, SizeT len) const;

  /**
   * Writes an object of type T to this buffer.
   * @param dest The object to read the data from.
   * @param offset The offset from which to start writing.
   * @param num The number of T objects to write.
   */
  template <typename T>
  void write(T* dest, SizeT offset, SizeT num = 1) {
    const SizeT n = sizeof(T) * num;
    if (offset + n > size)
      throw std::overflow_error("Buffer overflow while writing");
    write(reinterpret_cast<const Byte*>(dest), offset, n);
  }

  /**
   * Reads an object of type T from this buffer.
   * @param dest The object to write the data into.
   * @param offset The offset from which to read a T object
   * @param num The number of T objects to read.
   */
  template <typename T>
  SizeT read(T* dest, SizeT offset, SizeT num = 1) const {
    const SizeT n = sizeof(T) * num;
    if (offset + n > size)
      throw std::overflow_error("Buffer overflow while reading");
    return read(reinterpret_cast<Byte*>(dest), offset, n);
  }

  /**
   * @return the finite size of this buffer.
   */
  inline SizeT getSize() const { return size; }

  /**
   * Attempts to copy this buffer into another buffer. Uses an internal buffer
   * for chunk reading/writing of the data.
   * @param target The target buffer to write into.
   * @param targetOffset The offset to start writing. The target buffer needs to
   *                     be at least targetOffset+len (or this buffers size if len=0).
   * @param srcOffset The source offset to read from.
   * @param len The number of bytes to copy or 0 to write the entire buffer.
   */
  void copyTo(AbstractBuffer& target, SizeT targetOffset = 0,
              SizeT srcOffset = 0, SizeT len = 0) const;

 private:
  SizeT size;
};

} /* namespace brew */

#endif //BREW_ABSTRACT_BUFFFER_H
