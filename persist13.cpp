

#include <iostream>
#include <stdio.h>
using namespace std;

#define ENDD 255






void digmul(uint8_t* digits, uint8_t B) {
    div_t q ;
    q.quot = 0;
    while (*digits != ENDD) {
        *digits = *digits * B + q.quot;
        q = div(*digits, 10);
        *digits = q.rem;
        //cout << "WHILE: " << (int)(*digits) << "  " << carry << "\n";
        digits++;
    }
    if (q.quot != 0) {
        *digits = q.quot;
        digits++;
    }
    *digits = ENDD;
}


void dispdigits(uint8_t* digits) {
    while (*digits != ENDD) {
        cout << (int)( *digits) << " ";
        digits++;
    }
}

void mulall(uint8_t* result,  uint8_t* source_digits) {
    result[0] = source_digits[0];
    result[1] = ENDD;
    source_digits++;
    while ( *source_digits != ENDD) {
        digmul(result, *source_digits);
        source_digits++;
    }
}

void rep_mul(uint8_t* result, uint8_t first, unsigned long long sevens, unsigned long long eights, unsigned long long nines) {
    result[0] = first;
    result[1] = ENDD;
    for (; sevens > 0; sevens--) digmul(result, 7);
    for (; eights > 0; eights--) digmul(result, 8);
    for (; nines > 0; nines--) digmul(result, 9);
}

int perstistence(uint8_t* digits) {
    uint8_t buffer[20];
    uint8_t* ptr1;
    uint8_t* ptr2;
    int p = 1;
    while (digits[1] != ENDD) {
        p++;
        mulall(buffer, digits);
        ptr1 = buffer; ptr2 = digits;
       while(*ptr1 != ENDD) {
            *ptr2++ = *ptr1++;
        }
        *ptr2 = ENDD;
        //dispdigits(digits); cout << '\n';

    }
    return p;


}

bool equiv(uint8_t* digits, unsigned long long target[10]) {
// Function returns true if the number of twos, threes, etc. in digits is as given
    unsigned long long counts[10] = { 0,0,0,0,0,0,0,0,0,0 };
    while (*digits != ENDD) {
        counts[*digits]++;
        digits++;
    }
    
    for (int i = 2; i < 10; i++) {
        if (counts[i] != target[i]) return(false);
    }
    return(true);
    

}

int main(int argc, char* argv[])
{
    uint8_t* digits;
    unsigned long long target[10] = { 0,0,1,0,0,0,0,6,6,2 };

    if (argc != 8) {
        cout << "Incorrect arguments.\n";
        cout << "Syntax: persist13.exe leading_digit min#sevens max#sevens min#8s max#8s min#9s max#9s\n";
        return 2;
    }
    uint8_t first = atoi(argv[1]);
    
    
    unsigned long long sevens_start = atoi(argv[2]);
    unsigned long long sevens_stop = atoi(argv[3]);
    unsigned long long eights_start = atoi(argv[4]);
    unsigned long long eights_stop = atoi(argv[5]);
    unsigned long long nines_start = atoi(argv[6]);
    unsigned long long nines_stop = atoi(argv[7]);

    cout << "Running with a leading " << (int)first << ", " << sevens_start << "-" << sevens_stop << " sevens, " << eights_start << "-" << eights_stop << " eights, and " << nines_start << "-" << nines_stop << " nines.\n";

    cout << "Allocating memory...\n";

    digits = (uint8_t*)malloc((2 + sevens_stop + eights_stop + nines_stop)* sizeof(uint8_t));
    
    cout << "Running...\n";
    for (unsigned long long sevens = sevens_start; sevens <= sevens_stop; sevens++) {
        for (unsigned long long eights = eights_start; eights <= eights_stop; eights++) {
            for (unsigned long long nines = nines_start; nines <= nines_stop; nines++) {
                // Load up the 
                rep_mul(digits, first, sevens, eights, nines);
                if (equiv(digits, target)) {
                    cout << "\a\nNew number found! It has a leading " << (int)first << ", " << sevens << " sevens, " << eights << " eights, " << nines << " nines.\n";

                }

            }
        }
    }

    //rep_mul(digits, 2, 3, 4, 5);
    //dispdigits(digits);
    cout << "\nWe've searched everything! Press enter to close.";
    free(digits);
    cin >> first;
    return 0;


}
