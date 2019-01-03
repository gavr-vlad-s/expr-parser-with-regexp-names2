/*
    File:    elem.h
    Created: 23 March 2018 at 15:35 Moscow time
    Author:  Гаврилов Владимир Сергеевич
    E-mails: vladimir.s.gavrilov@gmail.com
             gavrilov.vladimir.s@mail.ru
             gavvs1977@yandex.ru
*/

#ifndef ELEM_H
#define ELEM_H
/**
 * Element of transition table.
 */
#include <cstdint>
template<typename Lexem_code>
struct Elem{
    /** A pointer to a string of characters that can be crossed. */
    char32_t*       symbols_;
    /** lexeme code */
    Lexem_code      code_;
    /** If the current character matches symbols[0], then
     *  the transition to the state first_state;
     *  if the current character matches symbols[1], then
     *  the transition to the state first_state + 1;
     *  if the current character matches symbols[2], then
     *  the transition to the state first_state + 2,
     *  and so on. */
    uint16_t        first_state_;
};
#endif