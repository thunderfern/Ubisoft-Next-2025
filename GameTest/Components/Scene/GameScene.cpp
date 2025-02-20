#include "stdafx.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

#include "GameScene.h"
#include "../GameObject/Tile/Tile.h"
#include "../GameObject/Line/Line.h"
#include "../Mouse/Mouse.h"
#include "../Physics/Physics.h"
#include "../Physics/Collision.h"
#include "SceneManager.h"
#include "../GameObject/Tile/UnlockTile.h"
#include "../GameObject/Tile/LockTile.h"
#include "../GameObject/Button/Button.h"

GameScene::GameScene(std::string levelPath, int nextScene, std::string playernum, int target, GameObject* levelcorr, Button* redoButton) {
    // setting the basic informatoin
    this->redoButton = redoButton;
    levelcheck = levelcorr;
    targetTurns = target;
    this->nextScene = nextScene;
    std::ifstream levelFile("Components/Scene/GameFiles/" + levelPath + ".txt");
    std::string curline;
    float curRow = 700.0f, curCol = 100.0f, rowInc = 0.0f, colInc = 0.0f;
    // reading in the tiles of the regular file and creating the tiles
    while (getline(levelFile, curline)) {
        std::stringstream ss(curline);
        char curnum;
        while (ss >> curnum) {
            if (curnum == '1') {
                // setting the golf ball specially
                golfBall = new GameObject("Assets/golfball.png", 1, 1, 0.025f);
                Collision *golfBallCol = new Collision(golfBall, CollisionShape::CIRCLE, golfBall->getWidth() / 2, golfBall->getHeight() / 2, 0.0f, 0.0f);
                golfBall->addCollision(golfBallCol);
                golfBall->setPos(curCol, curRow);
                curnum = 'f';
                golfstartx = curCol;
                golfstarty = curRow;
            }
            if (curnum == '2') {
                endGoal = new GameObject("Assets/golfhole.png", 1, 1, 0.025f);
                Collision *endGoalCol = new Collision(endGoal, CollisionShape::CIRCLE, endGoal->getWidth() / 2, endGoal->getHeight() / 2, 0.0f, 0.0f);
                endGoal->addCollision(endGoalCol);
                endGoal->setPos(curCol, curRow);
                curnum = 'f';
                
            }
            Tile *tile = new Tile(curnum - 'a', curCol, curRow);
            if (rowInc < 0.0001f) colInc = abs(tile->getWidth()), rowInc = abs(tile->getHeight());
            curCol += colInc;
            addObject(tile);
        }
        curCol = 100.0f;
        curRow -= rowInc;
    }
    levelFile.close();

    // adding the physics for the golf ball
    Physics *golfPhysics = new Physics(golfBall, PhysicsType::DYNAMIC, 1.0f, 0.0f, 0.0f, 0.0f);
    golfBall->setPhysics(golfPhysics);
    addObject(golfBall);
    if (endGoal != NULL) addObject(endGoal);
    line = new Line();
    addObject(line);

    // adding the necessary additions like text and line
    this->player = new Text(playernum);
    this->player->setPos(100.0f, 50.0f);
    this->levelName = new Text(levelPath);
    this->levelName->setPos(200.0f, 50.0f);
    this->turnText = new Text("Turn: " + std::to_string(turnNum));
    this->turnText->setPos(300.0f, 50.0f);
    Text* targetTurnsText = new Text("Target Turns: " + std::to_string(targetTurns));
    targetTurnsText->setPos(400.0f, 50.0f);
    addObject(player);
    addObject(levelName);
    addObject(turnText);
    addObject(targetTurnsText);
}

