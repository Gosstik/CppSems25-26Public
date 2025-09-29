# Семинар 6. Кодстайл. clang-tidy и clang-format

## Formatting and linting

### Types of naming

- snake_case
- UpperCamelCase (PascalCase)
- lowerCamelCase
- UPPER_CASE (SCREAMING_SNAKE_CASE)
- kebab-case

### Installation

- Easy way:

```bash
# Default version
sudo apt-get install clangd clang-tidy clang-format

# For fixed compiler version
sudo apt-get install clangd-19 clang-tidy-19 clang-format-19
```

- More complex, but consistent way:

```bash
CLANG_VERSION=20

mkdir clang
cd clang
curl -O https://apt.llvm.org/llvm.sh # or wget
chmod +x llvm.sh
sudo ./llvm.sh -${CLANG_VERSION}
sudo apt-get install \
  clangd-${CLANG_VERSION} \
  clang-tidy-${CLANG_VERSION} \
  clang-format-${CLANG_VERSION}

sudo apt-get autoremove
sudo update-alternatives --install /usr/bin/clang clang /usr/bin/clang-${CLANG_VERSION} ${CLANG_VERSION} \
  --slave /usr/bin/clang++ clang++ /usr/bin/clang++-${CLANG_VERSION} \
  --slave /usr/bin/clang-tidy clang-tidy /usr/bin/clang-tidy-${CLANG_VERSION} \
  --slave /usr/bin/clang-format clang-format /usr/bin/clang-format-${CLANG_VERSION} \
  --slave /usr/bin/clangd clangd /usr/bin/clangd-${CLANG_VERSION}

# Show current alternatives
sudo update-alternatives --display clang

# Choose concrete version interactively
sudo update-alternatives --config clang

# One-shot version selection
sudo update-alternatives --set clang /usr/bin/clang-${CLANG_VERSION}

# Delete all for specific version
sudo apt-get purge \
  clang-${CLANG_VERSION} \
  clang++-${CLANG_VERSION} \
  clangd-${CLANG_VERSION} \
  clang-tidy-${CLANG_VERSION} \
  clang-format-${CLANG_VERSION}
```

### clang-format

Work in terminal:

```bash
# Apply formatting to main.cpp
clang-format -i main.cpp

# Shows you warnings if something is formatted wrong (--dry-run)
clang-format -n main.cpp

# Format all files in current folder
clang-format -i *.cpp *.hpp

# Recursively format files in directory
find <dir> -iname '*.cpp' -o -iname '*.hpp' | xargs clang-format -i

# Apply config directly
clang-format -i --style="$(cat clang-format.txt)" main.cpp

# Apply config and save to out.cpp
clang-format --style="$(cat clang-format.txt)" main.cpp > out.cpp

# Show current config
clang-format --dump-config

# More options
clang-format --help
```

Опции конфигурации `clang-format` берёт из файла `.clang-format`. Все возможные опции `.clang-format` можно посмотреть [по ссылке](https://clang.llvm.org/docs/ClangFormatStyleOptions.html).

### clang-tidy

`clang-tidy` &mdash; линтер, то есть проверяет стиль нейминга и корректность кода. Большие проекты из множества файлов собираются системами сборки, которые генерируют специальные индексные файлы. Эти файлы `clang-tidy` использует в качестве `compilation database`. В нашем курсе мы будем писать всё в одном файле и пользоваться только стандартной библиотекой, поэтому заморачиваться с `compilation database` не будем. Ошибки вида

```text
Error while trying to load a compilation database
```

при запуске линтера можно игнорировать.

```bash
# Run checks
clang-tidy tidy.cpp

# Append arguments to the compiler command line
clang-tidy --extra-arg="-std=c++20" tidy.cpp

# For each enabled check explains, where it is enabled (i.e. .clang-tidy, command line, ...)
clang-tidy --explain-config

# Set file explicitly (to check for errors, for example)
clang-tidy --config-file=../.clang-tidy tidy.cpp

# Recursively check files in directory
find <dir> -iname '*.cpp' -o -iname '*.hpp' | xargs clang-tidy

# Apply json config
clang-tidy --config="$(cat algo_tidy.txt)" main.cpp

# Show current config
clang-tidy --dump-config

# More options
clang-format --help
```

Экзотика для желающих потыкаться:

```bash
# Try to fix warnings automatically. Do nothing if there are errors
clang-tidy --fix tidy.cpp

# Try to fix warnings automatically even if compilation errors were found
clang-tidy --fix-errors tidy.cpp

# Write allowed fixes to file
clang-tidy --export-fixes=tidy_fixes.txt tidy.cpp

# Profile clang-tidy check
clang-tidy --enable-check-profile tidy.cpp
```

Опции конфигурации `clang-tidy` берёт из файла `.clang-tidy`. Дополнительные опции `.clang-tidy` смотрите [по ссылке](https://clang.llvm.org/extra/clang-tidy/).


## Suppression of diagnostic and formatting

Иногда возникает ситуация, что в коде приходится в нескольких местах нарушить правила из `.clang-tidy`, при этом хочется сохранить их для остального проекта и нового кода. Для таких случаев есть специальные слова-маркеры, которые позволяют подавить проверку `clang-tidy` для одной строки или для блока кода. Опции можно посмотреть в [доке clang-tidy](https://clang.llvm.org/extra/clang-tidy/#suppressing-undesired-diagnostics) и доке [clang-format](https://clang.llvm.org/docs/ClangFormatStyleOptions.html#disabling-formatting-on-a-piece-of-code).


### Formatters and linters in vscode

`clang-format` extension: `xaver.clang-format`.

`clang-tidy` extension: `llvm-vs-code-extensions.vscode-clangd`.

Regrettably, currently vscode does not have widely used extension for full `.clang-tidy` support. However, `clangd` supports some of its features. All you need to do is to pass `--clang-tidy` argument to `clangd` in vscode settings. If no `.clang-tidy` file is found inside parent directories, `clangd` uses default settings. To redefine them to local project one can create `.clangd` configuration file in project root. To redefine user settings (for all projects) you should edit `~/.config/clangd/config.yaml`. More on `clangd` configuration: [clangd.llvm.org](https://clangd.llvm.org/config.html).

**Hint**: to redefine user default compilation flags in `vscode` you can use `clangd.fallbackFlags`.

Чтобы `clangd` увидел изменения `.clang-tidy`, нужно рестартануть сервер. Для этого в `pallete` нужно ввести: `clangd: Restart language server`.

Handy links:

- Больше про clangd и его возможности: [clangd.llvm.org/features](https://clangd.llvm.org/features)

## Algo compilation

```bash
clang++ -std=c++20 -Wall -Wextra -pedantic -Werror -g -fsanitize=address,undefined main.cpp
```
