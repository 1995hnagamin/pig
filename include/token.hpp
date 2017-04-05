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


#endif /*! TOKEN_HPP */
