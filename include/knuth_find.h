/*
    File:    knuth_find.h
    Created: 22 March 2018 at 19:09 Moscow time
    Author:  Гаврилов Владимир Сергеевич
    E-mails: vladimir.s.gavrilov@gmail.com
             gavrilov.vladimir.s@mail.ru
             gavvs1977@yandex.ru
*/

#ifndef KNUTH_FIND_H
#define KNUTH_FIND_H
#include <utility>
#include <cstddef>
/*
 * It happens that in std::map<K,V> the key type is integer, and a lot of keys with the
 * same corresponding values. If such a map must be a generated constant, then this map
 * can be optimized. Namely, iterating through a map using range-based for, we will
 * build a std::vector<std::pair<K, V>>. Then we group pairs std::pair<K, V> in pairs
 * in the form (segment, a value of type V), where 'segment' is a struct consisting of
 * lower bound and upper bound. Next, we permute the grouped pair in the such way that
 * in order to search for in the array of the resulting values we can use the algorithm
 * from the answer to exercise 6.2.24 of the book
 * Knuth D.E. The art of computer programming. Volume 3. Sorting and search. ---
 * 2nd ed. --- Addison-Wesley, 1998.
*/

#define RandomAccessIterator typename
#define Callable             typename
#define Integral             typename
template<typename T>
struct Segment{
    T lower_bound;
    T upper_bound;

    Segment()               = default;
    Segment(const Segment&) = default;
    ~Segment()              = default;
};

template<typename T, typename V>
struct Segment_with_value{
    Segment<T> bounds;
    V          value;

    Segment_with_value()                          = default;
    Segment_with_value(const Segment_with_value&) = default;
    ~Segment_with_value()                         = default;
};

/* This function uses algorithm from the answer to the exercise 6.2.24 of the monography
 *  Knuth D.E. The art of computer programming. Volume 3. Sorting and search. --- 2nd ed.
 *  --- Addison-Wesley, 1998.
*/
template<RandomAccessIterator I, typename K>
std::pair<bool, size_t> knuth_find(I it_begin, I it_end, K key)
{
    std::pair<bool, size_t> result = {false, 0};
    size_t                  i      = 1;
    size_t                  n      = it_end - it_begin;
    while(i <= n){
        const auto& curr        = it_begin[i - 1];
        const auto& curr_bounds = curr.bounds;
        if(key < curr_bounds.lower_bound){
            i = 2 * i;
        }else if(key > curr_bounds.upper_bound){
            i = 2 * i + 1;
        }else{
            result.first = true; result.second = i - 1;
            break;
        }
    }
    return result;
}
#endif