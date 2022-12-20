#pragma once
#include <string>
#include<list>
#include <thread>
#include <io.h>
#include "process.hpp"

using namespace TinyProcessLib;

bool file_exists(const std::string& name) {
    return (_access(name.c_str(), 0) != -1);
}

std::string find_browser_on_linux() {
    auto pathList = {
        "/usr/bin/google-chrome",
        "/usr/bin/microsoft-edge-stable",
        "/usr/bin/microsoft-edge",
        "/usr/bin/brave-browser"
    };

    for (auto it = pathList.begin(); it != pathList.end(); ++it) {
        if (file_exists(*it)) {
            return *it;
        }
    }
    return "";
}

std::string find_browser_on_mac() {
    auto pathList = {
       "/Applications/Google Chrome.app/Contents/MacOS/Google Chrome",
        "/Applications/Brave Browser.app/Contents/MacOS/Brave Browser",
        "/Applications/Microsoft Edge.app/Contents/MacOS/Microsoft Edge"
    };

    for (auto it = pathList.begin(); it != pathList.end(); ++it) {
        if (file_exists(*it)) {
            return *it;
        }
    }
    return "";
}

std::string find_browser_on_win() {
    auto pathList = {
       "C:/Program Files (x86)/Microsoft/Edge/Application/msedge.exe",
        "C:/Program Files/Microsoft/Edge/Application/msedge.exe",
        "C:/Program Files/Google/Chrome/Application/chrome.exe",
        "C:/Program Files/BraveSoftware/Brave-Browser/Application/brave.exe"
    };

    for(auto it  = pathList.begin();it != pathList.end(); ++ it){
        if (file_exists(*it)) {
            return *it;
        }
    }
    return "";
}

std::string find_browser() {
#ifdef _WIN32
    return    find_browser_on_win();
#elif __linux__
    return find_browser_on_linux();
#elif __APPLE__
    return find_browser_on_mac();
#endif
    return "";
}


std::string find_tmp_dir_linux() {
    auto pathList = {
        "/tmp", "/var/tmp", "/usr/tmp"
    };

    for (auto it = pathList.begin(); it != pathList.end(); ++it) {
        if (file_exists(*it)) {
            return *it;
        }
    }
    return "";
}

std::string find_tmp_dir_win() {
    std::string strUserProfile = getenv("USERPROFILE") + std::string("\\AppData\\Local\\Temp");
    std::string strRoot = getenv("SYSTEMROOT") +std::string( "\\Temp");
    std::list<std::string> pathList = {
strUserProfile,
strRoot,
 "c:/temp",
 "c:/tmp", 
 "/temp",
 "/tmp"
    };

    for (auto it = pathList.begin(); it != pathList.end(); ++it) {
        if (file_exists(*it)) {
            return *it;
        }
    }
    return "";
}

std::string find_tmp_dir() {
#ifdef _WIN32
    return find_tmp_dir_win();
#else
    return find_tmp_dir_linux();
#endif
    return "";
}


class webGui{
private:
    short m_port = 0;
    int      m_width = 0;
    int     m_height = 0;
    std::string m_browser_path = "";
    std::string m_browser_commond = "";
    std::string m_profile_dir = "";
    std::string m_url = "";

private:
    void post_init() {    
        m_profile_dir = find_tmp_dir() + "/webgui";
        m_url = "http://127.0.0.1:" + std::to_string(m_port);
        m_browser_path = find_browser();
        m_browser_commond = get_browser_command();
    }

    std::string get_browser_command() {
        std::string command = m_browser_path +  " --user-data-dir=" + m_profile_dir + "  --new-window  --no-first-run";

        if (m_width > 0 && m_height > 0) {
            command += "  --window-size=" + std::to_string(m_width) + "," + std::to_string(m_height);
        }
        else {
            command += "  --start-maximized";
        }
        command += " --app=" + m_url;

        printf("%s \n",command.c_str());
        return command;
    }
public:
    webGui(int width, int height, short port) : m_width(width), m_height(height), m_port(port) {
        post_init();
    }
    webGui(short port) :m_port(port) {
        post_init();
    }

    ~webGui() {}

public:

    static void start_browser(const std::string &strCommdLine) {
        // create browser process
        Process process1a(strCommdLine, "", [](const char* bytes, size_t n) {
           std::cout << "Output from stdout: " << std::string(bytes, n);
            });

        //wait the browser exit ,and exit the main process (exit -1).    and you can change a safed method
        auto exit_status = process1a.get_exit_status();
        std::cout << "Example 1a process returned: " << exit_status << " (" << (exit_status == 0 ? "success" : "failure") << ")" << std::endl;

        exit(-1);        
    }

    void run() {
        std::thread thr(start_browser, m_browser_commond);
        thr.detach();
    }
};