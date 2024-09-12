#include <stdexcept>
#include "RAII.h"

using namespace std;

FileRAII::FileRAII(const wstring& filePath, DWORD access, DWORD creationDisposition)
        : hFile(CreateFileW(filePath.c_str(),
                            access,
                            0,
                            nullptr,
                            creationDisposition,
                            FILE_ATTRIBUTE_NORMAL,
                            nullptr)) {
    if (hFile == INVALID_HANDLE_VALUE) {
        throw runtime_error("Failed to open file.");
    }
}

FileRAII::~FileRAII() {
    Close();
}

DWORD FileRAII::Read(char* buffer, DWORD bufferSize) {
    DWORD bytesRead;
    if (!ReadFile(hFile,
                  buffer,
                  bufferSize,
                  &bytesRead,
                  nullptr)) {
        throw runtime_error("Failed to read from file.");
    }
    return bytesRead;
}

void FileRAII::Close() {
    if (hFile != INVALID_HANDLE_VALUE) {
        CloseHandle(hFile);
        hFile = INVALID_HANDLE_VALUE;
    }
}
