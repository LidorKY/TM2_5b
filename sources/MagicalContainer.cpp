#include "MagicalContainer.hpp"
#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

using namespace std;

/* MagicalContainer */

MagicalContainer::MagicalContainer()
{
    this->container = vector<int>();
    this->primes = vector<int *>();
    this->container.clear();
    this->primes.clear();
}

MagicalContainer::~MagicalContainer()
{
    // Destructor
    for (auto it = this->primes.begin(); it != this->primes.end(); it++)
    {
        delete *it;
    }
}

void MagicalContainer::addElement(int num)
{
    // Find the position to insert the new element
    auto it = lower_bound(this->container.begin(), this->container.end(), num);

    // Insert the new element at the determined position
    this->container.insert(it, num);

    // Check if num is prime
    if (this->isPrime(num))
    {
        // Find the position to insert the new prime
        int *ptr = new int(num);
        auto it_prime = lower_bound(this->primes.begin(), this->primes.end(), ptr, [](int *a, int *b)
                                    { return *a < *b; });
        // Insert the new prime at the determined position
        this->primes.insert(it_prime, ptr);
    }
}

void MagicalContainer::removeElement(int num)
{
    for (auto it = this->container.begin(); it != this->container.end(); it++)
    {
        if (*it == num)
        {
            this->container.erase(it);
            return;
        }
    }
    throw runtime_error("Element not found");
}

int MagicalContainer::size()
{
    // Return size of container
    return this->container.size();
}

bool MagicalContainer::isPrime(int num)
{
    // Check if num is prime
    if (num <= 1)
    {
        return false;
    }
    if (num == 2 || num == 3)
    {
        return true;
    }
    for (int i = 2; i < num; i++)
    {
        if (num % i == 0)
        {
            return false;
        }
    }
    return true;
}

/* AscendingIterator */

MagicalContainer::AscendingIterator::AscendingIterator()
{
    this->index = 0;
    this->pointer_container = nullptr;
}

MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &container)
{
    this->index = 0;
    this->pointer_container = &container;
}
MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &container, size_t index)
{
    this->index = index;
    this->pointer_container = &container;
}
MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator &other)
{
    // Copy constructor
    this->index = other.index;
    this->pointer_container = other.pointer_container;
}

MagicalContainer::AscendingIterator::AscendingIterator(AscendingIterator &&other) noexcept
{
    // Move constructor
    this->index = other.index;
    this->pointer_container = other.pointer_container;
}

MagicalContainer::AscendingIterator::~AscendingIterator()
{
    // Destructor
    this->index = 0;
    this->pointer_container = nullptr;
}

MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other)
{
    // Assignment operator
    if (this->pointer_container != other.pointer_container)
    {
        throw runtime_error("Cannot assign iterator from different container");
    }
    if (this == &other)
    {
        return *this;
    }
    else
    {
        this->index = other.index;
        this->pointer_container = other.pointer_container;
    }
    return *this;
}

MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(AscendingIterator &&other) noexcept
{
    // Move assignment operator
    if (this == &other)
    {
        return *this;
    }
    else
    {
        this->index = other.index;
        this->pointer_container = other.pointer_container;
    }
    return *this;
}

bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &other) const
{
    // Equality operator
    if (this->index == other.index && this->pointer_container == other.pointer_container)
    {
        return true;
    }
    return false;
}

bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &other) const
{
    // Inequality operator
    if (this->index != other.index || this->pointer_container != other.pointer_container)
    {
        return true;
    }
    return false;
}

bool MagicalContainer::AscendingIterator::operator>(const MagicalContainer::AscendingIterator &other) const
{
    // Greater than operator
    if (this->index > other.index)
    {
        return true;
    }
    return false;
}

bool MagicalContainer::AscendingIterator::operator<(const MagicalContainer::AscendingIterator &other) const
{
    // Less than operator
    if (this->index < other.index)
    {
        return true;
    }
    return false;
}

int MagicalContainer::AscendingIterator::operator*()
{
    // Dereference operator
    return this->pointer_container->container.at(this->index);
}

MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++()
{
    // Pre-increment operator
    if (this->index < this->pointer_container->container.size())
    {
        this->index++;
        return *this;
    }
    throw runtime_error("Iterator out of bounds");
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin()
{
    // Begin iterator
    return AscendingIterator(*(this->pointer_container), 0);
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end()
{
    // End iterator
    return AscendingIterator(*(this->pointer_container), this->pointer_container->container.size());
}

/* SideCrossIterator */

MagicalContainer::SideCrossIterator::SideCrossIterator()
{
    container = nullptr;
    index = 0;
    i = 0;
}

MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container)
{
    this->container = &container;
    index = 0;
    i = 0;
}

MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container, size_t index)
{
    this->container = &container;
    this->index = index;
    i = (index % 2 != 0) ? container.container.size() - 1 - index / 2 : index / 2;
}

MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &other)
{
    container = other.container;
    index = other.index;
    i = other.i;
}

