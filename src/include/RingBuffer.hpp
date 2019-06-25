#ifndef PUGGO_RING_BUFFER_HPP
#define PUGGO_RING_BUFFER_HPP

namespace puggo {
	template<typename T, unsigned int Size>
	class RingBuffer {
	private:
		T buffer[Size];
		unsigned int index = 0;
		unsigned int length = 0;

	public:
		// Returns the max capacity of this ring buffer
		constexpr unsigned int getCapacity() const noexcept {
			return Size;
		}

		// Returns the number of items in the ring buffer
		unsigned int getLength() const noexcept {
			return length;
		}

		// Clears the buffer
		void clear() noexcept {
			length = 0;
		}

		// Returns the next element in the buffer and updates the head pointer to the next element
		// If the buffer is empty, nullptr will be returned
		T* extractNext() {
			if (length == 0) {
				return nullptr;
			}

			T* ptr = &buffer[index];
			index = (index + 1) % Size;
			--length;
			return ptr;
		}

		// Adds a copy of the element to the buffer
		// Returns false if the buffer is full
		bool add(const T& element) {
			if (length == Size) {
				return false;
			}

			buffer[(index + length) % Size] = element;
			++length;
			return true;
		}

		// Use this for move semantics with rvalue elements
		// Returns false if the buffer is full
		bool add(T&& element) {
			if (length == Size) {
				return false;
			}
			
			buffer[(index + length) % Size] = move(element);
			++length;
			return true;
		}
	};
}

#endif // !PUGGO_RING_BUFFER_HPP
