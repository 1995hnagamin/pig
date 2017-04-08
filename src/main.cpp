#include "lexer.hpp"
#include <iostream>

namespace {

void
show_help(const std::string &program) {
  std::cerr << "usage: " << program << " <filename>" << std::endl;
}

} // namespace

int
main(int argc, char **argv) {
  const auto tokens = lex_from_file(argv[1]);
  return 0;
}
