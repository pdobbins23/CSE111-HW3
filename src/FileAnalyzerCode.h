#pragma once

#include "src/FileAnalyzerFile.h"

class FileAnalyzerCode : public FileAnalyzerFile {
 private:
 public:
  FileAnalyzerCode(const std::string& filename);
  uint32_t get_lines() const;
  bool check_parens() const;
  static const std::vector<std::string> allowed_extensions;
};
