#include "src/FileAnalyzerCode.h"

#include <fstream>
#include <iostream>

FileAnalyzerCode::FileAnalyzerCode(const std::string& filename)
    : FileAnalyzerFile(filename, allowed_extensions) {}

const std::vector<std::string> FileAnalyzerCode::allowed_extensions = {".c", ".cpp", ".h"};

uint32_t FileAnalyzerCode::get_lines() const {
  uint32_t lines = 0;

  bool has_content = false;
  for (int i = 0; i < file_size(); i++) {
    if (!std::isspace(static_cast<unsigned char>(contents_[i]))) has_content = true;

    if (contents_[i] == '\n') {
      if (has_content) lines++;
      has_content = false;
    }
  }

  return lines;
}

bool FileAnalyzerCode::check_parens() const {
  return false;
}
