#include "src/FileAnalyzerWav.h"

#include <fstream>
#include <iostream>

FileAnalyzerWav::FileAnalyzerWav(const std::string& filename)
    : FileAnalyzerFile(filename, allowed_extensions) {}

const std::vector<std::string> FileAnalyzerWav::allowed_extensions = {".wav"};

WaveHeader FileAnalyzerWav::read_wave_header() const {
  WaveHeader header;

  header.chunk_id = ReadBigEndianInt32(0);
  header.chunk_size = ReadLittleEndianInt32(4);
  header.format = ReadBigEndianInt32(8);

  header.subchunk1_id = ReadBigEndianInt32(12);
  header.subchunk1_size = ReadLittleEndianInt32(16);
  header.audio_format = ReadLittleEndianInt16(20);
  header.num_channels = ReadLittleEndianInt16(22);
  header.sample_rate = ReadLittleEndianInt32(24);
  header.byte_rate = ReadLittleEndianInt32(28);
  header.block_align = ReadLittleEndianInt16(32);
  header.bits_per_sample = ReadLittleEndianInt16(34);

  header.subchunk2_id = ReadBigEndianInt32(36);
  header.subchunk2_size = ReadLittleEndianInt32(40);

  return header;
}

uint32_t FileAnalyzerWav::bitrate() const {
  WaveHeader header = read_wave_header();

  return header.byte_rate * 8;
}

uint16_t FileAnalyzerWav::channels() const {
  WaveHeader header = read_wave_header();

  return header.num_channels;
}
