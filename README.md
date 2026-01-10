# What is Gubash 🗒️
**`Portable POSIX-like shell`** is a portable shell created in **C++**. It is inspired by **Bash** and provides script support, as well as a number of advanced features.

## Main features 📖
- [ ] ***POSIX compatibility***: Supports basic POSIX designs and commands to ensure broad compatibility.
- [ ] ***Advanced functions***: Includes various features, such as process control, signal processing and function creation, which makes scripts more powerful.
- [ ] ***Multithreading support***: Fast processing of complex scripts and the possibility of parallel work.
- [ ] ***Dynamic plugin loading***: Expandability through custom scripts and commands.
- [ ] ***Intuitive autofill***: User-friendly interface for the team with autofill support.
- [ ] ***Improved debugging tools***: Tools for easy diagnostics and debugging of scripts.
- [ ] ***Cross-platform***: Ability to work on different platforms without changes.

# Project build 🔨
Clone the repository with the command `git clone 'repository'`.
```bash
git clone https://github.com/gubarger/Gubash.git
```
\
Create a **build** directory (or any other analoge) in the project folder.
```bash
mkdir Gubash\build
```

> [!TIP]
> If you want to use your `.gitignore`, create a `.gitignore.local` file and configure it to your needs.

\
Go to the `build` and build the project.
```bash
# cmake
cmake -DBUILD_TESTS=OFF .. # If you don't need tests.
cmake -DBUILD_TESTS=ON .. # If tests are needed (is by default).

# After cmake
./Gubash # Main program
./Gubash_tests # Main tests
```

> [!NOTE]
> There is support `valgrind/ctest` (if you have it installed. By default, **cmake** when building tests - installs only `googletests`.

```bash
# CTest
ctest
ctest -V  # Detailed conclusion.
ctest -R "MemoryTest"  # Tests only with a specific name.
ctest --output-on-failure  # Print if failed.
```

# Information about of <ins>Gubash</ins>

[See Changelog]() - Information about changes in the project.\
[See Info]() - Information about the project (for what, for whom and why it is useful, etc.).

# License 📒
Distribution under the **MIT** license.\
[See Mit license](https://mit-license.org/)
