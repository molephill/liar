out vec4 FragColor;

in vec3 ourColor;
in vec2 TextCoord;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
uniform Material material;

void main()
{
    //FragColor = vec4(ourColor, 1.0f);
    FragColor = texture(material.diffuse, TextCoord);
}
