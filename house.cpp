#include "house.h"

House::House(){
   pos_x = Random::get(-MAX_POS_X, MAX_POS_X);
   pos_z = Random::get(-MAX_POS_Z, MAX_POS_Z);

   randomize();
}
// location specific random attribute constructor
House::House(float x, float y, float z){
   pos_x = x;
   pos_y = y;
   pos_z = z;

   randomize();
}

// specific constructor
House::House(float x, float y, float z, float w, float l, float h_r, float h_w, float col_wall_r, float col_wall_g, float col_wall_b, float col_roof_r, float col_roof_g, float col_roof_b, glm::mat4 model, glm::mat4 rotation){
   pos_x = x;
   pos_z = z;

   width = w;
   length = l;
   height_roof = h_r;
   height_wall = h_w;

   colour_wall_r = col_wall_r;
   colour_wall_g = col_wall_g;
   colour_wall_b = col_wall_b;
   colour_roof_r = col_roof_r;
   colour_roof_g = col_roof_g;
   colour_roof_b = col_roof_b;
   
   mat_model = model;
   mat_rotation = rotation;
}

// sets the dimensional attributes of the house to passed values.
void House::set_dimensions(float w, float l, float h_w, float h_r){
   width = w;
   length = l;
   height_wall = h_w;
   height_roof = h_r;
}

// set rotation around y-axis of house according to passed degrees
void House::set_rotation(float degrees){
   mat_rotation = glm::rotate(glm::mat4(1.0f), glm::radians(degrees), glm::vec3(0.0, 1.0, 0.0));
}

// assigns passed rgb colour values to the walls and the roof
void House::set_colours(float col_wall_r, float col_wall_g, float col_wall_b, float col_roof_r, float col_roof_g, float col_roof_b){
   colour_wall_r = col_wall_r;
   colour_wall_g = col_wall_g;
   colour_wall_b = col_wall_b;
   colour_roof_r = col_roof_r;
   colour_roof_g = col_roof_g;
   colour_roof_b = col_roof_b;
}

// assigns a random colour to the walls and the roof each
void House::randomize_colours(){
   set_colours(
         Random::get(0.0, 1.0),
         Random::get(0.0, 1.0),
         Random::get(0.0, 1.0),
         Random::get(0.0, 1.0),
         Random::get(0.0, 1.0),
         Random::get(0.0, 1.0)
   );
}

// assigns random values within the given boundaries to the dimensional attributes of the house
void House::randomize_dimensions(){
    float rand_width = Random::get(MIN_HOUSE_WIDTH, MAX_HOUSE_WIDTH);
    float rand_length = Random::get(MIN_HOUSE_LENGTH, MAX_HOUSE_LENGTH);
    float rand_height_wall = Random::get(MIN_HOUSE_HEIGHT_WALL, MAX_HOUSE_HEIGHT_WALL);
    float rand_height_roof = Random::get(rand_height_wall, MAX_HOUSE_HEIGHT_ROOF);

    set_dimensions(rand_width, rand_length, rand_height_wall, rand_height_roof);
}

void House::randomize_rotation(){
    float rand_degrees = Random::get(0.0, 360.0);
    set_rotation(rand_degrees);
}

// randomizes the house attributes
void House::randomize(){
    randomize_dimensions();
    randomize_rotation();
    randomize_colours();

}
