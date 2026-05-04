#pragma once

#include "behaviortree_cpp/bt_factory.h"

/**
 * @brief Simulated robot that navigates a room, opens doors, and picks an
 *        apple from a fridge.
 *
 * All actions are "dummy" — they just print to stdout to show they are
 * being called at the right time by the behavior tree.
 *
 * Internal state (door open/closed) is tracked so that the Condition nodes
 * return meaningful SUCCESS / FAILURE values.
 */
class Robot
{
public:
    /// Register every Action / Condition with the BT factory
    void registerNodes(BT::BehaviorTreeFactory& factory);

    // ---------- Condition callbacks ----------
    BT::NodeStatus isRoomDoorClosed();
    BT::NodeStatus isFridgeDoorClosed();

    // ---------- Action callbacks ----------
    BT::NodeStatus moveToRoomDoor();
    BT::NodeStatus openRoomDoor();
    BT::NodeStatus enterRoom();
    BT::NodeStatus moveToFridge();
    BT::NodeStatus openFridgeDoor();
    BT::NodeStatus findApple();
    BT::NodeStatus pickApple();
    BT::NodeStatus closeFridgeDoor();
    BT::NodeStatus exitRoom();

private:
    bool room_door_open_  = false;   // Room door starts closed
    bool fridge_door_open_ = false;  // Fridge door starts closed
};
