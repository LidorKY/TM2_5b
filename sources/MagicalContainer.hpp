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
    vector<int> primes;

public:
    /* Constructor */
    MagicalContainer();

    /* Functions */
    void addElement(int num);
    void removeElement(int num);
    int size();

    class AscendingIterator
    {
    private:
        unsigned long index;
        MagicalContainer *pointer_container;

    public:
        /* Constructors */
        AscendingIterator();
        AscendingIterator(MagicalContainer container);
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
        unsigned long index;
        MagicalContainer *pointer_container;

    public:
        /* Constructors */
        SideCrossIterator();
        SideCrossIterator(MagicalContainer container);
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
        int &operator*();

        /* Pre-increment operator */
        SideCrossIterator &operator++();

        /* Pointers */
        SideCrossIterator begin();
        SideCrossIterator end();
    };

    class PrimeIterator
    {
    private:
        unsigned long index;
        MagicalContainer *pointer_prime_container;

    public:
        /* Constructors */
        PrimeIterator();
        PrimeIterator(MagicalContainer container);
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
        int &operator*();

        /* Pre-increment operator */
        PrimeIterator &operator++();

        /* Pointers */
        PrimeIterator begin();
        PrimeIterator end();
    };
};