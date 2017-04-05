#ifndef TOKEN_HPP
#define TOKEN_HPP

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

#endif /*! TOKEN_HPP */
