#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TextureCoordinate;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixSetting;

void main()
{
    FragColor = mix(texture(texture1, TextureCoordinate), texture(texture2, TextureCoordinate), mixSetting);
}
