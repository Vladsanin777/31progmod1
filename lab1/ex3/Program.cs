using System;
using u32 = int;

class BitMap {
    private u32[] _map = new u32[0x20];
    public BitMap() {}
    public u32 getBit(u32 bit) { return _map[bit >> 5]; }
    public void setBit(u32 bit) { _map[bit >> 5] |= (0x1 << (bit & 0x1F)); }
    public void eraseBit(u32 bit) { _map[bit >> 5] &= (~(0x1 << (bit & 0x1F))); }
    public void inverseBit(u32 bit) { _map[bit >> 5] ^= (0x1 << (bit & 0x1F)); }
    public void print() {
        Console.Write("0x");
        for (u32 i = 0x1f; i > -0x1; i--)
            Console.Write("{0:X8}", _map[i]);
        Console.WriteLine();
    }
    public void printSetBit(u32 bit) {
        print();
        setBit(bit);
        print();
    }
    public void printEraseBit(u32 bit) {
        print();
        eraseBit(bit);
        print();
    }
    public void printInverseBit(u32 bit) {
        print();
        inverseBit(bit);
        print();
    }
    static void Main() {
        u32 num = u32.Parse(Console.ReadLine());
        BitMap bitMap = new BitMap();
        Console.WriteLine(bitMap.getBit(num));
        bitMap.printSetBit(num);
        bitMap.printEraseBit(num);
        bitMap.printInverseBit(num);
    }
}
