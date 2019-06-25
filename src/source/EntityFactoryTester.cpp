#include <EntityFactoryTester.hpp>

using namespace puggo;

void EntityFactoryTester::initialize() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	EntityFactory::initialize();
}

void EntityFactoryTester::cleanUp() {
	EntityFactory::cleanUp();
}

void EntityFactoryTester::runTests() {
	createBasicEntity();
	createEntityWithCollisionBox();
	generateOneThousandEntities();
	deleteFourHundredEntities();
	generateThreeHundredMoreEntities();
}

void EntityFactoryTester::createBasicEntity() {
	cout << "running: " << __func__ << endl;

	Entity entity = EntityFactory::createBasicEntity();
	
	assert(entity.flags.transform);
	assert(EntityFactory::doesEntityExist(entity));
	entities.push_back(entity);

	cout << __func__ << ": successful" << endl;
}

void EntityFactoryTester::createEntityWithCollisionBox() {
	cout << "running: " << __func__ << endl;

	Entity entity = EntityFactory::createBasicEntity();
	EntityFactory::addComponent(entity, Components::COLLISION_BOX);
	
	assert(entity.flags.collisionBox);
	assert(EntityFactory::doesEntityExist(entity));
	entities.push_back(entity);

	cout << __func__ << ": successful" << endl;
}

void EntityFactoryTester::generateOneThousandEntities() {
	cout << "running: " << __func__ << endl;

	size_t initialSize = entities.size();

	for (size_t i = 0; i < 1000; ++i) {
		Entity entity = EntityFactory::createBasicEntity();
		entities.push_back(entity);
	}

	assert(entities.size() - initialSize == 1000);

	cout << __func__ << ": successful" << endl;
}

void EntityFactoryTester::deleteFourHundredEntities() {
	cout << "running: " << __func__ << endl;

	size_t initialSize = entities.size();
	for (size_t i = 0; i < 400; ++i) {
		EntityFactory::deleteEntity(entities[i]);
	}
	entities.erase(entities.begin(), entities.begin() + 400);

	assert(initialSize - entities.size() == 400);

	cout << __func__ << ": successful" << endl;
}

void EntityFactoryTester::generateThreeHundredMoreEntities() {
	cout << "running: " << __func__ << endl;

	size_t initialSize = entities.size();
	for (size_t i = 0; i < 300; ++i) {
		Entity entity = EntityFactory::createBasicEntity();
		entities.push_back(entity);
	}

	assert(entities.size() - initialSize == 300);

	cout << __func__ << ": successful" << endl;
}