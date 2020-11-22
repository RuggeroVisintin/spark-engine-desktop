#ifndef __MESHRESOURCE_H__
#define __MESHRESOURCE_H__

// c++ libraries
#include <vector>

// resources
#include "../Resource.h"
#include "../ResourceHandle.h"

// file system
#include <FileSystem/File.h>

// math structures
#include <math/Vec3.h>
#include <math/Vec2.h>

// gfx
#include <GFX/OpenGL/GLTypes.h>
#include <GFX/OpenGL/GLDevice.h>

// parsers
#include <Parsers/spk/SpkParser.h>
#include <Parsers/obj/ObjMesh.h>

// smart pointers 
#include <SmartPtrs/SharedPtr.h>

namespace SE
{
	namespace resource
	{
		class Mesh : public IResource
		{
			friend class MeshManager;
			typedef IResource Super;

		public:
			struct Geometry
			{
				unsigned int*								startIndex;
				unsigned int								indicesCount;

				ResourceHandle								materialHandle;
				//SE::resource::material::PMaterialResource	material;
			};

			class MeshVertex
			{
				// position, position, position, normal, normal, normal, uv, uv
			public:
				SE::core::math::Vec3<float>	position;
				SE::core::math::Vec3<float>	normal;
				SE::core::math::Vec2<float>	uv;

			public:
				bool operator==(const MeshVertex& meshVertex) const
				{
					return position == meshVertex.position && normal == meshVertex.normal && uv == meshVertex.uv;
				}

				bool operator!=(const MeshVertex& meshVertex) const
				{
					return position != meshVertex.position || normal != meshVertex.normal || uv == meshVertex.uv;
				}
			};

			struct MeshVertexHash {
				size_t operator()(const MeshVertex &o) const {
					return std::hash<float>()(o.position.getX()) ^ std::hash<float>()(o.position.getY())
						^ std::hash<float>()(o.position.getZ()) ^ std::hash<float>()(o.normal.getX())
						^ std::hash<float>()(o.normal.getY()) ^ std::hash<float>()(o.position.getZ())
						^ std::hash<float>()(o.uv.getX()) ^ std::hash<float>()(o.uv.getY());
				}
			};

		public:
			Mesh()
			{
				keepDataCached = true;
			}

			Mesh(const std::vector<MeshVertex>& vertices)
			{
				mVertices = vertices;
				keepDataCached = true;
			}

			Mesh(const std::vector<unsigned int>& indices)
			{
				mIndices = indices;
				keepDataCached = true;
			}

			Mesh
			(const std::vector<MeshVertex>& vertices,
				const std::vector<unsigned int>& indices)
			{
				mVertices = vertices;
				mIndices = indices;
				keepDataCached = true;
			}

			~Mesh() {}

		public:
			//void											serialize(SpkMesh& mesh);
			void											deSerialize(const SE::core::parser::binary::spk::SpkMesh& mesh);
			void											loadFromObj(const SE::core::parser::text::wavefront::ObjMesh& mesh);

			void											initGpuResources(SE::platform::backend::GLDevice* graphicsDevice);
			//void											freeGpuResources(SE::platform::beckend::GLDevice* graphicsDevice);

			void											optimize();

			void											setVertices(const std::vector<MeshVertex>& vertices) { mVertices = vertices; mVerticesCount = mVertices.size(); }
			const std::vector<MeshVertex>&					getVertices() const { return mVertices; }

			void											setIndices(const std::vector<unsigned int>& indices) { mIndices = indices; mIndicesCount = mIndices.size(); }
			const std::vector<unsigned int>&				getIndices() const { return mIndices; }

			void											setGeometries(const std::vector<Geometry>& geometries) { mGeometries = geometries; }
			const std::vector<Geometry>&					getGeometries() const { return mGeometries; }

			SE::platform::backend::GLVertexBufferHandle		getVertexBuffer() const { return mVertexBuffer; }
			SE::platform::backend::GLIndexBufferHandle		getIndexBuffer() const { return mIndexBuffer; }

			unsigned int									getVerticesCount() const { return mVerticesCount; }
			unsigned int									getIndicesCount() const { return mIndicesCount; }

		private:
			std::vector<MeshVertex>							mVertices;
			std::vector<unsigned int>						mIndices;
			std::vector<Geometry>							mGeometries;

			SE::platform::backend::GLVertexBufferHandle		mVertexBuffer;
			SE::platform::backend::GLIndexBufferHandle		mIndexBuffer;

			unsigned int									mIndicesCount;
			unsigned int									mVerticesCount;

		public:
			/**
			* @brief - defines whether the mesh has to be stored on RAM or not
			* @value - true to keep data on RAM, false to delete them when they are sent to GPU
			*/
			bool											keepDataCached;
		};

		typedef SE::core::memory::SharedPtr<Mesh> PMeshResource;
	}

}

#endif // !__MESHRESOURCE_H__