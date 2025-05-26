#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <conio.h>

#define MAX_HISTORY 50

std::vector<std::string> history;
int historyIndex = -1;

void cls()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordScreen = {0, 0};
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;

    GetConsoleScreenBufferInfo(hConsole, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter(hConsole, ' ', dwConSize, coordScreen, &cCharsWritten);
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
    SetConsoleCursorPosition(hConsole, coordScreen);
}

void help()
{
    std::cout << "\n=== MiniShell - ReactOS & Windows XP Compatible Shell ===\n\n";
    std::cout << "Built-in Commands:\n";
    std::cout << "  help      - Show this help message\n";
    std::cout << "  cls       - Clear screen\n";
    std::cout << "  exit      - Exit shell\n";
    std::cout << "  ver       - Show shell version\n";
    std::cout << "  echo      - Echo text\n";
    std::cout << "  cd        - Change directory\n";
    std::cout << "  dir       - List directory contents\n";
    std::cout << "  ls        - List files (alternative to dir)\n";
    std::cout << "  md/mkdir  - Create directory\n";
    std::cout << "  rd/rmdir  - Remove directory\n";
    std::cout << "  touch     - Create a text file\n";
    std::cout << "  cat       - Display file contents\n";
    std::cout << "  copy      - Copy file\n";
    std::cout << "  del       - Delete file\n";
    std::cout << "  ren       - Rename file\n";
    std::cout << "  sort      - Sort contents of a text file\n";
    std::cout << "  find      - Search for text in files\n";
    std::cout << "  type      - Display file contents\n";
    std::cout << "  date      - Show current date/time\n";
    std::cout << "  history   - Show command history\n";
    std::cout << "  [any]     - Run external program\n\n";
    std::cout << "Use <command> /? for detailed help on specific commands\n";
}

void ver()
{
    std::cout << "MiniShell version 1.2 (ReactOS & Windows XP Compatible)\n";
    std::cout << "Built with Win32 API for maximum compatibility\n";
    std::cout << "Copyright (c) 2025\n";
}

void echo(const std::string &text)
{
    std::cout << text << "\n";
}

void cd(const std::string &path)
{
    if (!SetCurrentDirectoryA(path.c_str()))
    {
        std::cerr << "Error: Could not change directory.\n";
    }
}

void dir()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // Save current attributes
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    // Set bright white color for directory listing
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    system("dir");

    // Restore original attributes
    SetConsoleTextAttribute(hConsole, csbi.wAttributes);
}

void touch(const std::string &filename)
{
    std::ofstream file(filename.c_str());
    if (file)
    {
        std::cout << "Created: " << filename << "\n";
    }
    else
    {
        std::cerr << "Failed to create file.\n";
    }
}

void sort_file(const std::string &filename)
{
    std::ifstream file(filename.c_str());
    if (!file)
    {
        std::cerr << "Could not open file.\n";
        return;
    }
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line))
    {
        lines.push_back(line);
    }
    file.close();
    std::sort(lines.begin(), lines.end());
    std::ofstream out(filename.c_str());
    for (const auto &l : lines)
    {
        out << l << "\n";
    }
    std::cout << "Sorted: " << filename << "\n";
}

void show_history()
{
    for (size_t i = 0; i < history.size(); ++i)
    {
        std::cout << i + 1 << ": " << history[i] << "\n";
    }
}

