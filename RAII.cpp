#include <stdexcept>
#include "RAII.h"

using namespace std;

FileRAII::FileRAII(const wstring& filePath, uint32_t access, uint32_t creationDisposition) {
    hFile = CreateFileW(filePath.c_str(),
                        static_cast<DWORD>(access),
                        0,
                        nullptr,
                        static_cast<DWORD>(creationDisposition),
                        FILE_ATTRIBUTE_NORMAL,
                        nullptr);
    if (hFile == INVALID_HANDLE_VALUE) {
        throw runtime_error("Failed to open file.");
    }
}

FileRAII::~FileRAII() {
    Close();
}

uint32_t FileRAII::Read(char* buffer, uint32_t bufferSize) {
    DWORD bytesRead;
    if (!ReadFile(hFile, buffer, bufferSize, &bytesRead, nullptr)) {
        throw runtime_error("Failed to read from file.");
    }
    return static_cast<uint32_t>(bytesRead);
}

void FileRAII::Close() {
    if (hFile != INVALID_HANDLE_VALUE) {
        CloseHandle(hFile);
        hFile = INVALID_HANDLE_VALUE;
    }
}