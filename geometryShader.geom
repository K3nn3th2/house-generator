#version 330

layout(points) in;
layout(triangle_strip, max_vertices = 50) out;

out vec3 fColour;

uniform mat4 u_mvp;
uniform mat4 u_rotation;

uniform vec4 u_location;

uniform float u_length;
uniform float u_width;
uniform float u_height_roof;
uniform float u_height_wall;

uniform float u_height_clip;

uniform vec3 u_colour_roof;
uniform vec3 u_colour_wall;


void handleVertex(vec4 pos){
   // rotate vertex around house center
   vec4 pos_rotated = u_rotation * (pos - u_location);
   vec4 pos_final = pos_rotated + u_location;
   
   // apply mvp matrix
   gl_Position = u_mvp * pos_final;
   gl_ClipDistance[0] = dot(pos_final, vec4(0.0, -1.0, 0.0, u_height_clip));
   EmitVertex();

}

void build_house(vec4 position){
   // front side
   fColour = u_colour_wall;
   handleVertex(position + vec4(-u_width/2, 0.0, -u_length/2, 0.0)); // 1: bottom left
   handleVertex(position + vec4(u_width/2, 0.0, -u_length/2, 0.0)); // 2: bottom-right
   handleVertex(position + vec4(-u_width/2, u_height_wall, -u_length/2, 0.0)); // 3: top left
   handleVertex(position + vec4(u_width/2, u_height_wall, -u_length/2, 0.0)); // 4: top right
   handleVertex(position + vec4(0, u_height_roof, -u_length/2, 0.0)); // 5: top
   EndPrimitive();

   // right side
   handleVertex(position + vec4(u_width/2, 0.0, -u_length/2, 0.0)); // 1: bottom right
   handleVertex(position + vec4(u_width/2, 0.0, u_length/2, 0.0)); // 2: back bottom right
   handleVertex(position + vec4(u_width/2, u_height_wall, -u_length/2, 0.0)); // 4: top right
   handleVertex(position + vec4(u_width/2, u_height_wall, u_length/2, 0.0)); // 4: back top right
   EndPrimitive();

   // back side
   handleVertex(position + vec4(u_width/2, 0.0, u_length/2, 0.0)); // 2: bottom-right
   handleVertex(position + vec4(-u_width/2, 0.0, u_length/2, 0.0)); // 1: bottom left
   handleVertex(position + vec4(u_width/2, u_height_wall, u_length/2, 0.0)); // 4: top right
   handleVertex(position + vec4(-u_width/2, u_height_wall, u_length/2, 0.0)); // 3: top left
   handleVertex(position + vec4(0, u_height_roof, u_length/2, 0.0)); // 5: top
   EndPrimitive();

   // left side
   handleVertex(position + vec4(-u_width/2, 0.0, -u_length/2, 0.0)); // 1: bottom left
   handleVertex(position + vec4(-u_width/2, u_height_wall, -u_length/2, 0.0)); // 4: top left
   handleVertex(position + vec4(-u_width/2, 0.0, u_length/2, 0.0)); // 2: back bottom left
   handleVertex(position + vec4(-u_width/2, u_height_wall, u_length/2, 0.0)); // 4: back top left
   EndPrimitive();

   // roof
   fColour = u_colour_roof;
   handleVertex(position + vec4(u_width/2, u_height_wall, -u_length/2, 0.0)); // 1: top right
   handleVertex(position + vec4(u_width/2, u_height_wall, u_length/2, 0.0)); // 2: top back right
   handleVertex(position + vec4(0, u_height_roof, -u_length/2, 0.0)); // 3: top front
   handleVertex(position + vec4(0, u_height_roof, u_length/2, 0.0)); // 4: top back
   handleVertex(position + vec4(-u_width/2, u_height_wall, -u_length/2, 0.0)); // 5: top left
   handleVertex(position + vec4(-u_width/2, u_height_wall, u_length/2, 0.0)); // 6: top back left
   EndPrimitive();
}

void main() {
   
   build_house(u_location);

}


