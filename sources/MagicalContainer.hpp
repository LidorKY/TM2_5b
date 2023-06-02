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
    vector<int> container;
    vector<int *> primes;

public:
    /* Constructor */
    MagicalContainer();
    ~MagicalContainer();

    /* Functions */
    void addElement(int num);
    void removeElement(int num);
    int size();
    bool isPrime(int num);

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
        MagicalContainer *container;
        size_t index;
        size_t i;

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
        PrimeIterator();
        PrimeIterator(MagicalContainer &container);
        PrimeIterator(MagicalContainer &container, size_t index);
        PrimeIterator(const PrimeIterator &other);
        PrimeIterator(PrimeIterator &&other) noexcept; // Move constructor

        /* Destructor */
        ~PrimeIterator();

        /* Assignment operators */
        PrimeIterator &operator=(const PrimeIterator &other);
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

    /* Copy Constructor */
    MagicalContainer(const MagicalContainer &other);

    /* Copy Assignment Operator */
    MagicalContainer &operator=(const MagicalContainer &other);

    /* Move Constructor */
    MagicalContainer(MagicalContainer &&other) noexcept;

    /* Move Assignment Operator */
    MagicalContainer &operator=(MagicalContainer &&other) noexcept;
};
