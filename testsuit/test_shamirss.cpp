#include <iomanip>
#include <iostream>
#include <gmpxx.h>

#include "shamirss.hpp"


using namespace std;


int main(int argc, char const *argv[])
{
    int i = 0;
    int success = 0;

    size_t nusers = 10;
    size_t threshold = 7;

    FIELD_n secret;
    secret = FIELD_n(11);

    cout << "Testing Shamir Secret Sharing protocol" << endl;
    cout << "--------------START OF TEST-------------------" << endl;    

    ShamirSS sss; 

    share_v_t shares = sss.getShares(threshold,nusers,secret);
    // shares.resize(threshold);
    FIELD_n result = sss.reconSecret(shares);

    cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
    if(result == secret) 
        cout << "OK" << endl;
    else 
    {
        cout  << "FAIL" << endl;
        success = -1;
    }
 

    cout << "--------------END OF TEST-------------------" << endl;
    return success;
}
