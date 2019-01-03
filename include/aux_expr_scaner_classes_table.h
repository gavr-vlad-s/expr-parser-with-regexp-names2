/*
    File:    aux_expr_scaner_classes_table.h
    Created: 03 April 2018 at 18:53 Moscow time
    Author:  Гаврилов Владимир Сергеевич
    E-mails: vladimir.s.gavrilov@gmail.com
             gavrilov.vladimir.s@mail.ru
             gavvs1977@yandex.ru
*/

#ifndef AUX_EXPR_SCANER_CLASSES_TABLE_H
#define AUX_EXPR_SCANER_CLASSES_TABLE_H
#include "../include/elem.h"
#include "../include/aux_expr_lexem.h"
/* For the keyword processing automaton, the member state of the class Main_scaner
 * is the index of the element in the transition table, denoted below as
 * a_keyword_jump_table. */
extern const Elem<Aux_expr_lexem_code> a_classes_jump_table[];
#endif