#version 330 core
out vec4 FragColor;

in vec3 FragPos;

void main()
{
    FragColor = vec4(abs(FragPos.x) + 0.2, abs(FragPos.y) + 0.2, abs(FragPos.z) + 0.2, 1.0);
}