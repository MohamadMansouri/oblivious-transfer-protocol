#include <iomanip>
#include <iostream>
#include <gmpxx.h>

#include "opprf.hpp"

#define NB_TESTS 10

using namespace std;


int main(int argc, char const *argv[])
{
    int i = 0;
    int success = 0;
    uint16_t theta = 1000;
    uint16_t x[NB_TESTS];
    opprf_G_t ga = CURVE().getRandomPoint();
    crs_ddh_ec_t crs = dmeDDH_EC().crs;

    cout << "Testing OPPRF protocol" << endl;
    cout << "--------------START OF TEST-------------------" << endl;    

    for(size_t j=0; j<NB_TESTS; j++)
    {
        x[j] = (uint16_t) (rand() % theta);
    }

    OPPRFserver opprfs = OPPRFserver(theta, crs);
    OPPRFclient opprfc = OPPRFclient(theta, crs);

    for(size_t j=0; j<NB_TESTS; j++)
    {
        // set secret for the server
        opprfs.setSecret(ga);

        // set input for the client
        opprfc.setMessage(x[j]);

        // prepare server inputs
        opprfs.prepareKeysAndInputs();

        //run l OTs
        for(int i=MSG_BITS; i >0; i--)
        {
            // client send pk for its selection b 
            pkey_t pk = opprfc.runOTRound_start(i);
            // server encrypt both OT inputs
            ot_ctxts_t c = opprfs.runOTRound(i, pk);
            // client decrypts the ciphertext of its selection b
            opprfc.runOTRound_end(i, c);
        }

        // server encrypts its masks
        opprf_symctxt_t c = opprfs.sendEncryptedMasks();

        // client decrypts mask and unmask the result
        opprfc.unmaskResult(c);


        cout << left << setw(6) << "Test " << ++i << ":" << setw(0) << "\t";
        if(opprfc.getResult() == opprfs.getKOPPRF() + ga*x[j]) 
            cout << "OK" << endl;
        else 
        {
            cout  << "FAIL" << endl;
            success = -1;
        }
        opprfs.clean();
        opprfc.clean();
    }

 

    cout << "--------------END OF TEST-------------------" << endl;

    return success;
}
