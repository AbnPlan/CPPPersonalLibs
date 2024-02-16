#include "string.h"

std::ostream& operator<<(std::ostream& os, const string& str) {
    os << str.getString();
    return os;
}

std::istream& operator>>(std::istream& is, string& str) {
    const size_t BUFFER_SIZE = 1000;
    char temp[BUFFER_SIZE];
    is >> temp;
    str.setString(temp);
    return is;
}

/**
 * Takes a C string and calculates it's length. This function assumes that the C string is null terminated, otherwise, it might cause undefined behaviour.
 * @param string Target string to calculate length.
 * @return Length of a the target string
 */
size_t string::calculateLength(const char* string) const {
    size_t counter;
    for (counter = 0; string[counter] != '\0'; counter++);
    return counter;
}

/**
 * Frees memory for the string member variable
 */
void string::clearString() {
    if (this->str != nullptr) delete[] this->str;
}

/**
 * Creates a copy of a C string
 * @param strToCopy String that is to be copied.
*/
char* string::strCpy(const char* strToCopy) const {
    size_t copyLen = this->calculateLength(strToCopy);
    size_t i = 0;

    char* result = new char[copyLen];

    for (i = 0; i < copyLen; i++) {
        result[i] = strToCopy[i];
    }

    result[i + 1] = '\0';

    return result;
}

/**
 * Concatenates 2 C strings together.
 * @param str1
 * @param str2
 * @return str1 + str2
 */
char* string::strCat(const char* str1, const char* str2) const {
    size_t i, j;

    size_t str1Len = this->calculateLength(str1);
    size_t str2Len = this->calculateLength(str2);

    size_t newLength = str1Len + str2Len;

    char* result = new char[newLength + 1];

    for (i = 0; i < str1Len; i++) {
        result[i] = str1[i];
    }

    for (j = 0; i < newLength; i++) {
        result[i] = str2[j++];
    }

    result[i + 1] = '\0';

    return result;
}


/**
 * Creates an instance of a string with an empty string.
 */
string::string() : str(nullptr), length(0) {
    this->setString("");
}

/**
 * Creates a copy of another string object.
 * @param copy Another instance of the string object.
 */
string::string(const string& copy) : str(nullptr), length(0) {
    this->setString(copy);
}

/**
 * Take a C string and convert it into a string object.
 * @param str C string.
 */
string::string(const char* str) : str(nullptr), length(0) {
    this->setString(str);
}

/**
 * Take a C string and convert it into a string object.
 * @param str A char.
 */
string::string(const char& character) : str(nullptr), length(0) {
    this->str = new char[2];
    this->str[0] = character;
    this->str[1] = '\0';
    this->length = this->calculateLength(str);
}

/**
 * Releases the object from memory.
 */
string::~string() {
    this->clearString();
}

/**
 * Takes a string object and copies the string to this new instance.
 * @param string Another instance of string
 */
void string::setString(const string& str) {
    if (this == &str) throw std::invalid_argument("Cannot set string with itself.");
    this->setString(str.getString());
}

/**
 * Takes a C string and copies it into the string instance.
 * @param str A null terminated C string
 */
void string::setString(const char* str) {
    this->clearString();
    if (str == nullptr) {
        this->str = this->strCpy("");
        this->length = 1;
        return;
    }
    this->str = strCpy(str);
    this->length = this->calculateLength(str);
}

/**
 * Gets the length of the current string.
 * @return Length of string.
 */
size_t string::getLength() const {
    return this->length;
}

char* string::getString() const {
    return this->str;
}

string string::toUpper() const {
    string upper = this->str;
    for (int i = 0;i < this->getLength();i++) {
        if (upper[i] >= 'a' && upper[i] <= 'z') upper[i] = upper[i] + 32;
    }

    string newString(upper);

    return newString;
}

string string::toLower() const {
    char* lower = this->strCpy(this->str);

    for (size_t i = 0;i < this->getLength();i++) {
        if (lower[i] >= 'A' && lower[i] <= 'Z') lower[i] = lower[i] + 32;
    }

    string newString(lower);

    return newString;
}

string& string::operator=(const string& other) {
    this->setString(other);
    return *this;
}

string& string::operator=(string&& other) noexcept {
    if (this != &other) {
        clearString(); // Deallocate current resources

        // Move the pointer and length from the other object
        str = other.str;
        length = other.length;

        // Reset the other object to a valid state
        other.str = nullptr;
        other.length = 0;
    }
    return *this;
}

string& string::operator=(const char* other) {
    this->setString(other);
    return *this;
}

bool string::operator==(const string& other) {
    bool checkLen = this->getLength() == other.getLength();

    if (!checkLen) return false;

    for (size_t i = 0; i < this->getLength(); i++) {
        if (this->str[i] == other.str[i]) continue;
        return false;
    }
    return true;
}

string string::operator+(const string& other) const {
    char* resultStr = this->strCat(this->str, other.getString());
    return string(resultStr);
}

string string::operator+(const char& other) const {
    string charConv = other;
    string newStr = *this + charConv;
    return newStr;
}

char& string::operator[](const int index) {
    size_t realIndex;

    if (index > this->getLength() - 1 || index < (this->getLength() * -1)) {
        throw std::out_of_range("String index is out of range.");
    }

    realIndex = index < 0 ? this->getLength() + index : index;

    return str[realIndex];
}
