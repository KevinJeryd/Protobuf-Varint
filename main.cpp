#include <iostream>
#include <fstream>
#include <string>
#include <WinSock2.h>
#include <vector>
#include "include/varint.h"

int main() {
   std::vector<unsigned char> varint1 = readFile("../../varint/1.uint64");
   std::vector<unsigned char> varint150 = readFile("../../varint/150.uint64");
   std::vector<unsigned char> varintMax = readFile("../../varint/maxint.uint64");

   uint64_t varintDec = bytesToInt(varint150);

   std::cout << "Value to be encoded: " << varintDec << std::endl;

   std::vector<unsigned char> encodedVarint = encodeVarint(varintDec);

   printf("Encoded Value: ");
   
   for (auto byteNum : encodedVarint) {
      printf("%02x", byteNum);
   }
   std::cout << std::endl;

   std::vector<unsigned char> encodedVarint2 {0x01, 0x01};

   uint64_t decodedVarint = decodeVarint(encodedVarint2);

   printf("Decoded Value: %d", decodedVarint);
   std::cout << std::endl;

   uint64_t varint1Dec = bytesToInt(varint1);
   uint64_t varint150Dec = bytesToInt(varint150);
   uint64_t varintMaxDec = bytesToInt(varintMax);

   std::cout << "roundtripTest for varint1: " << roundtripTest(varint1Dec) << std::endl;
   std::cout << "roundtripTest for varint150: " << roundtripTest(varint150Dec) << std::endl;
   std::cout << "roundtripTest for varintMax: " << roundtripTest(varintMaxDec) << std::endl;

    return 0;
}

int roundtripTest(const uint64_t varint) {
   std::vector<unsigned char> encodedVarint = encodeVarint(varint);
   uint64_t decodedVarint = decodeVarint(encodedVarint);

   return varint == decodedVarint;
}

std::vector<unsigned char> encodeVarint(uint64_t value) {
   std::vector<unsigned char> result;

   while (value > 0) {
      unsigned char bytePortion = value & 0x7F;
      value >>= 7;
      
      if (value > 0) {
         bytePortion |= 0x80;
      }

      result.push_back(bytePortion);
   }

   return result;
}

uint64_t decodeVarint(const std::vector<unsigned char>& bytes) {
   uint64_t result{};

   std::cout << "Bytes to be decoded: ";
   for (auto byte : bytes) {
      printf("%02x", byte);
   }
   std::cout << std::endl;

   int i = 0;

   // If the MSB is set, then we have more bytes to read
   // Technically we don't need to check this since we have a byte sequence as input
   // So we can just use the size of the vector ig
   do {
      result |= (bytes[i] & 0x7F) << (i * 7);
      ++i;
   } while (bytes[i-1] & 0x80); // Really scuffed way of doing it, but I just wanted to check the MSB... 

   return result;
}

uint64_t bytesToInt(const std::vector<unsigned char>& bytes) {
    uint64_t result = 0;
    size_t byteCount = bytes.size();
    for (size_t i = 0; i < byteCount; ++i) {
        result |= (uint64_t)bytes[i] << (8 * (byteCount - 1 - i));
    }
    return result;
}

std::vector<unsigned char> readFile(const std::string& path) {
   std::ifstream file;
   file.open(path, std::ios::binary);
   
   if (!file.is_open()) {
      std::cerr << "Error: Could not open file " << path << std::endl;
      return std::vector<unsigned char>();
   } else {
      // get the starting position
      std::streampos start = file.tellg();

      // go to the end
      file.seekg(0, std::ios::end);

      // get the ending position
      std::streampos end = file.tellg();

      // go back to the start
      file.seekg(0, std::ios::beg);

      // create a vector to hold the data that
      // is resized to the total size of the file
      // Not really needed since all input are uint64    
      std::vector<unsigned char> contents;
      contents.resize(static_cast<size_t>(end - start));

      // read it in
      file.read((char*)&contents[0], contents.size());

      file.close();
      
      return contents;
   }
} 