#version 450 core

in vec3 v_position;
in vec3 v_normal;
in vec2 v_texCoord;
flat in uint v_instanceID;
out vec4 color;

uniform vec3 u_slicesColors[1000];
uniform vec3 u_solidBlocksBorderColor = vec3(0.3f, 0.3f, 0.3f);
uniform vec3 u_activeBlockBorderColor = vec3(1.0f, 1.0f, 1.0f);
uniform sampler2D u_texture;
uniform bool u_drawActiveBlock = false;

float threshold = 0.02f;

bool isBorder(vec2 texCoord, float threshold) {
    return texCoord.s <= threshold || texCoord.s >= 1.0f-threshold || texCoord.t <= threshold || texCoord.t >= 1.0f-threshold;
}
bool isBorder(vec2 texCoord) {
    return isBorder(texCoord, threshold);
}

void main() {
    if (!u_drawActiveBlock) {
        if (isBorder(v_texCoord, 0.01f)) {
            color = vec4(u_solidBlocksBorderColor, 1.0f);
        } else {
            color = vec4(vec3(0.6f*vec4(u_slicesColors[v_instanceID], 0.6f) + 0.4f*texture(u_texture, v_texCoord)), 1.0f);
        }
    } else {
        if (isBorder(v_texCoord)) {
            color = vec4(u_activeBlockBorderColor, 1.0f);
        } else {
            color = vec4(1.0f, 1.0f, 1.0f, 0.5f);
        }
    }
}
