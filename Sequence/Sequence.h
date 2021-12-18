//
// Created by fokus on 09.11.2021.
//

#pragma once


template <typename T> class Sequence {
public:
    //decompose
    virtual int GetSize() const = 0;
    virtual T Get(int index) const = 0;
    virtual T GetLast() const = 0;
    virtual T GetFirst() const = 0;
    virtual Sequence<T>* GetSubSequence(int start, int end) = 0;

    //operations
    virtual void Set(int index, T item) = 0;
    virtual Sequence<T>* Concat(Sequence<T>* list) = 0;
    virtual void Append(T item) = 0;
    virtual void Prepend(T item) = 0;
    virtual void InsertAt(T item, int index) = 0;
    virtual void RemoveAt(int index) = 0;

    virtual void Swap(int index1, int index2) = 0;
    virtual Sequence<T>* Clone() = 0;
    // operators
    virtual T operator[](const int index) = 0;

};