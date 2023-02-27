#include <cassert>
#include <vector>
#include <climits> // for INT_MIN and INT_MAX
#include "BitRepresentation.h"
/*
template <typename T>
void testBitRepresentation() {
    // Test BitRepresentation(T number) constructor
    BitRepresentation<T> br1(10);
    assert(br1.getNumber() == 10);
    BitRepresentation<T> br2(-10);
    assert(br2.getNumber() == -10);
    //BitRepresentation<T> br3(INT_MIN);
    //assert(br3.getNumber() == INT_MIN);
    //BitRepresentation<T> br4(INT_MAX);
    //assert(br4.getNumber() == INT_MAX);
    BitRepresentation<T> br5(0);
    assert(br5.getNumber() == 0);

    // Test BitRepresentation(vector<bool>) constructor
    std::vector<bool> v1(8, true); // 8-bit vector with all bits set to 1
    BitRepresentation<T> br6(v1);
    cout << (int)br6.getNumber() << endl;
    assert(br6.getNumber() == -1);
    std::vector<bool> v2(8, false); // 8-bit vector with all bits set to 0
    BitRepresentation<T> br7(v2);
    assert(br7.getNumber() == 0);
    std::vector<bool> v3{true, false, true, false, true, false, true, false}; // 8-bit vector with alternating 1s and 0s
    BitRepresentation<T> br8(v3);
    assert(br8.getNumber() == -86);
    std::vector<bool> v4(16, true); // 16-bit vector with more elements than the number of bits in the data member
    BitRepresentation<T> br9(v4);
    assert(br9.getNumber() == 65535);
    std::vector<bool> v5; // empty vector
    BitRepresentation<T> br10(v5);
    assert(br10.getNumber() == 0);

    // Test getBinary() function
    assert(br6.getBinary() == "11111111");
    assert(br7.getBinary() == "00000000");
    assert(br8.getBinary() == "01010101");
    //assert(br3.getBinary() == "10000000000000000000000000000000");
    //assert(br4.getBinary() == "01111111111111111111111111111111");

    // Test getHexadecimal() function
    assert(br6.getHexadecimal() == "FF");
    assert(br7.getHexadecimal() == "00");
    assert(br8.getHexadecimal() == "55");
    //assert(br3.getHexadecimal() == "80000000");
    //assert(br4.getHexadecimal() == "7FFFFFFF");

    // Test setBit() function
    br7.setBit(0);
    assert(br7.getNumber() == 1);
    br7.setBit(7);
    assert(br7.getNumber() == 129);
    br7.setBit(8); // invalid location
    assert(br7.getNumber() == 129);

    // Test unsetBit() function
    br8.unsetBit(0);
    assert(br8.getNumber() == 84);
    br8.unsetBit(7);
    assert(br8.getNumber() == 4);
    br8.unsetBit(8); // invalid location
    assert(br8.getNumber() == 4);

    // Test isBitSet() function
    assert(br6.isBitSet(0) == true);
    assert(br6.isBitSet(7) == true);
    assert(br6.isBitSet(8) == false);
    assert(br7.isBitSet(0) == true);
    assert(br7.isBitSet(7) == true);
    assert(br7.isBitSet(8) == false);
    assert(br8.isBitSet(0) == false);
    assert(br8.isBitSet(7) == false);
    assert(br8.isBitSet(8) == false);

    // Test getNumber() function
    assert(br1.getNumber() == 10);
    assert(br2.getNumber() == -10);
    //assert(br3.getNumber() == INT_MIN);
    //assert(br4.getNumber() == INT_MAX);
    assert(br5.getNumber() == 0);
}

int main() {
    testBitRepresentation<char>();
    testBitRepresentation<short>();
    testBitRepresentation<int>();
    testBitRepresentation<long>();
    testBitRepresentation<long long>();
}

*/

int main() {
    vector<bool> v1 = {true, false, true, false}; // == 0b1010
    BitRepresentation<char> s1(v1); // s1.data = 0b00001010 => 10
    vector<bool> v2 = {true, true, true, true, false, false, false, false};
    BitRepresentation<char> s2(v2); // s2.data = 0b11110000 => -16
    vector<bool> v3 = {true, false, false, true, true, true, true, true, true,
                       false, false, false, false};
    BitRepresentation<char> s3(v3); // s3.data = 0b11110000 => -16
// since the char data type has only 8 bits, only the last 8
// booleans in v3 were used to initialize s3.data.
// The rest (i.e. the first 5 elements of v3) were discarded.
    cout << "s1 is: " << (int)s1.getNumber() << " and the binary representation is: " << s1.getBinary() << " and the hexadecimal representation is: " << s1.getHexadecimal() << endl;
    cout << "s2 is: " << (int)s2.getNumber() << " and the binary representation is: " << s2.getBinary() << " and the hexadecimal representation is: " << s2.getHexadecimal() << endl;
    cout << "s3 is: " << (int)s3.getNumber() << " and the binary representation is: " << s3.getBinary() << " and the hexadecimal representation is: " << s3.getHexadecimal() << endl;

    BitRepresentation<unsigned int> s4(INT_MAX);
    cout << "s4 is: " << (int)s4.getNumber() << " and the binary representation is: " << s4.getBinary() << " and the hexadecimal representation is: " << s4.getHexadecimal() << endl;
    s4.setBit(31);
    cout << "modified s4 is: " << (int)s4.getNumber() << " and the binary representation is: " << s4.getBinary() << " and the hexadecimal representation is: " << s4.getHexadecimal() << endl;
    s4.unsetBit(31);
    cout << "modified s4 is: " << (int)s4.getNumber() << " and the binary representation is: " << s4.getBinary() << " and the hexadecimal representation is: " << s4.getHexadecimal() << endl;
    return 0;
}