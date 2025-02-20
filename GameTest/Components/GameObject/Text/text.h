#include "../GameObject.h"

#include <string>

#ifndef Text_h
#define Text_h

class Text : public GameObject {

    protected:
        std::string text;
    
    public:
        Text(std::string txt);
        std::string getText();
        void setText(std::string txt);

};
#endif