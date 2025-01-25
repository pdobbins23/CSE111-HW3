#include "src/FileAnalyzerCode.h"

#include <fstream>
#include <iostream>
#include <stack>

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
  std::stack<int> s;

  for (int i = 0; i < file_size(); i++) {
    switch (contents_[i]) {
      case '(':
        s.push(0);
        break;
      case ')':
        if (s.top() != 0) return false;
        s.pop();
        break;
      case '[':
        s.push(1);
        break;
      case ']':
        if (s.top() != 1) return false;
        s.pop();
        break;
      case '{':
        s.push(2);
        break;
      case '}':
        if (s.top() != 2) return false;
        s.pop();
        break;
    }
  }
  
  return s.empty();
}
