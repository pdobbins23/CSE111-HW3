#pragma once

#include "src/FileAnalyzerFile.h"

struct WaveHeader {
  // RIFF
  uint32_t chunk_id;
  uint32_t chunk_size;
  uint32_t format;
  // fmt
  uint32_t subchunk1_id;
  uint32_t subchunk1_size;
  uint16_t audio_format;
  uint16_t num_channels;
  uint32_t sample_rate;
  uint32_t byte_rate;
  uint16_t block_align;
  uint16_t bits_per_sample;
  // data
  uint32_t subchunk2_id;
  uint32_t subchunk2_size;
};

class FileAnalyzerWav : public FileAnalyzerFile {
 private:
 public:
  FileAnalyzerWav(const std::string& filename);
  WaveHeader read_wave_header() const;
  uint32_t bitrate() const;
  uint16_t channels() const;
  static const std::vector<std::string> allowed_extensions;
};
