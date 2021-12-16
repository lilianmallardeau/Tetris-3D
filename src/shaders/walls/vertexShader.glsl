#version 450 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;
out vec3 v_position;
out vec3 v_normal;
out vec2 v_texCoord;

uniform mat4 u_viewProjMatrix;
uniform mat4 u_transforms[1000];

void main() {
    vec4 worldPosition = u_transforms[gl_InstanceID] * vec4(position, 1.0f);
    gl_Position = u_viewProjMatrix * worldPosition;

    v_position = vec3(worldPosition);
    v_normal = normalize(mat3(transpose(inverse(u_transforms[gl_InstanceID]))) * normal);
    v_texCoord = texCoord;
}
