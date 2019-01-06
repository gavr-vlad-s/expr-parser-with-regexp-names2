/*
    File:    abstract_scaner.h
    Created: 06 August 2018 at 10:30 Moscow time
    Author:  Гаврилов Владимир Сергеевич
    E-mails: vladimir.s.gavrilov@gmail.com
             gavrilov.vladimir.s@mail.ru
             gavvs1977@yandex.ru
*/

#ifndef ABSTRACT_SCANER_H
#define ABSTRACT_SCANER_H
#   include <cstddef>
#   include <cstdint>
#   include <string>
#   include <memory>
#   include "../include/position.h"
#   include "../include/location.h"
#   include "../include/errors_and_tries.h"
#   include "../include/error_count.h"
#   include "../include/char_trie.h"
namespace ascaner{
    template<typename Lexeme_type>
    struct Token{
        Token() = default;
        Position_range range_;
        Lexeme_type    lexeme_;
    };

    template<typename Lexeme_type>
    class Abstract_scaner{
    public:
        Abstract_scaner<Lexeme_type>()                       = default;
        Abstract_scaner(const Location_ptr& location, const Errors_and_tries& et);
        Abstract_scaner(const Abstract_scaner<Lexeme_type>&) = default;
        virtual ~Abstract_scaner<Lexeme_type>()              = default;

        /*  Function back() return the current lexem into the input stream. */
        void                back();

        /* Function current_lexeme() returns information about current lexem,
         * i.e. returns a lexeme code and a lexeme value. */
        virtual Token<Lexeme_type> current_lexeme() = 0;

        Position_range      lexeme_pos()       const;
        char32_t*           lexeme_begin_ptr() const;

        virtual std::string lexeme_to_string(const Lexeme_type& li) = 0;

        std::string token_to_string(const Token<Lexeme_type>& tok);
    protected:
        int                          state_; //< the current state of the current automaton
        Location_ptr                 loc_;
        char32_t*                    lexeme_begin_; /* pointer to the lexem begin */
        char32_t                     ch_;           /* current character */

        /* set of categories for the current character */
        uint64_t                     char_categories_;

        /* intermediate value of the lexem information */
        Token<Lexeme_type>           token_;

        Position_range               lexeme_pos_;

        /* a pointer to a class that counts the number of errors: */
        std::shared_ptr<Error_count> en_;
        /* a pointer to the prefix tree for identifiers: */
        std::shared_ptr<Char_trie>   ids_;
        /* a pointer to the prefix tree for string literals: */
        std::shared_ptr<Char_trie>   strs_;

        /* buffer for writing the processed identifier or string: */
        std::u32string               buffer_;
    };

    template<typename Lexem_type>
    Abstract_scaner<Lexem_type>::Abstract_scaner(const Location_ptr&     location,
                                                 const Errors_and_tries& et)
    {
        ids_                     = et.ids_trie_;
        strs_                    = et.strs_trie_;
        en_                      = et.ec_;
        loc_                     = location;
        lexeme_begin_            = location->pcurrent_char_;
        token_.range_.begin_pos_ = Position();
        token_.range_.end_pos_   = Position();
        lexeme_pos_.begin_pos_   = Position();
        lexeme_pos_.end_pos_     = Position();
    }

    template<typename Lexeme_type>
    char32_t* Abstract_scaner<Lexeme_type>::lexeme_begin_ptr() const
    {
        return lexeme_begin_;
    }

    template<typename Lexeme_type>
    Position_range Abstract_scaner<Lexeme_type>::lexeme_pos() const
    {
        return lexeme_pos_;
    }

    template<typename Lexeme_type>
    void Abstract_scaner<Lexeme_type>::back()
    {
        loc_->pcurrent_char_ = lexeme_begin_;
        loc_->pos_           = lexeme_pos_.begin_pos_;
    }

    template<typename Lexeme_type>
    std::string Abstract_scaner<Lexeme_type>::token_to_string(const Token<Lexeme_type>& tok)
    {
        std::string result;
        auto&       p      = tok.range_;
        auto&       b      = p.begin_pos_;
        auto&       e      = p.end_pos_;
        result             = "[line: "   + std::to_string(b.line_no_)  +
                             ", pos: "   + std::to_string(b.line_pos_) + "]"
                             "--[line: " + std::to_string(e.line_no_)  +
                             ", pos: "   + std::to_string(e.line_pos_) + "]";
        result += " lexeme: " + lexeme_to_string(tok.lexeme_);
        return result;
    }
};
#endif