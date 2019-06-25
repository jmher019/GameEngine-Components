#ifndef PUGGO_ENTITY_FACTORY_TESTER_HPP
#define PUGGO_ENTITY_FACTORY_TESTER_HPP

#include <vector>

#include <EntityFactory.hpp>
#include <UnitTester.hpp>

#ifndef _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif // !_CRTDBG_MAP_ALLOC


namespace puggo {
	class EntityFactoryTester : public UnitTester {
	protected:
		// Run initialization code here
		void initialize() override;

		// Run test functions in here
		void runTests() override;

		// Run clean up code in here
		void cleanUp() override;

	private:
		vector<Entity> entities;

		// Tests if a basic entity with just a transform component can be created
		void createBasicEntity();

		// Tests if a collision box component can be added to an entity
		void createEntityWithCollisionBox();

		// Tests if 1000 entities can be generated
		void generateOneThousandEntities();

		// Tests if 400 entites can be deleted
		void deleteFourHundredEntities();

		// Tests if we can add 300 more entities
		void generateThreeHundredMoreEntities();
	};
}

#endif // !PUGGO_ENTITY_FACTORY_TESTER_HPP
