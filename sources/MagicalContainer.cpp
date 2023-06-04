#include "MagicalContainer.hpp"
#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

using namespace std;

/* MagicalContainer */

MagicalContainer::MagicalContainer()
{
    this->container = vector<int>(); // Empty vector
    this->primes = vector<int *>();  // Empty vector that holds pointers to primes in order to avoid copying and having O(1) in memory
    this->container.clear();         // Clear vector
    this->primes.clear();            // Clear vector
}

MagicalContainer::~MagicalContainer()
{
    // Destructor
    for (auto it = this->primes.begin(); it != this->primes.end(); it++) // Delete all pointers to primes
    {
        delete *it;
    }
}

void MagicalContainer::addElement(int num)
{
    // Find the position to insert the new element
    auto it = lower_bound(this->container.begin(), this->container.end(), num); // O(log(n)) - Compare by value
    // Insert the new element at the determined position
    this->container.insert(it, num); // O(n)

    // Check if num is prime
    if (this->isPrime(num)) // O(n) - Check if num is prime
    {
        // Find the position to insert the new prime
        int *ptr = new int(num); // Create a pointer to the new prime
        auto it_prime = lower_bound(this->primes.begin(), this->primes.end(), ptr, [](int *a, int *b)
                                    { return *a < *b; }); // O(log(n)) - Compare by value
        // Insert the new prime at the determined position
        this->primes.insert(it_prime, ptr); // O(n) - Insert by value
    }
}

void MagicalContainer::removeElement(int num)
{
    // Find the element
    for (auto it = this->container.begin(); it != this->container.end(); it++) // O(n) - Find the element
    {
        if (*it == num) // O(1) - Compare by value
        {
            this->container.erase(it); // O(n) - Remove the element
            return;
        }
    }
    throw runtime_error("Element not found"); // Element not found
}

int MagicalContainer::size()
{
    return this->container.size(); // O(1) - Return size of container
}

bool MagicalContainer::isPrime(int num)
{
    // Check if num is prime
    if (num <= 1) // O(1) - Check if num is less than 1
    {
        return false;
    }
    if (num == 2 || num == 3) // O(1) - Check if num is 2 or 3
    {
        return true;
    }
    for (int i = 2; i < num; i++) // O(n) - Check if num is divisible by any number between 2 and num
    {
        if (num % i == 0) // O(1) - Check if num is divisible by i
        {
            return false; // num is not prime
        }
    }
    return true; // num is prime
}

/* AscendingIterator */

MagicalContainer::AscendingIterator::AscendingIterator()
{                                      // Default constructor
    this->index = 0;                   // Default index
    this->pointer_container = nullptr; // Default pointer to container
}

MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &container)
{                                         // Constructor
    this->index = 0;                      // Default index
    this->pointer_container = &container; // Pointer to container
}
MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &container, size_t index)
{                                         // Constructor
    this->index = index;                  // Index
    this->pointer_container = &container; // Pointer to container
}
MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator &other)
{
    // Copy constructor
    this->index = other.index;                         // Copy index
    this->pointer_container = other.pointer_container; // Copy pointer to container
}

MagicalContainer::AscendingIterator::AscendingIterator(AscendingIterator &&other) noexcept
{
    // Move constructor
    this->index = other.index;                         // Move index
    this->pointer_container = other.pointer_container; // Move pointer to container
}

MagicalContainer::AscendingIterator::~AscendingIterator()
{
    // Destructor
    this->index = 0;                   // Default index
    this->pointer_container = nullptr; // Default pointer to container
}

MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other)
{
    // Assignment operator
    if (this->pointer_container != other.pointer_container) // Check if iterators are from the same container
    {
        throw runtime_error("Cannot assign iterator from different container"); // Iterators are from different containers
    }
    if (this == &other) // Check if iterators are the same
    {
        return *this; // Iterators are the same
    }
    else
    {
        this->index = other.index;                         // Copy index
        this->pointer_container = other.pointer_container; // Copy pointer to container
    }
    return *this;
}

MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(AscendingIterator &&other) noexcept
{
    // Move assignment operator
    if (this == &other) // Check if iterators are the same
    {
        return *this; // Iterators are the same
    }
    else
    {
        this->index = other.index;                         // Move index
        this->pointer_container = other.pointer_container; // Move pointer to container
    }
    return *this; // Return this
}

bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &other) const
{
    // Equality operator
    if (this->index == other.index && this->pointer_container == other.pointer_container) // Check if iterators are the same
    {
        return true; // Iterators are the same
    }
    return false; // Iterators are not the same
}

bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &other) const
{
    // Inequality operator
    if (this->index != other.index || this->pointer_container != other.pointer_container) // Check if iterators are not the same
    {
        return true; // Iterators are not the same
    }
    return false; // Iterators are the same
}

