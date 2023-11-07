
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "random_funcs.h"

const float MAX_POS_X = 25.0;
const float MAX_POS_Z = 25.0;

const float MIN_HOUSE_WIDTH = 1.5;
const float MIN_HOUSE_LENGTH = 1.5;
const float MIN_HOUSE_HEIGHT_WALL = 1.5;

const float MAX_HOUSE_WIDTH = 3.5;
const float MAX_HOUSE_LENGTH = 5.5;
const float MAX_HOUSE_HEIGHT_ROOF = 4.5;
const float MAX_HOUSE_HEIGHT_WALL = 3.0;

class House{
    
    public:
        float height_roof, height_wall, width, length;
        float pos_x, pos_y, pos_z = 0.0;
        float colour_wall_r, colour_wall_g, colour_wall_b;
        float colour_roof_r, colour_roof_g, colour_roof_b;
        glm::mat4 mat_model = glm::mat4(1.0f);
        glm::mat4 mat_rotation;

        // random constructor
        House(){
           pos_x = random_float(-MAX_POS_X, MAX_POS_X);
           pos_z = random_float(-MAX_POS_Z, MAX_POS_Z);
           set_random_dimensions();
           set_random_colours();
        }

        House(float x, float y, float z){
           pos_x = x;
           pos_y = y;
           pos_z = z;
           set_random_dimensions();
           set_random_colours();
        }

        // specific constructor
        House(float x, float y, float z, float w, float l, float h_r, float h_w, float col_wall_r, float col_wall_g, float col_wall_b, float col_roof_r, float col_roof_g, float col_roof_b, glm::mat4 model){
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
        }

        // This method sets the dimensional attributes of the house to random values within the specified boundaries.
        void set_random_dimensions(){
           mat_rotation = glm::rotate(glm::mat4(1.0f), glm::radians(random_float(0.0, 359.0)), glm::vec3(0.0, 1.0, 0.0));
           width = random_float(MIN_HOUSE_WIDTH, MAX_HOUSE_WIDTH);
           length = random_float(MIN_HOUSE_LENGTH, MAX_HOUSE_LENGTH);
           height_wall = random_float(MIN_HOUSE_HEIGHT_WALL, MAX_HOUSE_HEIGHT_WALL);
           height_roof = random_float(height_wall, MAX_HOUSE_HEIGHT_ROOF);

           //if (height_roof > house_highest)
            //   house_highest = height_roof;
        }

        void set_random_colours(){
           colour_wall_r = random_float(0.0, 1.0);
           colour_wall_g = random_float(0.0, 1.0);
           colour_wall_b = random_float(0.0, 1.0);
           colour_roof_r = random_float(0.0, 1.0);
           colour_roof_g = random_float(0.0, 1.0);
           colour_roof_b = random_float(0.0, 1.0);
        }

};
