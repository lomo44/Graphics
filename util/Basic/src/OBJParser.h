#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>
#include "Vector.h"
#include "newClass.h"

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

class OBJParser{
public:
    OBJParser(){};
    void parsefile(std::string filepath);
    ~OBJParser(){};
private:
    void clearBuffer();  
    std::vector<Vector4f> m_Vbuffer;
    std::vector<Vector4f> m_Nbuffer;
    std::vector<Vector4f> m_Tbuffer;
    std::vector<ObjectGroup> m_Gbuffer;
    ObjectGroup m_CurrentGroup;
    MeshObject* m_pOutPutObject;
};
