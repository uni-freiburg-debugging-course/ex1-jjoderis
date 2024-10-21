#include "AST/AST.h"
#include "Lexer/Lexer.h"
#include "Lexer/Token.h"
#include "SMTEvaluation/Evaluation.h"
#include "SMTFile/SMTFile.h"
#include <CLISetting/CLISetting.h>
#include <CLISettingsParser/CLISettingsParser.h>
#include <filesystem>
#include <iostream>

enum Settings { InputFile };

int main(int argc, const char **argv) {
  cpp_cli::ProgramSettings<
      cpp_cli::CLISetting<InputFile, std::filesystem::path>>
      settings = cpp_cli::parseProgramSettingsFromCL(
          argc, argv,
          cpp_cli::CLISettingBuilder<InputFile, std::filesystem::path>{}
              .addShort('i')
              .build());

  SMTFile input{settings.get<InputFile>()};

  Lexer lexer{};

  while (!input.eof()) {
    const std::string &line{input.nextLine()};
    if (line.length()) {
      if (!line.length())
        continue;
      std::vector<Token> &tokens = lexer.parse(line);

      try {
        ASTree tree{tokens};
        std::cout << evaluateTree(tree) << std::endl;
      } catch (const char *msg) {
        std::cout << msg << std::endl;
      }
    }
  }
}
