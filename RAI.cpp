#include <stdexcept>
#include "RAII.h"

FileRAII::FileRAII(const std::wstring& filePath, DWORD access, DWORD creationDisposition) {
    hFile = CreateFileW(filePath.c_str(),
                        access,
                        0,                    // Немає спільного доступу
                        nullptr,              // Немає безпеки
                        creationDisposition,
                        FILE_ATTRIBUTE_NORMAL,
                        nullptr);
    if (hFile == INVALID_HANDLE_VALUE) {
        throw std::runtime_error("Failed to open file.");
    }
}

FileRAII::~FileRAII() {
    Close();
}

FileRAII::FileRAII(FileRAII&& other) noexcept : hFile(other.hFile) {
    other.hFile = INVALID_HANDLE_VALUE;
}

FileRAII& FileRAII::operator=(FileRAII&& other) noexcept {
    if (this != &other) {
        Close();
        hFile = other.hFile;
        other.hFile = INVALID_HANDLE_VALUE;
    }
    return *this;
}

DWORD FileRAII::Read(char* buffer, DWORD bufferSize) {
    DWORD bytesRead;
    if (!ReadFile(hFile, buffer, bufferSize, &bytesRead, nullptr)) {
        throw std::runtime_error("Failed to read from file.");
    }
    return bytesRead;
}


void FileRAII::Close() {
    if (hFile != INVALID_HANDLE_VALUE) {
        CloseHandle(hFile);
        hFile = INVALID_HANDLE_VALUE;
    }
}
