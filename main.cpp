#include <CLISetting/CLISetting.h>
#include <CLISettingsParser/CLISettingsParser.h>

#include <filesystem>
#include <fstream>
#include <iostream>

#include "AST/AST.h"
#include "Lexer/Lexer.h"
#include "Lexer/Token.h"
#include "SMTEvaluation/Evaluation.h"

enum Settings { InputFile };

int main(int argc, const char **argv) {
  cpp_cli::ProgramSettings<cpp_cli::CLISetting<InputFile, std::filesystem::path>> settings =
      cpp_cli::parseProgramSettingsFromCL(
          argc, argv, cpp_cli::CLISettingBuilder<InputFile, std::filesystem::path>{}.addShort('i').build()
      );

  std::ifstream input{settings.get<InputFile>()};

  while (!input.eof()) {
    std::vector<Token> tokens = tokenize(input);
    if (!tokens.size()) continue;

    try {
      ASTree tree{tokens};
      std::cout << evaluateTree(tree) << std::endl;
    } catch (const char *msg) {
      std::cout << msg << std::endl;
    }
  }
}
