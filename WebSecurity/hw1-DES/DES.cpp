#include <iostream>  
#include <fstream>  
#include <bitset>  
#include <string>  
#include "tables.cpp"
using namespace std; 

// keys
bitset<64> key;
bitset<48> subKey[16];

void generateKey();
bitset<64> encrypt(bitset<64> &plainMsg);
bitset<64> decrypt(bitset<64> &cipherMsg);
bitset<64> crypto_kernel(bitset<64> &msg, bool isEncrypt);

bitset<32> Feistel_f(bitset<32> R, bitset<48> k);
bitset<28> roundLeft(bitset<28> k, int shiftCount);

// actually [8] is meaningless, just a reminder
bitset<64> char2Bitset(const char s[8]) {
    bitset<64> bits;  
    for(int i = 0; i < 8; i++)  
        for(int j = 0; j<8; j++)  
            bits[i * 8 + j] = ((s[i] >> j) & 1);  
    return bits;  
}

int main() {
    // start

    string strkey = "yuanshou";
    key = char2Bitset(strkey.c_str());
    // generate key in bitset
    generateKey();

    ifstream in("plain.txt", ios::binary);   
    ofstream out("cipher.txt", ios::binary);
    // ifstream in("rabbit1.jpg", ios::binary);
    // ofstream out("rabbit_encrypt.jpg", ios::binary);
    bitset<64> plain;  
    while(in.read((char*)&plain, sizeof(plain))) {  
        bitset<64> cipher  = encrypt(plain);  
        out.write((char*)&cipher, sizeof(cipher));  
        plain.reset();
    }  
    in.close();  
    out.close();  

    // decrypt cipher.txt -> decrypt.txt
    in.open("cipher.txt", ios::binary);  
    out.open("decrypt.txt", ios::binary);  
    // in.open("rabbit_encrypt.jpg", ios::binary);  
    // out.open("decrypt_rabbit.jpg", ios::binary);  
    while(in.read((char*)&plain, sizeof(plain))) {  
        bitset<64> temp  = decrypt(plain);  
        out.write((char*)&temp, sizeof(temp));  
        plain.reset();
    }  
    in.close();  
    out.close(); 

    // end
}

bitset<64> crypto_kernel(bitset<64> &msg, bool isEncrypt = true) {
    bitset<64> ret, tmpIPreplace;
    bitset<32> Li, Ri, tmpRi;

    /**
     * IP replacement
     * IP table is marked in 1~64, but IPreplace is [0..63]
     * stringText in bitset : last plain char will be in first bits in bitset
     */
    for (int i = 0; i < 64; i++) {
        tmpIPreplace[63 - i] = msg[64 - IP[i]];
    }
    /**
     * get Li, Ri
     * Li : first 32 bits in M0  ( due to "reverse", Li is IPreplace[32..63] )
     * Ri : last 32 bits in M0   ( due to "reverse", Ri is IPreplace[0..31] )
     */
    for (int i = 0; i < 32; i++) {
        Li[i] = tmpIPreplace[i + 32];
        Ri[i] = tmpIPreplace[i];
    }

    // T Iteration ( 16 times )
    for (int iTcount = 0; iTcount < 16; iTcount++) {
        tmpRi = Ri;
        if (isEncrypt)
        Ri = Li ^ Feistel_f(Ri, subKey[iTcount]);
        else
        Ri = Li ^ Feistel_f(Ri, subKey[15 - iTcount]); 
        Li = tmpRi;
    }

    // Merge Li, Ri: Merge as [Ri_Li]: Ri -> ret[32..63], Li -> ret[0..31]
    for (int i = 0; i < 32; i++) {
        ret[i] = Li[i];
        ret[i + 32] = Ri[i];
    }

    // IP-1 replacement
    tmpIPreplace = ret;
    for (int i = 0; i < 64; i++) {
        ret[63 - i] = tmpIPreplace[64 - IP_1[i]];
    }

    return ret; 
}

bitset<64> encrypt(bitset<64>& plainMsg) {
    return crypto_kernel(plainMsg);
}

bitset<64> decrypt(bitset<64>& cipherMsg) {
    return crypto_kernel(cipherMsg, false);
}

/**
 * Feistel function f(R[i-1], K[i]);
 * E Extend
 * S-box(6 to 4) 
 * P replacement
 */
bitset<32> Feistel_f(bitset<32> R, bitset<48> k) {
    // E Extend on R
    bitset<48> expandR;
    for (int i = 0; i < 48; i++) {
        expandR[47 - i] = R[32 - E[i]];
    }
    // xor
    expandR ^= k;
    // look up in S-box
    bitset<32> ret;
    int retIdx = 0;
    for (int i = 0; i < 48; i += 6) {
        int row = expandR[47 - i] * 2 + expandR[47 - i - 5];
        int col = expandR[47-i-1]*8 + expandR[47-i-2]*4 + expandR[47-i-3]*2 + expandR[47-i-4];  
        int num = S_BOX[i/6][row][col]; 
        bitset<4> numberBit(num);
        for (int ii = 0; ii < 4; ii++) {
            ret[31 - retIdx - ii] = numberBit[3 - ii];
        }
        retIdx += 4;
    }
    // P replacement
    bitset<32> tmp = ret;  
    for(int i = 0; i < 32; i++)  
        ret[31 - i] = tmp[32 - P[i]];  
    return ret; 
}

bitset<28> roundLeft(bitset<28> k, int shiftCount) {
    bitset<28> tmp = k;
    for (int i = 27; i >= 0; i--) {
        if (i - shiftCount < 0) {
            k[i] = tmp[i - shiftCount + 28];
        } else {
            k[i] = tmp[i - shiftCount];
        }
    }
    return k;
}

void generateKey() {
    bitset<56> keyWithoutChkBit;
    bitset<28> left, right;
    bitset<48> keyCompressed_PC2;
    // remove check bits
    for (int i = 0; i < 56; i++) {
        keyWithoutChkBit[55 - i] = key[64 - PC_1[i]];
    }
    // generate subKeys
    for (int subKeyIdx = 0; subKeyIdx < 16; subKeyIdx++) {
        // get left & right
        for (int i = 0; i < 28; i++) {
            left[i] = keyWithoutChkBit[i + 28];
            right[i] = keyWithoutChkBit[i];
        }
        left = roundLeft(left, shiftBits[subKeyIdx]);  
        right = roundLeft(right, shiftBits[subKeyIdx]);  
        for (int i = 0; i < 28; i++) {
            keyWithoutChkBit[i + 28] = left[i];
            keyWithoutChkBit[i] = right[i];
        }
        for (int i = 0; i < 48; i++) {
            keyCompressed_PC2[47 - i] = keyWithoutChkBit[56 - PC_2[i]];
        }
        subKey[subKeyIdx] = keyCompressed_PC2;
    }
}