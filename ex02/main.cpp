#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include "Brain.hpp"

int main()
{
	std::cout << "=== Testing the given example ===" << std::endl;
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	delete j; // should not create a leak
	delete i;

	std::cout << "\n=== Testing array of Animals ===" << std::endl;
	const int arraySize = 10;
	Animal* animals[arraySize];

	// Fill half with Dogs, half with Cats
	for (int idx = 0; idx < arraySize; idx++)
	{
		if (idx < arraySize / 2)
			animals[idx] = new Dog();
		else
			animals[idx] = new Cat();
	}

	std::cout << "\nTesting sounds:" << std::endl;
	for (int idx = 0; idx < arraySize; idx++)
	{
		std::cout << "Animal " << idx << " (" << animals[idx]->getType() << "): ";
		animals[idx]->makeSound();
	}

	std::cout << "\nDeleting all animals:" << std::endl;
	for (int idx = 0; idx < arraySize; idx++)
		delete animals[idx];

	std::cout << "\n=== Testing deep copy ===" << std::endl;
	
	// Test Dog deep copy
	std::cout << "\n--- Dog deep copy test ---" << std::endl;
	Dog originalDog;
	originalDog.getBrain()->setIdea(0, "I love bones!");
	originalDog.getBrain()->setIdea(1, "Walkies are the best!");

	std::cout << "\nOriginal dog's ideas:" << std::endl;
	std::cout << "Idea 0: " << originalDog.getBrain()->getIdea(0) << std::endl;
	std::cout << "Idea 1: " << originalDog.getBrain()->getIdea(1) << std::endl;

	Dog copiedDog(originalDog);
	std::cout << "\nCopied dog's ideas (should be the same):" << std::endl;
	std::cout << "Idea 0: " << copiedDog.getBrain()->getIdea(0) << std::endl;
	std::cout << "Idea 1: " << copiedDog.getBrain()->getIdea(1) << std::endl;

	// Modify original to test deep copy
	originalDog.getBrain()->setIdea(0, "Modified idea");
	std::cout << "\nAfter modifying original dog:" << std::endl;
	std::cout << "Original idea 0: " << originalDog.getBrain()->getIdea(0) << std::endl;
	std::cout << "Copied idea 0: " << copiedDog.getBrain()->getIdea(0) << " (should be unchanged)" << std::endl;

	// Test assignment operator
	Dog assignedDog;
	assignedDog = originalDog;
	std::cout << "\nAssigned dog's idea 0: " << assignedDog.getBrain()->getIdea(0) << std::endl;

	// Test Cat deep copy
	std::cout << "\n--- Cat deep copy test ---" << std::endl;
	Cat originalCat;
	originalCat.getBrain()->setIdea(0, "I love fish!");
	originalCat.getBrain()->setIdea(1, "Nap time is sacred!");

	Cat copiedCat(originalCat);
	std::cout << "Original cat's idea 0: " << originalCat.getBrain()->getIdea(0) << std::endl;
	std::cout << "Copied cat's idea 0: " << copiedCat.getBrain()->getIdea(0) << std::endl;

	// Verify they have different brain addresses (deep copy)
	if (originalCat.getBrain() != copiedCat.getBrain())
		std::cout << "SUCCESS: Different brain addresses - deep copy confirmed!" << std::endl;
	else
		std::cout << "ERROR: Same brain addresses - shallow copy detected!" << std::endl;

	return 0;
}