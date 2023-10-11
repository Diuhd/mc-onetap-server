#include <iostream>
#include <cstdlib>
#include <filesystem>
#include <windows.h>
#include <fstream>

int main() {
  std::string runtimepath = "C:\\mcserver\\RUNNINGCOUNT.txt";
  std::string download = "https://api.papermc.io/v2/projects/paper/versions/1.20.2/builds/233/downloads/paper-1.20.2-233.jar";
  std::string path = "C:\\mcserver";
  if (std::filesystem::exists(path) && std::filesystem::is_directory(path)){
    std::cout << "Directory Exists" << std::endl;
  } else {
    std::cout << "Directory Doesnt Exist... making a new one." << std::endl;
    std::filesystem::create_directory(path);
    std::cout << "Directory Created Successfully!\n";
  }
  std::string file_name = "paper-1.20.2-233.jar";
  std::string curl_command = "curl -o \"" + path + "\\" + file_name + "\" \"" + download + "\"";
  std::string paperpath = "C:\\mcserver\\paper-1.20.2-233.jar";
  if (std::filesystem::exists(paperpath)) {
    std::cout << "Paper is already downloaded in the directory!\n";
    std::cout << "Skipping curl command...\n";
  } else {
    system(curl_command.c_str());
    std::cout << "Downloaded Paper Succesfully!\n";
  }
  std::string batpath = "C:\\mcserver\\start.bat";
  if (std::filesystem::exists(batpath)) {
    std::cout << "start.bat exists.\n";
  } else {
    std::cout << "Creating start.bat...\n";
    std::ofstream batchFile(batpath);
    if (batchFile.is_open()) {
      batchFile << "@echo off\n" << "cd /d %~dp0\n" <<"java -Xms2G -Xmx4G -jar " << file_name << " nogui\n" << "pause";
      batchFile.close();
    } else {
      std::cerr << "Error: Unable to create bat file.";
      exit(1);
    }
  }

  std::string eulapath = "C:\\mcserver\\eula.txt";
  if (std::filesystem::exists(eulapath)) {
    std::cout << "EULA.txt already exists.\n";
  } else {
    std::ofstream eula(eulapath);
    if (eula.is_open()) {
      eula << "eula = true";
    } else {
      std::cerr << "Unable to Contact/Create EULA.txt\n";
    }
  }

  std::string killscriptpath = "C:\\mcserver\\killscript.bat";
  if (std::filesystem::exists(killscriptpath)) {
    std::cout << "Task Kill Script On.\n";
  } else {
    std::ofstream killscript(killscriptpath);
    if (killscript.is_open()) {
        killscript << "@echo off\n"
                     "net session >nul 2>&1\n"
                     "if %%errorLevel%% == 0 (\n"
                     "    echo Script is running with admin privileges\n"
                     ") else (\n"
                     "    echo Script is not running with admin privileges\n"
                     "    echo Requesting admin privileges...\n"
                     "    powershell -command \"Start-Process cmd -ArgumentList '/K', 'taskkill /F /IM cmd.exe /T' -Verb RunAs\"\n"
                     ")\n";
    }
  }

  system("start cmd /k C:\\mcserver\\start.bat");
  std::string quit;
  std::cin >> quit;
  if (quit == "quit") {
    system("start cmd /k C:\\mcserver\\killscript.bat");
    exit(2);
  }

  return 0;
}