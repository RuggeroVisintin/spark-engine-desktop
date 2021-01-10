#include <unordered_map>
#include "MeshResource.h"
#include <Assertion/Assert.h>
#include <Time/Win32/Win32HiResTimer.h>

namespace SE
{
	namespace resource
	{
		void Mesh::deSerialize(const SE::core::parser::binary::spk::SpkMesh& mesh)
		{
			mVertices.assign((MeshVertex*)mesh.meshData.vertices, (MeshVertex*)mesh.meshData.vertices + mesh.meshInfo.verticesCount);
			mIndices.assign((unsigned int*)mesh.meshData.indices, (unsigned int*)mesh.meshData.indices + mesh.meshInfo.indicesCount);

			mName = mesh.meshInfo.name;
		}

		void Mesh::loadFromObj(const SE::core::parser::text::wavefront::ObjMesh& mesh, const std::string& name)
		{
			mName = name;

			mVertices.resize(mesh.getTotalTrianglesCount() * 3);
			mIndices.resize(mesh.getTotalTrianglesCount() * 3);

			int count = 0;

			for (int j = 0; j < mesh.getGeometriesCount(); j++) {
				for (int i = 0; i < mesh.getGeometries()[j].getTrianglesCount(); i++) {
					MeshVertex tempVertex;

					tempVertex.position = mesh.getGeometries()[j].getPositions()[mesh.getGeometries()[j].getTriangles()[i].pos[0]];
					tempVertex.normal = mesh.getGeometries()[j].getNormals()[mesh.getGeometries()[j].getTriangles()[i].nor[0]];
					//tempVertex.uv = mesh.getGeometries()[j].getTexCoords()[mesh.getGeometries()[j].getTriangles()[i].txc[0]];

					mVertices[(count * 3)] = tempVertex;

					tempVertex.position = mesh.getGeometries()[j].getPositions()[mesh.getGeometries()[j].getTriangles()[i].pos[1]];
					tempVertex.normal = mesh.getGeometries()[j].getNormals()[mesh.getGeometries()[j].getTriangles()[i].nor[1]];
					//tempVertex.uv = mesh.getGeometries()[j].getTexCoords()[mesh.getGeometries()[j].getTriangles()[i].txc[1]];

					mVertices[(count * 3) + 1] = tempVertex;

					tempVertex.position = mesh.getGeometries()[j].getPositions()[mesh.getGeometries()[j].getTriangles()[i].pos[2]];
					tempVertex.normal = mesh.getGeometries()[j].getNormals()[mesh.getGeometries()[j].getTriangles()[i].nor[2]];
					//tempVertex.uv = mesh.getGeometries()[j].getTexCoords()[mesh.getGeometries()[j].getTriangles()[i].txc[2]];

					mVertices[(count * 3) + 2] = tempVertex;

					count++;
				}
			}

			// NEW VERSION
			optimize();
		}

		void Mesh::initGpuResources(SE::platform::backend::GLDevice* graphicsDevice) {
			SPARK_ASSERT(graphicsDevice, "Mesh::initGpuResources - @param graphicsDevice - is empty");

			if (mIndexBuffer.isNull()) {
				mIndexBuffer = graphicsDevice->createIndexBuffer();
			}

			graphicsDevice->bindIndexBuffer(mIndexBuffer);
			graphicsDevice->fillIndexBuffer(mIndices.size() * sizeof(mIndices[0]), mIndices.data(), GL_STATIC_DRAW);
			graphicsDevice->unbindIndexBuffer();

			if (mVertexBuffer.isNull()) {
				mVertexBuffer = graphicsDevice->createVertexBuffer();
			}

			graphicsDevice->bindVertexBuffer(mVertexBuffer);

			// keep it hard-coded for now
			graphicsDevice->enableVertexAttributeArray(0);
			graphicsDevice->defineVertexAttributePointer(0, 3, GL_FLOAT, false, sizeof(float) * 8, 0);

			graphicsDevice->enableVertexAttributeArray(1);
			graphicsDevice->defineVertexAttributePointer(1, 3, GL_FLOAT, false, sizeof(float) * 8, (const GLvoid*)(sizeof(float) * 3));

			graphicsDevice->enableVertexAttributeArray(2);
			graphicsDevice->defineVertexAttributePointer(2, 3, GL_FLOAT, false, sizeof(float) * 8, (const GLvoid*)(sizeof(float) * 6));

			graphicsDevice->fillVertexBuffer(mVertices.size() * sizeof(mVertices[0]), mVertices.data(), GL_STATIC_DRAW);
			graphicsDevice->unbindVertexBuffer();

			if (keepDataCached == false)
			{
				mVertices.clear();
				mIndices.clear();

				mVertices.reserve(0);
				mIndices.reserve(0);
			}
		}

		void Mesh::optimize()
		{
			std::vector<MeshVertex> tempVertices = mVertices;
			mVertices.clear();
			mVertices.reserve(tempVertices.size());

			std::unordered_map<MeshVertex, int, MeshVertexHash> uniqueVertices;

			for (int i = 0, count = tempVertices.size(); i < count; ++i)
			{
				MeshVertex vertex = tempVertices[i];
				int id = mVertices.size();
				auto result = uniqueVertices.insert(std::pair<MeshVertex, int>(vertex, id));

				if (result.second)
				{
					mIndices.push_back(id);
					mVertices.push_back(vertex);
				}
				else
				{
					mIndices.push_back(result.first->second); // result.first è un iteratore
				}
			}

			mIndicesCount = mIndices.size();
			mVerticesCount = mVertices.size();
		}
	}
}