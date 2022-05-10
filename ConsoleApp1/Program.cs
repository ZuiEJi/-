using System;

namespace ConsoleApp1
{
    class Program
    {
        static void Main(string[] args)
        {
            int n = 10;
            add(ref n);
            System.Console.WriteLine(n);
        }

        static void add(ref int n)
        {
            n = n + 1;

        }

        
    }
}
