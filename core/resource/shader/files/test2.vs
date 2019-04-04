layout (location = POSITION0) in vec3 aPos;

#ifdef NORMAL0
layout (location = NORMAL0) in vec3 aNormal;
#endif

#ifdef TEXCOORDNIATE0
layout (location = TEXCOORDNIATE0) in vec2 aUV;
#endif

#ifdef BONEINDICES0
layout (location = BONEINDICES0) in ivec4 aBoneIDs;
#endif

#ifdef BONEWEIGHTS0
layout (location = BONEWEIGHTS0) in vec4 aBoneWeights;
#endif

out vec3 ourColor;
out vec2 TextCoord;

uniform mat4 u_MvpMatrix;

#if defined(BONEINDICES0) || defined(BONEWEIGHTS0)
const int MAX_BONES = 100;
uniform mat4 gBones[MAX_BONES];
#endif

void main()
{
    gl_Position = u_MvpMatrix * vec4(aPos, 1.0);
    ourColor = vec3(1.0, 0.0, 0.0);
    TextCoord = aUV;
}
