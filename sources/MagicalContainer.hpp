#pragma once
#include <iostream>
#include <vector>

using namespace std;

namespace ariel
{
}

class MagicalContainer
{
private:
    vector<int> container; // The container
    vector<int *> primes;  // The primes in the container

public:
    /* Constructor */
    MagicalContainer();                                  // Default constructor
    ~MagicalContainer();                                 // Destructor
    MagicalContainer(const MagicalContainer &other);     // Copy constructor
    MagicalContainer(MagicalContainer &&other) noexcept; // Move constructor

    /* Copy Assignment Operator */
    MagicalContainer &operator=(const MagicalContainer &other);

    /* Move Assignment Operator */
    MagicalContainer &operator=(MagicalContainer &&other) noexcept;

    /* Functions */
    void addElement(int num);    // Add element to the container
    void removeElement(int num); // Remove element from the container
    int size();                  // Return the size of the container
    bool isPrime(int num);       // Return true if the number is prime, else return false

    class AscendingIterator
    {
    private:
        size_t index;
        MagicalContainer *pointer_container;

    public:
        /* Constructors */
        AscendingIterator();
        AscendingIterator(MagicalContainer &container);
        AscendingIterator(MagicalContainer &container, size_t index);
        AscendingIterator(const AscendingIterator &other);
        AscendingIterator(AscendingIterator &&other) noexcept; // Move constructor

        /* Destructor */
        ~AscendingIterator();

        /* Assignment operators */
        AscendingIterator &operator=(const AscendingIterator &other);
        AscendingIterator &operator=(AscendingIterator &&other) noexcept; // Move assignment operator

        /* Comparison operators */
        bool operator==(const AscendingIterator &other) const;
        bool operator!=(const AscendingIterator &other) const;
        bool operator>(const AscendingIterator &other) const;
        bool operator<(const AscendingIterator &other) const;

        /* Dereference operator */
        int operator*();

        /* Pre-increment operator */
        AscendingIterator &operator++();

        /* Pointers */
        AscendingIterator begin();
        AscendingIterator end();
    };

    class SideCrossIterator
    {
    private:
        size_t index;
        size_t jumping_index;
        MagicalContainer *pointer_container;

    public:
        /* Constructors */
        SideCrossIterator();
        SideCrossIterator(MagicalContainer &container);
        SideCrossIterator(MagicalContainer &container, size_t index);
        SideCrossIterator(const SideCrossIterator &other);
        SideCrossIterator(SideCrossIterator &&other) noexcept; // Move constructor

        /* Destructor */
        ~SideCrossIterator();

        /* Assignment operators */
        SideCrossIterator &operator=(const SideCrossIterator &other);
        SideCrossIterator &operator=(SideCrossIterator &&other) noexcept; // Move assignment operator

        /* Comparison operators */
        bool operator==(const SideCrossIterator &other) const;
        bool operator!=(const SideCrossIterator &other) const;
        bool operator>(const SideCrossIterator &other) const;
        bool operator<(const SideCrossIterator &other) const;

        /* Dereference operator */
        int operator*();

        /* Pre-increment operator */
        SideCrossIterator &operator++();

        /* Pointers */
        SideCrossIterator begin();
        SideCrossIterator end();
    };

    class PrimeIterator
    {
    private:
        size_t prime_index;
        MagicalContainer *pointer_prime_container;

    public:
        /* Constructors */
        PrimeIterator();                                          // Default constructor
        PrimeIterator(MagicalContainer &container);               // Constructor
        PrimeIterator(MagicalContainer &container, size_t index); // Constructor
        PrimeIterator(const PrimeIterator &other);                // Copy constructor
        PrimeIterator(PrimeIterator &&other) noexcept;            // Move constructor

        /* Destructor */
        ~PrimeIterator();

        /* Assignment operators */
        PrimeIterator &operator=(const PrimeIterator &other);     // Copy assignment operator
        PrimeIterator &operator=(PrimeIterator &&other) noexcept; // Move assignment operator

        /* Comparison operators */
        bool operator==(const PrimeIterator &other) const;
        bool operator!=(const PrimeIterator &other) const;
        bool operator>(const PrimeIterator &other) const;
        bool operator<(const PrimeIterator &other) const;

        /* Dereference operator */
        int operator*();

        /* Pre-increment operator */
        PrimeIterator &operator++();

        /* Pointers */
        PrimeIterator begin();
        PrimeIterator end();
    };
};
