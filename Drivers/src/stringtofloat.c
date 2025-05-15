#include <stdint.h>
#include <stdbool.h>
#include"strintofloat.h"

float stringToFloat(const char *str) {
    float value = 0.0f;
    float fraction = 1.0f;
    bool negative = false;
    bool decimal = false;
    
    // Skip whitespace
    while (*str == ' ') str++;
    
    // Handle sign
    if (*str == '-') {
        negative = true;
        str++;
    } else if (*str == '+') {
        str++;
    }
    
    // Process characters
    while (*str != '\0') {
        if (*str >= '0' && *str <= '9') {
            if (decimal) {
                fraction *= 0.1f;
                value += (*str - '0') * fraction;
            } else {
                value = value * 10.0f + (*str - '0');
            }
        } else if (*str == '.') {
            decimal = true;
        } else {
            break; // Stop at invalid characters
        }
        str++;
    }
    
    return negative ? -value : value;
}