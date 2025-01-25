#include "src/FileAnalyzerText.h"

#include <fstream>
#include <iostream>
#include <algorithm>

FileAnalyzerText::FileAnalyzerText(const std::string& filename)
    : FileAnalyzerFile(filename, allowed_extensions) {}

const std::vector<std::string> FileAnalyzerText::allowed_extensions = {".txt"};

std::vector<std::pair<char, uint32_t>> FileAnalyzerText::get_letter_count() const {
  std::unordered_map<char, uint32_t> map;

  for (char i = 97; i < 123; i++)
    map[i] = 0;

  for (int i = 0; i < file_size(); i++) {
    if (std::isalpha(contents_[i])) {
      map[contents_[i]]++;
    }
  }

  std::vector<std::pair<char, uint32_t>> result;

  for (auto &p : map) {
    result.push_back(p);
  }

  std::sort(result.begin(), result.end(), [](auto a, auto b) {
              return a.first < b.first;
            });

  return result;
}

std::vector<std::pair<char, uint32_t>> FileAnalyzerText::get_letter_count_sorted() const {
  auto v = get_letter_count();

  std::sort(v.begin(), v.end(), [](auto a, auto b) {
              return a.second > b.second || (a.second == b.second && a.first < b.first);
            });

  return v;
}

std::unordered_map<std::string, uint32_t> FileAnalyzerText::word_frequency() const {
  std::unordered_map<std::string, uint32_t> map;

  std::string buf;

  for (int i = 0; i < file_size(); i++) {
    char c = contents_[i];
    if (std::isalpha(c) || c == '-' || c =='\'') {
      buf += c;
    } else {
      map[buf]++;
      buf = std::string{};
    }
  }

  return map;
}

std::vector<std::string> FileAnalyzerText::get_most_common() const {
  auto map = word_frequency();

  std::vector<std::pair<std::string, uint32_t>> max;

  for (auto &p : map) {
    if (max.size() == 0 || p.second > max[0].second) {
      max.clear();
      max.push_back(p);
    } else if (p.second == max[0].second)
      max.push_back(p);
  }

  std::vector<std::string> result;

  for (auto &p : max)
    result.push_back(p.first);

  return result;
}

std::vector<std::string> FileAnalyzerText::get_least_common() const {
  auto map = word_frequency();

  std::vector<std::pair<std::string, uint32_t>> min;

  for (auto &p : map) {
    if (min.size() == 0 || p.second < min[0].second) {
      min.clear();
      min.push_back(p);
    } else if (p.second == min[0].second)
      min.push_back(p);
  }

  std::vector<std::string> result;

  for (auto &p : min)
    result.push_back(p.first);

  return result;
}
