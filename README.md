# Roguelike Engine

## Краткая суть проекта
Движок для Roguelike-игр с поддержкой модов. Загружает подземелья и игровые сущности из внешних текстовых файлов.

## Требования
- CMake 3.10 или выше
- Компилятор C++17

## Инструкция по сборке

```bash
cmake -S . -B build
cmake --build build
cd build
.\RoguelikeEngine.exe
