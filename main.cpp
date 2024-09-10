#include <iostream>
#include <fstream>
#include <string>
#include <WinSock2.h>
#include <vector>
#include "include/varint.h"

int main() {
   std::vector<unsigned char> varint = readFile("../../varint/150.uint64");

   for (auto byteNum : varint) {
      printf("%02x", byteNum);
      printf(" ");
   }

   std::cout << std::endl;

   uint64_t varintDec = bytesToInt(varint);

   std::cout << varintDec << std::endl;
   
    return 0;
}

std::vector<unsigned char> encodeVarint(uint64_t value) {
   return std::vector<unsigned char>();
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

      std::cout << "start: " << start << std::endl;
      std::cout << "end: " << end << std::endl;

      std::cout << "File size is: " << (end - start) << " bytes." << std::endl;

      // create a vector to hold the data that
      // is resized to the total size of the file    
      std::vector<unsigned char> contents;
      contents.resize(static_cast<size_t>(end - start));

      // read it in
      file.read((char*)&contents[0], contents.size());

      file.close();
      
      return contents;
   }
} 