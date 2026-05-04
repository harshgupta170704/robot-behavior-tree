#include "robot_nodes.h"
#include <iostream>
#include <thread>
#include <chrono>

using BT::NodeStatus;

// Small helper to add a realistic delay and visual separation
static void simulateWork(int ms = 300)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

// ============================================================
//                      CONDITION NODES
// ============================================================

NodeStatus Robot::isRoomDoorClosed()
{
    if (!room_door_open_)
    {
        std::cout << "  [Condition] Room door is CLOSED." << std::endl;
        return NodeStatus::SUCCESS;   // yes, it IS closed
    }
    std::cout << "  [Condition] Room door is already OPEN." << std::endl;
    return NodeStatus::FAILURE;       // not closed
}

NodeStatus Robot::isFridgeDoorClosed()
{
    if (!fridge_door_open_)
    {
        std::cout << "  [Condition] Fridge door is CLOSED." << std::endl;
        return NodeStatus::SUCCESS;
    }
    std::cout << "  [Condition] Fridge door is already OPEN." << std::endl;
    return NodeStatus::FAILURE;
}

// ============================================================
//                       ACTION NODES
// ============================================================

NodeStatus Robot::moveToRoomDoor()
{
    std::cout << "  [Action] Moving towards the door of the room..." << std::endl;
    simulateWork();
    std::cout << "  [Action] Reached the room door." << std::endl;
    return NodeStatus::SUCCESS;
}

NodeStatus Robot::openRoomDoor()
{
    std::cout << "  [Action] Opening the room door..." << std::endl;
    simulateWork();
    room_door_open_ = true;
    std::cout << "  [Action] Room door is now OPEN." << std::endl;
    return NodeStatus::SUCCESS;
}

NodeStatus Robot::enterRoom()
{
    std::cout << "  [Action] Entering the room..." << std::endl;
    simulateWork();
    std::cout << "  [Action] Successfully entered the room." << std::endl;
    return NodeStatus::SUCCESS;
}

NodeStatus Robot::moveToFridge()
{
    std::cout << "  [Action] Moving towards the fridge..." << std::endl;
    simulateWork();
    std::cout << "  [Action] Reached the fridge." << std::endl;
    return NodeStatus::SUCCESS;
}

NodeStatus Robot::openFridgeDoor()
{
    std::cout << "  [Action] Opening the fridge door..." << std::endl;
    simulateWork();
    fridge_door_open_ = true;
    std::cout << "  [Action] Fridge door is now OPEN." << std::endl;
    return NodeStatus::SUCCESS;
}

NodeStatus Robot::findApple()
{
    std::cout << "  [Action] Searching for the apple in the fridge..." << std::endl;
    simulateWork();
    std::cout << "  [Action] Apple found!" << std::endl;
    return NodeStatus::SUCCESS;
}

NodeStatus Robot::pickApple()
{
    std::cout << "  [Action] Picking the apple..." << std::endl;
    simulateWork();
    std::cout << "  [Action] Apple picked up successfully." << std::endl;
    return NodeStatus::SUCCESS;
}

NodeStatus Robot::closeFridgeDoor()
{
    std::cout << "  [Action] Closing the fridge door..." << std::endl;
    simulateWork();
    fridge_door_open_ = false;
    std::cout << "  [Action] Fridge door is now CLOSED." << std::endl;
    return NodeStatus::SUCCESS;
}

NodeStatus Robot::exitRoom()
{
    std::cout << "  [Action] Exiting the room..." << std::endl;
    simulateWork();
    std::cout << "  [Action] Successfully exited the room." << std::endl;
    return NodeStatus::SUCCESS;
}

// ============================================================
//                    REGISTRATION
// ============================================================

void Robot::registerNodes(BT::BehaviorTreeFactory& factory)
{
    // ---- Conditions ----
    factory.registerSimpleCondition(
        "IsRoomDoorClosed",
        std::bind(&Robot::isRoomDoorClosed, this));

    factory.registerSimpleCondition(
        "IsFridgeDoorClosed",
        std::bind(&Robot::isFridgeDoorClosed, this));

    // ---- Actions ----
    factory.registerSimpleAction(
        "MoveToRoomDoor",
        std::bind(&Robot::moveToRoomDoor, this));

    factory.registerSimpleAction(
        "OpenRoomDoor",
        std::bind(&Robot::openRoomDoor, this));

    factory.registerSimpleAction(
        "EnterRoom",
        std::bind(&Robot::enterRoom, this));

    factory.registerSimpleAction(
        "MoveToFridge",
        std::bind(&Robot::moveToFridge, this));

    factory.registerSimpleAction(
        "OpenFridgeDoor",
        std::bind(&Robot::openFridgeDoor, this));

    factory.registerSimpleAction(
        "FindApple",
        std::bind(&Robot::findApple, this));

    factory.registerSimpleAction(
        "PickApple",
        std::bind(&Robot::pickApple, this));

    factory.registerSimpleAction(
        "CloseFridgeDoor",
        std::bind(&Robot::closeFridgeDoor, this));

    factory.registerSimpleAction(
        "ExitRoom",
        std::bind(&Robot::exitRoom, this));
}
