#ifndef HEADER
#define HEADER
#include <cstring>

class String {
    public:
        String() {
            string.str.size = 0;
            string.str.m_ptr = nullptr;
            m_size = 0;
            m_capacity = 16;
        }

        String(const char* str) {
            int strl = std::strlen(str);
            if (strl < 16) {
                std::strcpy(string.onstack, str);
                string.onstack[strl] = '\0';
                m_size = strl;
                m_capacity = 16;
            }
            else {
                string.str.size = strl;
                string.str.m_ptr = new char[strl + 1];
                std::strcpy(string.str.m_ptr, str);
                m_size = strl;
                m_capacity = strl;
            }
        }

        String& operator=(const String& other) {
            if (this == &other) {
                return *this;
            }
            if(other.m_size < 16) {
                std::strcpy(string.onstack, other.string.onstack);
                m_size = other.m_size;  
            }
            else {
                string.str.size = other.m_size;
                string.str.m_ptr = new char[m_size + 1];
                std::strcpy(string.str.m_ptr, other.string.str.m_ptr);
                m_size = other.m_size;
            }
            return *this;
        }

        String& append(const char* str) {
            int newLength = std::strlen(str);
            int newSize = m_size + newLength;

            if (newSize <= 15) {
                std::strcat(string.onstack, str);
                m_size = newSize;
            } 
            else 
            {
                char* newPtr = new char[newSize + 1];
                if (m_size <= 15) {
                    std::strcpy(newPtr, string.onstack);
                } 
                else {
                    std::strcpy(newPtr, string.str.m_ptr);
                    delete[] string.str.m_ptr;
                }
                std::strcpy(newPtr + m_size, str); 

                string.str.size = newSize;
                string.str.m_ptr = newPtr;
                m_size = newSize;
            }
            return *this;
        }

        void push_back(char ch) {
            int newsize = m_size + 1;
            if (newsize < 16) {
                string.onstack[m_size] = ch;
                string.onstack[newsize] = '\0';
                m_size = newsize;
            }
            else {
                char* newptr = new char[newsize + 1];
                if (m_size < 16) {
                    std::strcpy(newptr, string.onstack);
                }
                else {
                    std::strcpy(newptr, string.str.m_ptr);
                    delete[] string.str.m_ptr;
                }
                newptr[m_size] = ch;
                newptr[newsize] = '\0';

                string.str.size = newsize;
                string.str.m_ptr = newptr;
                m_size = newsize;
            }
        }

        char* print() {
            if(m_size < 16) {
                return string.onstack;
            }
            else {
                return string.str.m_ptr;
            }
        }
    ~String() {
        if (m_size > 15) {
            delete[] string.str.m_ptr;
        }
    }
    private:
        struct dyn_str {
            int size;
            char* m_ptr;
        };
        union string {
            char onstack[16];
            dyn_str str;
        } string;
        int m_size;
        int m_capacity;
};

#endif