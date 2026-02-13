#include "IMateriaSource.hpp"
#include "MateriaSource.hpp"
#include "ICharacter.hpp"
#include "Character.hpp"
#include "AMateria.hpp"
#include "Ice.hpp"
#include "Cure.hpp"

int main()
{
	std::cout << "=== Running provided test ===" << std::endl;
	IMateriaSource* src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());

	ICharacter* me = new Character("me");

	AMateria* tmp;
	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);

	ICharacter* bob = new Character("bob");

	me->use(0, *bob);
	me->use(1, *bob);

	delete bob;
	delete me;
	delete src;

	std::cout << "\n=== Additional comprehensive tests ===" << std::endl;
	
	// Test character copying
	std::cout << "\n--- Testing Character deep copy ---" << std::endl;
	Character alice("alice");
	alice.equip(new Ice());
	alice.equip(new Cure());
	
	Character aliceCopy(alice);
	std::cout << "Alice and copy have different addresses: " << (&alice != &aliceCopy) << std::endl;
	
	// Test unequip (should save addresses before unequipping to avoid leaks)
	std::cout << "\n--- Testing unequip ---" << std::endl;
	Character charlie("charlie");
	AMateria* iceMateria = new Ice();
	AMateria* cureMateria = new Cure();
	
	charlie.equip(iceMateria);
	charlie.equip(cureMateria);
	
	// Store addresses to clean up later
	AMateria* unequippedMateria = iceMateria;
	charlie.unequip(0);
	// Now we clean up the unequipped materia
	delete unequippedMateria;
	
	// Test invalid operations
	std::cout << "\n--- Testing invalid operations ---" << std::endl;
	charlie.use(0, alice); // Should do nothing (slot is empty)
	charlie.unequip(10); // Invalid index
	charlie.use(10, alice); // Invalid index
	
	// Test full inventory
	std::cout << "\n--- Testing full inventory ---" << std::endl;
	Character dave("dave");
	dave.equip(new Ice());
	dave.equip(new Cure());
	dave.equip(new Ice());
	dave.equip(new Cure());
	AMateria* extraMateria = new Ice();
	dave.equip(extraMateria); // Should fail - inventory full
	delete extraMateria; // Clean up the materia that couldn't be equipped
	
	// Test MateriaSource
	std::cout << "\n--- Testing MateriaSource ---" << std::endl;
	MateriaSource source;
	source.learnMateria(new Ice());
	source.learnMateria(new Cure());
	
	AMateria* newIce = source.createMateria("ice");
	AMateria* newCure = source.createMateria("cure");
	AMateria* unknown = source.createMateria("lightning"); // Should return NULL
	
	if (newIce)
	{
		std::cout << "Created ice materia: " << newIce->getType() << std::endl;
		delete newIce;
	}
	if (newCure)
	{
		std::cout << "Created cure materia: " << newCure->getType() << std::endl;
		delete newCure;
	}
	if (!unknown)
		std::cout << "Unknown materia creation returned NULL as expected" << std::endl;

	// Test materia assignment
	std::cout << "\n--- Testing Materia assignment (type shouldn't change) ---" << std::endl;
	Ice originalIce;
	Cure originalCure;
	std::cout << "Original ice type: " << originalIce.getType() << std::endl;
	std::cout << "Original cure type: " << originalCure.getType() << std::endl;
	
	// This should not change the type according to the subject
	Ice assignedIce;
	assignedIce = originalIce;
	std::cout << "Assigned ice type (should still be ice): " << assignedIce.getType() << std::endl;

	return 0;
}