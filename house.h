#ifndef HOUSE_H
#define HOUSE_H

#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include "random.hpp"


using Random = effolkronium::random_static;

/*
 * This file describes the class used to represent a parametric house.
 */

const float MAX_POS_X = 25.0;
const float MAX_POS_Z = 25.0;

const float MIN_HOUSE_WIDTH = 1.5;
const float MIN_HOUSE_LENGTH = 1.5;
const float MIN_HOUSE_HEIGHT_WALL = 1.5;

const float MAX_HOUSE_WIDTH = 3.5;
const float MAX_HOUSE_LENGTH = 5.5;
const float MAX_HOUSE_HEIGHT_ROOF = 4.5;
const float MAX_HOUSE_HEIGHT_WALL = 3.0;

/*
 * The class representing a house.
 * Params:
 *    width: width of house
 *    length: length of house
 *    height_wall: height of house walls
 *    height_roof: height of house roof
 *    colour_wall_r, colour_wall_g, colour_wall_b: rgb colour values for the walls
 *    colour_roof_r, colour_roof_g, colour_roof_b: rgb colour values for the roof
 *    mat_model: model matrix of house
 *    mat_rotation: rotationt matrix to be applied to the house
 *
 * The default constructor returns a house with random location as well as random colour and size parameters.
 * The remaining constructors allow a more specific instantiation of the house object.
 *
 */

class House{
    
    public:
        float height_roof, height_wall, width, length;
        float pos_x, pos_y, pos_z = 0.0;
        float colour_wall_r, colour_wall_g, colour_wall_b;
        float colour_roof_r, colour_roof_g, colour_roof_b;
        glm::mat4 mat_model = glm::mat4(1.0f);
        glm::mat4 mat_rotation;

        // random constructor
        House();

        // location specific random attribute constructor
        House(float x, float y, float z);

        // specific constructor
        House(float x, float y, float z, float w, float l, float h_r, float h_w, float col_wall_r, float col_wall_g, float col_wall_b, float col_roof_r, float col_roof_g, float col_roof_b, glm::mat4 model, glm::mat4 rotation);

        // This method sets the dimensional attributes of the house to random values within the specified boundaries.
        void set_dimensions(float width, float length, float height_wall, float height_roof);
        void set_rotation(float degrees);

        // assigns a random colour to the walls and the roof
        void set_colours(float col_wall_r, float col_wall_g, float col_wall_b, float col_roof_r, float col_roof_g, float col_roof_b);

        // randomizes the house attributes
        void randomize();
        void randomize_colours();
        void randomize_dimensions();
        void randomize_rotation();

};
#endif
