#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>

class Model
{
private:
    //Attribute
    std::vector<float> m_position_texture_normal;
    int m_sz;
    //Function
    std::vector<std::string> splitString(std::string str, char delimiter);
    float getFloat(std::string input);
    int getInt(std::string input);
public:
    Model(std::string objFilePath);
    ~Model();
    void Draw();
   
};

#endif
