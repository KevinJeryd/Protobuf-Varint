#ifndef VARINT_H
#define VARINT_H

#include <stdint.h>
#include <vector>
#include <string>

std::vector<unsigned char> readFile(const std::string& path);
uint64_t bytesToInt(const std::vector<unsigned char>& bytes);
std::vector<unsigned char> encodeVarint(uint64_t value);
uint64_t decodeVarint(const std::vector<unsigned char>& bytes);
int roundtripTest(const uint64_t varint);

#endif // VARINT_H