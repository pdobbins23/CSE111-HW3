// Copyright (c) 2025 Ethan Sifferman.
// All rights reserved. Distribution Prohibited.

#include <fstream>
#include <iostream>
#include <vector>

#include "CLI/CLI.hpp"
#include "src/FileAnalyzer.h"

int main(int argc, char* argv[]) {
  std::string filename;
  bool get_size = false;

  bool png_get_width = false;
  bool png_get_height = false;

  bool csv_get_rows = false;
  bool csv_get_columns = false;
  bool csv_verify_dimensions = false;

  bool wav_get_bitrate = false;
  bool wav_get_channels = false;

  bool code_get_lines = false;
  bool code_check_parens = false;

  bool text_get_most_common = false;
  bool text_get_least_common = false;
  bool text_get_letter_count = false;
  bool text_get_letter_count_sorted = false;

  CLI::App app{"Program to read a file specified as command-line argument"};

  app.add_option("filename", filename, "File to read")->required();
  app.add_flag("--get-size", get_size, "Print the size of the file");

  app.add_flag("--png-get-width", png_get_width, "Print the width of a PNG");
  app.add_flag("--png-get-height", png_get_height, "Print the height of a PNG");

  app.add_flag("--csv-get-rows", csv_get_rows,
               "Print the number of rows in a CSV");
  app.add_flag("--csv-get-columns", csv_get_columns,
               "Print the number of columns in a CSV");
  app.add_flag("--csv-verify-dimensions", csv_verify_dimensions,
               "Print true if all CSV rows have the same number of columns, "
               "false otherwise");

  app.add_flag("--wav-get-bitrate", wav_get_bitrate,
               "Print the bitrate of a WAV file");
  app.add_flag("--wav-get-channels", wav_get_channels,
               "Print the number of channels in a WAV file");

  app.add_flag("--code-get-lines", code_get_lines,
               "Print the number of lines in a code file");
  app.add_flag("--code-check-parens", code_check_parens,
               "Indicate the correctness of ()[]{} usage");

  app.add_flag("--text-get-most-common", text_get_most_common,
               "Print the most common word in a text file");
  app.add_flag("--text-get-least-common", text_get_least_common,
               "Print the least common word in a text file");
  app.add_flag("--text-get-letter-count", text_get_letter_count,
               "Print the letter count in a text file");
  app.add_flag("--text-get-letter-count-sorted", text_get_letter_count_sorted,
               "Print the letter count in a text file sorted");

  app.require_option(1, 2);  // Enforce only one flag can be input

  CLI11_PARSE(app, argc, argv);

  if (get_size) {
    std::cout << FileAnalyzerFile(filename).file_size() << std::endl;
  } else if (png_get_width) {
    std::cout << FileAnalyzerPng(filename).width() << std::endl;
  } else if (png_get_height) {
    std::cout << FileAnalyzerPng(filename).height() << std::endl;
  } else if (csv_get_rows) {
    std::cout << FileAnalyzerCsv(filename).rows() << std::endl;
  } else if (csv_get_columns) {
    std::cout << FileAnalyzerCsv(filename).cols() << std::endl;
  } else if (csv_verify_dimensions) {
    std::cout << std::boolalpha << FileAnalyzerCsv(filename).verify_dimensions() << std::endl;
  } else if (wav_get_bitrate) {
    std::cout << FileAnalyzerWav(filename).bitrate() << std::endl;
  } else if (wav_get_channels) {
    std::cout << FileAnalyzerWav(filename).channels() << std::endl;
  } else if (code_get_lines) {
    std::cout << FileAnalyzerCode(filename).get_lines() << std::endl;
  } else if (code_check_parens) {
    std::cout << FileAnalyzerCode(filename).check_parens() << std::endl;
  } else if (text_get_most_common) {
    auto most_common = FileAnalyzerText(filename).get_most_common();

    for (auto word : most_common)
      std::cout << word << std::endl;
  } else if (text_get_least_common) {
    auto least_common = FileAnalyzerText(filename).get_least_common();

    for (auto word : least_common)
      std::cout << word << std::endl;
  } else if (text_get_letter_count) {
    auto letters = FileAnalyzerText(filename).get_letter_count();

    for (auto p : letters)
      std::cout << p.first << ": " << p.second << std::endl;
  } else if (text_get_letter_count_sorted) {
    auto letters = FileAnalyzerText(filename).get_letter_count_sorted();

    for (auto p : letters)
      std::cout << p.first << ": " << p.second << std::endl;
  }
  return 0;
}
