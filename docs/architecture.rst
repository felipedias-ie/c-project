Architecture
============

Overview
--------

slither.c is a client-server multiplayer snake game inspired by slither.io.

Components
----------

**Client** (``src/client/main.c``)
    Handles rendering with raylib, user input, and network communication.
    Uses linear interpolation to smooth movement between server updates.

**Server** (``src/server/main.c``)
    Authoritative game server. Manages physics, collisions, food spawning,
    and bot AI. Broadcasts world state to all clients at 60 ticks/second.

**Shared** (``src/common/shared.h``)
    Common data structures and packet definitions used by both client and server.

Network Protocol
----------------

Uses ENet for reliable/unreliable UDP communication:

- **Channel 0** (Reliable): Join, Init, Die packets
- **Channel 1** (Unreliable): Input, World state packets

Packet sequence numbers prevent out-of-order updates from causing jitter.

Data Flow
---------

::

    Client                          Server
      |                               |
      |------- JOIN_PACKET ---------->|
      |<------ INIT_PACKET -----------|
      |                               |
      |------- INPUT_PACKET --------->|  (60 Hz)
      |<------ WORLD_PACKET ----------|  (60 Hz)
      |                               |
      |<------ DIE_PACKET ------------|  (on death)


