#include "token_stream.hpp"

bool
TokenStream::unget_token(size_t times) {
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
TokenStream::push_token(const TokenRef &token) {
  tokens.push_back(token);
  return true;
}

TokenRef
TokenStream::get_token() const {
  return tokens.at(cur_index);
}

TokenKind
TokenStream::get_token_kind() const {
  return get_token()->get_kind();
}
