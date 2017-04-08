#include "lexer.hpp"
#include <iostream>

int
main(int argc, char **argv) {
  const auto tokens = lex_from_file(argv[1]);
  return 0;
}
