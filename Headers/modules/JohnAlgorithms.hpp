#ifndef JOHN_UTILS
#define JOHN_UTILS

#include <string>

namespace john_utils {
    // std::string reverseString(std::string str);
       /**
     * @brief Function to reverse a given input string
     * 
     * @param str input
     * @return std::string reversed
     */
    inline std::string reverseString(std::string str) {
        std::string returnValue = "";
        for (int i = str.length() - 1; i >-1; i--) {
            returnValue+= str[i];
        }
        return returnValue;
    }
 
};


#endif