bool MagicalContainer::AscendingIterator::operator>(const MagicalContainer::AscendingIterator &other) const
{
    // Greater than operator
    if (this->index > other.index) // Check if this index is greater than other index
    {
        return true; // This index is greater than other index
    }
    return false; // This index is not greater than other index
}

bool MagicalContainer::AscendingIterator::operator<(const MagicalContainer::AscendingIterator &other) const
{
    // Less than operator
    if (this->index < other.index) // Check if this index is less than other index
    {
        return true; // This index is less than other index
    }
    return false; // This index is not less than other index
}

int MagicalContainer::AscendingIterator::operator*()
{
    // Dereference operator
    return this->pointer_container->container.at(this->index); // Return value at index
}

MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++()
{
    // Pre-increment operator
    if (this->index < this->pointer_container->container.size()) // Check if index is less than container size
    {
        this->index++; // Increment index
        return *this;  // Return this
    }
    throw runtime_error("Iterator out of bounds"); // Iterator is out of bounds
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin()
{
    // Begin iterator
    return AscendingIterator(*(this->pointer_container), 0); // Return iterator at index 0
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end()
{
    // End iterator
    return AscendingIterator(*(this->pointer_container), this->pointer_container->container.size()); // Return iterator at index container size
}

/* SideCrossIterator */

MagicalContainer::SideCrossIterator::SideCrossIterator()
{
    pointer_container = nullptr;
    index = 0;
    jumping_index = 0;
}

MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container)
{
    this->pointer_container = &container;
    index = 0;
    jumping_index = 0;
}

MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container, size_t index)
{
    this->pointer_container = &container;
    this->index = index;
    if (index % 2 != 0) // Odd index number (right side)
    {
        jumping_index = container.container.size() - 1 - index / 2; // Calculate i for right side
    }
    else
    {
        jumping_index = index / 2; // Calculate i for left side
    }
}

MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &other)
{
    pointer_container = other.pointer_container; // Copy container
    index = other.index;                         // Copy index
    jumping_index = other.jumping_index;         // Copy i
}

MagicalContainer::SideCrossIterator::SideCrossIterator(SideCrossIterator &&other) noexcept
    : pointer_container(other.pointer_container), index(other.index), jumping_index(other.jumping_index)
{
    other.pointer_container = nullptr; // Default container
    other.index = 0;                   // Default index
    other.jumping_index = 0;           // Default i
}

MagicalContainer::SideCrossIterator::~SideCrossIterator() {}

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other)
{
    if (this->pointer_container != other.pointer_container) // Check if iterators are from the same container
    {
        throw std::runtime_error("Cannot assign iterator from different container"); // Iterators are from different containers
    }

    if (this != &other) // Check if iterators are the same
    {
        this->index = other.index;                 // Copy index
        this->jumping_index = other.jumping_index; // Copy i
    }
    return *this;
}

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(SideCrossIterator &&other) noexcept
{
    if (this != &other) // Check if iterators are the same
    {
        this->pointer_container = other.pointer_container; // Move container
        this->index = other.index;                         // Move index
        this->jumping_index = other.jumping_index;         // Move i

        other.pointer_container = nullptr; // Default container
        other.index = 0;                   // Default index
        other.jumping_index = 0;           // Default i
    }
    return *this; // Return this
}

bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const
{
    if (this->pointer_container == other.pointer_container && this->index == other.index) // Check if iterators are the same
    {
        return true; // Iterators are the same
    }
    else
    {
        return false; // Iterators are not the same
    }
}

bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &other) const
{
    if (*this == other) // Check if iterators are the same
    {
        return false; // Iterators are the same
    }
    else
    {
        return true; // Iterators are not the same
    }
}

bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const
{
    if (this->index > other.index) // Check if this index is greater than other index
    {
        return true; // This index is greater than other index
    }
    else
    {
        return false; // This index is not greater than other index
    }
}

bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const
{
    if (this->index < other.index) // Check if this index is less than other index
    {
        return true; // This index is less than other index
    }
    else
    {
        return false; // This index is not less than other index
    }
}

