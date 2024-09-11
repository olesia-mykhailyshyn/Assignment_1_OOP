#pragma once
#define byte win_byte_override  // уникнути конфлікту з std::byte
#include <windows.h>
#undef byte

#include <string>

class FileRAII {
public:
    FileRAII(const std::wstring& filePath, DWORD access, DWORD creationDisposition);
    FileRAII(const FileRAII&) = delete;
    FileRAII& operator=(const FileRAII&) = delete;
    FileRAII(FileRAII&& other) noexcept;
    FileRAII& operator=(FileRAII&& other) noexcept;
    DWORD Read(char* buffer, DWORD bufferSize);
    ~FileRAII();

private:
    HANDLE hFile;
    void Close();
};
