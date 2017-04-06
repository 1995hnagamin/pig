#ifndef TOKEN_STREAM_HPP
#define TOKEN_STREAM_HPP

#include "token.hpp"
#include <vector>

class TokenStream {
  public:
  TokenStream() : cur_index(0), tokens() {
  }
  ~TokenStream() = default;
  bool ungetToken(size_t times = 1);
  bool improve();
  bool pushToken(const TokenRef &);
  TokenRef getToken() const;
  TokenKind getTokenKind() const;

  private:
  size_t cur_index;
  std::vector<TokenRef> tokens;
};

#endif /*! TOKEN_STREAM_HPP */