int MagicalContainer::SideCrossIterator::operator*()
{
    if (pointer_container == nullptr) // If container is not initialized
    {
        throw std::runtime_error("Iterator not initialized"); // Iterator is not initialized
    }

    return pointer_container->container[jumping_index]; // Return value at i
}

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++()
{
    if (pointer_container == nullptr) // If container is not initialized
    {
        throw std::runtime_error("Iterator not initialized"); // Iterator is not initialized
    }

    if (index >= pointer_container->container.size()) // If index is out of bounds
    {
        throw std::runtime_error("Iterator out of bounds"); // Iterator is out of bounds
    }

    ++index; // Increment index

    if (index % 2 != 0)
    {
        jumping_index = pointer_container->container.size() - 1 - index / 2; // Calculate i for right side
    }
    else // If index is even, go forwards
    {
        jumping_index = index / 2; // Calculate i for left side
    }

    return *this;
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin()
{
    if (pointer_container == nullptr) // If container is not initialized
    {
        throw std::runtime_error("Iterator not initialized"); // Iterator is not initialized
    }

    return SideCrossIterator(*pointer_container, 0); // Return iterator at index 0
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end()
{
    if (pointer_container == nullptr) // If container is not initialized
    {
        throw std::runtime_error("Iterator not initialized"); // Iterator is not initialized
    }

    return SideCrossIterator(*pointer_container, pointer_container->container.size()); // Return iterator at index size
}

/* PrimeIterator */

MagicalContainer::PrimeIterator::PrimeIterator()
{
    // Default constructor
    this->prime_index = 0;                   // Prime index
    this->pointer_prime_container = nullptr; // Pointer to container
}

MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &container)
{
    // Constructor with container argument
    this->prime_index = 0;                      // Prime index
    this->pointer_prime_container = &container; // Pointer to container
}

MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &container, size_t index)
{
    // Constructor with container and index argument
    this->prime_index = index;                  // Prime index
    this->pointer_prime_container = &container; // Pointer to container
}

MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other)
{
    // Copy constructor
    this->prime_index = other.prime_index;                         // Prime index
    this->pointer_prime_container = other.pointer_prime_container; // Pointer to container
}

MagicalContainer::PrimeIterator::PrimeIterator(PrimeIterator &&other) noexcept
{
    // Move constructor
    this->prime_index = other.prime_index;                         // Prime index
    this->pointer_prime_container = other.pointer_prime_container; // Pointer to container
}

MagicalContainer::PrimeIterator::~PrimeIterator()
{
    // Destructor
}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other)
{
    // Assignment operator
    if (this->pointer_prime_container != other.pointer_prime_container) // If container is not initialized
    {
        throw runtime_error("Cannot assign iterator from different container"); // Throw exception
    }
    if (this == &other) // If same object
    {
        return *this; // Return this
    }
    else // If different object
    {
        this->prime_index = other.prime_index;                         // Prime index
        this->pointer_prime_container = other.pointer_prime_container; // Pointer to container
    }
    return *this;
}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(PrimeIterator &&other) noexcept
{
    // Move assignment operator
    if (this != &other) // If different object
    {
        this->prime_index = other.prime_index;                         // Prime index
        this->pointer_prime_container = other.pointer_prime_container; // Pointer to container

        other.prime_index = 0;                   // Prime index
        other.pointer_prime_container = nullptr; // Pointer to container
    }

    return *this;
}

bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator &other) const
{
    // Equality operator
    if (this->prime_index == other.prime_index && this->pointer_prime_container == other.pointer_prime_container) // If same object
    {
        return true; // Return true if same object and index is same as other index and container is same as other container (same object)
    }
    else if (this->prime_index == other.prime_index && this->pointer_prime_container != other.pointer_prime_container) // If different object
    {
        return false; // Return false if different object and index is same as other index but container is not same as other container (different object)
    }
    return false; // Return false if different object and index is not same as other index and container is not same as other container (different object)
}

bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &other) const
{
    // Inequality operator
    if (this->prime_index != other.prime_index) // If different index (different object)
    {
        return true; // Return true if different index
    }
    else if (this->pointer_prime_container != other.pointer_prime_container) // If different container (different object)
    {
        return true; // Return true if different container
    }
    return false; // Return false if same object
}

bool MagicalContainer::PrimeIterator::operator>(const MagicalContainer::PrimeIterator &other) const
{
    // Greater than operator
    if (this->prime_index > other.prime_index) // If greater than
    {
        return true; // Return true if greater than
    }
    return false; // Return false if not greater than
}

bool MagicalContainer::PrimeIterator::operator<(const MagicalContainer::PrimeIterator &other) const
{
    // Less than operator
    if (this->prime_index < other.prime_index) // If less than
    {
        return true; // Return true if less than
    }
    return false; // Return false if not less than
}

int MagicalContainer::PrimeIterator::operator*()
{
    // Dereference operator
    return *this->pointer_prime_container->primes.at(this->prime_index); // Return value at index
}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++()
{
    // Pre-increment operator
    if (this->prime_index < this->pointer_prime_container->primes.size()) // If index is less than size
    {
        this->prime_index++; // Increment index
        return *this;        // Return this
    }
    else
    {
        throw runtime_error("Cannot increment iterator past end of container"); // Throw exception
    }
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin()
{
    // Begin iterator
    return PrimeIterator(*this->pointer_prime_container, 0); // Return iterator at index 0
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end()
{
    // End iterator
    return PrimeIterator(*this->pointer_prime_container, this->pointer_prime_container->primes.size()); // Return iterator at index size
}