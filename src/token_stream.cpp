#include "token_stream.hpp"

bool
TokenStream::ungetToken(size_t times) {
  if (cur_index > times) {
    return false;
  }
  cur_index -= times;
  return true;
}

bool
TokenStream::improve() {
  if (cur_index + 1 >= tokens.size()) {
    return false;
  }
  ++cur_index;
  return true;
}

bool
TokenStream::pushToken(const TokenRef &token) {
  tokens.push_back(token);
  return true;
}

TokenRef
TokenStream::getToken() const {
  return tokens.at(cur_index);
}

TokenKind
TokenStream::getTokenKind() const {
  return getToken()->getKind();
}
