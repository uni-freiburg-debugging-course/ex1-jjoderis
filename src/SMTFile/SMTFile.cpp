#include "SMTFile.h"

SMTFile::SMTFile(const std::filesystem::path &path) : m_filestream{path} {}

SMTFile::~SMTFile() { m_filestream.close(); }

std::string SMTFile::nextLine() {
  std::string line{};
  getline(m_filestream, line);
  return line;
}

bool SMTFile::eof() const { return m_filestream.eof(); }
