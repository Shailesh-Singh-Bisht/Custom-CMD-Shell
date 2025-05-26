# MiniShell - A Lightweight Command-Line Interface
<!-- ALL-CONTRIBUTORS-BADGE:START - Do not remove or modify this section -->
[![All Contributors](https://img.shields.io/badge/all_contributors-4-orange.svg?style=flat-square)](#contributors-)
<!-- ALL-CONTRIBUTORS-BADGE:END -->

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

## Contributors ✨

Thanks goes to these wonderful people ([emoji key](https://allcontributors.org/docs/en/emoji-key)):

<!-- ALL-CONTRIBUTORS-LIST:START - Do not remove or modify this section -->
<!-- prettier-ignore-start -->
<!-- markdownlint-disable -->
<table>
  <tbody>
    <tr>
      <td align="center" valign="top" width="14.28%"><a href="https://shailesh-singh-bisht-portfolio.vercel.app/"><img src="https://avatars.githubusercontent.com/u/107263955?v=4?s=100" width="100px;" alt="Shailesh Singh Bisht"/><br /><sub><b>Shailesh Singh Bisht</b></sub></a><br /><a href="#maintenance-Shailesh-Singh-Bisht" title="Maintenance">🚧</a></td>
      <td align="center" valign="top" width="14.28%"><a href="https://github.com/royalhub123"><img src="https://avatars.githubusercontent.com/u/168981505?v=4?s=100" width="100px;" alt="royalhub123"/><br /><sub><b>royalhub123</b></sub></a><br /><a href="https://github.com/Shailesh-Singh-Bisht/Custom-CMD-Shell/commits?author=royalhub123" title="Tests">⚠️</a></td>
      <td align="center" valign="top" width="14.28%"><a href="https://github.com/Akhilnautiyal5"><img src="https://avatars.githubusercontent.com/u/113812781?v=4?s=100" width="100px;" alt="Akhil Nautiyal"/><br /><sub><b>Akhil Nautiyal</b></sub></a><br /><a href="https://github.com/Shailesh-Singh-Bisht/Custom-CMD-Shell/commits?author=Akhilnautiyal5" title="Code">💻</a></td>
      <td align="center" valign="top" width="14.28%"><a href="https://github.com/Vivek-Pokhriyal"><img src="https://avatars.githubusercontent.com/u/202429019?v=4?s=100" width="100px;" alt="Vivek-Pokhriyal"/><br /><sub><b>Vivek-Pokhriyal</b></sub></a><br /><a href="https://github.com/Shailesh-Singh-Bisht/Custom-CMD-Shell/commits?author=Vivek-Pokhriyal" title="Code">💻</a> <a href="https://github.com/Shailesh-Singh-Bisht/Custom-CMD-Shell/commits?author=Vivek-Pokhriyal" title="Tests">⚠️</a> <a href="https://github.com/Shailesh-Singh-Bisht/Custom-CMD-Shell/issues?q=author%3AVivek-Pokhriyal" title="Bug reports">🐛</a></td>
    </tr>
  </tbody>
  <tfoot>
    <tr>
      <td align="center" size="13px" colspan="7">
        <img src="https://raw.githubusercontent.com/all-contributors/all-contributors-cli/1b8533af435da9854653492b1327a23a4dbd0a10/assets/logo-small.svg">
          <a href="https://all-contributors.js.org/docs/en/bot/usage">Add your contributions</a>
        </img>
      </td>
    </tr>
  </tfoot>
</table>

<!-- markdownlint-restore -->
<!-- prettier-ignore-end -->

<!-- ALL-CONTRIBUTORS-LIST:END -->

This project follows the [all-contributors](https://github.com/all-contributors/all-contributors) specification. Contributions of any kind welcome!