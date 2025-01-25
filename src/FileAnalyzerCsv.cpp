#include "src/FileAnalyzerCsv.h"

#include <fstream>
#include <iostream>

FileAnalyzerCsv::FileAnalyzerCsv(const std::string& filename)
    : FileAnalyzerFile(filename, allowed_extensions) {}

const std::vector<std::string> FileAnalyzerCsv::allowed_extensions = {".csv"};

uint32_t FileAnalyzerCsv::rows() const {
  uint32_t rows = 0;

  for (int i = 0; i < file_size(); i++) {
    if (contents_[i] == '\n') rows++;
  }

  return rows;
}

uint32_t FileAnalyzerCsv::cols() const {
  if (file_size() == 0) return 0;

  uint32_t cols = 1;

  for (int i = 0; i < file_size(); i++) {
    if (contents_[i] == ',') cols++;
    if (contents_[i] == '\n') break;
  }

  return cols;
}

bool FileAnalyzerCsv::verify_dimensions() const {
  if (file_size() == 0) return true;

  bool valid = true;

  uint32_t header_cols = cols();
  uint32_t cols = 1;

  for (int i = 0; i < file_size(); i++) {
    if (contents_[i] == ',') cols++;
    if (contents_[i] == '\n') {
      if (cols != header_cols) {
        valid = false;
        break;
      }

      cols = 1;
    }
  }

  return valid;
}
