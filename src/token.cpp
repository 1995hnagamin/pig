#include "token.hpp"

Token::~Token() {
}

std::string
IdentTok::to_string() const {
  return ident;
}

std::string
KeywordTok::to_string() const {
  return keyword;
}

std::string
DigitTok::to_string() const {
  return std::to_string(number);
}

std::string
SymbolTok::to_string() const {
  return std::string(1, symbol);
}

std::string
EofTok::to_string() const {
  return "(EOF)";
}

TokenRef make_ident_token(const std::string &ident) {
  return std::make_shared<IdentTok>(ident);
}

TokenRef make_keyword_token(const std::string &keyword) {
  return std::make_shared<KeywordTok>(keyword);
}

TokenRef make_digit_token(int num) {
  return std::make_shared<DigitTok>(num);
}

TokenRef make_symbol_token(char symbol) {
  return std::make_shared<SymbolTok>(symbol);
}

TokenRef
make_eof_token() {
  return std::make_shared<EofTok>();
}
