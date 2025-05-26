# MiniShell - A Lightweight Command-Line Interface

MiniShell is a lightweight, feature-rich command-line interface built with C++ and Win32 API. It provides essential command-line functionality with a classic terminal appearance and modern usability features.

## Features

- 📁 File Management Commands

  - `dir/ls` - List directory contents
  - `cd` - Change directory
  - `md/mkdir` - Create directory
  - `rd/rmdir` - Remove directory
  - `copy` - Copy files
  - `del` - Delete files
  - `ren` - Rename files
  - `touch` - Create empty files

- 📝 File Operations

  - `cat/type` - Display file contents
  - `sort` - Sort file contents
  - `find` - Search text in files

- 🔧 System Commands

  - `cls` - Clear screen
  - `date` - Show date and time
  - `ver` - Show version info
  - `echo` - Display messages
  - `history` - Show command history

- 🎨 User Interface Features
  - Classic command prompt appearance
  - Command history with up/down arrow navigation
  - Proper console window sizing
  - Support for external commands

## Installation

### Pre-built Binary

1. Download the latest `minishell.exe` from the releases section
2. Add to PATH (Optional, for system-wide access):
   - Open System Properties (Win + Break)
   - Click "Advanced system settings"
   - Click "Environment Variables"
   - Under "System variables", select "Path"
   - Click "Edit" and "New"
   - Add the folder path containing minishell.exe
   - Click "OK" on all windows

### Building from Source

#### Prerequisites

- CMake (3.10 or higher)
- MinGW-w64 or Visual Studio with C++ support
- Git (optional)

#### Build Steps

1. Clone or download the repository:

   ```powershell
   git clone <https://github.com/Shailesh-Singh-Bisht/Custom-CMD-Shell>
   cd MyShell
   ```

2. Create and enter build directory:

   ```powershell
   mkdir build
   cd build
   ```

3. Generate build files with CMake:

   ```powershell
   # For MinGW
   cmake .. -G "MinGW Makefiles"

   # For Visual Studio
   cmake .. -G "Visual Studio 17 2022" -A Win32
   ```

4. Build the project:

   ```powershell
   # For MinGW
   mingw32-make

   # For Visual Studio
   cmake --build . --config Release
   ```

The executable will be created in the `build/bin` directory.

## Usage

### Basic Commands

```bash
# Show help
help

# Change directory
cd path/to/directory

# List files
dir
ls

# Create directory
mkdir new_folder

# Copy file
copy source.txt destination.txt

# Find text in file
find filename.txt "search text"

# Show command history
history
```

### Command Line Options

- Use `/?` after any command to see its help message
- External commands can be run directly from the shell

## Development

### Project Structure

- `MyShell.cpp` - Main source file
- `resource.rc` - Resource file for application icon
- `CMakeLists.txt` - CMake build configuration
- `cmd_icon.ico` - Application icon

### Adding New Commands

1. Declare the command function in `MyShell.cpp`
2. Implement the function using Win32 API for compatibility
3. Add command handling in the main command loop
4. Update the help text

## Contributing

Contributions are welcome! Please feel free to submit pull requests.

1. Fork the repository
2. Create a feature branch
3. Commit your changes
4. Push to the branch
5. Create a Pull Request

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments

- Built with Win32 API for maximum compatibility
- Inspired by classic command-line interfaces
