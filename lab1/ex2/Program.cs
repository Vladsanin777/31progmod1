using System;
using u32 = int;

class Bit32 {
    private u32 _num;
    public Bit32(u32 num) { _num = num; }
    public u32 getNum() { return _num; }
    public void setNum(u32 num) { _num = num; }
    public u32 getBit(u32 bit) { return (_num >> bit) & 0x1; }
    public u32 sumBit(u32 bit1, u32 bit2) { 
        return getBit(bit1) + getBit(bit2);
    }
    public u32 upBit(u32 bit) { return _num | (0x1 << bit); }
    public u32 downBit(u32 bit) { return _num & (~(0x1 << bit)); }
    public u32 inverseBit(u32 bit) { return _num ^ (0x1 << bit); }
    public u32 sumBit2and3() { return sumBit(2, 3); }
    public u32 sumBit2and4() { return sumBit(2, 4); }
    public u32 sumBit5and10() { return sumBit(5, 10); }
    public u32 upBit7() { return upBit(7); }
    public u32 downBit15() { return downBit(15); }
    public u32 inverseBit30() { return inverseBit(30); }
    static void Main() {
        Bit32 bit32 = new Bit32(u32.Parse(Console.ReadLine()));
        Console.Write(
            "sumBit2and3 {0}, sumBit2and4 {1}, sumBit5and10 {2}, ", 
            bit32.sumBit2and3(), bit32.sumBit2and4(), bit32.sumBit5and10());
        Console.WriteLine(
            "upBit7 {0}, downBit15 {1}, inverseBit30 {2}", 
            bit32.upBit7(), bit32.downBit15(), bit32.inverseBit30());
    }
}
