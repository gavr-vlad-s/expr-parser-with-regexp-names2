/*
    File:    error_count.cpp
    Created: 13 December 2015 at 09:05 Moscow time
    Author:  Гаврилов Владимир Сергеевич
    E-mails: vladimir.s.gavrilov@gmail.com
             gavrilov.vladimir.s@mail.ru
             gavvs1977@yandex.ru
*/

#include <cstdio>
#include "../include/error_count.h"

void Error_count::increment_number_of_errors()
{
    number_of_errors_++;
}

size_t Error_count::get_number_of_errors() const
{
    return number_of_errors_;
}

void Error_count::print() const
{
    printf("\nTotal errors %zu\n", number_of_errors_);
}