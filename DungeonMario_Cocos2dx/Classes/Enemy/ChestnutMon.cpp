//
//  ChestnutMon.cpp
//  DungeonMario
//
//  Created by Marshall Wang on 2017/7/8.
//
//

#include "ChestnutMon.hpp"

void ChestnutMon::initSprite() {
    
}

void ChestnutMon::startPlaying() {
    
}

void ChestnutMon::onContactWithPlayer(PhysicsBody* chestnut, MarioPlayer* player) {
    /**
     * get Player Instance from GlobalParams::Instance()
     *
     * judge : if stepped by Player => go die
     *         if just collision => player go die, restart
     */
    log("Turtle Contact With Player");
    auto chestnutBoundingBox = chestnut->getOwner()->getBoundingBox();
    auto playerBoundingBox = player->getPlayerSprite()->getBoundingBox();
    
    // if stepped by Player
    if (chestnutBoundingBox.getMaxY() <= playerBoundingBox.getMinY()) {
        chestnut->getOwner()->removeFromParent();
    } else {
        player->getHurt();
    }
}
