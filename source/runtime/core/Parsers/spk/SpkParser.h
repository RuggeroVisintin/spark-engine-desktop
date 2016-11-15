#ifndef __SPKPARSER_H__
#define __SPKPARSER_H__

#include <vector>
#include <string>
#include <cstdint>
#include "../../math/Vec3.h"

#include <FileSystem/FileSystem.h>
#include <FileSystem/File.h>

namespace SE
{
    namespace core
    {
        namespace parser
        {
            namespace binary
            {
                namespace spk
                {
                    struct SpkMesh 
                    {
                    	struct SpkMeshInfo
                    	{
                    		char							name[64];
                    		uint32_t						verticesCount;
                    		uint32_t						indicesCount;
                    		uint64_t						dataLength;
                    	};
                    
                    	struct SpkMeshData
                    	{
                    		struct SpkMeshVertex
                    		{
                    			typedef math::Vec3<float>			Position;
								typedef math::Vec3<float>			Normal;
								typedef math::Vec3<float>			Uv;
                    
                    			Position					position;
                    			Normal						normal;
                    			Uv							uv;
                    		};
                    
                    		SpkMeshVertex*					vertices;
                    		uint32_t*						indices;
                    	};
                    
                    	SpkMeshInfo							meshInfo;
                    	SpkMeshData							meshData;
                    
                    	uint64_t							getDataLength() const
                    	{
                    		return		sizeof(SpkMeshInfo) + 
                    					sizeof(SpkMeshData::SpkMeshVertex) * meshInfo.verticesCount + 
                    					sizeof(uint32_t) * meshInfo.indicesCount;
                    	}
                    };
                    
                    class SpkParser
                    {
                    private:
                    	struct SpkFileHeader
                    	{
                    		char						magic[6];
                    		uint16_t					version;
                    		uint64_t					dataLength;
                    	};
                    
                    public:
                    	SpkParser();
                    	~SpkParser();
                    
                    public:
						bool						writeMesh(const SpkMesh& spkMesh, SE::platform::filesystem::OsFile* fileHandle);
						bool						readMesh(SpkMesh& spkMesh, SE::platform::filesystem::OsFile* fileHandle);
                    
                    };
                }
            }
        }
    }
}


#endif // !__SPKPARSER_H__