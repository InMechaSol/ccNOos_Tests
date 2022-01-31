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
        public static void DeleteFilesAndFoldersRecursively(string target_dir)
        {
            foreach (string file in Directory.GetFiles(target_dir))
            {
                File.Delete(file);
            }

            foreach (string subDir in Directory.GetDirectories(target_dir))
            {
                DeleteFilesAndFoldersRecursively(subDir);
            }

            System.Threading.Thread.Sleep(1); // This makes the difference between whether it works or not. Sleep(0) is not enough.
            Directory.Delete(target_dir);
        }

        // this is called for each directory in the ccNOos directory
        public static void CopyModifyDirectoryRecursively(string target_dir, string dirstring, string odstring)
        {
            // process each file
            foreach (string fstring in Directory.GetFiles(target_dir))
            {
                // fstring - path to source file
                // filestring - path to destination file
                string filestring = fstring.Replace(odstring, dirstring);


                if(!Directory.Exists(Path.GetDirectoryName(filestring)))
                {
                    Directory.CreateDirectory(Path.GetDirectoryName(filestring));
                }
                
                if (Path.GetExtension(fstring).Equals(".c"))
                {
                    if(fstring.Contains("ccLibs"))
                        // copy 
                        File.Copy(fstring, filestring);
                    else if (!fstring.Contains("Application_Platform_Main"))
                        // copy and change extension to hpp
                        File.Copy(fstring, filestring.Replace(".c",".hpp"));
                }
                else if (Path.GetExtension(fstring).Equals(".cpp"))
                {
                    if(fstring.Contains("Application_Platform_Main"))
                    {
                        // copy change name and extension
                        // copy and modify #include line within
                        string dcname = Path.GetDirectoryName(fstring);
                        dcname = dcname.Substring(dcname.LastIndexOf("\\") + 1);

                        string fctext = File.ReadAllText(fstring.Replace(".cpp",".c"));
                        fctext = fctext.Replace("#include \"..\\testApps\\" + dcname + "\\PlatformApp_Serialization.h\"", "#include \"PlatformApp_Serialization.hpp\"");

                        string ftext = File.ReadAllText(fstring);
                        ftext = ftext.Replace("#include \"Application_Platform_Main.c\"", "");
                        
                        string inostring = Path.GetFileName(filestring.Replace("Application_Platform_Main", dcname).Replace(".cpp", ".ino"));
                        inostring = odstring + "\\..\\Arduino\\"+ dcname + "\\" + inostring;
                        inostring = Path.GetFullPath(inostring);
                        File.WriteAllText(inostring, fctext+ftext);
                    }
                    else if(fstring.Contains("Application_Solution"))
                    {
                        // copy change name and extension
                        // copy and modify #include line within
                        string dcname = Path.GetDirectoryName(fstring);
                        dcname = dcname.Substring(dcname.LastIndexOf("\\") + 1);

                        string fctext = File.ReadAllText(fstring.Replace(".cpp", ".c"));
                        fctext = fctext.Replace("Application_Solution.h\"", "Application_Solution.hpp\"");                        

                        string ftext = File.ReadAllText(fstring);
                        ftext = ftext.Replace("#include \"Application_Solution.c\"", "");
                        string inostring = Path.GetFileName(filestring);
                        inostring = odstring + "\\..\\Arduino\\" + dcname + "\\" + inostring;
                        inostring = Path.GetFullPath(inostring);
                        File.WriteAllText(inostring, fctext + ftext);
                    }
                    else if (fstring.Contains("PlatformApp_Serialization"))
                    {
                        // copy change name and extension
                        // copy and modify #include line within
                        string dcname = Path.GetDirectoryName(fstring);
                        dcname = dcname.Substring(dcname.LastIndexOf("\\") + 1);

                        string fctext = File.ReadAllText(fstring.Replace(".cpp", ".c"));
                        fctext = fctext.Replace("PlatformApp_Serialization.h\"", "PlatformApp_Serialization.hpp\"");

                        string ftext = File.ReadAllText(fstring);
                        ftext = ftext.Replace("#include \"PlatformApp_Serialization.c\"", "");
                        string inostring = Path.GetFileName(filestring);
                        inostring = odstring + "\\..\\Arduino\\" + dcname + "\\" + inostring;
                        inostring = Path.GetFullPath(inostring);
                        File.WriteAllText(inostring, fctext + ftext);
                    }
                    else
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
                        File.WriteAllText(filestring, ftext);
                    }
                    
                }
                else
                {
                    string PlatformString = "";
                    // copy, should be h files,  maybe others
                    if (fstring.Contains("Platform") && fstring.Contains("Arduino"))
                    {
                        PlatformString = fstring;
                        string filestring1 = filestring.Replace("\\tests\\testPlatforms", "");
                        if (File.Exists(filestring1))
                            File.Delete(filestring1);
                        File.Copy(fstring, filestring1);
                    }
                    else if (fstring.Contains("Application_Solution") || fstring.Contains("PlatformApp_Serialization"))
                    {
                        // copy change name and extension
                        string dcname = Path.GetDirectoryName(fstring);
                        dcname = dcname.Substring(dcname.LastIndexOf("\\") + 1);

                        string ftext = File.ReadAllText(fstring);
                        ftext = ftext.Replace("Application_Solution.h\"", "Application_Solution.hpp\"");
                        ftext = ftext.Replace("PlatformApp_Serialization.h\"", "PlatformApp_Serialization.hpp\"");

                        string inostring = Path.GetFileName(filestring);
                        inostring = odstring + "\\..\\Arduino\\" + dcname + "\\" + inostring;
                        inostring = Path.GetFullPath(inostring).Replace(".h",".hpp");
                        if (File.Exists(inostring))
                            File.Delete(inostring);
                        File.WriteAllText(inostring, ftext);
                    }
                    else
                        File.Copy(fstring, filestring.Replace(Path.GetExtension(filestring), Path.GetExtension(fstring)));

                }
            }

            // recursively process each sub-directory
            foreach (string subDir in Directory.GetDirectories(target_dir))
            {
                CopyModifyDirectoryRecursively(subDir, dirstring, odstring);
            }

        }

        static void Main(string[] args)
        {
            // Program expects ccNOosTest Directory as an input
            if (args.Length == 2)
            {
                string ccNOosTestsDIR = Path.GetFullPath(args[0]);
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
                    else
                    {
                        // loop through all like named directories, 
                        // loop through all files, 
                        // delete from "arduino", 
                        // copy and modify from "ccNOos" 
                        foreach (string dstring in Directory.GetDirectories(ArduinoDIR))
                        {
                            DeleteFilesAndFoldersRecursively(dstring);
                        }
                    }

                    

                    foreach (string dstring in Directory.GetDirectories(ccNOosDIR))
                    {
                        CopyModifyDirectoryRecursively(dstring, ArduinoDIR, ccNOosDIR);

                    }
                    Console.WriteLine("Arduino Lib Source Generated!");
                }
                else
                {
                    Console.WriteLine("FAILURE:( " + ccNOosTestsDIR + " does not exist!");
                    return;
                }

                string objDIR = Path.GetFullPath(args[1]);
                bool notOnce = true;
                if (Directory.Exists(objDIR))
                {
                    foreach(string filenamestring in Directory.GetFiles(objDIR))
                    {
                        if(filenamestring.EndsWith(".i"))
                        {
                            Console.Write($"Processing {filenamestring} ...");
                            notOnce = false;
                            char[] seps = { '\n', '\r' };
                            string [] lines = File.ReadAllText(filenamestring).Split(seps, StringSplitOptions.RemoveEmptyEntries);
                            string outText = "";
                            foreach(string lString in lines)
                            {
                                if (!String.IsNullOrWhiteSpace(lString))
                                    outText += lString + "\n";
                            }
                            Console.Write("Saving ...");
                            File.WriteAllText(filenamestring.Replace(".i",".cpp"),outText);
                            Console.Write("Done!\n");
                        }
                    }

                    if (notOnce)
                        Console.WriteLine("No .i Files to Process this Time.");
                    else
                        Console.WriteLine("Pre-Processed Files Cleaned and Saved for Flat Console Test!");
                    return;

                }
                else
                {
                    Console.WriteLine("FAILURE:( " + objDIR + " does not exist!");
                    return;
                }
            }
            else
            {
                Console.WriteLine("FAILURE:( Correct Directories were not entered as program inputs!");
                return;
            }

            
        }
    }
    
}
