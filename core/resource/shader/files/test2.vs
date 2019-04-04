layout (location = POSITION0) in vec3 aPos;

#ifdef NORMAL0
layout (location = NORMAL0) in vec3 aNormal;
#endif

#ifdef TEXCOORDNIATE0
layout (location = TEXCOORDNIATE0) in vec2 aUV;
#endif

#ifdef BONEINDICES0
layout (location = BONEINDICES0) in vec4 a_BoneIndices;
#endif

#ifdef BONEWEIGHTS0
layout (location = BONEWEIGHTS0) in vec4 a_BoneWeights;
#endif

out vec3 ourColor;
out vec2 TextCoord;

uniform mat4 u_MvpMatrix;

#if defined(BONEINDICES0) || defined(BONEWEIGHTS0)
const int MAX_BONES = 100;
uniform mat4 u_Bones[MAX_BONES];
#endif

void main()
{
#if defined(BONEINDICES0) || defined(BONEWEIGHTS0)
	mat4 skinTransform=mat4(0.0);
	skinTransform += u_Bones[int(a_BoneIndices.x)] * a_BoneWeights.x;
	skinTransform += u_Bones[int(a_BoneIndices.y)] * a_BoneWeights.y;
	skinTransform += u_Bones[int(a_BoneIndices.z)] * a_BoneWeights.z;
	skinTransform += u_Bones[int(a_BoneIndices.w)] * a_BoneWeights.w;
	vec4 position=skinTransform * vec4(aPos, 1.0);
	gl_Position = u_MvpMatrix * position;
#else
	gl_Position = u_MvpMatrix * vec4(aPos, 1.0);
#endif
    ourColor = vec3(1.0, 0.0, 0.0);
    TextCoord = aUV;
}
