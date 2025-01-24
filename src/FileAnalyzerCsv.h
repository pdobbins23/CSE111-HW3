#pragma once

#include "src/FileAnalyzerFile.h"

class FileAnalyzerCsv : public FileAnalyzerFile {
 private:
 public:
  FileAnalyzerCsv(const std::string& filename);
  uint32_t rows() const;
  uint32_t cols() const;
  bool verify_dimensions() const;
  static const std::vector<std::string> allowed_extensions;
};
