#ifndef PUGGO_UNIT_TESTER_HPP
#define PUGGO_UNIT_TESTER_HPP

namespace puggo {
	class UnitTester {
	protected:
		// Run initialization code here
		virtual void initialize() = 0;

		// Run test functions in here
		virtual void runTests() = 0;

		// Run clean up code in here
		virtual void cleanUp() = 0;

	public:
		void run() {
			initialize();
			runTests();
			cleanUp();
		}
	};
}

#endif // !PUGGO_UNIT_TESTER_HPP
