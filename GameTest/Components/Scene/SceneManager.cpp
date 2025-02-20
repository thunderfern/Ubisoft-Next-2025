#include "stdafx.h"

#include "SceneManager.h"
#include "Scene.h"

SceneManager::SceneManager() {}

SceneManager* SceneManager::instance() {
    static SceneManager *instance = new SceneManager();
    return instance;
}