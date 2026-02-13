#include "MateriaSource.hpp"

MateriaSource::MateriaSource()
{
	std::cout << "MateriaSource constructor called" << std::endl;
	for (int i = 0; i < 4; i++)
		templates[i] = NULL;
}

MateriaSource::MateriaSource(const MateriaSource& other)
{
	std::cout << "MateriaSource copy constructor called" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		if (other.templates[i])
			templates[i] = other.templates[i]->clone();
		else
			templates[i] = NULL;
	}
}

MateriaSource& MateriaSource::operator=(const MateriaSource& other)
{
	std::cout << "MateriaSource copy assignment operator called" << std::endl;
	if (this != &other)
	{
		// Delete current templates
		for (int i = 0; i < 4; i++)
		{
			if (templates[i])
			{
				delete templates[i];
				templates[i] = NULL;
			}
		}
		// Clone new templates
		for (int i = 0; i < 4; i++)
		{
			if (other.templates[i])
				templates[i] = other.templates[i]->clone();
			else
				templates[i] = NULL;
		}
	}
	return *this;
}

MateriaSource::~MateriaSource()
{
	std::cout << "MateriaSource destructor called" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		if (templates[i])
			delete templates[i];
	}
}

void MateriaSource::learnMateria(AMateria* m)
{
	if (!m)
		return;

	for (int i = 0; i < 4; i++)
	{
		if (!templates[i])
		{
			templates[i] = m;
			std::cout << "MateriaSource learned " << m->getType() << " at slot " << i << std::endl;
			return;
		}
	}
	std::cout << "MateriaSource is full, cannot learn more materias!" << std::endl;
	delete m;
}

AMateria* MateriaSource::createMateria(std::string const & type)
{
	for (int i = 0; i < 4; i++)
	{
		if (templates[i] && templates[i]->getType() == type)
		{
			std::cout << "MateriaSource creating " << type << std::endl;
			return templates[i]->clone();
		}
	}
	std::cout << "MateriaSource doesn't know how to create " << type << std::endl;
	return NULL;
}