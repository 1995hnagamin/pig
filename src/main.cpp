#include "lexer.hpp"
#include <cassert>
#include <iostream>

namespace {

void
show_help(const std::string &program) {
  std::cerr << "usage: " << program << " <filename>" << std::endl;
}

} // namespace

int
main(int argc, char **argv) {
  if (argc < 2) {
    assert(argc == 1);
    show_help(argv[0]);
    return 0;
  }
  auto tokens = lex_from_file(argv[1]);
  do {
    const auto token = tokens->get_token();
    std::cout << token->to_string() << "\t";
  } while (tokens->improve());
  std::cout << std::endl;
  return 0;
}
