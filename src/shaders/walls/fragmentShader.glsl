#version 450 core

in vec3 v_position;
in vec3 v_normal;
in vec2 v_texCoord;
out vec4 color;

uniform vec3 u_color = vec3(0.0f);
uniform vec3 u_borderColor = vec3(0.0f, 0.0f, 0.0f);
uniform sampler2D u_texture;

// Phong
uniform vec3 u_lightPosition;
uniform vec3 u_cameraPosition;
uniform vec3 u_lightColor = vec3(1.0f, 1.0f, 1.0f);
uniform float u_ambiantIntensity = 0.4f;
uniform float u_diffuseIntensity = 1.0f;
uniform float u_specularIntensity = 0.5f;
uniform float alpha = 32;

float borderThreshold = 0.02f;

bool isBorder(vec2 texCoord, float borderThreshold) {
    return texCoord.s <= borderThreshold || texCoord.s >= 1.0f-borderThreshold || texCoord.t <= borderThreshold || texCoord.t >= 1.0f-borderThreshold;
}
bool isBorder(vec2 texCoord) {
    return isBorder(texCoord, borderThreshold);
}

vec3 phong() {
    vec3 ambiant, diffuse, specular;
    vec3 lightDirection = normalize(u_lightPosition - v_position);
    vec3 cameraDirection = normalize(u_cameraPosition - v_position);

    // Ambiant lighting
    ambiant = vec3(u_ambiantIntensity) * u_lightColor;

    // Diffuse lighting
    diffuse = u_diffuseIntensity * max(dot(v_normal, lightDirection), 0.0f) * u_lightColor;

    // Specular lighting
    vec3 reflected_ray = reflect(-lightDirection, v_normal);
    specular = u_specularIntensity * pow(max(dot(cameraDirection, reflected_ray), 0.0f), alpha) * u_lightColor;

    vec3 phong = ambiant + diffuse + specular;
    return phong;
}

void main() {
    if (isBorder(v_texCoord, 0.02f)) {
        color = vec4(u_borderColor, 1.0f);
    } else {
        color = vec4(vec3(0.5f*vec4(u_color, 0.5f) + 0.5f*texture(u_texture, v_texCoord)), 1.0f);
//        color = vec4(0.0f, 0.0f, 0.0f, 0.0f);
    }
    color = vec4(phong() * color.rgb, color.a);
}
