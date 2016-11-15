#include "SpkParser.h"
#include <iostream>

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
                    SpkParser::SpkParser()
                    {
                    
                    }
                    
                    SpkParser::~SpkParser()
                    {
                    
                    }
                    
                    bool SpkParser::writeMesh(const SpkMesh& spkMesh, SE::platform::filesystem::OsFile* fileHandle)
                    {
                    	if (!fileHandle || fileHandle->isReadOnly()) {
                    		return false;
                    	}
                    
						fileHandle->seekBegin(0);
                    	SpkFileHeader tempHeader;
                    
                    	tempHeader.magic[0] = 'S';
                    	tempHeader.magic[1] = 'P';
                    	tempHeader.magic[2] = 'K';
                    	tempHeader.magic[3] = 'M';
                    	tempHeader.magic[4] = 'S';
                    	tempHeader.magic[5] = 'H';
                    
                    	tempHeader.version = 100;
                    
                    	tempHeader.dataLength = sizeof(SpkFileHeader) + spkMesh.getDataLength();
                    	SpkMesh::SpkMeshInfo info = spkMesh.meshInfo;
                    	info.dataLength = spkMesh.getDataLength();
                    
                    	fileHandle->write(&tempHeader, sizeof(SpkFileHeader));
                    	fileHandle->write(&info, sizeof(SpkMesh::SpkMeshInfo));
                    
                    	if (spkMesh.meshInfo.verticesCount > 0) {
                    		fileHandle->write(spkMesh.meshData.vertices, spkMesh.meshInfo.verticesCount * sizeof(SpkMesh::SpkMeshData::SpkMeshVertex));
                    	}
                    
                    	if (spkMesh.meshInfo.indicesCount > 0) {
                    		fileHandle->write(spkMesh.meshData.indices, spkMesh.meshInfo.indicesCount * sizeof(uint32_t));
                    	}
                    
                    	return true;
                    }
                    
                    bool SpkParser::readMesh(SpkMesh& spkMesh, SE::platform::filesystem::OsFile* fileHandle)
                    {
                    	if (!fileHandle || fileHandle->isWriteOnly()) {
                    		return false;
                    	}
                    
                    	fileHandle->seekBegin(0);                    
                    	SpkFileHeader tempHeader;
                    
                    	fileHandle->read(&tempHeader, sizeof(SpkFileHeader));
                    	fileHandle->read(&spkMesh.meshInfo, sizeof(SpkMesh::SpkMeshInfo));
                    
                    	if (spkMesh.meshInfo.verticesCount > 0) {
                    		spkMesh.meshData.vertices = (SpkMesh::SpkMeshData::SpkMeshVertex*)malloc(spkMesh.meshInfo.verticesCount * sizeof(SpkMesh::SpkMeshData::SpkMeshVertex));
                    	}
                    
                    	if (spkMesh.meshInfo.indicesCount > 0) {
                    		spkMesh.meshData.indices = (uint32_t*)malloc(spkMesh.meshInfo.indicesCount * sizeof(uint32_t));
                    	}
                    
                    	fileHandle->read(spkMesh.meshData.vertices, spkMesh.meshInfo.verticesCount * sizeof(SpkMesh::SpkMeshData::SpkMeshVertex));
                    	fileHandle->read(spkMesh.meshData.indices, spkMesh.meshInfo.indicesCount * sizeof(uint32_t));
                    }
                }
            }
        }
    }
}