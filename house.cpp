#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <random>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"
#include "camera.h"

/*
 * This Program renders a random amount of houses with random coloured walls and roofs at random positions.
 * They "appear" out of the ground and "disappear" again in a cycle.
 * The cycle proceeds the following way:
 *
 *    1. Houses appear within 1 second
 *    2. Houses stay put for 3 seconds
 *    3. Houses disapper within 1 second
 *
 * The tallest house will take 1 second each to appear and to disappear. Smaller buildings take less time.
 *
 * */

const int WIDTH = 1920;
const int HEIGHT = 1080;

const int MIN_RANDOM_HOUSES = 3;
const int MAX_RANDOM_HOUSES = 7;

// dimensional constraints for the houses

const float MAX_POS_X = 25.0;
const float MAX_POS_Z = 25.0;

const float MIN_HOUSE_WIDTH = 1.5;
const float MIN_HOUSE_LENGTH = 1.5;
const float MIN_HOUSE_HEIGHT_WALL = 1.5;

const float MAX_HOUSE_WIDTH = 3.5;
const float MAX_HOUSE_LENGTH = 5.5;
const float MAX_HOUSE_HEIGHT_ROOF = 4.5;
const float MAX_HOUSE_HEIGHT_WALL = 3.0;

float house_highest = 0.0;

// initialize random number generator
std::random_device rd;
std::mt19937 gen(rd());


// camera
Camera camera(glm::vec3(25.0f, 10.0f, 25.0f));
glm::mat4 mat_projection = glm::perspective(glm::radians(80.0f), (float)WIDTH / (float)HEIGHT, 1.0f, 150.0f);

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;
float startFrame = 0.0f;
float currentFrame = 0.0;
float duration = 0.0;
float ratio = 0.0;

int random_int(int min, int max){
    std::uniform_int_distribution<int> dist(min, max);
    float generated = dist(gen);
    return generated;
}

float random_float(float min, float max){
    std::uniform_real_distribution<float> dist(min, max);
    float generated = dist(gen);
    return generated;
}

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

           if (height_roof > house_highest)
               house_highest = height_roof;
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


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

double get_clip_height(){
     double height_clip = house_highest;
     if (duration <= 1.0){ // increase clipping plane height.
         ratio = duration;
         height_clip = ratio * house_highest;

     }else if(duration >= 5.0){ // total animation cycle is over. reset clip plane height and timer 
         height_clip = 0.0;
         std::cout << "Resetting animation." << std::endl; 
         startFrame = static_cast<float>(glfwGetTime());

     }else if(duration >= 4.0){ // lower the clipping plane.
         ratio = (duration - 4.0);
         double dist = house_highest - ratio * house_highest;
         height_clip = dist;
     }
     return height_clip;

}

int main() {
    // Initialize GLFW and GLEW
    glfwInit();
    // Create a window
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Parametric House Renderer", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glewInit();

    std::vector<std::vector<float>> housePositions = {
      { 30.0, 0.0, 7.0 },
      { 27.0, 0.0, 7.5 },
      { 18.0, 0.0, 6.7 },
      { 14.2, 0.0, 7.0 },
      { 11.2, 0.0, 7.0 },
      { 4.0, 0.0, 7.5 },
      { 1.0, 0.0, 6.5 },
      { -1.5, 0.0, 7.1 },
      { -4.5, 0.0, 6.1 },
      // opposite
      { 28.0, 0.0, -1.0 },
      { 25.0, 0.0, -0.1 },
      { 18.0, 0.0, -1.7 },
      { 14.2, 0.0, -1.0 },
      { 11.2, 0.0, -1.3 },
      { 7.2, 0.0, -1.0 },
      { 3.6, 0.0, 1.2 },
      { 0.6, 0.0, -1.2 },
      { -2.9, 0.0, -0.2 },
    };

    // Initialize data
    std::vector<House*> houses;
    int amount_houses = random_int(MIN_RANDOM_HOUSES, MAX_RANDOM_HOUSES);
    for (int i = 0; i < amount_houses; i++){
        House* random_house = new House();
        houses.push_back(random_house);
    }
    for (std::vector<float> pos : housePositions){
        House* random_house = new House(pos[0], pos[1], pos[2]);
        houses.push_back(random_house);
    }

    // Initialize shaders
    Shader shader("vertexShader.vert", "fragmentShader.frag", "geometryShader.geom");
    shader.use();

    glEnable(GL_CLIP_PLANE0);
    glEnable(GL_DEPTH_TEST);

    startFrame = static_cast<float>(glfwGetTime());
    double height_clip;

    while (!glfwWindowShouldClose(window)) {

        processInput(window);
        // Time handling
        currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        duration = currentFrame - startFrame;
        lastFrame = currentFrame;

        height_clip = get_clip_height();

        // reset house parameters and time when the 5 sec cycle is over
        if (duration > 5.0){
            house_highest = 0.0;
            for (House* house : houses){
                house->set_random_dimensions();
            }
            startFrame = static_cast<float>(glfwGetTime());
        }


        glm::mat4 mat_view = camera.GetViewMatrix();;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.setFloat("u_height_clip", height_clip);
        for(House* house : houses){
           shader.setFloat("u_width", house->width);
           shader.setFloat("u_length", house->length);
           shader.setFloat("u_height_wall", house->height_wall);
           shader.setFloat("u_height_roof", house->height_roof);
           shader.setVec4("u_location", house->pos_x, house->pos_y, house->pos_z, 1.0);
           shader.setVec3("u_colour_roof", house->colour_roof_r, house->colour_roof_g, house->colour_roof_b);
           shader.setVec3("u_colour_wall", house->colour_wall_r, house->colour_wall_g, house->colour_wall_b);
           shader.setMat4("u_mvp", mat_projection * mat_view * house->mat_model);
           shader.setMat4("u_rotation", house->mat_rotation);
           glDrawArrays(GL_POINTS, 0, 10);
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
