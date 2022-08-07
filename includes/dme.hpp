#ifndef __DME__
#define __DME__

#include <gmpxx.h>
#include <tuple>

#include "ecc_secp256r1.hpp"

typedef Field_secp256r1_p FIELD_p;
typedef Field_secp256r1_n FIELD_n;
typedef Point_secp256r1 POINT;
typedef Curve_secp256r1 CURVE;

typedef struct CRS_DDH_EC
{
    POINT g0, g1, h0, h1;

    CRS_DDH_EC() {};
    CRS_DDH_EC(POINT g0, POINT g1, POINT h0, POINT h1);
    CRS_DDH_EC& operator= (const CRS_DDH_EC& crs);
    bool operator== (const CRS_DDH_EC& crs) const;
    void updateCurve(CURVE* c);

} crs_ddh_ec_t;

typedef struct td_messy_DDH_EC
{
    FIELD_n e0, e1;

    td_messy_DDH_EC() {};
    td_messy_DDH_EC(FIELD_n e0, FIELD_n e1);
    td_messy_DDH_EC& operator=(const td_messy_DDH_EC& td);
    bool operator==(const td_messy_DDH_EC& td) const;
} td_messy_ddh_ec_t;

typedef struct td_dec_DDH_EC
{
    FIELD_n y;

    td_dec_DDH_EC() {};
    td_dec_DDH_EC(FIELD_n y);
    td_dec_DDH_EC& operator=(const td_dec_DDH_EC& td);
    bool operator==(const td_dec_DDH_EC& td) const;
} td_dec_ddh_ec_t;

enum dme_mode_t {messy, dec};  

enum dme_branch_t{b0 = 0, b1 = 1};


typedef struct PKEY
{
    POINT g, h;
 
    PKEY() {};
    PKEY(POINT g, POINT h);
    PKEY& operator=(const PKEY& pk);
    bool operator==(const PKEY& pk) const;
} pkey_t;

typedef FIELD_n skey_t; 

typedef struct KeyPair_t
{
    pkey_t pk;
    skey_t sk;

    KeyPair_t() {};
    KeyPair_t(pkey_t pk, skey_t sk);
    KeyPair_t& operator=(const KeyPair_t& keys);
    bool operator==(const KeyPair_t& keys) const;
} keypair_t;


typedef struct CTXT
{
    POINT u; 
    POINT mv;

    CTXT() {};
    CTXT(POINT u, POINT mv);
    
    CTXT& operator=(const CTXT& ctxt);
    bool operator==(const CTXT& ctxt) const;

} ctxt_t;

typedef POINT msg_t;

class dmeDDH_EC
{
private:
    static const size_t secparam = 256; //bits
    
    CURVE* curve =  new CURVE;

    dme_mode_t mode;  
    td_messy_ddh_ec_t td_m;
    td_dec_ddh_ec_t td_d;


public:
    crs_ddh_ec_t  crs;


    dmeDDH_EC();
    dmeDDH_EC(dme_mode_t mu);
    dmeDDH_EC(crs_ddh_ec_t crs);
    ~dmeDDH_EC();

    CURVE* getCurve(void) {return curve;}

    keypair_t KeyGen(dme_branch_t branch) const;
    ctxt_t Enc(const pkey_t& pk, dme_branch_t b, const msg_t& m) const;
    msg_t Dec(const skey_t& sk, const ctxt_t& c) const;
    dme_branch_t FindMessy(const pkey_t& pk) const;
    std::tuple<pkey_t, skey_t, skey_t > TrapKeyGen() const;

};





#endif