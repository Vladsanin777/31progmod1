using System;

class SumBit {
    static int sumBit(int num) {
        return ((num >> 1) & 1) + ((num >> 10) & 1);
    }
    static void Main() {
        int num = int.Parse(Console.ReadLine());
        Console.WriteLine(sumBit(num));
    }
}
