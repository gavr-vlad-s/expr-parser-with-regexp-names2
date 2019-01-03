/*
    File:    aux_expr_scaner.h
    Created: 20 July 2017 at 12:14 Moscow time
    Author:  Гаврилов Владимир Сергеевич
    E-mails: vladimir.s.gavrilov@gmail.com
             gavrilov.vladimir.s@mail.ru
             gavvs1977@yandex.ru
*/

#ifndef AUX_EXPR_SCANER_H
#define AUX_EXPR_SCANER_H

#include <string>
#include <memory>
#include "../include/abstract_scaner.h"
#include "../include/error_count.h"
#include "../include/trie.h"
#include "../include/aux_expr_lexem.h"

class Aux_expr_scaner : public ascaner::Abstract_scaner<Aux_expr_lexem_info>{
public:
    Aux_expr_scaner()                            = default;
    Aux_expr_scaner(const ascaner::Location_ptr& location, const Errors_and_tries& et) :
        ascaner::Abstract_scaner<Aux_expr_lexem_info>(location, et) {};
    Aux_expr_scaner(const Aux_expr_scaner& orig) = default;
    virtual ~Aux_expr_scaner()                   = default;
    ascaner::Token<Aux_expr_lexem_info> current_lexeme() override;
    std::string lexeme_to_string(const Aux_expr_lexem_info& li) override;
private:
    enum Automaton_name{
        A_start, A_backslash, A_maybe_class, A_class,
        A_hat,   A_action,    A_regexp_name
    };
    Automaton_name automaton_; /* current automaton */

    typedef bool (Aux_expr_scaner::*Automaton_proc)();
    /* It is the type of the pointer on function-member that implements
     * the state machine that handles the lexem. The function should
     * return true if the token has not been read to the end,
     * and false otherwise. */

    typedef void (Aux_expr_scaner::*Final_proc)();
    /* It is the type of the pointer on function-member that performs
     * the necessary actions in case of unexpected end of lexem. */

    static Automaton_proc procs_[];
    static Final_proc     finals_[];
    /* functions for handling lexems: */
    bool start_proc();       bool backslash_proc();
    bool maybe_class_proc(); bool class_proc();
    bool hat_proc();         bool action_proc();
    bool regexp_name_proc();
    /* functions to perform actions in case of unexpected end of lexem */
    void none_final_proc();         void backslash_final_proc();
    void maybe_class_final_proc();  void class_final_proc();
    void hat_final_proc();          void action_final_proc();
    void regexp_name_final_proc();
    /* If the lexem most likely is character class, then the following
     * function corrects lexem code, and displays the needed diagnostic
     * messsage. */
    void correct_class();
};

using Aux_expr_scaner_ptr = std::unique_ptr<Aux_expr_scaner>;
#endif