MagicalContainer::SideCrossIterator::SideCrossIterator(SideCrossIterator &&other) noexcept
    : container(other.container), index(other.index), i(other.i)
{
    other.container = nullptr;
    other.index = 0;
    other.i = 0;
}

MagicalContainer::SideCrossIterator::~SideCrossIterator() {}

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other)
{
    if (this->container != other.container)
    {
        throw std::runtime_error("Cannot assign iterator from different container");
    }

    if (this != &other)
    {
        this->index = other.index;
        this->i = other.i;
    }
    return *this;
}

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(SideCrossIterator &&other) noexcept
{
    if (this != &other)
    {
        this->container = other.container;
        this->index = other.index;
        this->i = other.i;

        other.container = nullptr;
        other.index = 0;
        other.i = 0;
    }
    return *this;
}

bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const
{
    if (this->container == other.container && this->index == other.index)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &other) const
{
    if (*this == other)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const
{
    if (this->index > other.index)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const
{
    if (this->index < other.index)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int MagicalContainer::SideCrossIterator::operator*()
{
    if (container == nullptr)
    {
        throw std::runtime_error("Iterator not initialized");
    }

    return (*container).container[i];
}

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++()
{
    if (container == nullptr)
    {
        throw std::runtime_error("Iterator not initialized");
    }

    if (index >= (*container).container.size())
    {
        throw std::runtime_error("Iterator out of bounds");
    }

    ++index;

    if (index % 2 != 0)
    {
        i = (*container).container.size() - 1 - index / 2;
    }
    else
    {
        i = index / 2;
    }

    return *this;
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin()
{
    if (container == nullptr)
    {
        throw std::runtime_error("Iterator not initialized");
    }

    return SideCrossIterator(*container, 0);
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end()
{
    if (container == nullptr)
    {
        throw std::runtime_error("Iterator not initialized");
    }

    return SideCrossIterator(*container, (*container).container.size());
}

/* PrimeIterator */

MagicalContainer::PrimeIterator::PrimeIterator()
{
    // Default constructor
    this->prime_index = 0;
    this->pointer_prime_container = nullptr;
}

MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &container)
{
    // Constructor with container argument
    this->prime_index = 0;
    this->pointer_prime_container = &container;
}

MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &container, size_t index)
{
    // Constructor with container and index argument
    this->prime_index = index;
    this->pointer_prime_container = &container;
}

MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other)
{
    // Copy constructor
    this->prime_index = other.prime_index;
    this->pointer_prime_container = other.pointer_prime_container;
}

MagicalContainer::PrimeIterator::PrimeIterator(PrimeIterator &&other) noexcept
{
    // Move constructor
    this->prime_index = other.prime_index;
    this->pointer_prime_container = other.pointer_prime_container;
}

MagicalContainer::PrimeIterator::~PrimeIterator()
{
    // Destructor
}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other)
{
    // Assignment operator
    if (this->pointer_prime_container != other.pointer_prime_container)
    {
        throw runtime_error("Cannot assign iterator from different container");
    }
    if (this == &other)
    {
        return *this;
    }
    else
    {
        this->prime_index = other.prime_index;
        this->pointer_prime_container = other.pointer_prime_container;
    }
    return *this;
}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(PrimeIterator &&other) noexcept
{
    // Move assignment operator
    // if (this == &other)
    // {
    //     return *this;
    // }
    // else
    // {
    //     this->index = other.index;
    //     this->pointer_prime_container = other.pointer_prime_container;
    // }
    return *this;
}

bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator &other) const
{
    // Equality operator
    if (this->prime_index == other.prime_index && this->pointer_prime_container == other.pointer_prime_container)
    {
        return true;
    }
    else
    {
        return false;
    }
    return false;
}

bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &other) const
{
    // Inequality operator
    if (this->prime_index != other.prime_index)
    {
        return true;
    }
    else if (this->pointer_prime_container != other.pointer_prime_container)
    {
        return true;
    }
    return false;
}

bool MagicalContainer::PrimeIterator::operator>(const MagicalContainer::PrimeIterator &other) const
{
    // Greater than operator
    if (this->prime_index > other.prime_index)
    {
        return true;
    }
    return false;
}

bool MagicalContainer::PrimeIterator::operator<(const MagicalContainer::PrimeIterator &other) const
{
    // Less than operator
    if (this->prime_index < other.prime_index)
    {
        return true;
    }
    return false;
}

int MagicalContainer::PrimeIterator::operator*()
{
    // Dereference operator
    return *this->pointer_prime_container->primes.at(this->prime_index);
}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++()
{
    // Pre-increment operator
    if (this->prime_index < this->pointer_prime_container->primes.size())
    {
        this->prime_index++;
        return *this;
    }
    else
    {
        throw runtime_error("Cannot increment iterator past end of container");
    }
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin()
{
    // Begin iterator
    return PrimeIterator(*this->pointer_prime_container, 0);
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end()
{
    // End iterator
    return PrimeIterator(*this->pointer_prime_container, this->pointer_prime_container->primes.size());
}