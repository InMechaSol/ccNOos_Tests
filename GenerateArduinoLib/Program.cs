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
        public static void CopyModifyDirectoryRecursively(string target_dir, string dirstring)
        {
            // process each file
            foreach (string fstring in Directory.GetFiles(target_dir))
            {
                // fstring - path to source file
                // filestring - path to destination file
                string filestring = dirstring + "\\" + fstring.Substring(fstring.LastIndexOf("\\")+1);
                
                if (Path.GetExtension(fstring).Equals(".c"))
                {
                    // copy and change extension to hpp
                    File.Copy(fstring, filestring.Replace(".c", ".hpp"));
                }
                else if (Path.GetExtension(fstring).Equals(".cpp"))
                {
                    //if(fstring.Contains("Application_Solution"))
                    //{
                    //    // copy change name and extension
                    //    // copy and modify #include line within
                    //    string dcname = Path.GetDirectoryName(fstring);
                    //    dcname = dcname.Substring(dcname.LastIndexOf("\\") + 1);

                    //    string fctext = File.ReadAllText(fstring.Replace(".cpp", ".c"));
                    //    fctext = fctext.Replace("Application_Solution.h\"", "Application_Solution.hpp\"");                        

                    //    string ftext = File.ReadAllText(fstring);
                    //    ftext = ftext.Replace("#include \"Application_Solution.c\"", "");
                    //    string inostring = Path.GetFileName(filestring);
                    //    //inostring = odstring + "\\..\\Arduino\\" + dcname + "\\" + inostring;
                    //    inostring = Path.GetFullPath(inostring);
                    //    File.WriteAllText(filestring, fctext + ftext);
                    //}
                    //else if (fstring.Contains("PlatformApp_Serialization"))
                    //{
                    //    // copy change name and extension
                    //    // copy and modify #include line within
                    //    string dcname = Path.GetDirectoryName(fstring);
                    //    dcname = dcname.Substring(dcname.LastIndexOf("\\") + 1);

                    //    string fctext = File.ReadAllText(fstring.Replace(".cpp", ".c"));
                    //    fctext = fctext.Replace("PlatformApp_Serialization.h\"", "PlatformApp_Serialization.hpp\"");

                    //    string ftext = File.ReadAllText(fstring);
                    //    ftext = ftext.Replace("#include \"PlatformApp_Serialization.c\"", "");
                    //    string inostring = Path.GetFileName(filestring);
                    //    //inostring = odstring + "\\..\\Arduino\\" + dcname + "\\" + inostring;
                    //    inostring = Path.GetFullPath(inostring);
                    //    File.WriteAllText(inostring, fctext + ftext);
                    //}
                    //else
                    //{
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
                    //}
                    
                }
                else if (Path.GetExtension(fstring).Equals(".h") || Path.GetExtension(fstring).Equals(".ino"))
                {
                    if(!fstring.Contains("Platform"))
                        File.Copy(fstring, filestring);
                    else if(fstring.Contains("Arduino"))
                        File.Copy(fstring, filestring);
                    else if (fstring.Contains("PlatformApp_Serialization"))
                        File.Copy(fstring, filestring);

                    //else if (fstring.Contains("Application_Solution") || fstring.Contains("PlatformApp_Serialization"))
                    //{
                    //    // copy change name and extension
                    //    string dcname = Path.GetDirectoryName(fstring);
                    //    dcname = dcname.Substring(dcname.LastIndexOf("\\") + 1);

                    //    string ftext = File.ReadAllText(fstring);
                    //    ftext = ftext.Replace("Application_Solution.h\"", "Application_Solution.hpp\"");
                    //    ftext = ftext.Replace("PlatformApp_Serialization.h\"", "PlatformApp_Serialization.hpp\"");

                    //    string inostring = Path.GetFileName(filestring);
                    //    //inostring = odstring + "\\..\\Arduino\\" + dcname + "\\" + inostring;
                    //    inostring = Path.GetFullPath(inostring).Replace(".h",".hpp");
                    //    if (File.Exists(inostring))
                    //        File.Delete(inostring);
                    //    File.WriteAllText(inostring, ftext);
                    //}
                    //else
                    //    File.Copy(fstring, filestring);

                }
            }

            // recursively process each sub-directory
            foreach (string subDir in Directory.GetDirectories(target_dir))
            {
                if(!subDir.Contains("tests\\testApps") && !subDir.Contains("tests\\testMainFiles"))
                    CopyModifyDirectoryRecursively(subDir, dirstring);
                else if(subDir.Contains("tests\\testApps"))
                {
                    string tempDirstring = subDir + "\\" + dirstring.Substring(dirstring.LastIndexOf("\\") + 1);
                    CopyModifyDirectoryRecursively(tempDirstring, dirstring);
                }
                else if(subDir.Contains("tests\\testMainFiles"))
                {
                    string tempDirstring = subDir + "\\" + dirstring.Substring(dirstring.LastIndexOf("\\") + 1) + "\\Arduino";
                    CopyModifyDirectoryRecursively(tempDirstring, dirstring);
                }
            }

        }

        static void Main(string[] args)
        {
            // Program expects ccNOosTest Directory as an input
            if (args.Length == 3)
            {

                string ccNOosTestAppDir = Path.GetFullPath(args[0]);
                if (!Directory.Exists(ccNOosTestAppDir))
                {
                    Console.WriteLine("FAILURE:( " + ccNOosTestAppDir + " does not exist!");
                    return;
                }


                string ccNOosTestsDIR = Path.GetFullPath(ccNOosTestAppDir+"\\..\\..\\..\\..\\");
                if (Directory.Exists(ccNOosTestsDIR))
                {
                    string ccNOosDIR = ccNOosTestsDIR + "ccNOos";
                    if (!Directory.Exists(ccNOosDIR))
                    {
                        Console.WriteLine("FAILURE:( " + ccNOosDIR + " does not exist!");
                        return;
                    }


                    //string ArduinoDIR = ccNOosTestsDIR + "Arduino\\" + ccNOosTestAppDir.Substring(ccNOosTestAppDir.LastIndexOf("\\")+1);
                    string ArduinoDIR = Path.GetFullPath(args[1]);
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
                        DeleteFilesAndFoldersRecursively(ArduinoDIR);
                        Directory.CreateDirectory(ArduinoDIR);
                    }

                    

                    foreach (string dstring in Directory.GetDirectories(ccNOosDIR))
                    {
                        CopyModifyDirectoryRecursively(dstring, ArduinoDIR);

                    }
                    Console.WriteLine("Arduino Source Generated!");
                }
                else
                {
                    Console.WriteLine("FAILURE:( " + ccNOosTestsDIR + " does not exist!");
                    return;
                }





                ////////////////////////////////////////////////////////
                //// this is for the FlatFiles project
                string objDIR = Path.GetFullPath(args[2]);
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
