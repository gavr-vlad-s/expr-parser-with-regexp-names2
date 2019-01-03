/*
    File:    expr_scaner.h
    Created: 25 August 2018 at 10:01 Moscow time
    Author:  Гаврилов Владимир Сергеевич
    E-mails: vladimir.s.gavrilov@gmail.com
             gavrilov.vladimir.s@mail.ru
             gavvs1977@yandex.ru
*/

#ifndef EXPR_SCANER_H
#define EXPR_SCANER_H
#   include <string>
#   include <memory>
#   include <set>
#   include "../include/expr_lexem_info.h"
#   include "../include/location.h"
#   include "../include/errors_and_tries.h"
#   include "../include/error_count.h"
#   include "../include/trie_for_set.h"
#   include "../include/scope.h"
#   include "../include/aux_expr_scaner.h"
#   include "../include/aux_expr_lexem.h"
#   include "../include/abstract_scaner.h"
#   include "../include/position.h"

namespace escaner{
    using Expr_token = ascaner::Token<Expr_lexem_info>;

    class Expr_scaner{
    public:
        Expr_scaner()                        = default;
        Expr_scaner(const Expr_scaner& orig) = default;
        ~Expr_scaner()                       = default;

        Expr_scaner(const ascaner::Location_ptr&     location,
                    const Errors_and_tries&          et,
                    const Trie_for_set_of_char32ptr& trie_for_set,
                    const std::shared_ptr<Scope>&    scope) :
            set_trie_(trie_for_set),
            aux_scaner_(std::make_unique<Aux_expr_scaner>(location, et)),
            et_(et),
            loc_(location),
            scope_(scope)
            {}

        Expr_token  current_lexeme();
        char32_t*   lexeme_begin_ptr() const;
        std::string lexeme_to_string(const Expr_lexem_info& li);
        std::string token_to_string(const Expr_token& tok);
        void        back();
    private:
        Trie_for_set_of_char32ptr set_trie_;
        Aux_expr_scaner_ptr       aux_scaner_;
        Errors_and_tries          et_;
        ascaner::Location_ptr     loc_;
        std::shared_ptr<Scope>    scope_;

        char32_t*                 lexeme_begin_; /* pointer to the lexem begin */
//         Expr_token                token_;
        ascaner::Position_range   lexeme_pos_;

        using Aux_token = ascaner::Token<Aux_expr_lexem_info>;

        Aux_token                 aeti_;
        Aux_expr_lexem_code       aetic_;

        Expr_lexem_info convert_lexeme(const Aux_token&);

        void check_regexp_name(size_t idx);

        enum class State{
            Begin_class_complement, First_char,
            Body_chars,             End_class_complement
        };

        /*
        * The lexeme 'character class complement' can be descripted as the following
        * regular expression:
        *          ab+c
        * where
        *      a is the lexeme 'Begin_char_class_complement',
        *      b is the lexeme 'Character' or 'Character class',
        *      c is the lexeme 'End_char_class_complement'.
        *
        * If we construct a non-deterministic finite automaton by this regexp, next we
        * build a corresponding deterministic finite automaton, and, finally, we
        * minimize the deterministic automaton, then we obtain a finite automaton with
        * the following transition table:
        *
        * |-------|---|---|---|--------------|
        * | State | a | b | c |    Remark    |
        * |-------|---|---|---|--------------|
        * |   A   | B |   |   | Begin state. |
        * |-------|---|---|---|--------------|
        * |   B   |   | C |   |              |
        * |-------|---|---|---|--------------|
        * |   C   |   | C | E |              |
        * |-------|---|---|---|--------------|
        * |   E   |   |   |   | End state.   |
        * |-------|---|---|---|--------------|
        *
        * But for ease of writing, we need to introduce more meaningful names for states
        * of a finite automaton. The following table shows the matching state names from
        * the previous table and meaningful names. Meaningful names are collected in the
        * enumeration State.
        *
        * |---|------------------------|
        * |   |    Meaningful name     |
        * |---|------------------------|
        * | A | Begin_class_complement |
        * |---|------------------------|
        * | B | First_char             |
        * |---|------------------------|
        * | C | Body_chars             |
        * |---|------------------------|
        * | E | End_class_complement   |
        * |---|------------------------|
        *
        */

        State               state_;
        size_t              set_idx_ = 0;

        size_t get_set_complement();

        using State_proc = void (Expr_scaner::*)();


        std::set<char32_t>  curr_set_;

        static State_proc   procs_[];

        void begin_class_complement_proc(); void first_char_proc();
        void body_chars_proc();             void end_class_complement_proc();
    };

    using Expr_scaner_ptr = std::shared_ptr<Expr_scaner>;
};
#endif