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
        public static string LicenseText()
        {
            return @"
    Copyright 2021 <a href=""https://www.inmechasol.org/"" target=""_blank"">InMechaSol, Inc</a>    

    Licensed under the Apache License, Version 2.0(the ""License"");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an ""AS IS"" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.";
        }
        public static void FixFileBriefNLicense(string fstring)
        {
            bool fileNeedsNewHeaderText = true;
            string ftypeText = "HowUnlikelyWouldItBe@if thisEx@ctTextWasN8";
            if (Path.GetExtension(fstring) == ".h")
            {
                if (Path.GetFileName(fstring).Contains("Platform_"))
                    ftypeText = "Platform Specification, " + Path.GetFileNameWithoutExtension(fstring).Replace("Platform_", "");
                else
                    ftypeText = "Declarations for straight C and C++";
            }
            else if (Path.GetExtension(fstring) == ".cpp" || Path.GetExtension(fstring) == ".ino")
            {
                ftypeText = "Implementation for C++ wrappers";
            }
            else if (Path.GetExtension(fstring) == ".c")
            {
                ftypeText = "Implementation for straight C";
            }
            else
                return;


            Console.WriteLine("Processing: " + fstring);
            string fileText = File.ReadAllText(fstring);


            if (fileText.StartsWith("/** \\file " + Path.GetFileName(fstring)))
            { 
                if(fileText.Contains("\n*   \\brief <a href=\"https://www.inmechasol.org/\" target=\"_blank\">IMS</a>:\r\n\t\t<a href=\"https://github.com/InMechaSol/ccNOos\" target=\"_blank\">ccNOos</a>,\r\n\t\t"))
                { 
                    if(fileText.Contains(ftypeText))
                    { 
                        if(fileText.Contains("\r\n\r\nNotes:"))
                        { 
                            if ( fileText.Contains("(.c includes .h) - for straight C") && fileText.Contains("(.cpp includes .c which includes .h) - for C++ wrapped straight C") && fileText.Contains("Always compiled to a single compilation unit, either C or CPP, not both"))
                            {
                                if (fileText.Contains(@"Copyright 2021 <a href=""https://www.inmechasol.org/"" target=""_blank"">InMechaSol, Inc</a>"))
                                {
                                    if (fileText.Contains("Licensed under the Apache License, Version 2.0(the \"License\");") && fileText.Contains("you may not use this file except in compliance with the License.") && fileText.Contains("You may obtain a copy of the License at"))
                                    {
                                        if (fileText.Contains("http://www.apache.org/licenses/LICENSE-2.0"))
                                        {
                                            if (fileText.Contains("Unless required by applicable law or agreed to in writing, software") &&
                                                fileText.Contains("distributed under the License is distributed on an \"AS IS\" BASIS,") &&
                                                fileText.Contains("WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.") &&
                                                fileText.Contains("See the License for the specific language governing permissions and") &&
                                                fileText.Contains("limitations under the License.")
                                                )
                                            {
                                                fileNeedsNewHeaderText = false;
            }   }   }   }   }   }   }   }   }

            if(fileNeedsNewHeaderText)
            {
                int j = fileText.IndexOf("\n#");
                int k = fileText.IndexOf("\n/*");
                int i = fileText.IndexOf("*/");
                int h = 0;
                if (j > -1)// first compiler statement (#ifndef, #include, ... ) 
                {
                    if (k>-1)// opened comment
                    {
                        if(i>k&&i<j)// closed comment before first compiler statement
                        {
                            h = j - 1; // clear from compiler statement to top of file
                        }
                    } 
                    else// never opened comment
                    {
                        h = j - 1; // clear from compiler statement to top of file
                    }
                }
                fileText = fileText.Substring(h);
                fileText = fileText.Substring(fileText.IndexOf("\n#"));
                fileText = "/** \\file " + Path.GetFileName(fstring) + "\r\n*   \\brief <a href=\"https://www.inmechasol.org/\" target=\"_blank\">IMS</a>:\r\n\t\t<a href=\"https://github.com/InMechaSol/ccNOos\" target=\"_blank\">ccNOos</a>,\r\n\t\t" + ftypeText + " \r\n" + LicenseText() + "\r\n\r\nNotes:\r\n\t(.c includes .h) - for straight C or\r\n\t(.cpp includes .c which includes .h) - for C++ wrapped straight C\r\n\t*Always compiled to a single compilation unit, either C or CPP, not both\r\n\r\n*/\r\n" + fileText;

                File.WriteAllText(fstring, fileText);
               
            }
        }

        // this is called for each directory in the ccNOos directory
        public static void CopyModifyDirectoryRecursively(string target_dir, string dirstring)
        {
            // process each file
            foreach (string fstring in Directory.GetFiles(target_dir))
            {
                // fstring - path to source file
                FixFileBriefNLicense(fstring);
                // filestring - path to destination file
                string filestring = dirstring + "\\" + fstring.Substring(fstring.LastIndexOf("\\") + 1);
                
                if (Path.GetExtension(fstring).Equals(".c"))
                {                    
                    
                    // copy and change extension to hpp
                    File.Copy(fstring, filestring.Replace(".c", ".hpp"));
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
                    File.WriteAllText(filestring, ftext);
                    //}

                }
                else if (Path.GetExtension(fstring).Equals(".h") || Path.GetExtension(fstring).Equals(".ino"))
                {
                    if (!fstring.Contains("Platform"))
                        File.Copy(fstring, filestring);
                    else if (fstring.Contains("Arduino"))
                        File.Copy(fstring, filestring);
                    else if (fstring.Contains("PlatformApp_Serialization"))
                        File.Copy(fstring, filestring);

                }
            }

            // recursively process each sub-directory
            foreach (string subDir in Directory.GetDirectories(target_dir))
            {
                if (!subDir.Contains("tests\\testApps") && !subDir.Contains("tests\\testMainFiles"))
                    CopyModifyDirectoryRecursively(subDir, dirstring);
                else if (subDir.Contains("tests\\testApps"))
                {
                    if (subDir.Contains("apiModules") || subDir.Contains("deviceModules"))
                    {
                        CopyModifyDirectoryRecursively(subDir, dirstring);
                    }
                    else
                    {
                        string tempDirstring = subDir + "\\" + dirstring.Substring(dirstring.LastIndexOf("\\") + 1);
                        CopyModifyDirectoryRecursively(tempDirstring, dirstring);
                    }

                }
                else if (subDir.Contains("tests\\testMainFiles"))
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
