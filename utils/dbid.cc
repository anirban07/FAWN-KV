/* -*- Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*- */
using namespace std;
#include <iostream>
#include <iomanip>
#include "dbid.h"
#include "print.h"
#include "hashutil.h"


namespace fawn {
    DBID::DBID() : actual_size(0) {
        memset(value, '\0', sizeof(value));
    }

    DBID::DBID(const char* c, unsigned int size) {
        Init(c, size);
    }

    DBID::DBID(const string &s) {
        Init(s.data(), s.size());
    }

    void DBID::Init(const char *c, unsigned int size) {
        // Keep track of input size (vs. DBID_LENGTH)
        actual_size = size;
        hash_num = HashUtil::BobHash(c);

        if (size > DBID_LENGTH) {
            cout << "Only " << DBID_LENGTH << " byte IDs supported, size = " << size << ".  Truncating ..." << endl;
            cout << "Change DBID_LENGTH in dbid.h to a large number to support larger key sizes." << endl;
            actual_size = size = DBID_LENGTH;
        }

        // Set value
        memcpy(value, c, size);

        // Pad entry with 0s if needed
        if (size < DBID_LENGTH)
            memset(value+size, '\0', DBID_LENGTH - size);

    }

    DBID::~DBID() {

    }

    string* DBID::actual_data() {
        return new string((char *)value, actual_size);
    }

    const string DBID::actual_data_str() const {
        return string((char *)value, actual_size);
    }


    void DBID::printValue() const {
        cout << "actual dbid size: " << actual_size << endl;
        print_payload((const u_char*)value, DBID_LENGTH);
    }

    void DBID::printValue(int prefix_bytes) const {
        cout << "actual dbid size: " << actual_size << ", printing first " << prefix_bytes << " bytes of dbid" << endl;
        print_payload((const u_char*)value, prefix_bytes);
    }


    bool DBID::operator==(const DBID &rhs) const {
        return hash_num == rhs.hash_num;
    }

    // Bytewise comparison of equal-length byte arrays
    bool DBID::operator<(const DBID &rhs) const {
        return hash_num < rhs.hash_num;
    }

    uint64_t DBID::operator-(const DBID &rhs) const {
        if (hash_num > rhs.hash_num)
            return (uint64_t) (hash_num - rhs.hash_num);
        else
            return (uint64_t) (rhs.hash_num - hash_num);
    }

    // returns this - rhs
    //     DBID DBID::operator-(const DBID &rhs) const
    //     {
    //         int8_t carryover = 0;
    //         char ans[DBID_LENGTH];
    //         for (uint i = DBID_LENGTH-1; i >= 0; i--) {
    //             uint8_t diff = ((value[i] & 0xff) - (rhs.value[i] & 0xff)) & 0xff;
    //             carryover = (diff == 0 && carryover == 1);
    //             ans[i] = (diff - carryover) & 0xff;
    //         }
    //         return DBID(ans, DBID_LENGTH);
    //     }



    // Comparison function for ring space.
    bool between(const string& startKey, const string& endKey, const string& thisKey) {
        DBID startID(startKey);
        DBID endID(endKey);
        DBID thisID(thisKey);

        return between(&startID, &endID, &thisID);
    }

    bool between(const DBID* startID, const DBID* endID, const DBID* thisID) {
        if (*startID == *endID) {
            return true;
        } else if (*endID < *startID) {
            // endKey < startKey, so there is wrap around
            if (*startID < *thisID || !(*endID < *thisID)) {
                return true;
            }
        } else {
            // startKey < endKey
            // if startKey < key and !(key > endKey)
            if (*startID < *thisID && !(*endID < *thisID)) {
                return true;
            }
        }

        return false;
    }

}
