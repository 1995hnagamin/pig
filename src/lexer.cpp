#include "lexer.hpp"
#include <cassert>
#include <fstream>
#include <iostream>
#include <tuple>

namespace {

using CharPredicate = int (*)(int);

std::tuple<std::string, std::string::const_iterator>
get_while(CharPredicate pred,
          std::string::const_iterator iter,
          const std::string::const_iterator &end) {
  std::string token(1, *iter);
  ++iter;
  while (iter != end && pred(*iter)) {
    token.push_back(*iter);
    ++iter;
  }
  return std::make_tuple(token, iter);
}

using Result = std::tuple<TokenRef, std::string::const_iterator>;

Result
get_symbol_token(std::string::const_iterator iter) {
  const auto symbols = static_cast<std::string>("*+-=;,(){}");
  const auto pos = symbols.find(*iter);
  if (pos == std::string::npos) {
    return std::make_tuple(TokenRef(nullptr), iter);
  }
  ++iter;
  return std::make_tuple(make_symbol_token(symbols.at(pos)), iter);
}

Result
get_token(std::string::const_iterator iter,
          const std::string::const_iterator &end) {
  while (isspace(*iter)) {
    ++iter;
  }
  if (iter == end) {
    return std::make_tuple(TokenRef(nullptr), iter);
  }

  if (*iter == EOF) {
    return std::make_tuple(make_eof_token(), ++iter);
  } else if (std::isalpha(*iter)) {
    // keyword or identifier
    auto next_iter = iter;
    std::string word;
    std::tie(word, next_iter) = get_while(std::isalnum, iter, end);

    assert(!word.empty());
    const auto token = isupper(word.front()) ? make_keyword_token(word)
                                             : make_ident_token(word);

    return std::make_tuple(token, next_iter);
  } else if (std::isdigit(*iter)) {
    // numeric
    auto next_iter = iter;
    std::string num;
    std::tie(num, next_iter) = get_while(isdigit, iter, end);

    assert(!num.empty());
    return std::make_tuple(make_digit_token(std::stoi(num)), next_iter);
  }
  // otherwise, the next token must be a symbol
  return get_symbol_token(iter);
}

void
show_unclear_token_error_and_abort(char c) {
  std::cerr << "unclear token: " << c << std::endl;
  abort();
}

} // namespace

std::unique_ptr<TokenStream>
lex_from_file(const std::string &input_file) {
  std::ifstream ifs;
  ifs.open(input_file, std::ios::in);
  if (!ifs) {
    return nullptr;
  }

  TokenStream *stream = new TokenStream();
  std::string cur_line;
  while (ifs && std::getline(ifs, cur_line)) {
    for (auto iter = cur_line.cbegin(), next_iter = cur_line.cend();
         iter != cur_line.cend();
         iter = next_iter) {
      TokenRef token = nullptr;
      std::tie(token, next_iter) = get_token(iter, cur_line.cend());
      if (!token) {
        delete stream;
        ifs.close();
        show_unclear_token_error_and_abort(*iter);
      }
      stream->push_token(token);
    }
  }

  ifs.close();
  return std::unique_ptr<TokenStream>(stream);
}
