#version 450

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 vp;

layout(location = 0) in vec3 input_position;
layout(location = 1) in vec4 input_color;
layout(location = 2) in vec2 input_tex_coord;
layout(location = 3) in vec3 input_normal;

out vec4 v_color;
out vec2 tex_coord;
out vec3 Position_worldspace;
out vec3 Normal_cameraspace;
out vec3 EyeDirection_cameraspace;
out vec3 LightDirection_cameraspace;


void main(){
    gl_Position = vp * model * vec4(input_position, 1.0f);

    // http://www.opengl-tutorial.org/beginners-tutorials/tutorial-8-basic-shading/ 
    // Position of the vertex, in worldspace : M * position
    Position_worldspace = (model * vec4(input_position,1)).xyz;

    // Vector that goes from the vertex to the camera, in camera space.
    // In camera space, the camera is at the origin (0,0,0).
    vec3 vertexPosition_cameraspace = ( view * model * vec4(input_position,1)).xyz;
    EyeDirection_cameraspace = vec3(0,0,0) - vertexPosition_cameraspace;

    vec3 LightPosition_worldspace = vec3(2,0,0);

    // Vector that goes from the vertex to the light, in camera space. M is ommited because it's identity.
    vec3 LightPosition_cameraspace = ( view * vec4(LightPosition_worldspace,1)).xyz;
    LightDirection_cameraspace = LightPosition_cameraspace + EyeDirection_cameraspace;

    // Normal of the the vertex, in camera space
    Normal_cameraspace = ( view * model * vec4(input_normal,0)).xyz; // Only correct if ModelMatrix does not scale the model ! Use its inverse transpose if not.

    v_color = input_color;
    tex_coord = input_tex_coord;
}
