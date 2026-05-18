# Roguelike Engine

---

## Краткая суть проекта

Движок позволяет генерировать процедурные подземелья, управлять персонажем,
сражаться с монстрами и использовать предметы. Ключевой особенностью является
**загрузка контента из внешних файлов (JSON/CSV)**, что позволяет изменять
игру без перекомпиляции кода.

---

## Структура проекта

```
RoguelikeEngine/
├── CMakeLists.txt
├── Dockerfile
├── .dockerignore
├── README.md
│
├── include/ # Заголовочные файлы
│ ├── GameEngine.h
│ ├── Player.h
│ ├── Monster.h
│ ├── Item.h
│ ├── Level.h
│ ├── Room.h
│ ├── ModLoader.h
│ └── Logger.h
│
├── src/ # Исходные файлы
│ ├── main.cpp
│ ├── GameEngine.cpp
│ ├── Player.cpp
│ ├── Monster.cpp
│ ├── Item.cpp
│ ├── Level.cpp
│ ├── Room.cpp
│ ├── ModLoader.cpp
│ └── Logger.cpp
│
├── tests/ # Unit-тесты Catch2
│ ├── CMakeLists.txt
│ ├── test_*.cpp
│ └── Тестовые_сценарии.txt
│
├── scenarios/ # Мини-программы сценариев
│ ├── CMakeLists.txt
│ └── scenario_*.cpp
│
└── mods/ # Конфигурационные файлы модов
├── monsters.json
├── items.json
└── rooms.json
```

---

## Инструкция по сборке

### Требования

| Инструмент | Версия |
|------------|--------|
| CMake | >= 3.14 |
| Компилятор C++ | GCC 7+ / Clang 5+ / MSVC 2017+ (C++17) |

### Команды сборки

```bash
cmake -S . -B build
cmake --build build
```

### Запуск

```bash
# Linux / macOS
cd build
./roguelike_game

# Windows
cd build
roguelike_game.exe
```

Первый запуск `cmake` скачивает Catch2 с GitHub (нужен интернет).

### Аргументы командной строки

| Аргумент | Описание | Пример |
|---|---|---|
| `--help` | Показать справку| `roguelike_game --help` |
| `--level N` | Начать с уровня N (по умолчанию: 1) | `roguelike_game --level 5` |
| `--width N` | Ширина подземелья в комнатах (по умолчанию: 8) | `roguelike_game --width 10` |
| `--height N` | Высота подземелья в комнатах (по умолчанию: 8) | `roguelike_game --height 10` |
| `--mods PATH` | Путь к папке с модами (по умолчанию: ../mods/) | `roguelike_game --mods . а./my_mods/` |

### Игровой процесс

| Команда | Действие |
|---|---|
| w / a / s / d | Перемещение по комнатам |
| f | Атаковать монстра |
| i | Открыть инвентарь и использовать предмет |
| p | Подобрать предмет с пола |
| q | Выйти из игры |

### Пример игровой сессии

```
========================================
       ROGUELIKE ENGINE
========================================
               LEVEL 1
========================================
Generating level 8x8...

[HP: 100/100 | LVL: 1 | EXP: 0/100]
Position: (0, 0)
Enemies left on level: 41
Commands: (w/a/s/d) move, (f)ight, (i)nventory, (p)ickup, (q)uit
> d
You moved to room (1, 0)

=== BATTLE ===
You encounter Goblin!
Your HP: 100 (ATK:15 DEF:5) | Goblin HP: 50 (ATK:12 DEF:3)
(f)ight, (r)un
> f
Player attacks Goblin! Damage: 12
Goblin takes 12 damage. HP: 38/50
Goblin attacks! Damage: 7
Player takes 7 damage. Health: 93/100
...
Gained 50 EXP! Total: 50
Health Potion fell on the ground!
Goblin defeated!

[HP: 65/100 | LVL: 1 | EXP: 50/100]
Position: (1, 0)
Enemies left on level: 40
Commands: (w/a/s/d) move, (f)ight, (i)nventory, (p)ickup, (q)uit
> q

========================================
             GAME OVER
    Dungeon level reached: 1
    Character level reached: 1
========================================
```

---

## Тестирование (КР №4)

Чтобы все корректно отображалось рекомендуется временно переключить кодировку консоли командой `chcp 65001`.

Запуск unit-тестов:

```bash
cd build/tests
roguelike_tests.exe
```

Запуск сценариев:

```bash
cd build/scenarios
scenario_1_game_start.exe
scenario_2_level_generation.exe
# ... и так далее

for %f in (scenario_*.exe) do %f      #для запуска всех сценариев
```

Список сценариев и пояснения: `tests/Тестовые_сценарии.txt`.

---

## Контейнеризация (КР №5)

### 1. Сборка образа

Выполнять из корня репозитория:

```bash
docker build -t roguelike-game:latest .
```

**Что происходит:** Docker создаёт образ `roguelike-game:latest`. На этапе `builder` выполняются cmake, компиляция и **`ctest --output-on-failure`**. Если хотя бы один тест Catch2 падает, сборка образа прерывается с ошибкой — это и есть проверка тестов в контейнере. В финальный образ попадают только `roguelike_game`, `roguelike_tests` и мини-сценарии, без исходников и папки `build/`.

### 2. Запуск игры

Интерактивный режим (`-it` — терминал + ввод с клавиатуры):

```bash
docker run -it --rm roguelike-game:latest
```
| Флаг | Пояснение |
|---|---|
| `-it` | Интерактивный TTY: ввод команд (w/a/s/d, f, i, p, q) |
| `--rm` |Удалить контейнер после выхода |

**Штатный выход из игры:** ввести `q` и Enter.

### 3. Запуск unit-тестов

Тесты уже выполняются при `docker build`; отдельно их можно показать в готовом образе:

```bash
docker run --rm --entrypoint /usr/local/bin/roguelike_tests roguelike-game:latest
```
`--entrypoint` подменяет точку входа (по умолчанию — `roguelike_game`), чтобы запустить только тестовый исполняемый файл. Ожидаемый результат — сообщение Catch2 об успешном прохождении всех тестов.


### 4. Запуск мини-сценариев

В образе лежат бинарники в `/usr/local/bin/scenarios/`:

```bash
docker run --rm --entrypoint /usr/local/bin/scenarios/scenario_1_game_start roguelike-game:latest
docker run --rm --entrypoint /usr/local/bin/scenarios/scenario_2_level_generation roguelike-game:latest
# ... и т.д.
```

### 5. Запуск всех сценариев подряд

```bash
docker run --rm --entrypoint sh roguelike-game:latest -c "for f in /usr/local/bin/scenarios/scenario_*; do $f; done"
```

### 6. Запуск с аргументами

```bash
docker run -it --rm roguelike-game:latest --level 5 --width 10 --height 10
docker run -it --rm roguelike-game:latest --help
```

---

## Использованные сторонние библиотеки

В проекте используется только одна сторонняя библиотека — Catch2, предназначенная для unit-тестирования. Она подключается автоматически через систему FetchContent в файле tests/CMakeLists.txt. Все остальные зависимости стандартная библиотека C++17.
