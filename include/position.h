/*
    File:    position.h
    Created: 06 August 2018 at 10:40 Moscow time
    Author:  Гаврилов Владимир Сергеевич
    E-mails: vladimir.s.gavrilov@gmail.com
             gavrilov.vladimir.s@mail.ru
             gavvs1977@yandex.ru
*/

#ifndef POSITION_H
#define POSITION_H
#   include <cstddef>
namespace ascaner{
    struct Position{
        Position()                           = default;
        Position(const Position&)            = default;
        ~Position()                          = default;
        Position& operator=(const Position&) = default;

        Position(size_t line_no, size_t line_pos) :
            line_no_(line_no), line_pos_(line_pos) {}

        size_t line_no_  = 1;
        size_t line_pos_ = 1;
    };

    struct Position_range{
        Position begin_pos_;
        Position end_pos_;
    };
};
#endif