void run_external(const std::string &command, const std::vector<std::string> &args)
{
    std::string full_cmd = command;
    for (const auto &arg : args)
    {
        full_cmd += " " + arg;
    }

    STARTUPINFOA si = {sizeof(si)};
    PROCESS_INFORMATION pi;

    if (CreateProcessA(
            NULL,
            const_cast<char *>(full_cmd.c_str()),
            NULL,
            NULL,
            FALSE,
            0,
            NULL,
            NULL,
            &si,
            &pi))
    {
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    else
    {
        std::cerr << "Failed to start process.\n";
    }
}

std::vector<std::string> split(const std::string &input)
{
    std::istringstream iss(input);
    std::vector<std::string> tokens;
    std::string token;
    while (iss >> token)
        tokens.push_back(token);
    return tokens;
}

std::string join(const std::vector<std::string> &tokens, const std::string &sep = " ")
{
    std::ostringstream oss;
    for (size_t i = 0; i < tokens.size(); ++i)
    {
        oss << tokens[i];
        if (i != tokens.size() - 1)
            oss << sep;
    }
    return oss.str();
}

std::string read_input()
{
    std::string buffer;
    int ch;
    while ((ch = _getch()) != 13)
    { // Enter
        if (ch == 8)
        { // Backspace
            if (!buffer.empty())
            {
                buffer.pop_back();
                std::cout << "\b \b";
            }
        }
        else if (ch == 224)
        { // Special key (arrows)
            ch = _getch();
            if (ch == 72 && !history.empty())
            { // Up arrow
                historyIndex = (historyIndex <= 0) ? (int)history.size() - 1 : historyIndex - 1;
                std::cout << "\r                                                                 \r";
                std::cout << "> " << history[historyIndex];
                buffer = history[historyIndex];
            }
        }
        else
        {
            buffer += (char)ch;
            std::cout << (char)ch;
        }
    }
    std::cout << "\n";
    return buffer;
}

void ls()
{
    dir();
}

void make_directory(const std::string &path)
{
    if (!CreateDirectoryA(path.c_str(), NULL))
    {
        DWORD error = GetLastError();
        if (error == ERROR_ALREADY_EXISTS)
        {
            std::cerr << "Directory already exists.\n";
        }
        else
        {
            std::cerr << "Failed to create directory.\n";
        }
    }
    else
    {
        std::cout << "Directory created successfully.\n";
    }
}

void remove_directory(const std::string &path)
{
    if (!RemoveDirectoryA(path.c_str()))
    {
        std::cerr << "Failed to remove directory.\n";
    }
    else
    {
        std::cout << "Directory removed successfully.\n";
    }
}

void cat(const std::string &filename)
{
    std::ifstream file(filename.c_str());
    if (!file)
    {
        std::cerr << "Could not open file.\n";
        return;
    }
    std::string line;
    while (std::getline(file, line))
    {
        std::cout << line << "\n";
    }
}

void copy_file(const std::string &source, const std::string &dest)
{
    if (!CopyFileA(source.c_str(), dest.c_str(), TRUE))
    {
        std::cerr << "Failed to copy file.\n";
    }
    else
    {
        std::cout << "File copied successfully.\n";
    }
}

void delete_file(const std::string &filename)
{
    if (!DeleteFileA(filename.c_str()))
    {
        std::cerr << "Failed to delete file.\n";
    }
    else
    {
        std::cout << "File deleted successfully.\n";
    }
}

void rename_file(const std::string &oldname, const std::string &newname)
{
    if (!MoveFileA(oldname.c_str(), newname.c_str()))
    {
        std::cerr << "Failed to rename file.\n";
    }
    else
    {
        std::cout << "File renamed successfully.\n";
    }
}

void find_in_file(const std::string &filename, const std::string &text)
{
    std::ifstream file(filename.c_str());
    if (!file)
    {
        std::cerr << "Could not open file.\n";
        return;
    }
    std::string line;
    int line_number = 0;
    while (std::getline(file, line))
    {
        line_number++;
        if (line.find(text) != std::string::npos)
        {
            std::cout << "Line " << line_number << ": " << line << "\n";
        }
    }
}

void show_date()
{
    SYSTEMTIME st;
    GetLocalTime(&st);
    char buffer[80];
    sprintf(buffer, "%02d/%02d/%04d %02d:%02d:%02d",
            st.wMonth, st.wDay, st.wYear,
            st.wHour, st.wMinute, st.wSecond);
    std::cout << buffer << "\n";
}

// Console configuration
void setup_console()
{
    // Get console handle
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);

    // Set console colors (black background, light gray text - classic CMD look)
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    // Set console window size and buffer size
    COORD bufferSize = {80, 300};
    SMALL_RECT windowSize = {0, 0, 79, 24}; // 80x25 window

    SetConsoleScreenBufferSize(hConsole, bufferSize);
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);

    // Set console mode
    DWORD mode;
    GetConsoleMode(hInput, &mode);
    SetConsoleMode(hInput, mode | ENABLE_PROCESSED_INPUT | ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT | ENABLE_MOUSE_INPUT);

    // Clear screen to apply colors
    cls();
}

void setup_window()
{
    // Get window handle
    HWND console = GetConsoleWindow();
    if (console != NULL)
    {
        // Set window style to include system menu, minimize and maximize buttons
        LONG style = GetWindowLong(console, GWL_STYLE);
        style |= WS_OVERLAPPEDWINDOW;
        SetWindowLong(console, GWL_STYLE, style);

        // Set window position and size
        RECT r;
        GetWindowRect(console, &r);
        MoveWindow(console, r.left, r.top, 800, 600, TRUE);
    }
}

int main()
{
    SetConsoleTitleA("MiniShell for ReactOS");
    setup_console();
    setup_window();
    std::string input;
    char cwd[MAX_PATH];

    while (true)
    {
        GetCurrentDirectoryA(MAX_PATH, cwd);
        std::cout << cwd << " > ";
        input = read_input();

        if (input.empty())
            continue;

        if (history.empty() || input != history.back())
        {
            history.push_back(input);
            if (history.size() > MAX_HISTORY)
                history.erase(history.begin());
        }
        historyIndex = -1;

        auto tokens = split(input);
        std::string command = tokens[0];
        tokens.erase(tokens.begin());
        if (tokens.size() == 1 && tokens[0] == "/?")
        {
            help();
            continue;
        }

        if (command == "exit")
            break;
        else if (command == "cls")
            cls();
        else if (command == "help")
            help();
        else if (command == "ver")
            ver();
        else if (command == "echo")
            echo(join(tokens));
        else if (command == "cd" && !tokens.empty())
            cd(tokens[0]);
        else if (command == "dir" || command == "ls")
            dir();
        else if ((command == "md" || command == "mkdir") && !tokens.empty())
            make_directory(tokens[0]);
        else if ((command == "rd" || command == "rmdir") && !tokens.empty())
            remove_directory(tokens[0]);
        else if (command == "touch" && !tokens.empty())
            touch(tokens[0]);
        else if (command == "cat" && !tokens.empty())
            cat(tokens[0]);
        else if (command == "type" && !tokens.empty())
            cat(tokens[0]);
        else if (command == "copy" && tokens.size() >= 2)
            copy_file(tokens[0], tokens[1]);
        else if (command == "del" && !tokens.empty())
            delete_file(tokens[0]);
        else if (command == "ren" && tokens.size() >= 2)
            rename_file(tokens[0], tokens[1]);
        else if (command == "sort" && !tokens.empty())
            sort_file(tokens[0]);
        else if (command == "find" && tokens.size() >= 2)
            find_in_file(tokens[0], tokens[1]);
        else if (command == "date")
            show_date();
        else if (command == "history")
            show_history();
        else
            run_external(command, tokens);
    }

    return 0;
}
