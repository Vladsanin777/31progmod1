using System;
using System.Runtime.InteropServices;

public class Array<T> where T : unmanaged
{
    private readonly T[] m_arr;
    private readonly int m_size;

    private static uint _Randseed = (uint)Environment.TickCount;

    private static T[] FillRandom(int size)
    {
        T[] arr = new T[size];
        for (int i = 0; i < size; i++)
        {
            _Randseed = _Randseed * 1103515245 + 12345;
            arr[i] = CastToT(_Randseed);
        }
        return arr;
    }

    private static T CastToT(uint value)
    {
        if (typeof(T) == typeof(int))
            return (T)(object)(int)value;
        if (typeof(T) == typeof(uint))
            return (T)(object)value;
        if (typeof(T) == typeof(byte))
            return (T)(object)(byte)value;
        if (typeof(T) == typeof(sbyte))
            return (T)(object)(sbyte)value;
        if (typeof(T) == typeof(short))
            return (T)(object)(short)value;
        if (typeof(T) == typeof(ushort))
            return (T)(object)(ushort)value;
        if (typeof(T) == typeof(long))
            return (T)(object)(long)value;
        if (typeof(T) == typeof(ulong))
            return (T)(object)(ulong)value;
        if (typeof(T) == typeof(char))
            return (T)(object)(char)value;
        
        throw new NotSupportedException($"Type {typeof(T)} is not supported");
    }

    public Array(int size)
    {
        m_size = size;
        m_arr = FillRandom(size);
    }

    public void Decrement()
    {
        T buf = m_arr[0];
        Buffer.BlockCopy(m_arr, Marshal.SizeOf<T>(), m_arr, 0, (m_size - 1) * Marshal.SizeOf<T>());
        m_arr[m_size - 1] = buf;
    }

    public void Increment()
    {
        T buf = m_arr[m_size - 1];
        Buffer.BlockCopy(m_arr, 0, m_arr, Marshal.SizeOf<T>(), (m_size - 1) * Marshal.SizeOf<T>());
        m_arr[0] = buf;
    }

    public void ShiftLeft(int shift)
    {
        shift %= m_size;
        if ((m_size >> 1) < shift)
        {
            ShiftRight(m_size - shift);
            return;
        }

        T[] buf = new T[shift];
        Buffer.BlockCopy(m_arr, 0, buf, 0, shift * Marshal.SizeOf<T>());
        Buffer.BlockCopy(m_arr, shift * Marshal.SizeOf<T>(), m_arr, 0, (m_size - shift) * Marshal.SizeOf<T>());
        Buffer.BlockCopy(buf, 0, m_arr, (m_size - shift) * Marshal.SizeOf<T>(), shift * Marshal.SizeOf<T>());
    }

    public void ShiftRight(int shift)
    {
        shift %= m_size;
        if ((m_size >> 1) < shift)
        {
            ShiftLeft(m_size - shift);
            return;
        }

        T[] buf = new T[shift];
        Buffer.BlockCopy(m_arr, (m_size - shift) * Marshal.SizeOf<T>(), buf, 0, shift * Marshal.SizeOf<T>());
        Buffer.BlockCopy(m_arr, 0, m_arr, shift * Marshal.SizeOf<T>(), (m_size - shift) * Marshal.SizeOf<T>());
        Buffer.BlockCopy(buf, 0, m_arr, 0, shift * Marshal.SizeOf<T>());
    }

    public override string ToString()
    {
        return $"Array = {{ {string.Join(" ", m_arr)} }}";
    }
}

public class Program
{
    public static void Main(string[] args)
    {
        if (args.Length != 1)
        {
            Console.WriteLine($"Must launch: \"{Environment.GetCommandLineArgs()[0]} <any number>\"");
            return;
        }

        if (!int.TryParse(args[0], out int size))
        {
            Console.WriteLine("Invalid number");
            return;
        }

        Array<int> arr = new Array<int>(size);
        
        Console.WriteLine("arr >> 1, arr << 1, arr << 3, arr >> 3, arr << 126, arr >> 126;");
        Console.WriteLine(arr);
        
        arr.Increment();
        Console.WriteLine(arr);
        
        arr.Decrement();
        Console.WriteLine(arr);
        
        arr.ShiftLeft(3);
        Console.WriteLine(arr);
        
        arr.ShiftRight(3);
        Console.WriteLine(arr);
        
        arr.ShiftLeft(126);
        Console.WriteLine(arr);
        
        arr.ShiftRight(126);
        Console.WriteLine(arr);
    }
}           
