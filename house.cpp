#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <random>
#include <vector>
#include <chrono>

/* This Program displays a random number of houses in OpenGL.
 * These houses appear to "grow" out of the ground and disappear again, repeatedly.
 * The animation cycle takes one second to let all of the houses appear completely (the highest one will take one second to be fully displayed), displays them for three seconds, and lets them disappear again within one second.
 * In between the cycles, all of the houses are assigned new random dimensional attribute values which are displayed in the next cycle.
*/

const int WIDTH = 1920;
const int HEIGHT = 1080;

const double MAX_POS_X = 10.0;
const double MAX_POS_Z = 10.0;

// dimensional constraints for the houses

const double MIN_HOUSE_WIDTH = 0.5;
const double MIN_HOUSE_LENGTH = 0.5;
const double MIN_HOUSE_HEIGHT_WALL = 0.5;

const double MAX_HOUSE_WIDTH = 2.5;
const double MAX_HOUSE_LENGTH = 2.5;
const double MAX_HOUSE_HEIGHT_ROOF = 3.5;
const double MAX_HOUSE_HEIGHT_WALL = 2.5;

double house_highest = 0.0;
    

// initialize random number generator
std::random_device rd;
std::mt19937 gen(rd());


double random_val(double min, double max){
    std::uniform_real_distribution<double> dist(min, max);
    return dist(gen);
}

/* The class used to hold data regarding a house
 * It holds the dimensional and positional attributes as well as the RGB channel values for the roof and the walls of the house.
 * It contains a method which sets the dimensional attributes to random numbers.
*/

class House{
    
    public:
        double height_roof, height_wall, width, length;
        double pos_x, pos_z;
        double pos_y = 0.0; //on ground level
        double color_wall_r, color_wall_g, color_wall_b;
        double color_roof_r, color_roof_g, color_roof_b;

        House(){
           pos_x = random_val(-MAX_POS_X, MAX_POS_X);
           pos_z = random_val(-MAX_POS_Z, MAX_POS_Z);
            
           set_random_dimensions();

           color_wall_r = random_val(0.0, 1.0);
           color_wall_g = random_val(0.0, 1.0);
           color_wall_b = random_val(0.0, 1.0);

           color_roof_r = random_val(0.0, 1.0);
           color_roof_g = random_val(0.0, 1.0);
           color_roof_b = random_val(0.0, 1.0);
        }

        // specific constructor in case needed
        House(double x, double y, double z, double w, double l, double h_r, double h_w, double col_wall_r, double col_wall_g, double col_wall_b, double col_roof_r, double col_roof_g, double col_roof_b){
           pos_x = x;
           pos_z = z;

           width = w;
           length = l;
           height_roof = h_r;
           height_wall = h_w;

           color_wall_r = col_wall_r;
           color_wall_g = col_wall_g;
           color_wall_b = col_wall_b;
           color_roof_r = col_roof_r;
           color_roof_g = col_roof_g;
           color_roof_b = col_roof_b;
        }

        // This method sets the dimensional attributes to random values within the specified boundaries.
        void set_random_dimensions(){
           width = random_val(MIN_HOUSE_WIDTH, MAX_HOUSE_WIDTH);
           length = random_val(MIN_HOUSE_LENGTH, MAX_HOUSE_LENGTH);
           height_wall = random_val(MIN_HOUSE_HEIGHT_WALL, MAX_HOUSE_HEIGHT_WALL);
           height_roof = random_val(height_wall, MAX_HOUSE_HEIGHT_ROOF);

           if (height_roof > house_highest)
               house_highest = height_roof;
        }

        void draw_roof(){
            glBegin(GL_TRIANGLE_STRIP);
            glColor3f(color_roof_r, color_roof_g, color_roof_b); // roof color
                                                                 //
            // front left top
            glVertex3f(pos_x - width/2, pos_y + height_wall, pos_z - length/2);
            // back right top
            glVertex3f(pos_x - width/2, pos_y + height_wall, pos_z + length/2);
            // front roof top
            glVertex3f(pos_x, pos_y + height_roof, pos_z - length/2);
            // back roof top
            glVertex3f(pos_x, pos_y + height_roof, pos_z + length/2);
            // front right top
            glVertex3f(pos_x + width/2, pos_y + height_wall, pos_z - length/2);
            // back right top
            glVertex3f(pos_x + width/2, pos_y + height_wall, pos_z + length/2);

            glEnd();

        }

