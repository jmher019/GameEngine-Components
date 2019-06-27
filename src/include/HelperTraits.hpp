#ifndef PUGGO_HELPER_TRAITS
#define PUGGO_HELPER_TRAITS

#include <iostream>

namespace puggo {
	template <typename Derived, typename Base>
	constexpr bool extends() {
		return std::is_base_of<Base, Derived>::value;
	}
}

#endif // !PUGGO_HELPER_TRAITS
