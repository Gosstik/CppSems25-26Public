# Семинар 7. Санитайзеры и дебагер

## Sanitizers

Виды санитайзеров:

- address
- leak (подмножество address)
- undefined
- thread (не будем смотреть)

Флаги компиляции:

```bash
g++ -fsanitize=address main.cpp
g++ -fsanitize=undefined main.cpp

g++ -fsanitize=address,undefined main.cpp
```

При использовании только флагов выше в отчёте об ошибке вместо строк из исходника может писаться (a.out+0x2d22). Чтобы показывались ссылки на строки из исходника, нужно добавить флаги `-g` и `-O0`:

```bash
clang++ -std=c++20 -O0 -g -fsanitize=address,undefined main.cpp
```

Не все санитайзеры можно комбинировать между собой, так что просто перечислить сразу все не получится. Обычно можно в качестве второго санитайзера указывать `undefined`, но вот использовать `address` + `thread` не рекомендуется.

Можно явно посмотреть, во что превращается ваш код, скомпилировав его в godbolt.

Когда добавляется флаг санитайзеров, вызовы некоторых функций в программе заменяются на другие, в которых расставлены определённые проверки (выход за границы массива, переполнение и т.п.). Отсюда 2 вывода:

1) Проверки санитайзерами происходят **в рантайме**, поэтому некорректный код тоже вполне себе будет компилироваться.
2) Добавление санитайзеров замедляет программу.

Задания в контестах обычно запускаются с санитайзерами. Локально тоже следует тестировать с ними.

Самые распространённые ошибки, отлавливаемые address санитайзером:

- heap use after free
- stack use after scope
- double free or corruption
- heap-buffer-overflow (выход за границы массива)


## Debugger

There are different debuggers for different platforms:

- MacOS: `GDB` or `LLDB`
- Windows: `Visual Studio Windows Debugger` or `GDB`
- Linux: `GDB` (or `LLDB` ???)

To use debugger, you have to compile your `.cpp` file with `-g` flag:

```bash
g++ -g -std=c++20 main.cpp
```

### GDB

Installation:

```bash
sudo apt-get install build-essential gdb
```

#### Cores

```bash
# Print current limit for core files size
ulimit -c

# Set max core dump file size to unlimited
ulimit -c unlimited

# Core files can be stored in
# - current directory with executable
# - /cores
# - somewhere in /var
# - ...
sudo find /var -iname "core*"

# To run gdb on core (executable must be compiled with -g and -O0 flags)
gdb <executable> <core_file>
gdb a.out gdb a.out /var/lib/apport/coredump/main.cpp.05e0d3b8-f36d-457b-9d83-feb123041c04.2435338.3701524

# Commands in gdb
bt # print stack trace
```

Commands in gdb: [cheetsheet](https://www.cs.princeton.edu/courses/archive/fall16/cos432/hw2/gdb-refcard.pdf).

Most commonly used:

- `bt` (backtrace) &mdash; print current stacktrace
- `list` &mdash; print source code around current position
- `b` (break) &mdash; set breakpoint
- `watch p` &mdash; set watchpoint for variable p
- `print p` &mdash; print value of variable p
- By step execution: `n` (next), `s` (step), `c` (continue), `f` (finish)

Attach to current process: TODO

### vscode

#### Installation

For correct work you have to install extensions:

- `ms-vscode.cpptools`
- `ms-vscode.cpptools-extension-pack`

If you use `clangd`, you have to add to `User Settings (JSON)` line:

```json
"C_Cpp.intelliSenseEngine": "disabled", // required for debugger
```

#### Usage

- In palette open `Debug: Add configuration...`
- Add your custom configuration

- On activity bar (left upper corner) open `Run And Debug`.
- `Create a launch.json file`
- Copy content of [.vscode](./vscode_debug/.vscode) to your folder

If you want you may generate `tasks.json` by running `Tasks: configure default build task`.


#### Concepts

`Attach` and `Launch` --- types of `request` in configuration.

- Break Points
- Step through the code
- Inside debug window
  - Variables
  - Watches
  - Call Stack

- Debug console:

```text
-exec bt
-exec print <expression>
```

#### Links

- [vscode debug](https://code.visualstudio.com/docs/editor/debugging)
- [vscode c++ debug](https://code.visualstudio.com/docs/cpp/launch-json-reference)

- [gc](https://tip.golang.org/doc/gc-guide)
- [safe rust](https://cacm.acm.org/research/safe-systems-programming-in-rust/)
- [AddressSanitizer.cpp](https://github.com/llvm/llvm-project/blob/main/llvm/lib/Transforms/Instrumentation/AddressSanitizer.cpp)
- [Address Sanitizer Memory Checks](https://www.usenix.org/sites/default/files/conference/protected-files/serebryany_atc12_slides.pdf)
- [llvm AddressSanitizer (slowdown is 2x)](https://clang.llvm.org/docs/AddressSanitizer.html)
- [GDB cheat sheet](https://www.cs.princeton.edu/courses/archive/fall16/cos432/hw2/gdb-refcard.pdf)