        void draw_walls(){
            glBegin(GL_TRIANGLE_STRIP);

            glColor3f(color_wall_r, color_wall_g, color_wall_b); // wall color
                                                                 
            // front left top
            glVertex3f(pos_x - width/2, pos_y + height_wall, pos_z - length/2);
            // front right bottom
            glVertex3f(pos_x + width/2, pos_y, pos_z - length/2 );
            // front right top
            glVertex3f(pos_x + width/2, pos_y + height_wall, pos_z - length/2);
            // back left bottom
            glVertex3f(pos_x + width/2, pos_y, pos_z + length/2);
            // back left top
            glVertex3f(pos_x + width/2, pos_y + height_wall, pos_z + length/2);
            // back right bottom
            glVertex3f(pos_x - width/2, pos_y, pos_z + length/2);
            // back right top
            glVertex3f(pos_x - width/2, pos_y + height_wall, pos_z + length/2);
            // front left bottom
            glVertex3f(pos_x - width/2, pos_y, pos_z - length/2);
            // front left top
            glVertex3f(pos_x - width/2, pos_y + height_wall, pos_z - length/2);
            // front right bottom
            glVertex3f(pos_x + width/2, pos_y, pos_z - length/2);

            glEnd();
            glBegin(GL_TRIANGLES);
            // front left top
            glVertex3f(pos_x - width/2, pos_y + height_wall, pos_z - length/2);
            // front right top
            glVertex3f(pos_x + width/2, pos_y + height_wall, pos_z - length/2);
            // front roof top
            glVertex3f(pos_x, pos_y + height_roof, pos_z - length/2);
            
            // front left top
            glVertex3f(pos_x - width/2, pos_y + height_wall, pos_z + length/2);
            // front right top
            glVertex3f(pos_x + width/2, pos_y + height_wall, pos_z + length/2);
            // back roof top
            glVertex3f(pos_x, pos_y + height_roof, pos_z + length/2);

            glEnd();

        }
        void draw(){
            draw_walls();
            draw_roof();
        }

};

void render(std::vector<House*> houses) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set up projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 100.0);

    // Set up modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(10.0, 10.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    for (House* house : houses){
        house->draw();
    }
        
}

int main() {
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Parametric House", NULL, NULL);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }
    glEnable(GL_DEPTH_TEST);

    std::vector<House*> houses;
    int amount_houses = (int)random_val(12.0, 35.0);

    for (int i = 0; i <= amount_houses; i++)
        houses.push_back(new House());

    double clipping_plane[4] = { 0.0, -1.0, 0.0, 0.0 };
    double ratio = 0.0;
    
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    while (!glfwWindowShouldClose(window)) {
        std::chrono::steady_clock::time_point between = std::chrono::steady_clock::now(); 
        std::chrono::milliseconds::rep duration = std::chrono::duration_cast<std::chrono::milliseconds>(between - start).count(); // get time passed since render start

        clipping_plane[3] = 100;
        if (duration <= 1000){ // increase clipping plane height.
            ratio = duration / 1000.0;
            clipping_plane[3] = ratio * house_highest;

        }else if(duration >= 5000){ // total animation cycle is over. reset clip plane height, height of the highest generated house, house parameters and timer.
            clipping_plane[3] = 0.0;
            std::cout << "Resetting animation." << std::endl; 
            house_highest = 0.0;
            for (House* house : houses){
                house->set_random_dimensions();
            }
            start = std::chrono::steady_clock::now();

        }else if(duration >= 4000){ // lower the clipping plane.
            ratio = (duration - 4000.0) / 1000.0;
            double dist = house_highest - ratio * house_highest;
            clipping_plane[3] = dist; 
        }

        glClipPlane(GL_CLIP_PLANE0, clipping_plane);
        glEnable(GL_CLIP_PLANE0);
        
        render(houses);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
