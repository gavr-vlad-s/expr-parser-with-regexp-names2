/*
    File:    scope.h
    Created: 29 March 2018 at 19:51 Moscow time
    Author:  Гаврилов Владимир Сергеевич
    E-mails: vladimir.s.gavrilov@gmail.com
             gavrilov.vladimir.s@mail.ru
             gavvs1977@yandex.ru
*/

#ifndef SCOPE_H
#define SCOPE_H
#include <map>
#include <cstddef>
#include <cstdint>
enum class Id_kind : uint8_t{
    Scaner_name,   Codes_type_name, Ident_name,
    Code_of_lexem, Lexem_info_name, Action_name,
    Regexp_name
};

/* Id_kinds is a representation of a set of Id_kind: if the bit i is set,
 * then static_cast<Id_kind>(i) belongs to the set, otherwise
 * static_cast<Id_kind>(i) does not belong to the set. */
using Id_kinds = uint8_t;

struct Id_attributes{
    /**
     * The kind of identifier, that is, whether this identifier is the name of the
     * scanner, the name of the type of lexeme codes, the lexeme code, or the name
     * of the action, etc.
     */
    Id_kinds kind_;
    /**
     * The numerical value of the lexeme code, if the identifier is the lexem code.
     */
    size_t   code_       = 0;
    /**
     * The index of the string literal, which is the definition of the action,
     * in the prefix tree of string literals, if the identifier is the name of
     * the action.
     */
    size_t   act_string_ = 0;
};

enum class Str_kind : uint16_t{
    Added_token_fields,        Added_members,           Keyword_repres,
    Delimiter_repres,          Action_definition,       Single_lined_comment_begin,
    Multi_lined_comment_begin, Multi_lined_comment_end, Header_additions,
    Impl_additions,            Init_actions,            Post_actions
};

/* Str_kinds is a representation of a set of Str_kinds: if the bit i is set,
 * then static_cast<Str_kinds>(i) belongs to the set, otherwise
 * static_cast<Str_kinds>(i) does not belong to the set. */
using Str_kinds = uint16_t;

struct Str_attributes{
    /**
     * The type of string literal, that is, whether it is a string representation of
     * the keyword, a string representation of the delimiter, a list of members added
     * to the scanner class, an action definition, the beginning of a single-line
     * comment, the beginning of a multi-line comment, or the end of a multi-line
     * comment.
     */
    Str_kinds kind_;
    /**
     * The lexeme code, if the string literal is a string representation of
     * a keyword or a delimiter.
     */
    size_t code_;
};

using Id_scope  = std::map<size_t, Id_attributes>;

using Str_scope = std::map<size_t, Str_attributes>;

class Scope{
public:
    /// Mapping of indeces of identifiers in the attributes of identifiers.
    Id_scope  idsc_;
    /// Mapping of indeces of string literals in the attributes of string literals.
    Str_scope strsc_;

    Scope()                  = default;
    ~Scope()                 = default;
    Scope(const Scope& orig) = default;
};
#endif