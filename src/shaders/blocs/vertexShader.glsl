#version 450 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;
out vec3 v_position;
out vec3 v_normal;
out vec2 v_texCoord;
out uint v_instanceID;

uniform mat4 u_viewProjMatrix;
uniform vec3 u_translations[1000];

void main() {
    vec4 worldPosition = vec4(position + u_translations[gl_InstanceID], 1.0f);
    gl_Position = u_viewProjMatrix * worldPosition;

    v_position = vec3(worldPosition);
    v_normal = normal;
    v_texCoord = texCoord;
    v_instanceID = gl_InstanceID;
}
