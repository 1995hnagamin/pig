#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

enum class TokenKind {
  Identifier,
  Keyword,
  Digit,
  Symbol,
  Eof,
};

class Token {
  public:
  Token(TokenKind k) : kind(k) {
  }
  virtual ~Token() = 0;
  TokenKind
  getKind() const {
    return kind;
  }

  private:
  const TokenKind kind;
};

class IdentTok : public Token {
  public:
  IdentTok(const std::string &i)
      : Token(TokenKind::Identifier), ident(i) {
  }
  ~IdentTok() override = default;
  static bool
  classof(const Token *T) {
    return T->gteKind() == TokenKind::Identifier;
  }

  private:
  std::string ident;
};

class KeywordTok : public Token {
  public:
  KeywordTok(const std::string &k)
      : Token(TokenKind::Keyword), keyword(k) {
  }
  ~KeywordTok() override = default;
  static bool
  classof(const Token *T) {
    return T->getKind() == TokenKind::Keyword;
  }

  private:
  std::string keyword;
};

class DigitTok : public Token {
  public:
  DigitTok(int num) : Token(TokenKind::Digit), number(num) {
  }
  ~DigitTok() override = default;
  static bool
  classof(const Token *T) {
    return T->getKind() == TokenKind::Digit;
  }

  private:
  int number;
};

class SymbolTok : public Token {
  public:
  SymbolTok(char s) : Token(TokenKind::Symbol), symbol(s) {
  }
  ~Symbol() override = default;
  static bool
  classof(const Token *T) {
    return T->getKind() == TokenKind::Symbol;
  }

  private:
  char symbol;
};

#endif /*! TOKEN_HPP */
