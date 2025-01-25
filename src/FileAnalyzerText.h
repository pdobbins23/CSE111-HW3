#pragma once

#include "src/FileAnalyzerFile.h"
#include <vector>
#include <utility>
#include <unordered_map>
#include <string>

class FileAnalyzerText : public FileAnalyzerFile {
 private:
 public:
  FileAnalyzerText(const std::string& filename);
  std::vector<std::pair<char, uint32_t>> get_letter_count() const;
  std::vector<std::pair<char, uint32_t>> get_letter_count_sorted() const;
  std::unordered_map<std::string, uint32_t> word_frequency() const;
  std::vector<std::string> get_most_common() const;
  std::vector<std::string> get_least_common() const;
  static const std::vector<std::string> allowed_extensions;
};
