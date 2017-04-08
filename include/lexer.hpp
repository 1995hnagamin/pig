#ifndef LEXER_HPP
#define LEXER_HPP

#include "token.hpp"
#include "token_stream.hpp"
#include <memory>
#include <string>

std::unique_ptr<TokenStream> lex_from_file(const std::string &);

#endif /*! LEXER_HPP */
