#include "../GameObject.h"

class Button : public GameObject {

    private:
        int nextScene;
        int defaultFrame;
        int swapFrame;

    public:
        Button(std::string spritePath, int spriteRow, int spriteCol, float scale, int dframe, int sframe, int nextScene = -1);
        void update(float deltaTime);
        bool isClicked();
};