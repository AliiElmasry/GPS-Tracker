#include <stdint.h>
#include <stdbool.h>
#include <math.h>

void floatToString(float value, char *buf, uint8_t decimals) {
    char *ptr = buf;
    int32_t int_part = (int32_t)value;
    int32_t frac_part;
    int32_t power = 1;

    // Handle negative numbers
    if (value < 0) {
        *ptr++ = '-';
        value = -value;
        int_part = -int_part;
    }

    // Calculate power of 10 for decimal precision
    for (uint8_t i = 0; i < decimals; i++) {
        power *= 10;
    }

    // Round and extract fractional part
    float rounded = value + (0.5f / power);
    frac_part = (int32_t)((rounded - int_part) * power);

    // Handle overflow from rounding
    if (frac_part >= power) {
        frac_part -= power;
        int_part++;
    }

    // Convert integer part
    if (int_part == 0) {
        *ptr++ = '0';
    } else {
        // Reverse digits into buffer
        char *start = ptr;
        while (int_part > 0) {
            *ptr++ = '0' + (int_part % 10);
            int_part /= 10;
        }
        // Reverse digits back to correct order
        char *end = ptr - 1;
        while (start < end) {
            char tmp = *start;
            *start++ = *end;
            *end-- = tmp;
        }
    }

    // Convert fractional part (correct order)
    if (decimals > 0) {
        *ptr++ = '.';
        
        // Extract digits from left to right
        int32_t divisor = power / 10;
        for (uint8_t i = 0; i < decimals; i++) {
            *ptr++ = '0' + (frac_part / divisor);
            frac_part %= divisor;
            divisor /= 10;
        }
    }

    *ptr = '\0'; // Null-terminate
}