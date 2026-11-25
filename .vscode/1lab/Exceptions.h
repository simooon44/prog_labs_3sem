#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <cstring>
#include <exception>

class AppException : public std::exception {
   public:
    explicit AppException(const char* msg) {
        std::strncpy(message_, msg, sizeof(message_) - 1);
        message_[sizeof(message_) - 1] = '\0';
    }

    virtual const char* what() const noexcept override { return message_; }

   private:
    char message_[256];
};

class DivisionByZeroException : public AppException {
   public:
    explicit DivisionByZeroException(const char* msg = "Division by zero")
        : AppException(msg) {}
};

class OutOfRangeException : public AppException {
   public:
    explicit OutOfRangeException(const char* msg = "Index out of range")
        : AppException(msg) {}
};

class FileIOException : public AppException {
   public:
    explicit FileIOException(const char* msg = "File I/O error")
        : AppException(msg) {}
};

class InputFormatException : public AppException {
   public:
    explicit InputFormatException(const char* msg = "Invalid input format")
        : AppException(msg) {}
};

#endif