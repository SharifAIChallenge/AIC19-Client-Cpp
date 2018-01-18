#include "FileDescriptor.h"

#include <unistd.h>

#include <utility>

FileDescriptor::FileDescriptor(int fd) noexcept
        : m_fd(fd)
{
}

FileDescriptor::~FileDescriptor() noexcept {
    reset();
}

FileDescriptor::FileDescriptor(FileDescriptor&& rhs) noexcept
        : m_fd (rhs.release())
{
}

FileDescriptor& FileDescriptor::operator= (FileDescriptor&& rhs) noexcept {
    reset(rhs.release());
    return *this;
}

void FileDescriptor::reset(int fd) {
    if (*this)
        close(m_fd);
    m_fd = fd;
}

int FileDescriptor::release() {
    int copy = -1;
    std::swap(m_fd, copy);
    return copy;
}

int FileDescriptor::get() const {
    return m_fd;
}

FileDescriptor::operator bool() const {
    return m_fd >= 0;
}

