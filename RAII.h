#pragma once
#define byte win_byte_override  // уникнути конфлікту з std::byte
#include <windows.h>
#undef byte

#include <string>

using namespace std;

class FileRAII {
public:
    FileRAII(const wstring& filePath, DWORD access, DWORD creationDisposition);
    DWORD Read(char* buffer, DWORD bufferSize);
    ~FileRAII();

private:
    HANDLE hFile;
    void Close();
};
