/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x | ~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(~x & ~y) & ~(x & y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    return !((x>>31) ^ (y>>31)) && !((!x) ^ (!y));
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int b16, b8, b4, b2, b1;
    b16 = (v > 0xFFFF) << 4;
    v = v >> b16;
    b8 = (v > 0xFF) << 3;
    v = v >> b8;
    b4 = (v > 0xF) << 2;
    v = v >> b4;
    b2 = (v > 0x3) << 1;
    v = v >> b2;
    b1 = v > 0x1;

    return b16 | b8 | b4 | b2 | b1;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int npos = n << 3;
    int mpos = m << 3;
    int nbyte = (x >> npos) & 0xFF;
    int mbyte = (x >> mpos) & 0xFF;
    x = x & ~((0xFF << npos) | (0xFF << mpos));
    return x | (nbyte << mpos) | (mbyte << npos);
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned result = 0;
    unsigned i = 32;
    while(i){
        result = (result << 1) | (v & 1);
        v = v>> 1;
        i--;
    }
    return result;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int mask = ~(((1 << 31) >> n) << 1);
    return (x >> n) & mask;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int b16, b8, b4, b2, b1, last;

    b16 = !(~(x >> 16)) << 4;
    x = x << b16;

    b8 = !(~(x >> 24)) << 3;
    x = x << b8;

    b4 = !(~(x >> 28)) << 2;
    x = x << b4;

    b2 = !(~(x >> 30)) << 1;
    x = x << b2;

    b1 = !(~(x >> 31));
    x = x << b1;

    last = (x >> 31) & 1;

    return b16 + b8 + b4 + b2 + b1 + last;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {

    int sign;
    int ax;
    int temp;
    int k;
    int shift;
    int main;
    int lost;
    int half;

    if (!x)
        return 0;

    sign = x & 0x80000000;

    if (sign) {
        if (x == 0x80000000)
            return 0xcf000000;
        ax = -x;
    } else {
        ax = x;
    }

    k = 0;
    temp = ax;

    while (temp > 1) {
        temp = temp >> 1;
        k = k + 1;
    }

    if (k < 24) {
        main = ax << (23 - k);
    } else {
        shift = k - 23;
        main = ax >> shift;
        lost = ax & ((1 << shift) - 1);
        half = 1 << (shift - 1);

        if (lost > half)
            main = main + 1;
        else if (lost == half) {
            if (main & 1)
                main = main + 1;
        }
    }

    return sign | (((k + 126) << 23) + main);
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    int exp;

    exp = uf & 0x7f800000;

    if (exp == 0x7f800000)
        return uf;

    if (!exp)
        return (uf & 0x80000000) | ((uf & 0x7fffffff) << 1);

    if (exp == 0x7f000000)
        return (uf & 0x80000000) | 0x7f800000;

    return uf + 0x00800000;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    int sign;
    int exp;
    int E;
    int high;
    int val;

    sign = uf2 >> 31;
    exp = (uf2 >> 20) & 0x7ff;
    E = exp - 1023;

    if (E < 0)
        return 0;

    if (E >= 31)
        return ~0x7fffffff;

    high = (uf2 & 0xfffff) | 0x100000;

    if (E <= 20) {
        val = high >> (20 - E);
    } else {
        val = (high << (E - 20)) | (uf1 >> (52 - E));
    }

    if (sign)
        return -val;

    return val;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if (x < -149)
        return 0;

    if (x < -126)
        return 1 << (x + 149);

    if (x > 127)
        return 0x7f800000;

    return (x + 127) << 23;
}
