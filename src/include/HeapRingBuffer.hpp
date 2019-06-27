#ifndef PUGGO_HEAP_RING_BUFFER
#define PUGGO_HEAP_RING_BUFFER

namespace puggo {
	template<typename T>
	class HeapRingBuffer {
	private:
		T* buffer = nullptr;
		unsigned int index = 0;
		unsigned int length = 0;
		unsigned int capacity = 0;
		bool freeMemoryInDeallocator = true;

	public:
		HeapRingBuffer() {}

		HeapRingBuffer(const unsigned int& capacity):
			capacity(capacity),
			buffer(new T[capacity]) {
		}

		HeapRingBuffer(const unsigned int& capacity, T* buffer) :
			capacity(capacity),
			buffer(buffer),
			freeMemoryInDeallocator(false) {
		}

		HeapRingBuffer(const HeapRingBuffer&) = delete;
		HeapRingBuffer(HeapRingBuffer&&) = delete;

		~HeapRingBuffer() noexcept {
			if (buffer != nullptr) {
				if (freeMemoryInDeallocator) {
					delete[] buffer;
				}
				buffer = nullptr;
				capacity = 0;
				length = 0;
			}
		}

		// Copy operator
		HeapRingBuffer& operator=(const HeapRingBuffer& ringBuffer) {
			this->~HeapRingBuffer();
			buffer = new T[ringBuffer.capacity];
			capacity = ringBuffer.capacity;
			length = ringBuffer.length;
			index = ringBuffer.index;
			freeMemoryInDeallocator = ringBuffer.freeMemoryInDeallocator;

			for (size_t i = 0; i < length; ++i) {
				unsigned int entry = (index + i) % capacity;
				buffer[entry] = ringBuffer.buffer[entry];
			}

			return *this;
		}

		// Move operator
		HeapRingBuffer& operator=(HeapRingBuffer&& ringBuffer) noexcept {
			this->~HeapRingBuffer();

			buffer = ringBuffer.buffer;
			capacity = ringBuffer.capacity;
			length = ringBuffer.length;
			index = ringBuffer.index;
			freeMemoryInDeallocator = ringBuffer.freeMemoryInDeallocator;

			ringBuffer.buffer = nullptr;
			ringBuffer.capacity = 0;
			ringBuffer.length = 0;
			ringBuffer.index = 0;

			return *this;
		}

		// Returns the max capacity of this ring buffer
		unsigned int getCapacity() const noexcept {
			return capacity;
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
			index = (index + 1) % capacity;
			--length;
			return ptr;
		}

		// Adds a copy of the element to the buffer
		// Returns false if the buffer is full
		bool add(const T& element) {
			if (length == capacity) {
				return false;
			}

			buffer[(index + length) % capacity] = element;
			++length;
			return true;
		}

		// Use this for move semantics with rvalue elements
		// Returns false if the buffer is full
		bool add(T&& element) {
			if (length == capacity) {
				return false;
			}

			buffer[(index + length) % capacity] = move(element);
			++length;
			return true;
		}
	};
}

#endif // !PUGGO_HEAP_RING_BUFFER
