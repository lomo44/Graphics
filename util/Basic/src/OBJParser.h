#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>
#include "Vector.h"

//#include "Material.h"
enum eObjEntryType{
    eObjEntryType_Vertex,
    eObjEntryType_Normal,
    eObjEntryType_Face,
    eObjEntryType_GroupName,
    eObjEntryType_SmoothGroup,
    eObjEntryType_Unknown
};

class ObjectGroup;
class MeshObject;
class Triangle;
class OBJParser{
public:
    OBJParser();
    void parsefile(std::string filepath);
    void printParsedInformation();
    MeshObject* getOutputObject();
    ~OBJParser();
private:
    void clearBuffer();  
    std::vector<Vector4f> m_Vbuffer;
    std::vector<Vector4f> m_Nbuffer;
    std::vector<Vector4f> m_Tbuffer;
    std::vector<Triangle> m_Fbuffer;
    std::string m_CurrentGroup;
    int m_CurrentShadingNum;
};
