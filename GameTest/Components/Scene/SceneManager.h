
#include <vector>

class Scene;

class SceneManager {

    public:

        std::vector<Scene *> scenes;
        Scene* currentScene;
        int nextScene;

        static SceneManager* instance();
    
    private:
        
        SceneManager();
};