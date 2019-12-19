#version 330 core
const int NB_BONES = 2;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 weights;

out vec3 FragPos;
out vec3 Normal;
out vec4 FragPosLightSpace;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;
uniform mat4 lightSpaceMatrix;

uniform bool drawAnimation;
uniform mat4 D[NB_BONES];
uniform mat4 U_inv[NB_BONES];

void main()
{
    if (drawAnimation){
        vec4 newVertex = vec4(0.0);
        vec4 newNormal = vec4(0.0);
        for (int i = 0; i < NB_BONES; ++i){
            newVertex += weights[i]*D[i]* model*U_inv[i] * vec4(aPos, 1.0);
        }
        FragPos = newVertex.xyz;
    } else {
        FragPos = vec3(model * vec4(aPos, 1.0));
    }

    Normal = mat3(transpose(inverse(model))) * aNormal;
    FragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0);
    gl_Position = projection * view * vec4(FragPos, 1.0);
}

