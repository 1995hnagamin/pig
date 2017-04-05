#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <memory>
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

  protected:
  Token(const Token &) = default;

  private:
  const TokenKind kind;
};

using TokenRef = std::shared_ptr<Token>;

class IdentTok : public Token {
  public:
  IdentTok(const std::string &i)
      : Token(TokenKind::Identifier), ident(i) {
  }
  ~IdentTok() override = default;
  static bool
  classof(const Token *T) {
    return T->getKind() == TokenKind::Identifier;
  }

  protected:
  IdentTok(const IdentTok &) = default;

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

  protected:
  KeywordTok(const KeywordTok &) = default;

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

  protected:
  DigitTok(const DigitTok &) = default;

  private:
  int number;
};

class SymbolTok : public Token {
  public:
  SymbolTok(char s) : Token(TokenKind::Symbol), symbol(s) {
  }
  ~SymbolTok() override = default;
  static bool
  classof(const Token *T) {
    return T->getKind() == TokenKind::Symbol;
  }

  protected:
  SymbolTok(const SymbolTok &) = default;

  private:
  char symbol;
};

#endif /*! TOKEN_HPP */
