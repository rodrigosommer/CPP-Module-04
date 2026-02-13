#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main()
{
	std::cout << "=== Testing Animal polymorphism ===" << std::endl;
	const Animal* meta = new Animal();
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	
	std::cout << "\nTypes:" << std::endl;
	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;
	
	std::cout << "\nSounds (should be specific to each animal):" << std::endl;
	i->makeSound(); // will output the cat sound!
	j->makeSound();
	meta->makeSound();
	
	std::cout << "\nDeleting animals:" << std::endl;
	delete meta;
	delete j;
	delete i;
	
	std::cout << "\n=== Testing Wrong polymorphism (should NOT work) ===" << std::endl;
	const WrongAnimal* wrongMeta = new WrongAnimal();
	const WrongAnimal* wrongCat = new WrongCat();
	
	std::cout << "\nTypes:" << std::endl;
	std::cout << wrongCat->getType() << " " << std::endl;
	
	std::cout << "\nSounds (should be WrongAnimal sound for both):" << std::endl;
	wrongCat->makeSound(); // will output the WrongAnimal sound!
	wrongMeta->makeSound();
	
	std::cout << "\nDeleting wrong animals:" << std::endl;
	delete wrongMeta;
	delete wrongCat;
	
	std::cout << "\n=== Additional tests ===" << std::endl;
	
	std::cout << "\nTesting direct instantiation:" << std::endl;
	Dog dog;
	Cat cat;
	dog.makeSound();
	cat.makeSound();
	
	std::cout << "\nTesting copy constructor:" << std::endl;
	Dog dog2(dog);
	Cat cat2(cat);
	dog2.makeSound();
	cat2.makeSound();
	
	std::cout << "\nTesting assignment operator:" << std::endl;
	Dog dog3;
	Cat cat3;
	dog3 = dog;
	cat3 = cat;
	dog3.makeSound();
	cat3.makeSound();
	
	return 0;
}