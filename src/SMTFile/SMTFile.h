#ifndef STM_FILE_H
#define STM_FILE_H

#include <filesystem>
#include <fstream>

class SMTFile {
public:
  SMTFile() = delete;
  SMTFile(const std::filesystem::path &path);
  ~SMTFile();

  std::string nextLine();
  bool eof() const;

private:
  std::fstream m_filestream;
};

#endif
