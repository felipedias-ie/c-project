# slither.c

A multiplayer snake game inspired by slither.io, written in C using raylib for graphics and enet for networking.

## Requirements

- macOS / Linux
- Conda (Miniconda or Anaconda)
- Git

## Setup

### 1. Create the conda environment

```bash
conda env create -f environment.yml
```

### 2. Activate the environment

```bash
conda activate slither_c
```

## Building

Make sure the conda environment is activated first:

```
rm -rf build && mkdir build && cd build && cmake .. && make
```

```bash
conda activate slither_c

mkdir build
cd build
cmake ..
make
```

This will produce two executables in the `build/` folder:
- `server` - the game server
- `client` - the game client

## Running

### 1. Start the server

```bash
./build/server
```

The server runs on port 7777 by default. You can specify a different port:

```bash
./build/server 8888
```

### 2. Start the client

```bash
./build/client
```

To connect to a different server:

```bash
./build/client <ip> <port>
```

For example:

```bash
./build/client 192.168.1.100 7777
```

## How to Play

1. Enter your name in the menu
2. Press ENTER to join the game
3. Move your mouse to control the snake direction
4. Eat the glowing food particles to grow
5. Avoid crashing into other snakes
6. Try to make other snakes crash into you to eat their remains

## Project Structure

```
src/
├── client/
│   └── main.c      # game client (rendering, input, networking)
├── server/
│   └── main.c      # game server (physics, collisions, AI bots)
└── common/
    └── shared.h    # shared definitions (packets, constants)
```

## Network Protocol

The game uses UDP via enet for low-latency communication:

- `JOIN_PACKET` - client requests to join with username
- `INIT_PACKET` - server assigns player ID
- `INPUT_PACKET` - client sends mouse angle
- `WORLD_PACKET` - server broadcasts all snake/food positions
- `DIE_PACKET` - server notifies client of death

## Documentation

Generate the HTML documentation:

```bash
cd docs
sphinx-build -b html . _build/html
```

Then open `docs/_build/html/index.html` in your browser.

## AI Disclosure

all parts of the code written with the help of a language model are labeled with [AI]

https://github.com/search?q=repo%3Afelipedias-ie%2Fc-project%20AI&type=code
