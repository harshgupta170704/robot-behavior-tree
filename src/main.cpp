/**
 * @file main.cpp
 * @brief Behavior Tree executable for the "fetch apple from fridge" task.
 *
 * Flow (from the assignment flowchart):
 *   1. Move towards the door of the room
 *   2. If room door is closed → open it
 *   3. Enter the room
 *   4. Move towards the fridge
 *   5. If fridge door is closed → open it
 *   6. Find the apple
 *   7. Pick the apple
 *   8. Close the fridge door
 *   9. Move towards the door of the room
 *  10. Exit the room
 *
 * BT structure (BTCPP_format v4):
 *
 *   Sequence
 *   ├── MoveToRoomDoor
 *   ├── Fallback                          ← "open room door if closed"
 *   │   ├── Inverter → IsRoomDoorClosed
 *   │   └── OpenRoomDoor
 *   ├── EnterRoom
 *   ├── MoveToFridge
 *   ├── Fallback                          ← "open fridge door if closed"
 *   │   ├── Inverter → IsFridgeDoorClosed
 *   │   └── OpenFridgeDoor
 *   ├── FindApple
 *   ├── PickApple
 *   ├── CloseFridgeDoor
 *   ├── MoveToRoomDoor
 *   └── ExitRoom
 */

#include "robot_nodes.h"
#include "behaviortree_cpp/bt_factory.h"

#include <iostream>

// =====================================================================
// XML definition of the Behavior Tree
// a markup language

// =====================================================================
// clang-format off
static const char* xml_text = R"(

<root BTCPP_format="4">

    <BehaviorTree ID="MainTree">
        <Sequence name="robot_fetch_apple_task">

            <!-- PHASE 1: Navigate to the room and enter -->
            <Action ID="MoveToRoomDoor" name="move_to_room_door_1"/>

            <Fallback name="ensure_room_door_open">
                <Inverter>
                    <Condition ID="IsRoomDoorClosed"/>
                </Inverter>
                <Action ID="OpenRoomDoor"/>
            </Fallback>

            <Action ID="EnterRoom"/>

            <!-- PHASE 2: Navigate to fridge and open it -->
            <Action ID="MoveToFridge"/>

            <Fallback name="ensure_fridge_door_open">
                <Inverter>
                    <Condition ID="IsFridgeDoorClosed"/>
                </Inverter>
                <Action ID="OpenFridgeDoor"/>
            </Fallback>

            <!-- PHASE 3: Get the apple -->
            <Action ID="FindApple"/>
            <Action ID="PickApple"/>

            <!-- PHASE 4: Clean up and exit -->
            <Action ID="CloseFridgeDoor"/>
            <Action ID="MoveToRoomDoor" name="move_to_room_door_2"/>
            <Action ID="ExitRoom"/>

        </Sequence>
    </BehaviorTree>

</root>
)";
// clang-format on

// =====================================================================
int main()
{
    std::cout << "========================================" << std::endl;
    std::cout << "  Robot Behavior Tree — Fetch Apple" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;

    // 1. Create factory and register our nodes
    BT::BehaviorTreeFactory factory;

    Robot robot;
    robot.registerNodes(factory);

    // 2. Create the tree from the inline XML
    auto tree = factory.createTreeFromText(xml_text);

    // 3. Print the tree structure
    std::cout << "--- Tree Structure ---" << std::endl;
    BT::printTreeRecursively(tree.rootNode());
    std::cout << std::endl;

    // 4. Execute the tree
    std::cout << "--- Execution Start ---" << std::endl;
    BT::NodeStatus result = tree.tickWhileRunning();
    std::cout << std::endl;

    // 5. Report final result
    std::cout << "--- Execution Complete ---" << std::endl;
    std::cout << "Final status: "
              << (result == BT::NodeStatus::SUCCESS ? "SUCCESS ✓" : "FAILURE ✗")
              << std::endl;

    return (result == BT::NodeStatus::SUCCESS) ? 0 : 1;
}
