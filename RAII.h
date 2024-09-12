#pragma once
#define byte win_byte_override  // уникнути конфлікту з std::byte
#include <windows.h>
#undef byte

#include <string>
#include <cstdint>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

class FileRAII {
public:
    FileRAII(const wstring& filePath, uint32_t access, uint32_t creationDisposition);
    uint32_t Read(char* buffer, uint32_t bufferSize);
    ~FileRAII();

private:
    HANDLE hFile;
    void Close();
};