void GameScene::updateSubScene() {
    // checking if the redo button is clicked
    if (redoButton != NULL && redoButton->isClicked()) {
        resetScene();
        otherMap->resetScene();
    }
    // if the ball is moving
    if (golfBall->getPhysics()->speed >= 0.0001f) {
        // check if we move onto next level
        if (endGoal != NULL && golfBall->getCollisionList()[0]->colliding(endGoal->getCollisionList()[0])) {
            for (auto g : gameObjects) g->setState(true);
            SceneManager::instance()->nextScene = 1;
            if (targetTurns >= turnNum) levelcheck->setState(true);
            resetScene();
            otherMap->resetScene();
        }
        Collision *golfCollision = golfBall->getCollisionList()[0];
        // checking if we need to unlock some tiles
        for (auto u : unlockedTiles) {
            for (auto c : u->getCollisionList()) {
                if (golfCollision->colliding(c)) {
                    u->notifyTiles();
                    u->setState(false);
                }
            }
        }
        line->setState(false);
        return;
    }
    // if we have no shot left, swap the player
    if (shotsLeft == 0) {
        SceneManager::instance()->nextScene = nextScene;
        turnNum++;
        turnText->setText(("Turn: " + std::to_string(turnNum)));
        shotsLeft = 1;
    }
    line->setState(true);
    line->setPos(golfBall->getX(), golfBall->getY());
    line->setPos2(Mouse::instance()->getX(), Mouse::instance()->getY());
    // drawing the line for aim, if too much distance we don't let it go
    if (line->getDist() < 100.0f) {
        line->setColour(Colour::WHITE);
        if (Mouse::instance()->isClicked()) {
            // getting the xcomponent and ycomponent of the change and converting to polar coordinates to store in physics
            float xchange = Mouse::instance()->getX() - golfBall->getX(), ychange = Mouse::instance()->getY() - golfBall->getY();
            golfBall->getPhysics()->direction = atanf(ychange / xchange);
            golfBall->getPhysics()->speed = std::min(5.0f, sqrt(xchange * xchange + ychange * ychange) / 20);
            if (xchange < 0.0f) golfBall->getPhysics()->direction += 3.14f;
            shotsLeft--;
        }
    }
    else line->setColour(Colour::RED);
}

void GameScene::addLockTiles(std::string tilesPath) {
    std::ifstream levelFile("Components/Scene/GameFiles/" + tilesPath + ".txt");
    std::string curline;
    float curRow = 700.0f, curCol = 100.0f, rowInc = 0.0f, colInc = 0.0f;
    // adding all the locked tiles and unlocked tiles based off of what they need
    while (getline(levelFile, curline)) {
        std::stringstream ss(curline);
        char curnum;
        LockTile *ltile;
        UnlockTile *utile;
        // setting the increase amount to place the tiles
        if (rowInc < 0.0001f) {
            utile = new UnlockTile(TileColour::PURPLE);
            colInc = abs(utile->getWidth()), rowInc = abs(utile->getHeight());
            delete utile;
        }
        // setting the correct tiles
        while (ss >> curnum) {
            switch (curnum) {
                case '1':
                    ltile = new LockTile(TileColour::PURPLE);
                    ltile->setPos(curCol, curRow);
                    lockedTiles.push_back(ltile);
                    addObject(ltile);
                    break;
                case '2':
                    utile = new UnlockTile(TileColour::PURPLE);
                    utile->setPos(curCol, curRow);
                    unlockedTiles.push_back(utile);
                    addObject(utile);
                    break;
                case '3':
                    ltile = new LockTile(TileColour::ROUGE);
                    ltile->setPos(curCol, curRow);
                    lockedTiles.push_back(ltile);
                    addObject(ltile);
                    break;
                case '4':
                    utile = new UnlockTile(TileColour::ROUGE);
                    utile->setPos(curCol, curRow);
                    unlockedTiles.push_back(utile);
                    addObject(utile);
                    break;
                case '5':
                    ltile = new LockTile(TileColour::GREEN);
                    ltile->setPos(curCol, curRow);
                    lockedTiles.push_back(ltile);
                    addObject(ltile);
                    break;
                case '6':
                    utile = new UnlockTile(TileColour::GREEN);
                    utile->setPos(curCol, curRow);
                    unlockedTiles.push_back(utile);
                    addObject(utile);
                    break;
                case '7':
                    ltile = new LockTile(TileColour::BLUE);
                    ltile->setPos(curCol, curRow);
                    lockedTiles.push_back(ltile);
                    addObject(ltile);
                    break;
                case '8':
                    utile = new UnlockTile(TileColour::BLUE);
                    utile->setPos(curCol, curRow);
                    unlockedTiles.push_back(utile);
                    addObject(utile);
                    break;
                default:
                    break;

            }
            curCol += colInc;
        }
        curCol = 100.0f;
        curRow -= rowInc;
    }
    levelFile.close();
}

// adding the unlocked tiles to link with the locked tiles by adding them as observers
void GameScene::addLink(GameScene *other) {
    for (auto u : unlockedTiles) {
        for (auto l : other->lockedTiles) {
            if (u->getColour() == l->getColour()) u->addObserver(l);
        }
    }
}

// resetting the scene by resetting the golfball positions and putting everything back on screen
void GameScene::resetScene() {
    golfBall->setPos(golfstartx, golfstarty);
    golfBall->getPhysics()->speed = 0.0f;
    for (auto g : gameObjects) g->setState(true);
    turnNum = 0;
    turnText->setText(("Turn: " + std::to_string(turnNum)));
    shotsLeft = 1;
}

GameScene::~GameScene() {
    for (int i = 0; i < gameObjects.size(); i++) delete gameObjects[i];
}