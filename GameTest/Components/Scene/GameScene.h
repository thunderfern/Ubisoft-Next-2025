#include "Scene.h"
#include "../GameObject/Text/text.h"

#include <string>
#include <vector>

class Line;
class UnlockTile;
class LockTile;
class Button;

#ifndef GameScene_h
#define GameScene_h

class GameScene : public Scene {

    private:
        GameScene* otherMap;
        GameObject* golfBall;
        GameObject* endGoal;
        float golfstartx;
        float golfstarty;
        Text* player;
        Text* levelName;
        Text* turnText;
        int nextScene;
        int shotsLeft;
        int turnNum;
        int targetTurns;
        Line *line;
        void updateSubScene();
        std::vector<UnlockTile*> unlockedTiles;
        std::vector<LockTile*> lockedTiles;
        GameObject* levelcheck;
        Button* redoButton;
    public:
        GameScene(std::string levelPath, int nextScene, std::string playername, int target, GameObject* levelcorr, Button *redoButton);
        void setOtherMap(GameScene *oMap) { otherMap = oMap; }
        void addLockTiles(std::string tilesPath);
        void addLink(GameScene *other);
        void resetScene();
        ~GameScene();
};
#endif