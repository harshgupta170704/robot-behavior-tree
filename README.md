# 🌳 Behavior Tree — Fetch Apple from Fridge

A standalone C++ behavior tree (independent of ROS) using the
[BehaviorTree.CPP v4](https://github.com/BehaviorTree/BehaviorTree.CPP)
library. The robot navigates a room, opens doors conditionally, picks an
apple from the fridge, and exits.

## Task Flowchart → BT Mapping

```
              Sequence (robot_fetch_apple_task)
              ├── MoveToRoomDoor
              ├── Fallback (ensure_room_door_open)
              │   ├── Inverter
              │   │   └── IsRoomDoorClosed          ← Condition
              │   └── OpenRoomDoor                  ← Action
              ├── EnterRoom
              ├── MoveToFridge
              ├── Fallback (ensure_fridge_door_open)
              │   ├── Inverter
              │   │   └── IsFridgeDoorClosed        ← Condition
              │   └── OpenFridgeDoor                ← Action
              ├── FindApple
              ├── PickApple
              ├── CloseFridgeDoor
              ├── MoveToRoomDoor
              └── ExitRoom
```

### How the conditional doors work

The flowchart says *"if door closed → open it, then continue"*.  In BT terms
this is a classic **Fallback + Inverter** pattern:

```
Fallback
├── Inverter → IsDoorClosed    (if NOT closed → SUCCESS → skip opening)
└── OpenDoor                   (if closed → open it)
```

## Prerequisites

| Tool   | Minimum Version |
|--------|----------------|
| CMake  | 3.16           |
| C++ 17 | GCC 7+ / MSVC 2017+ / Clang 5+ |
| Git    | any            |

> **No manual BehaviorTree.CPP install needed** — CMake `FetchContent`
> downloads and builds it automatically.

## Build & Run

### Linux / macOS

```bash
cd behavior_tree_task
mkdir build && cd build
cmake ..
make -j$(nproc)
./robot_bt
```

### Windows (Visual Studio / MSVC)

```powershell
cd behavior_tree_task
mkdir build; cd build
cmake ..
cmake --build . --config Release
.\Release\robot_bt.exe
```

## Expected Output

```
========================================
  Robot Behavior Tree — Fetch Apple
========================================

--- Tree Structure ---
 [Sequence: robot_fetch_apple_task]
    - [Action: move_to_room_door_1]
    - [Fallback: ensure_room_door_open]
       - [Inverter]
          - [Condition: IsRoomDoorClosed]
       - [Action: OpenRoomDoor]
    - [Action: EnterRoom]
    - [Action: MoveToFridge]
    - [Fallback: ensure_fridge_door_open]
       - [Inverter]
          - [Condition: IsFridgeDoorClosed]
       - [Action: OpenFridgeDoor]
    - [Action: FindApple]
    - [Action: PickApple]
    - [Action: CloseFridgeDoor]
    - [Action: move_to_room_door_2]
    - [Action: ExitRoom]

--- Execution Start ---
  [Action] Moving towards the door of the room...
  [Action] Reached the room door.
  [Condition] Room door is CLOSED.
  [Action] Opening the room door...
  [Action] Room door is now OPEN.
  [Action] Entering the room...
  [Action] Successfully entered the room.
  [Action] Moving towards the fridge...
  [Action] Reached the fridge.
  [Condition] Fridge door is CLOSED.
  [Action] Opening the fridge door...
  [Action] Fridge door is now OPEN.
  [Action] Searching for the apple in the fridge...
  [Action] Apple found!
  [Action] Picking the apple...
  [Action] Apple picked up successfully.
  [Action] Closing the fridge door...
  [Action] Fridge door is now CLOSED.
  [Action] Moving towards the door of the room...
  [Action] Reached the room door.
  [Action] Exiting the room...
  [Action] Successfully exited the room.

--- Execution Complete ---
Final status: SUCCESS ✓
```

## Project Structure

```
behavior_tree_task/
├── CMakeLists.txt           # Build config (auto-fetches BT.CPP)
├── include/
│   └── robot_nodes.h        # Robot class declaration
├── src/
│   ├── main.cpp             # BT XML definition + execution
│   └── robot_nodes.cpp      # Dummy action/condition implementations
└── README.md
```
