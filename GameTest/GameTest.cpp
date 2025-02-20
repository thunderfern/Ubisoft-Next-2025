///////////////////////////////////////////////////////////////////////////////
// Filename: GameTest.cpp
// Provides a demo of how to use the API
///////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>
#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
//------------------------------------------------------------------------
#include "App\app.h"
//------------------------------------------------------------------------

// Including the required libraries
#include "Components/GameObject/GameObject.h"
#include "Components/Camera/Camera.h"
#include "Components/Physics/Collision.h"
#include "Components/Physics/Physics.h"
#include "Components/Scene/Scene.h"
#include "Components/GameObject/Button/Button.h"

#include "Components/Scene/SceneManager.h"
#include "Components/Scene/DisplayScene.h"
#include "Components/Scene/GameScene.h"

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------


void Init() {

    std::vector<Scene *> scenes;

    // start screen
    DisplayScene* startScreen = new DisplayScene();
    Button* playButton = new Button("Assets/playbutton.png", 1, 2, 0.25f, 0, 1, 1);
    playButton->setPos(500.0f, 150.0f);
    GameObject *title = new GameObject("Assets/title.png", 1, 1, 0.5f);
    title->setPos(500.0f, 600.0f);
    startScreen->addObject(playButton);
    startScreen->addObject(title);
    scenes.push_back(startScreen);

    // menu screen
    DisplayScene* levelscreen = new DisplayScene();
    Button* level1button = new Button("Assets/levelscene.png", 4, 2, 0.75f, 0, 4, 2);
    level1button->setPos(150.0, 400.0);
    Button* level2button = new Button("Assets/levelscene.png", 4, 2, 0.75f, 1, 5, 4);
    level2button->getSprite()->SetFrame(1);
    level2button->setPos(375.0, 400.0);
    Button* level3button = new Button("Assets/levelscene.png", 4, 2, 0.75f, 2, 6, 6);
    level3button->getSprite()->SetFrame(2);
    level3button->setPos(600.0, 400.0);
    Button* level4button = new Button("Assets/levelscene.png", 4, 2, 0.75f, 3, 7, 8);
    level4button->getSprite()->SetFrame(3);
    level4button->setPos(825.0, 400.0);
    levelscreen->addObject(level1button);
    levelscreen->addObject(level2button);
    levelscreen->addObject(level3button);
    levelscreen->addObject(level4button);
    GameObject *level1check = new GameObject("Assets/checkmark.png", 1, 1, 0.1f);
    level1check->setPos(150.0, 250.0);
    level1check->setState(false);
    GameObject *level2check = new GameObject("Assets/checkmark.png", 1, 1, 0.1f);
    level2check->setPos(375.0, 250.0);
    level2check->setState(false);
    GameObject *level3check = new GameObject("Assets/checkmark.png", 1, 1, 0.1f);
    level3check->setPos(600.0, 250.0);
    level3check->setState(false);
    GameObject *level4check = new GameObject("Assets/checkmark.png", 1, 1, 0.1f);
    level4check->setPos(825.0, 250.0);
    level4check->setState(false);
    levelscreen->addObject(level1check);
    levelscreen->addObject(level2check);
    levelscreen->addObject(level3check);
    levelscreen->addObject(level4check);
    scenes.push_back(levelscreen);
    
    Button *redoButton = new Button("Assets/redobutton.png", 1, 1, 0.1f, 0, 0, -1);
    redoButton->setPos(800.0f, 100.0f);

    Button *homeButton = new Button("Assets/homebutton.png", 1, 1, 0.1f, 0, 0, 1);
    homeButton->setPos(900.0f, 100.0f);

    // level 1a
    GameScene *level1a = new GameScene("Level 1a", 3, "Player 1", 2, level1check, redoButton);
    level1a->addObject(homeButton);
    level1a->addObject(redoButton);
    scenes.push_back(level1a);

    // level 1b
    GameScene *level1b = new GameScene("Level 1b", 2, "Player 2", 2, level1check, NULL);
    scenes.push_back(level1b);

    level1a->addLockTiles("Level 1 lock a");
    level1b->addLockTiles("Level 1 lock b");

    level1a->setOtherMap(level1b);
    level1b->setOtherMap(level1a);

    level1a->addLink(level1b);
    level1b->addLink(level1a);

    // level 2a
    GameScene *level2a = new GameScene("Level 2a", 5, "Player 1", 2, level2check, redoButton);
    level2a->addObject(homeButton);
    level2a->addObject(redoButton);
    scenes.push_back(level2a);

    // level 2b
    GameScene *level2b = new GameScene("Level 2b", 4, "Player 2", 2, level2check, NULL);
    scenes.push_back(level2b);

    level2a->addLockTiles("Level 2 lock a");
    level2b->addLockTiles("Level 2 lock b");

    level2a->setOtherMap(level2b);
    level2b->setOtherMap(level2a);

    level2a->addLink(level2b);
    level2b->addLink(level2a);

    // level 3a
    GameScene *level3a = new GameScene("Level 3a", 7, "Player 1", 3, level3check, redoButton);
    level3a->addObject(homeButton);
    level3a->addObject(redoButton);
    scenes.push_back(level3a);

    // level 3b
    GameScene *level3b = new GameScene("Level 3b", 6, "Player 2", 3, level3check, NULL);
    scenes.push_back(level3b);

    level3a->addLockTiles("Level 3 lock a");
    level3b->addLockTiles("Level 3 lock b");

    level3a->setOtherMap(level3b);
    level3b->setOtherMap(level3a);

    level3a->addLink(level3b);
    level3b->addLink(level3a);

    // level 4a
    GameScene *level4a = new GameScene("Level 4a", 9, "Player 1", 3, level4check, redoButton);
    level4a->addObject(homeButton);
    level4a->addObject(redoButton);
    scenes.push_back(level4a);

    // level 4b
    GameScene *level4b = new GameScene("Level 4b", 8, "Player 2", 3, level4check, NULL);
    scenes.push_back(level4b);

    level4a->addLockTiles("Level 4 lock a");
    level4b->addLockTiles("Level 4 lock b");

    level4a->setOtherMap(level4b);
    level4b->setOtherMap(level4a);

    level4a->addLink(level4b);
    level4b->addLink(level4a);

    SceneManager *sceneManager = SceneManager::instance();
    sceneManager->currentScene = startScreen;
    sceneManager->nextScene = 0;
    sceneManager->scenes = scenes;

}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(const float deltaTime) {
    SceneManager *sceneManager = SceneManager::instance();
    sceneManager->currentScene->updateScene(deltaTime);
    sceneManager->currentScene = sceneManager->scenes[sceneManager->nextScene];
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render() {	
    SceneManager *sceneManager = SceneManager::instance();
    sceneManager->currentScene->renderObjects();
}

//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown() {	
	//------------------------------------------------------------------------
	// Example Sprite Code....
    SceneManager *sceneManager = SceneManager::instance();
    for (int i = 0; i < sceneManager->scenes.size(); i++) delete sceneManager->scenes[i];
	//delete testSprite;
	//------------------------------------------------------------------------
}