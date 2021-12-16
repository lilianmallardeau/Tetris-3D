#version 450 core

in vec3 v_position;
in vec3 v_normal;
in vec2 v_texCoord;
out vec4 color;

uniform vec3 u_color = vec3(0.0f);
uniform vec3 u_borderColor = vec3(0.0f, 0.0f, 0.0f);
uniform sampler2D u_texture;

float threshold = 0.02f;

bool isBorder(vec2 texCoord, float threshold) {
    return texCoord.s <= threshold || texCoord.s >= 1.0f-threshold || texCoord.t <= threshold || texCoord.t >= 1.0f-threshold;
}
bool isBorder(vec2 texCoord) {
    return isBorder(texCoord, threshold);
}

void main() {
    if (isBorder(v_texCoord, 0.02f)) {
        color = vec4(u_borderColor, 1.0f);
    } else {
        color = vec4(vec3(0.5f*vec4(u_color, 0.5f) + 0.5f*texture(u_texture, v_texCoord)), 1.0f);
//        color = vec4(0.0f, 0.0f, 0.0f, 0.0f);
    }
}
