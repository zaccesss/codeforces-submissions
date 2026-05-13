# Practice/1000

This folder contains 1000-rated practice problems (C++ solutions).

Guidelines
- Do not run or keep compiled `.exe` files in source directories. Put compiled binaries under the repository `bin/` folder.
- Compile with the output pointed to the `bin` folder so you never run executables from source directories.

Windows (PowerShell) example — compile into `bin\practice\1000` and run from there:

```powershell
# create destination folder (only needed once)
New-Item -ItemType Directory -Force -Path bin\practice\1000

# compile into bin
g++ -std=c++17 -O2 -pipe -o bin\practice\1000\230A.exe practice\1000\230A-dragons.cpp

# run from bin
bin\practice\1000\230A.exe < sample-input.txt
```

Linux / macOS example:

```bash
mkdir -p bin/practice/1000
g++ -std=c++17 -O2 -pipe -o bin/practice/1000/230A practice/1000/230A-dragons.cpp
./bin/practice/1000/230A < sample-input.txt
```

Why this rule?
- Keeping compiled binaries in `bin/` avoids accidentally committing large binaries, prevents running outdated artifacts in source folders, and keeps the repo clean.

