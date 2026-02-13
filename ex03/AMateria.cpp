#include "AMateria.hpp"
#include "ICharacter.hpp"

AMateria::AMateria(std::string const & type) : type(type)
{
	std::cout << "AMateria constructor called for type: " << type << std::endl;
}

AMateria::AMateria(const AMateria& other) : type(other.type)
{
	std::cout << "AMateria copy constructor called" << std::endl;
}

AMateria& AMateria::operator=(const AMateria& other)
{
	std::cout << "AMateria copy assignment operator called" << std::endl;
	if (this != &other)
	{
		// Note: we don't assign type because "copying the type doesn't make sense"
	}
	return *this;
}

AMateria::~AMateria()
{
	std::cout << "AMateria destructor called for type: " << type << std::endl;
}

std::string const & AMateria::getType() const
{
	return type;
}

void AMateria::use(ICharacter& target)
{
	std::cout << "* uses some materia on " << target.getName() << " *" << std::endl;
}