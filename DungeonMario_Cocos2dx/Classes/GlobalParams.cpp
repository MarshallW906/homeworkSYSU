//
//  GlobalParams.cpp
//  DungeonMario
//
//  Created by Marshall Wang on 2017/7/7.
//
//

#include "GlobalParams.hpp"

GlobalParams::GlobalParams() {
    gearRadius = 10;
    enemyPatrolSpeed = 3;
    playerMoveSpeed = 2;
    TotalStagesCount = 3;
	Mute = false;
    // Objects
    TagMap.insert(std::pair<std::string, int>("Player", 10));
    TagMap.insert(std::pair<std::string, int>("PlayerPhysics", 11));
    TagMap.insert(std::pair<std::string, int>("PlainRock", 20));
    TagMap.insert(std::pair<std::string, int>("PlainRockPhysics", 21));
    TagMap.insert(std::pair<std::string, int>("IceRock", 22));
    TagMap.insert(std::pair<std::string, int>("IceRockPhysics", 23));
    TagMap.insert(std::pair<std::string, int>("Tanhuang", 24));
    TagMap.insert(std::pair<std::string, int>("TanhuangPhysics", 25));
    TagMap.insert(std::pair<std::string, int>("DestinationPoint", 26));
    TagMap.insert(std::pair<std::string, int>("DestinationPointPhysics", 27));
    TagMap.insert(std::pair<std::string, int>("StartPoint", 28));
    TagMap.insert(std::pair<std::string, int>("StartPointPhysics", 29));
    TagMap.insert(std::pair<std::string, int>("Mushroom", 30));
    TagMap.insert(std::pair<std::string, int>("MushroomPhysics", 31));
    TagMap.insert(std::pair<std::string, int>("Key", 32));
    TagMap.insert(std::pair<std::string, int>("KeyPhysics", 33));
    TagMap.insert(std::pair<std::string, int>("FlyingPlatform", 34));
    TagMap.insert(std::pair<std::string, int>("FlyingPlatformPhysics", 35));
    TagMap.insert(std::pair<std::string, int>("Coin", 36));
    TagMap.insert(std::pair<std::string, int>("CoinPhysics", 37));
    TagMap.insert(std::pair<std::string, int>("DestinationPoint", 38));
    TagMap.insert(std::pair<std::string, int>("DestinationPointPhysics", 39));
    // Enemy
    TagMap.insert(std::pair<std::string, int>("Turtle", 50));
    TagMap.insert(std::pair<std::string, int>("TurtlePhysics", 51));
    TagMap.insert(std::pair<std::string, int>("Gear", 52));
    TagMap.insert(std::pair<std::string, int>("GearPhysics", 53));
    TagMap.insert(std::pair<std::string, int>("Spike", 54));
    TagMap.insert(std::pair<std::string, int>("SpikePhysics", 55));
    TagMap.insert(std::pair<std::string, int>("Chestnut", 56));
    TagMap.insert(std::pair<std::string, int>("ChestnutPhysics", 57));
    
}

GlobalParams::GlobalParams(GlobalParams const& oth) {
    gearRadius = oth.gearRadius;
    enemyPatrolSpeed = oth.enemyPatrolSpeed;
    playerMoveSpeed = oth.playerMoveSpeed;
}

GlobalParams & GlobalParams::operator=(GlobalParams const&oth) {
    gearRadius = oth.gearRadius;
    enemyPatrolSpeed = oth.enemyPatrolSpeed;
    playerMoveSpeed = oth.playerMoveSpeed;
    return *this;
}

bool GlobalParams::isKeyPressed(EventKeyboard::KeyCode code) {
    return GlobalParams::Instance().keys[code];
}
