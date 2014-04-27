using System;
using System.Linq;
using System.IO;
using System.Collections.Generic;


namespace Anagram
{
    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length == 0)
            {
                usage(); return;
            }

            string inputFile = args[0];
            if (!File.Exists(inputFile))
            {
                usage(inputFile); return;
            }

            Dictionary<string, List<string>> result = 
             findAnagram(inputFile);

            printResult(result);
        }

        static void usage()
        {
            Console.WriteLine("usage:\t{0}  file:[words.txt]",
                System.AppDomain.CurrentDomain.FriendlyName);
        }

        static void usage(string inputFile)
        {
            Console.WriteLine("File {0} not found", inputFile);
        }

        static void printResult(Dictionary<string, List<string>> result)
        {
            if (result.Keys.Count != 0)
            {
                List<string> words = result["longest"];
                Console.Write("\nlongest [");
                for (int i = 0; i != words.Count; ++i)
                {
                    Console.Write("{0}", words[i]);
                    if (i != words.Count - 1) Console.Write(",");
                }
                Console.Write("]");

                words = result["most"];
                Console.Write("\nmost [");
                for (int i = 0; i != words.Count; ++i)
                {
                    Console.Write("{0}", words[i]);
                    if (i != words.Count - 1) Console.Write(",");
                }
                Console.Write("]\n");

            }
        }

        static Dictionary<string, List<string>> findAnagram( string 
        inputFile)
        {

            bool isKeyExist;
            List<string> anagrams;
            string input, word, lexicalOrderedWord;
            int anagramWordLength, anagramOccuranceCount;
            int longestAnagram = 0, mostOccuredAnagramCount = 0, 
                linecount = 0;
            string keyOfLongestAnagram = "", keyOfMostOccurredAnagram = "";


            Dictionary<string, List<string>> result = 
             new Dictionary<string, List<string>>();
            Dictionary<string, List<string>> lexicalOrderRefMap = 
             new Dictionary<string, List<string>>();

            StreamReader inputStream = new StreamReader(inputFile);
            while (!inputStream.EndOfStream)
            {
                ++linecount;
                input = inputStream.ReadLine();
                if (input.Length == 0) continue;
                // skip empy lines
                else if (!input.All(c => char.IsLetter(c)))
                {   // non alphabetic characters found
                    Console.WriteLine(
                    "ERROR: non-Alphabet character on line {0}", linecount);
                    inputStream.Close();
                    return result;
                }

                word = input.ToLower();
                lexicalOrderedWord = String.Concat(word.OrderBy(c => c));

                // anagram will hold reference to list if key exists
                isKeyExist = lexicalOrderRefMap.TryGetValue( 
                  lexicalOrderedWord, out anagrams);

                if (!isKeyExist)
                { // creates key and list entry, when key does not exist
                    lexicalOrderRefMap.Add(
                      lexicalOrderedWord, new List<string>() { word });
                    continue;
                }

                anagrams.Add(word);

                if (anagrams.Count > 1)
                {
                    anagramWordLength = 
                     (lexicalOrderRefMap[lexicalOrderedWord])[0].Length;
                    if (anagramWordLength > longestAnagram)
                    { // longest anagrams
                        longestAnagram = anagramWordLength;
                        keyOfLongestAnagram = lexicalOrderedWord;

                    }

                    anagramOccuranceCount = 
                     (lexicalOrderRefMap[lexicalOrderedWord]).Count;
                    if (anagramOccuranceCount > mostOccuredAnagramCount)
                    {// most occurred anagram word
                        mostOccuredAnagramCount = anagramOccuranceCount;
                        keyOfMostOccurredAnagram = lexicalOrderedWord;
                    }

                }

            }

            inputStream.Close();
            result.Add("most",lexicalOrderRefMap[keyOfMostOccurredAnagram]);
            result.Add("longest", lexicalOrderRefMap[keyOfLongestAnagram]);
            return result;
        }
    }
}
