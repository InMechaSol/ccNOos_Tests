using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Text.RegularExpressions;

namespace GenerateArduinoLib
{
    class Program
    {
        static void Main(string[] args)
        {
            // Program expects ccNOosTest Directory as an input
            if (args.Length == 1)
            {
                string ccNOosTestsDIR = args[0];
                if (Directory.Exists(ccNOosTestsDIR))
                {
                    string ccNOosDIR = ccNOosTestsDIR + "\\ccNOos";
                    if (!Directory.Exists(ccNOosDIR))
                    {
                        Console.WriteLine("FAILURE:( " + ccNOosDIR + " does not exist!");
                        return;
                    }


                    string ArduinoDIR = ccNOosTestsDIR + "\\Arduino\\libraries\\ccNOos\\src";
                    if (!Directory.Exists(ArduinoDIR))
                    {
                        Directory.CreateDirectory(ArduinoDIR);
                    }

                    // loop through all like named directories, 
                    // loop through all files, 
                    // delete from "arduino", 
                    // copy and modify from "ccNOos" 
                    foreach (string dstring in Directory.GetDirectories(ArduinoDIR))
                    {
                        foreach (string fstring in Directory.GetFiles(dstring))
                        {
                            File.Delete(fstring);
                        }
                        Directory.Delete(dstring);
                    }
                    foreach (string dstring in Directory.GetDirectories(ccNOosDIR))
                    {
                        string[] tokens = dstring.Split('\\');
                        string dirstring = ArduinoDIR + "\\" + tokens[tokens.Length - 1];
                        Directory.CreateDirectory(dirstring);

                        foreach (string fstring in Directory.GetFiles(dstring))
                        {
                            string[] ftokens = fstring.Split('\\');

                            string filestring = dirstring + "\\" + ((ftokens[ftokens.Length - 1]).Split('.'))[0];

                            if (Path.GetExtension(fstring).Equals(".c"))
                            {
                                // copy and change extension to hpp
                                File.Copy(fstring, filestring + ".hpp");
                            }
                            else if (Path.GetExtension(fstring).Equals(".cpp"))
                            {
                                // copy and modify #include line within
                                string ftext = File.ReadAllText(fstring);

                                Regex rx = new Regex(@"#include .*\.([c])");
                                MatchCollection matches = rx.Matches(ftext);
                                foreach (Match m in matches)
                                {
                                    string[] toks = m.Value.Split('.');
                                    ftext = rx.Replace(ftext, toks[0] + ".hpp");
                                }
                                File.WriteAllText(filestring + ".cpp", ftext);
                            }
                            else
                            {
                                // copy, should be h files,  maybe others
                                File.Copy(fstring, filestring + Path.GetExtension(fstring));
                            }
                        }

                    }
                    Console.WriteLine("SUCCESS!");
                }
                else
                {
                    Console.WriteLine("FAILURE:( " + ccNOosTestsDIR + " does not exist!");
                    return;
                }
            }
            else
            {
                Console.WriteLine("FAILURE:( ccNOos Directory was not entered as input to program!");
                return;
            }

            
        }
    }
}
