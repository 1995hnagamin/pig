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
  virtual Token *clone() const = 0;
  TokenKind
  get_kind() const {
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
  Token *
  clone() const override {
    IdentTok *copy = new IdentTok(*this);
    return copy;
  }
  static bool
  classof(const Token *T) {
    return T->get_kind() == TokenKind::Identifier;
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
  Token *
  clone() const override {
    KeywordTok *copy = new KeywordTok(*this);
    return copy;
  }
  static bool
  classof(const Token *T) {
    return T->get_kind() == TokenKind::Keyword;
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
  Token *
  clone() const override {
    DigitTok *copy = new DigitTok(*this);
    return copy;
  }
  static bool
  classof(const Token *T) {
    return T->get_kind() == TokenKind::Digit;
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
  Token *
  clone() const override {
    SymbolTok *copy = new SymbolTok(*this);
    return copy;
  }
  static bool
  classof(const Token *T) {
    return T->get_kind() == TokenKind::Symbol;
  }

  protected:
  SymbolTok(const SymbolTok &) = default;

  private:
  char symbol;
};

class EofTok : public Token {
  public:
  EofTok() : Token(TokenKind::Eof) {
  }
  ~EofTok() override = default;
  Token *
  clone() const override {
    EofTok *eof = new EofTok();
    return eof;
  }
  static bool
  classof(const Token *T) {
    return T->get_kind() == TokenKind::Eof;
  }
};

TokenRef make_ident_token(const std::string &);
TokenRef make_keyword_token(const std::string &);
TokenRef make_digit_token(int);
TokenRef make_symbol_token(char);
TokenRef make_eof_token();

#endif /*! TOKEN_HPP */
