/*
    File:    command.h
    Created: 13 December 2015 at 09:05 Moscow time
    Author:  Гаврилов Владимир Сергеевич
    E-mails: vladimir.s.gavrilov@gmail.com
             gavrilov.vladimir.s@mail.ru
             gavvs1977@yandex.ru
*/

#ifndef COMMAND_H
#define COMMAND_H

#include <vector>
#include <cstddef>
/* This file defines the commands, in which are compiled regular expressions. */
enum class Command_name{
    Or,                    Concat,  Kleene,      Positive,
    Optional,              Char,    Char_class,  Unknown,
    Char_class_complement, Multior, Multiconcat, Regexp_name
};

struct Command{
    size_t action_name_; /* The index of the identifier that is the name of
                          * the action, in the prefix tree of identifiers. */
    Command_name name_;
    union{
        struct {
            size_t first_, second_;
        } args;
        char32_t   c_;
        size_t     idx_of_set_;
        size_t     idx_of_regexp_name_;
    };
};

using Command_buffer = std::vector<Command>;
#endif