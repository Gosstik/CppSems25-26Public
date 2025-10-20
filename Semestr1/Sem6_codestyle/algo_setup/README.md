# TLDR

## Для пользователей и clion, и vscode

Сначала установить все вспомогательные утилиты нужной версии:

- Вариант попроще:

```bash
# Default compiler version
sudo apt-get install clangd clang-tidy clang-format

# Specific compiler version
sudo apt-get install clangd-19 clang-tidy-19 clang-format-19
```

- Вариант посложнее (позволяет установить последнюю доступную версию компилятора для вашей версии linux):

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
```

## Только для пользователей vscode

Поставить расширения для плюсов:

```text
llvm-vs-code-extensions.vscode-clangd
ms-vscode.cpptools
ms-vscode.cpptools-extension-pack
ms-vscode.cpptools-themes

vadimcn.vscode-lldb
xaver.clang-format
```

### clang-format

- Проверить, что стоит расширение `xaver.clang-format`
- Создать `.clang-format` и вставить содержимое из [.clang-format](.clang-format)
- посмотреть (или поменять) шорткат, чтобы форматировать прямо в ide: settings -> Keyboard Shortcuts -> в поиске вбить "Format Document"
- перезагрузить ide (palette -> reload window) или clangd (palette -> clangd: Restart language server)
- Проверить, что всё работает: добавить строку "IndentWidth: 4" в `.clang-format` и применить шорткат - отступы в файле должны быть длины 4 (по дефолту 2)

### clang-tidy

- Проверить, что стоит расширение `llvm-vs-code-extensions.vscode-clangd`
- Создать файл `.clang-tidy` и вставить содержимое из [.clang-tidy](./.clang-tidy)
- Перезагрузить ide (palette -> reload window) или clangd (palette -> clangd: Restart language server)
- Проверить, что всё работает: создать функцию `void foo() {}` &mdash; в редакторе должна подсвечиваться ошибка `Invalid case style for function 'foo'`, должно предлагать заменить на `Foo()`

### Флаги компиляции

- Проверить, что стоит расширение `llvm-vs-code-extensions.vscode-clangd`
- Создать `.clangd` и вставить содержимое из [.clangd](./.clangd)
- Перезагрузить ide (palette -> reload window) или clangd (palette -> clangd: Restart language server)
- Проверить, что всё работает: написать в файле `int main() { int x; }` &mdash; должно отображать ошибку `Unused variable 'x'`
