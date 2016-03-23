#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>
#include "Vector.h"
#include "MeshObject.h"
enum eObjEntryType{
    eObjEntryType_Vertex,
    eObjEntryType_Normal,
    eObjEntryType_Face,
    eObjEntryType_GroupName,
    eObjEntryType_SmoothGroup,
    eObjEntryType_Unknown
};


class OBJParser{
public:
    OBJParser(){};
    void parsefile(std::string filepath);
    ~OBJParser(){};
private:
    void clearBuffer();
    void parseVertex(std::stringstream& ss);
    void parseNormal(std::stringstream& ss);
    void parseTexture(std::stringstream& ss);
    void parseFace(std::stringstream& ss);
    void parseGroup(std::stringstream& ss);
    
    std::vector<Vector4f> m_Vbuffer;
    std::vector<Vector4f> m_Nbuffer;
    std::vector<Vector4f> m_Tbuffer;
    std::vector<Vector4f> m_Fbuffer;
    MeshObjectSet* m_pOutPutObject;
};
