#ifndef STRING
#define STRING

#include <iostream>

class string {
    friend std::ostream& operator<<(std::ostream& os, const string& str);
    friend std::istream& operator>>(std::istream& is, string& str);
private:
    char* str;
    size_t length;

    size_t calculateLength(const char*) const;
    void clearString();
    char* strCpy(const char* str2) const;
    char* strCat(const char* str1, const char* str2) const;
public:
    string();
    string(const string& copy);
    string(const char* str);
    string(const char& character);
    ~string();

    void setString(const char* string);
    void setString(const string& string);
    size_t getLength() const;
    char* getString() const;

    string toUpper() const;
    string toLower() const;

    string& operator=(const string& other);
    string& operator=(string&& other);
    string& operator=(const char* other);
    bool operator==(const string& other);
    string operator+(const string& other) const;
    string operator+(const char& other) const;
    char& operator[](const int index);
};

#include "string.cpp"

#endif