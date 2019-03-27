layout (location = POSITION0) in vec3 aPos;

#ifdef NORMAL0
layout (location = NORMAL0) in vec3 aNormal;
#endif

#ifdef TEXCOORDNIATE0
layout (location = TEXCOORDNIATE0) in vec2 aUV;
#endif

out vec3 ourColor;
out vec2 TextCoord;

uniform mat4 u_MvpMatrix;

void main()
{
    gl_Position = u_MvpMatrix * vec4(aPos, 1.0);
    ourColor = vec3(1.0, 0.0, 0.0);
    TextCoord = aUV;
}
