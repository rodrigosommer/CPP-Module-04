#include "Character.hpp"

Character::Character() : name("unnamed")
{
	std::cout << "Character default constructor called" << std::endl;
	for (int i = 0; i < 4; i++)
		inventory[i] = NULL;
}

Character::Character(std::string const & name) : name(name)
{
	std::cout << "Character constructor called for: " << name << std::endl;
	for (int i = 0; i < 4; i++)
		inventory[i] = NULL;
}

Character::Character(const Character& other) : name(other.name)
{
	std::cout << "Character copy constructor called" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		if (other.inventory[i])
			inventory[i] = other.inventory[i]->clone();
		else
			inventory[i] = NULL;
	}
}

Character& Character::operator=(const Character& other)
{
	std::cout << "Character copy assignment operator called" << std::endl;
	if (this != &other)
	{
		name = other.name;
		// Delete current materias
		for (int i = 0; i < 4; i++)
		{
			if (inventory[i])
			{
				delete inventory[i];
				inventory[i] = NULL;
			}
		}
		// Clone new materias
		for (int i = 0; i < 4; i++)
		{
			if (other.inventory[i])
				inventory[i] = other.inventory[i]->clone();
			else
				inventory[i] = NULL;
		}
	}
	return *this;
}

Character::~Character()
{
	std::cout << "Character destructor called for: " << name << std::endl;
	for (int i = 0; i < 4; i++)
	{
		if (inventory[i])
			delete inventory[i];
	}
}

std::string const & Character::getName() const
{
	return name;
}

void Character::equip(AMateria* m)
{
	if (!m)
		return;
	
	for (int i = 0; i < 4; i++)
	{
		if (!inventory[i])
		{
			inventory[i] = m;
			std::cout << name << " equipped " << m->getType() << " at slot " << i << std::endl;
			return;
		}
	}
	std::cout << name << "'s inventory is full!" << std::endl;
}

void Character::unequip(int idx)
{
	if (idx >= 0 && idx < 4 && inventory[idx])
	{
		std::cout << name << " unequipped " << inventory[idx]->getType() << " from slot " << idx << std::endl;
		inventory[idx] = NULL;
	}
	else
	{
		std::cout << name << " has nothing to unequip at slot " << idx << std::endl;
	}
}

void Character::use(int idx, ICharacter& target)
{
	if (idx >= 0 && idx < 4 && inventory[idx])
	{
		inventory[idx]->use(target);
	}
	else
	{
		std::cout << name << " has nothing to use at slot " << idx << std::endl;
	}
}