/*
    File:    expr_parser.cpp
    Created: 05 January 2019 at 15:09 Moscow time
    Author:  Гаврилов Владимир Сергеевич
    E-mails: vladimir.s.gavrilov@gmail.com
             gavrilov.vladimir.s@mail.ru
             gavvs1977@yandex.ru
*/

#include <cstdio>
#include <string>
#include <memory>
#include "../include/get_processed_text.h"
#include "../include/location.h"
#include "../include/errors_and_tries.h"
#include "../include/error_count.h"
#include "../include/char_trie.h"
#include "../include/scope.h"
#include "../include/expr_scaner.h"
#include "../include/trie_for_set.h"
#include "../include/char_conv.h"

static const char* usage_str =
    R"~(expr-parser-test, программа для тестирования синтаксического разбора регулярных
выражений, являющегося составной частью генератора лексических анализаторов Мяука.
Версия 2.0. (c) Гаврилов Владимир Сергеевич, 2015-2019.

Данная программа является свободным программным обеспечением с открытым исходным
текстом и распространяется под лицензией GPLv3.

Данное программное обеспечение предоставляется КАК ЕСТЬ,
без предоставления каких-либо гарантий.

Использование:
    expr-parser-test файл-с-тестом
)~";

enum Myauka_exit_codes{
    Success, No_args, File_processing_error, Syntax_error
};

// static void add_regexp_name(Errors_and_tries&       etr,
//                             std::shared_ptr<Scope>& scope,
//                             const std::u32string&   name)
// {
//     Id_attributes iattr;
//     iattr.kind_             = 1u << static_cast<uint8_t>(Id_kind::Regexp_name);
//     size_t        idx       = etr.ids_trie_ -> insert(name);
//     scope->idsc_[idx]       = iattr;
//
//     auto name_in_utf8 = u32string_to_utf8(name);
//     printf("Index of regexp name %s is %zu.\n", name_in_utf8.c_str(), idx);
// }
//
// static const std::u32string regexp_names[] = {
//     U"decimal_code", U"octal_code",   U"binary_code",
//     U"hex_code",     U"char_by_code", U"quoted_string",
//     U"full_string"
// };
//
// static void add_regexp_names(Errors_and_tries&       etr,
//                              std::shared_ptr<Scope>& scope)
// {
//     for(const auto& n : regexp_names){
//         add_regexp_name(etr, scope, n);
//     }
// }

int main(int argc, char* argv[])
{
    if(1 == argc){
        printf(usage_str, argv[0]);
        return No_args;
    }
    auto              text   = get_processed_text(argv[1]);
    if(!text.length()){
        return File_processing_error;
    }

    char32_t*         p      = const_cast<char32_t*>(text.c_str());
    auto              loc    = std::make_shared<ascaner::Location>(p);
    Errors_and_tries  et;
    et.ec_                   = std::make_shared<Error_count>();
    et.ids_trie_             = std::make_shared<Char_trie>();
    et.strs_trie_            = std::make_shared<Char_trie>();
    auto              scp    = std::make_shared<Scope>();

//     add_regexp_names(et, scp);
    auto              ts     = std::make_shared<Trie_for_set_of_char32>();
    auto              exprsc = std::make_shared<escaner::Expr_scaner>(loc, et, ts, scp);

    return Success;
}