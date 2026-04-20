#define FREEGLUT_STATIC  
#include <GL/freeglut.h>  
#include <stdlib.h>       
#include <cmath>          
#include <vector>         
#include <ctime>          
// ====================== Texture Variable Declarations ======================
// Texture ID variables: store OpenGL-generated texture identifiers
GLuint buildingTexture;       // Building wall texture
GLuint subwayTexture;         // Subway ground texture
GLuint subwayWallTexture;     // Subway wall texture
GLuint light1Texture;         // Light texture 1 (for billboards, etc.)
GLuint light2Texture;         // Light texture 2
GLuint light3Texture;         // Light texture 3
GLuint light4Texture;         // Light texture 4
GLuint light5Texture;         // Light texture 5 (for light effects)
GLuint posterTexture;         // Poster texture 1
GLuint poster2Texture;        // Poster texture 2
GLuint mapTexture;            // Map texture
GLuint groundTexture;         // Ground texture
// Texture dimension and pixel data variables
GLint imageWidth, imageHeight, pixelLength;  // Texture image width, height, and pixel data length
GLubyte* pixelData = nullptr;           // Building texture pixel data pointer
GLubyte* subwayPixelData = nullptr;     // Subway ground texture pixel data pointer
GLubyte* subwayWallPixelData = nullptr; // Subway wall texture pixel data pointer
GLubyte* light1PixelData = nullptr;     // Light texture 1 pixel data pointer
GLubyte* light2PixelData = nullptr;     // Light texture 2 pixel data pointer
GLubyte* light3PixelData = nullptr;     // Light texture 3 pixel data pointer
GLubyte* light4PixelData = nullptr;     // Light texture 4 pixel data pointer
GLubyte* light5PixelData = nullptr;     // Light texture 5 pixel data pointer
GLubyte* posterPixelData = nullptr;     // Poster texture 1 pixel data pointer
GLubyte* poster2PixelData = nullptr;    // Poster texture 2 pixel data pointer
GLubyte* mapPixelData = nullptr;        // Map texture pixel data pointer
GLubyte* groundPixelData = nullptr;     // Ground texture pixel data pointer
// ====================== Math Constant Definitions ======================
// Manual definition of ¦Ð value (ensure compatibility with compilers without M_PI)
#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif
// ====================== Camera Parameters ======================
// Camera position coordinates (initial position fixed)
float cameraX = 1.5f, cameraY = 12.5f, cameraZ = 15.5f;
// Camera rotation angles (yaw controls left/right look, pitch controls up/down look)
float cameraYaw = 15.0f, cameraPitch = -10.0f;
// Previous mouse position (for calculating mouse movement delta)
int lastMouseX = 400, lastMouseY = 300;
// Left mouse button pressed state flag
bool mouseLeftDown = false;
const int GRID_SIZE = 80;
const float CELL_SIZE = 2.0f;
const float GROUND_Y = 0.0f;
const float GRAY_FILL = 0.35f;
const float GRAY_GRID = 0.6f;
// ====================== Robot State Variables ======================
bool leftArmRaised = false;         // Flag indicating if left arm is raised
// ====================== Teapot State Variables ======================
bool teapotRaised = false;          // Flag indicating if teapot is raised
const float TEAPOT_INITIAL_Y = 9.5f; // Teapot initial Y coordinate (height when not raised)
const float TEAPOT_OFFSET = 1.0f;    // Height offset when teapot is raised
// ====================== Building Parameter Definitions ======================
// Building 1 parameters
const float BLD1_X = 28.0f;       // X-axis coordinate
const float BLD1_Z = -20.0f;      // Z-axis coordinate
const float BLD1_Y = 0.0f;        // Y-axis coordinate (bottom height)
const float BLD1_WIDTH = 10.0f;   // Width (X-axis direction)
const float BLD1_DEPTH = 13.0f;   // Depth (Z-axis direction)
const float BLD1_HEIGHT = 40.0f;  // Height (Y-axis direction)
const float BLD1_GRAY = 0.45f;    // Wall grayscale value
// Building 2 parameters
const float BLD2_X = -5.0f;
const float BLD2_Z = -25.0f;
const float BLD2_Y = 0.0f;
const float BLD2_WIDTH = 10.0f;
const float BLD2_DEPTH = 10.0f;
const float BLD2_HEIGHT = 43.0f;
const float BLD2_GRAY = 0.45f;
// Building 3 parameters
const float BLD3_X = 0.0f;
const float BLD3_Z = -40.0f;
const float BLD3_Y = 0.0f;
const float BLD3_WIDTH = 12.0f;
const float BLD3_DEPTH = 12.0f;
const float BLD3_HEIGHT = 38.0f;
const float BLD3_GRAY = 0.4f;
// Building 4 parameters
const float BLD4_X = 13.0f;
const float BLD4_Z = -90.0f;
const float BLD4_Y = 0.0f;
const float BLD4_WIDTH = 10.0f;
const float BLD4_DEPTH = 10.0f;
const float BLD4_HEIGHT = 40.0f;
const float BLD4_GRAY = 0.48f;
// Building 5 parameters
const float BLD5_X = 25.0f;
const float BLD5_Z = -100.0f;
const float BLD5_Y = 0.0f;
const float BLD5_WIDTH = 8.0f;
const float BLD5_DEPTH = 8.0f;
const float BLD5_HEIGHT = 34.0f;
const float BLD5_GRAY = 0.42f;
// Building 6 parameters
const float BLD6_X = 35.0f;
const float BLD6_Z = -50.0f;
const float BLD6_Y = 0.0f;
const float BLD6_WIDTH = 10.0f;
const float BLD6_DEPTH = 10.0f;
const float BLD6_HEIGHT = 38.0f;
const float BLD6_GRAY = 0.5f;
// Building 7 parameters
const float BLD7_X = 30.0f;
const float BLD7_Z = -13.0f;
const float BLD7_Y = 0.0f;
const float BLD7_WIDTH = 15.0f;
const float BLD7_DEPTH = 10.0f;
const float BLD7_HEIGHT = 23.0f;
const float BLD7_GRAY = 0.43f;
// Building 8 parameters
const float BLD8_X = 30.0f;
const float BLD8_Z = 0.0f;
const float BLD8_Y = 0.0f;
const float BLD8_WIDTH = 10.0f;
const float BLD8_DEPTH = 10.0f;
const float BLD8_HEIGHT = 28.0f;
const float BLD8_GRAY = 0.43f;
// Building 9 parameters
const float BLD9_X = 35.0f;
const float BLD9_Z = -110.0f;
const float BLD9_Y = 0.0f;
const float BLD9_WIDTH = 10.0f;
const float BLD9_DEPTH = 10.0f;
const float BLD9_HEIGHT = 30.0f;
const float BLD9_GRAY = 0.43f;
// Building 10 parameters
const float BLD10_X = 30.0f;
const float BLD10_Z = 11.0f;
const float BLD10_Y = 0.0f;
const float BLD10_WIDTH = 10.0f;
const float BLD10_DEPTH = 10.0f;
const float BLD10_HEIGHT = 32.0f;
const float BLD10_GRAY = 0.43f;
// Building 11 parameters
const float BLD11_X = -12.0f;
const float BLD11_Z = 15.0f;
const float BLD11_Y = 5.5f;
const float BLD11_WIDTH = 2.0f;
const float BLD11_DEPTH = 24.0f;
const float BLD11_HEIGHT = 20.0f;
const float BLD11_GRAY = 0.50f;
// Building 12 parameters
const float BLD12_X = -0.40f;
const float BLD12_Z = 20.0f;
const float BLD12_Y = 5.0f;
const float BLD12_WIDTH = 15.0f;
const float BLD12_DEPTH = 2.5f;
const float BLD12_HEIGHT = 18.0f;
const float BLD12_GRAY = 0.50f;

// Building 13 parameters
const float BLD13_X = -9.75f;
const float BLD13_Z = 0.0f;
const float BLD13_Y = 5.0f;
const float BLD13_WIDTH = 15.0f;
const float BLD13_DEPTH = 2.5f;
const float BLD13_HEIGHT = 18.0f;
const float BLD13_GRAY = 0.50f;
// Building 14 parameters
const float BLD14_X = -5.0f;
const float BLD14_Z = 10.0f;
const float BLD14_Y = 5.0f;
const float BLD14_WIDTH = 15.0f;
const float BLD14_DEPTH = 20.0f;
const float BLD14_HEIGHT = 1.2f;
const float BLD14_GRAY = 0.60f;
// Building 15 parameters
const float BLD15_X = -5.0f;
const float BLD15_Z = 10.0f;
const float BLD15_Y = 21.7f;
const float BLD15_WIDTH = 15.0f;
const float BLD15_DEPTH = 20.0f;
const float BLD15_HEIGHT = 1.2f;
const float BLD15_GRAY = 0.60f;
// Building 16 parameters
const float BLD16_X = 1.7f;
const float BLD16_Z = 7.0f;
const float BLD16_Y = 5.0f;
const float BLD16_WIDTH = 0.5f;
const float BLD16_DEPTH = 20.0f;
const float BLD16_HEIGHT = 5.25f;
const float BLD16_GRAY = 0.50f;
// Building 17 parameters
const float BLD17_X = 1.7f;
const float BLD17_Z = 7.0f;
const float BLD17_Y = 20.0f;
const float BLD17_WIDTH = 0.5f;
const float BLD17_DEPTH = 20.0f;
const float BLD17_HEIGHT = 2.0f;
const float BLD17_GRAY = 0.50f;
// Building 18 parameters
const float BLD18_X = 11.0f;
const float BLD18_Z = -23.0f;
const float BLD18_Y = 26.0f;
const float BLD18_WIDTH = 3.0f;
const float BLD18_DEPTH = 25.0f;
const float BLD18_HEIGHT = 2.0f;
const float BLD18_GRAY = 0.05f;
// Building 19 parameters
const float BLD19_X = 15.0f;
const float BLD19_Z = -45.0f;
const float BLD19_Y = 8.0f;
const float BLD19_WIDTH = 3.0f;
const float BLD19_DEPTH = 30.0f;
const float BLD19_HEIGHT = 2.0f;
const float BLD19_GRAY = 0.05f;
// Building 20 parameters
const float BLD20_X = -1.0f;
const float BLD20_Z = 9.5f;
const float BLD20_Y = 8.5f;
const float BLD20_WIDTH = 7.0f;
const float BLD20_DEPTH = 3.5f;
const float BLD20_HEIGHT = 0.5f;
const float BLD20_GRAY = 0.3f;
// Building 21 parameters
const float BLD21_X = -1.0f;
const float BLD21_Z = 9.5f;
const float BLD21_Y = 3.5f;
const float BLD21_WIDTH = 1.0f;
const float BLD21_DEPTH = 1.5f;
const float BLD21_HEIGHT = 5.0f;
const float BLD21_GRAY = 0.3f;
// ====================== Rectangular Track Parameters ======================
const float RECT_LEFT = 15.0f;     // Left boundary X coordinate of the track rectangle
const float RECT_RIGHT = 42.0f;    // Right boundary X coordinate of the track rectangle
const float RECT_TOP = 22.0f;      // Top boundary Z coordinate of the track rectangle
const float RECT_BOTTOM = -32.0f;  // Bottom boundary Z coordinate of the track rectangle
const float RECT_HEIGHT = 9.0f;   // Track height (Y coordinate)
// ====================== High-speed Train Parameters ======================
const float TRAIN_SPEED = 0.003f;      // Train movement speed
const float TRAIN_LENGTH = 30.0f;      // Train length
const float TRAIN_WIDTH = 3.0f;        // Train width
const float TRAIN_HEIGHT = 5.5f;       // Train height
const float TRAIN_GRAY = 0.2f;         // Train grayscale value (not used, replaced by RGB color)
float trainProgress = 0.0f;            // Train progress on track (0.0 to 1.0)
// Train color (very dark blue)
const float TRAIN_R = 0.0f;    // Red component
const float TRAIN_G = 0.0f;    // Green component
const float TRAIN_B = 0.1f;    // Blue component
// ====================== Custom Line Parameters ======================
// First line endpoint coordinates
const float LINE1_START_X = 8.0f;
const float LINE1_START_Z = -100.0f;
const float LINE1_START_Y = 22.0f;
const float LINE1_END_X = 14.0f;
const float LINE1_END_Z = 20.0f;
const float LINE1_END_Y = 25.0f;
// Second line endpoint coordinates
const float LINE2_START_X = 9.0f;
const float LINE2_START_Z = -100.0f;
const float LINE2_START_Y = 22.0f;
const float LINE2_END_X = 15.0f;
const float LINE2_END_Z = 20.0f;
const float LINE2_END_Y = 25.0f;
// Third line endpoint coordinates
const float LINE3_START_X = 9.0f;
const float LINE3_START_Z = -90.0f;
const float LINE3_START_Y = 35.0f;
const float LINE3_END_X = 60.0f;
const float LINE3_END_Z = -90.0f;
const float LINE3_END_Y = 35.0f;
// ====================== Cable Car Parameters ======================
const int CABLE_CAR_COUNT = 3;              // Number of cable cars
const float CABLE_CAR_SPEED = 0.001f;       // Cable car movement speed
const float CABLE_CAR_SIZE = 3.0f;          // Cable car size
float cableCarProgress[CABLE_CAR_COUNT] = { 0.0f, 0.33f, 0.66f }; // Initial progress offset for each cable car
const float CABLE_CAR_GRAY = 0.45f;         // Cable car grayscale value
const float CABLE_LINE_GRAY = 0.4f;         // Cable line grayscale value
const float CABLE_CAR_Y_OFFSET = -2.0f;     // Cable car Y-axis downward offset
// Cable car color (wine-red tone)
const float CABLE_CAR_R = 0.25f;    // Red component
const float CABLE_CAR_G = 0.0f;     // Green component
const float CABLE_CAR_B = 0.05f;    // Blue component
// ====================== Aircraft Parameters ======================
// Aircraft waypoint structure
struct Point3D {
    float x, y, z;  // 3D coordinates
};
// Aircraft waypoint array (all X coordinates reduced by 10)
const Point3D pathPoints[] = {
    {45.0f, 35.0f, -90.0f},   // First waypoint
    {1.0f, 5.0f, -23.0f},     // Second waypoint
    {4.0f, 25.0f, 20.0f}      // Third waypoint
};
const int PATH_POINT_COUNT = sizeof(pathPoints) / sizeof(Point3D);  // Number of waypoints
const float PLANE_SPEED = 0.005f;   // Aircraft movement speed (increased)
float planeProgress = 0.0f;         // Aircraft progress on path (0.0 to 1.0)
const float PLANE_SIZE = 2.0f;      // Aircraft size
// Aircraft color (silver)
const float PLANE_R = 0.75f;    // Red component
const float PLANE_G = 0.75f;    // Green component
const float PLANE_B = 0.75f;    // Blue component
// ====================== Texture Reading Function ======================
// Read texture data from BMP file
void ReadTexture(const char* filename, GLubyte*& data, int& width, int& height, int& length) {
    FILE* pFile;  // File pointer
    fopen_s(&pFile, filename, "rb");  // Open file in binary read mode
    if (pFile == 0) {  // If file opening fails
        printf("Unable to open texture file: %s\n", filename);  // Print error message
        return;  // Return
    }
    // Read BMP file header information
    fseek(pFile, 0x0012, SEEK_SET);  // Move file pointer to width/height information location
    fread(&width, sizeof(width), 1, pFile);   // Read width
    fread(&height, sizeof(height), 1, pFile); // Read height

    // Calculate pixel data length
    length = width * 3;  // Pixel data length per row (RGB three channels)
    while (length % 4 != 0) length++;  // Pad to multiple of 4
    length *= height;  // Multiply by height to get total pixel data length
    // Allocate memory and read pixel data
    data = (GLubyte*)malloc(length);  // Allocate memory
    if (data == 0) {  // If memory allocation fails
        fclose(pFile);  // Close file
        return;  // Return
    }
    fseek(pFile, 54, SEEK_SET);  // Move file pointer to start of pixel data
    fread(data, length, 1, pFile);  // Read pixel data
    fclose(pFile);  // Close file

    printf("Texture loaded successfully: %s, dimensions: %dx%d\n", filename, width, height);  // Print loading info
}
// ====================== Texture Loading Function ======================
// Load texture and generate OpenGL texture ID
GLuint LoadTexture(const char* filename, GLubyte*& data) {
    int width, height, length;  // Texture dimension variables
    ReadTexture(filename, data, width, height, length);  // Read texture file
    if (data == 0) {  // If pixel data is empty (load failed)
        printf("Texture load failed: %s\n", filename);  // Print error message
        return 0;  // Return 0 indicating failure
    }
    GLuint textureID;  // Texture ID variable
    glGenTextures(1, &textureID);  // Generate a texture ID
    glBindTexture(GL_TEXTURE_2D, textureID);  // Bind texture to 2D texture target
    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  // Use linear filtering when minifying
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  // Use linear filtering when magnifying
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);       // Clamp texture coordinates beyond S direction
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);       // Clamp texture coordinates beyond T direction
    // Upload texture data to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
        GL_BGR_EXT, GL_UNSIGNED_BYTE, data);  // Note: BMP is BGR format
    return textureID;  // Return texture ID
}
// ====================== Texture Initialization Function ======================
// Initialize all textures
void initTexture() {
    // Read and load building texture
    buildingTexture = LoadTexture("building.bmp", pixelData);
    // Read and load subway ground texture
    subwayTexture = LoadTexture("subway_ground.bmp", subwayPixelData);
    // Read and load subway wall texture
    subwayWallTexture = LoadTexture("subway_wall.bmp", subwayWallPixelData);
    // Read and load light1 texture
    light1Texture = LoadTexture("light1.bmp", light1PixelData);
    // Read and load light2 texture
    light2Texture = LoadTexture("light2.bmp", light2PixelData);
    // Read and load light3 texture
    light3Texture = LoadTexture("light3.bmp", light3PixelData);
    // Read and load light4 texture
    light4Texture = LoadTexture("light4.bmp", light4PixelData);
    // Read and load light5 texture
    light5Texture = LoadTexture("light5.bmp", light5PixelData);
    // Read and load poster texture
    posterTexture = LoadTexture("poster.bmp", posterPixelData);
    // Read and load poster2 texture
    poster2Texture = LoadTexture("poster2.bmp", poster2PixelData);
    // Read and load map texture
    mapTexture = LoadTexture("map.bmp", mapPixelData);
    // Read and load ground texture
    groundTexture = LoadTexture("ground.bmp", groundPixelData);
}
// ====================== Bezier Curve Calculation Function ======================
// Calculate point on Bezier curve (using de Casteljau algorithm)
Point3D calculateBezierPoint(const Point3D* points, int count, float t) {
    Point3D* temp = new Point3D[count];  // Allocate temporary array
    for (int i = 0; i < count; i++) {    // Copy control points to temporary array
        temp[i] = points[i];
    }
    int n = count - 1;  // Degree of Bezier curve
    for (int k = 1; k <= n; k++) {  // Perform n iterations
        for (int i = 0; i <= n - k; i++) {  // Update each intermediate point
            temp[i].x = (1 - t) * temp[i].x + t * temp[i + 1].x;  // X coordinate interpolation
            temp[i].y = (1 - t) * temp[i].y + t * temp[i + 1].y;  // Y coordinate interpolation
            temp[i].z = (1 - t) * temp[i].z + t * temp[i + 1].z;  // Z coordinate interpolation
        }
    }
    Point3D result = temp[0];  // Final result is in temp[0]
    delete[] temp;  // Free temporary array
    return result;  // Return calculation result
}
// ====================== Aircraft Orientation Calculation Function ======================
// Calculate aircraft's next point
Point3D getNextPoint(float t, float delta = 0.01f) {
    float nextT = t + delta;  // Calculate slightly later time parameter
    if (nextT > 1.0f) nextT = 1.0f;  // Limit not exceeding 1.0
    return calculateBezierPoint(pathPoints, PATH_POINT_COUNT, nextT);  // Return next position
}
// ====================== Train Position Calculation Function ======================
// Calculate train's position and orientation on rectangular track
void calculateTrainPosition(float* x, float* y, float* z, float* yaw) {
    float rectHorizontal = RECT_RIGHT - RECT_LEFT;  // Horizontal track length (right-left sides)
    float rectVertical = RECT_TOP - RECT_BOTTOM;    // Vertical track length (top-bottom sides)
    float totalLength = 2 * (rectHorizontal + rectVertical);  // Total track length

    // Progress value calculated directly, not reversed
    float distance = trainProgress * totalLength;  // Calculate distance traveled

    if (distance <= rectVertical) {
        // 1. Right track: from bottom (RECT_BOTTOM) ¡ú top (RECT_TOP)
        *x = RECT_RIGHT;  // X coordinate fixed as right boundary
        *z = RECT_BOTTOM + distance;  // Z value increases from bottom to top
        *yaw = 90.0f;  // Train front faces upward
    }
    else if (distance <= rectVertical + rectHorizontal) {
        // 2. Top track: from right (RECT_RIGHT) ¡ú left (RECT_LEFT)
        *x = RECT_RIGHT - (distance - rectVertical);  // X value decreases from right to left
        *z = RECT_TOP;  // Z coordinate fixed as top boundary
        *yaw = 180.0f;  // Train front faces left
    }
    else if (distance <= rectVertical + rectHorizontal + rectVertical) {
        // 3. Left track: from top (RECT_TOP) ¡ú bottom (RECT_BOTTOM)
        *x = RECT_LEFT;  // X coordinate fixed as left boundary
        *z = RECT_TOP - (distance - rectVertical - rectHorizontal);  // Z value decreases from top to bottom
        *yaw = 270.0f;  // Train front faces downward
    }
    else {
        // 4. Bottom track: from left (RECT_LEFT) ¡ú right (RECT_RIGHT)
        *x = RECT_LEFT + (distance - rectVertical - rectHorizontal - rectVertical);  // X value increases from left to right
        *z = RECT_BOTTOM;  // Z coordinate fixed as bottom boundary
        *yaw = 0.0f;  // Train front faces right
    }
    *y = RECT_HEIGHT;  // Y coordinate fixed as track height
}

// ====================== Cable Car Position Calculation Function ======================
// Calculate position of cable car with specified index
void calculateCableCarPosition(int index, float* x, float* y, float* z) {
    float progress = cableCarProgress[index];  // Get this cable car's progress
    if (progress > 1.0f) progress -= 1.0f;  // If exceeds 1.0, loop back to start

    // Linear interpolation calculation of position, plus Y-axis offset
    *x = LINE1_START_X + (LINE1_END_X - LINE1_START_X) * progress;  // X coordinate interpolation
    *y = LINE1_START_Y + (LINE1_END_Y - LINE1_START_Y) * progress + CABLE_CAR_Y_OFFSET;  // Y coordinate interpolation plus offset
    *z = LINE1_START_Z + (LINE1_END_Z - LINE1_START_Z) * progress;  // Z coordinate interpolation
}

// ====================== Track Drawing Function ======================
// Draw rectangular track
void drawRectTrack() {
    glColor3f(0.5f, 0.5f, 0.5f);  // Set track color
    glLineWidth(2.0f);  // Set line width
    glEnable(GL_LINE_STIPPLE);  // Enable dashed line mode
    glLineStipple(1, 0x00FF);  // Set dashed line pattern (01010101)
    glBegin(GL_LINE_LOOP);  // Begin drawing closed line loop
    glVertex3f(RECT_LEFT, RECT_HEIGHT - 0.5f, RECT_BOTTOM);   // Bottom-left corner
    glVertex3f(RECT_RIGHT, RECT_HEIGHT - 0.5f, RECT_BOTTOM);  // Bottom-right corner
    glVertex3f(RECT_RIGHT, RECT_HEIGHT - 0.5f, RECT_TOP);     // Top-right corner
    glVertex3f(RECT_LEFT, RECT_HEIGHT - 0.5f, RECT_TOP);      // Top-left corner
    glEnd();  // End drawing
    glDisable(GL_LINE_STIPPLE);  // Disable dashed line mode
}
// ====================== Custom Line Drawing Function ======================
// Draw three black lines
void drawCustomLines() {
    // First line (black)
    glColor3f(0.0f, 0.0f, 0.0f);  // Set color to black
    glLineWidth(3.0f);            // Set line width 3 pixels
    glBegin(GL_LINES);            // Begin drawing line
    glVertex3f(LINE1_START_X, LINE1_START_Y, LINE1_START_Z);  // Start point
    glVertex3f(LINE1_END_X, LINE1_END_Y, LINE1_END_Z);        // End point
    glEnd();                      // End drawing

    // Second line (black)
    glColor3f(0.0f, 0.0f, 0.0f);  // Set color to black
    glLineWidth(3.0f);            // Set line width 3 pixels
    glBegin(GL_LINES);            // Begin drawing line
    glVertex3f(LINE2_START_X, LINE2_START_Y, LINE2_START_Z);  // Start point
    glVertex3f(LINE2_END_X, LINE2_END_Y, LINE2_END_Z);        // End point
    glEnd();                      // End drawing

    // Third line (black)
    glColor3f(0.0f, 0.0f, 0.0f);  // Set color to black
    glLineWidth(3.0f);            // Set line width 3 pixels
    glBegin(GL_LINES);            // Begin drawing line
    glVertex3f(LINE3_START_X, LINE3_START_Y, LINE3_START_Z);  // Start point
    glVertex3f(LINE3_END_X, LINE3_END_Y, LINE3_END_Z);        // End point
    glEnd();                      // End drawing

    glLineWidth(1.0f);  // Restore default line width
}
// ====================== Cable Car Drawing Function ======================
// Draw cable car with specified index (wine-red color)
void drawCableCar(int index) {
    float x, y, z;  // Cable car position variables
    calculateCableCarPosition(index, &x, &y, &z);  // Calculate cable car position

    glPushMatrix();    // Save current matrix
    glTranslatef(x, y, z);  // Translate to cable car position

    // Cable car body (wine-red color)
    glColor3f(CABLE_CAR_R, CABLE_CAR_G, CABLE_CAR_B);  // Set color
    glutSolidCube(CABLE_CAR_SIZE);  // Draw cube as cable car body

    // Cable car top hook (darker wine-red)
    glColor3f(CABLE_CAR_R - 0.15f, CABLE_CAR_G, CABLE_CAR_B - 0.05f);  // Set darker color
    glPushMatrix();    // Save matrix
    glScalef(0.3f, 0.5f, 0.3f);  // Scale hook size
    glTranslatef(0.0f, 1.0f, 0.0f);  // Translate upward
    glutSolidCube(1.0f);  // Draw hook
    glPopMatrix();     // Restore matrix

    glPopMatrix();     // Restore matrix
}

// ====================== Aircraft Drawing Function ======================
// Draw aircraft
void drawPlane() {
    // Get current position
    Point3D currentPos = calculateBezierPoint(pathPoints, PATH_POINT_COUNT, planeProgress);  // Current point
    Point3D nextPos = getNextPoint(planeProgress);  // Next point

    // Calculate orientation (yaw and pitch angles)
    float dx = nextPos.x - currentPos.x;  // X direction increment
    float dz = nextPos.z - currentPos.z;  // Z direction increment
    float yaw = atan2(dx, -dz) * 180.0f / M_PI;  // Calculate yaw angle (rotate around Y-axis)

    float dy = nextPos.y - currentPos.y;  // Y direction increment
    float dist = sqrt(dx * dx + dz * dz);  // Horizontal distance
    float pitch = atan2(dy, dist) * 180.0f / M_PI;  // Calculate pitch angle (rotate around X-axis)

    glPushMatrix();    // Save current matrix
    glTranslatef(currentPos.x, currentPos.y, currentPos.z);  // Translate to current position
    glRotatef(yaw, 0.0f, 1.0f, 0.0f);   // Rotate around Y-axis
    glRotatef(pitch, 1.0f, 0.0f, 0.0f); // Rotate around X-axis
    // Aircraft body (silver)
    glColor3f(PLANE_R, PLANE_G, PLANE_B);  // Set silver color
    glutSolidCube(PLANE_SIZE);  // Draw cube as body
    // Wing
    glPushMatrix();    // Save matrix
    glScalef(0.5f, 0.2f, 3.0f);  // Scale wing size
    glutSolidCube(PLANE_SIZE);  // Draw wing
    glPopMatrix();     // Restore matrix
    // Tail fin
    glPushMatrix();    // Save matrix
    glTranslatef(0.0f, PLANE_SIZE / 2, -PLANE_SIZE / 2);  // Translate to tail position
    glScalef(0.5f, 2.0f, 0.5f);  // Scale tail fin size
    glutSolidCube(PLANE_SIZE / 2);  // Draw tail fin
    glPopMatrix();     // Restore matrix
    // Nose (slightly darker silver)
    glColor3f(PLANE_R - 0.2f, PLANE_G - 0.2f, PLANE_B - 0.2f);  // Set slightly darker silver
    glPushMatrix();    // Save matrix
    glTranslatef(0.0f, 0.0f, PLANE_SIZE / 2);  // Translate to front position
    glutSolidCone(PLANE_SIZE / 2, PLANE_SIZE, 8, 8);  // Draw cone as nose
    glPopMatrix();     // Restore matrix
    glPopMatrix();     // Restore matrix
}
// ====================== All Cable Cars Drawing Function ======================
// Draw all cable cars
void drawCableCars() {
    for (int i = 0; i < CABLE_CAR_COUNT; i++) {  // Iterate through all cable cars
        drawCableCar(i);  // Draw each cable car
    }
}
// ====================== Cable Car Position Update Function ======================
// Update positions of all cable cars
void updateCableCars() {
    for (int i = 0; i < CABLE_CAR_COUNT; i++) {  // Iterate through all cable cars
        cableCarProgress[i] += CABLE_CAR_SPEED;  // Increase progress value
        if (cableCarProgress[i] > 1.0f) {        // If exceeds 1.0
            cableCarProgress[i] = 0.0f;          // Reset to 0.0
        }
    }
}
// ====================== Aircraft Position Update Function ======================
// Update aircraft's position
void updatePlane() {
    planeProgress += PLANE_SPEED;  // Increase progress value
    if (planeProgress > 1.0f) {    // If exceeds 1.0
        planeProgress = 0.0f;      // Reset to 0.0
    }
}

// ====================== Train Drawing Function ======================
// Draw high-speed train (very dark blue)
void drawTrain() {
    float trainX, trainY, trainZ, trainYaw;  // Train position and orientation variables
    calculateTrainPosition(&trainX, &trainY, &trainZ, &trainYaw);  // Calculate train position

    glPushMatrix();    // Save current matrix
    glTranslatef(trainX, trainY - TRAIN_HEIGHT / 2, trainZ);  // Translate to train position
    glRotatef(trainYaw, 0.0f, 1.0f, 0.0f);  // Rotate around Y-axis to correct orientation

    // Train body (very dark blue)
    glColor3f(TRAIN_R, TRAIN_G, TRAIN_B);  // Set color
    glPushMatrix();    // Save matrix
    glTranslatef(0.0f, TRAIN_HEIGHT / 2, 0.0f);  // Translate to height center
    glScalef(TRAIN_LENGTH, TRAIN_HEIGHT, TRAIN_WIDTH);  // Scale train size
    glutSolidCube(1.0f);  // Draw cube as train body
    glPopMatrix();     // Restore matrix

    glPopMatrix();     // Restore matrix
    drawRectTrack();   // Draw track
}

// ====================== 2D Plane Drawing Functions ======================
// Following functions add textured 2D planes to various faces of buildings


void drawBuilding1LeftPlane() {
    glPushMatrix();    // Save current matrix
    glTranslatef(BLD1_X - BLD1_WIDTH / 2 - 0.01f, BLD1_Y + BLD1_HEIGHT / 2, BLD1_Z);  // Translate to building left face
    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, buildingTexture);  // Bind building texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white (texture color unaffected)
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -BLD1_HEIGHT / 2, BLD1_DEPTH / 2);   // Bottom-left corner (texture coordinate, vertex coordinate)
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, BLD1_HEIGHT / 2, BLD1_DEPTH / 2);    // Top-left corner
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, BLD1_HEIGHT / 2, -BLD1_DEPTH / 2);   // Top-right corner
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -BLD1_HEIGHT / 2, -BLD1_DEPTH / 2);  // Bottom-right corner
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}


void drawBuilding1SmallLeftPlane() {
    glPushMatrix();    // Save current matrix
    // Translate to building 1 left face position
    glTranslatef(BLD1_X - BLD1_WIDTH / 2.0 - 0.8f, BLD1_Y + BLD1_HEIGHT / 2, BLD1_Z);

    const float smallPlaneWidth = 14.0f;    // Small plane width
    const float smallPlaneHeight = 1.7f;    // Small plane height

    const float offsetY = -8.0f;    // Y-axis offset
    const float offsetZ = 5.0f;     // Z-axis offset

    // Translate to specified position
    glTranslatef(0.0f, offsetY, offsetZ);

    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, light1Texture);  // Bind light1 texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white

    // Draw 2D plane
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, smallPlaneWidth / 2);
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}


void drawBuilding1SmallLeftPlane15() {
    glPushMatrix();    // Save current matrix
    // Translate to building 1 left face position
    glTranslatef(BLD1_X - BLD1_WIDTH / 2.0 + 1.8f, BLD1_Y + BLD1_HEIGHT / 2, BLD1_Z);

    const float smallPlaneWidth = 10.0f;    // Small plane width
    const float smallPlaneHeight = 1.7f;    // Small plane height

    const float offsetY = -8.0f;    // Y-axis offset
    const float offsetZ = 20.0f;    // Z-axis offset

    // Translate to specified position
    glTranslatef(0.0f, offsetY, offsetZ);

    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, light1Texture);  // Bind light1 texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white

    // Draw 2D plane
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, smallPlaneWidth / 2);
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}


void drawBuilding1SmallLeftPlane2() {
    glPushMatrix();    // Save current matrix
    // Translate to building 1 left face position
    glTranslatef(BLD1_X - BLD1_WIDTH / 2.0 - 3.5f, BLD1_Y + BLD1_HEIGHT / 2, BLD1_Z);

    const float smallPlaneWidth = 7.0f;     // Small plane width
    const float smallPlaneHeight = 7.0f;    // Small plane height

    const float offsetY = 16.0f;    // Y-axis offset
    const float offsetZ = -3.2f;    // Z-axis offset

    // 1. First translate to specified position
    glTranslatef(0.0f, offsetY, offsetZ);
    // 2. Rotate 90 degrees around Y-axis
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);

    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, light2Texture);  // Bind light2 texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white

    // Draw 2D plane
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, smallPlaneWidth / 2);
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}


void drawBuilding1SmallLeftPlane3() {
    glPushMatrix();    // Save current matrix
    // Translate to building 1 left face position
    glTranslatef(BLD1_X - BLD1_WIDTH / 30.5f, BLD1_Y + BLD1_HEIGHT / 2, BLD1_Z);

    const float smallPlaneWidth = 9.4f;      // Small plane width
    const float smallPlaneHeight = 14.9f;    // Small plane height

    const float offsetY = 11.9f;    // Y-axis offset
    const float offsetZ = 6.9f;     // Z-axis offset

    // Translate to specified position then rotate 90 degrees
    glTranslatef(0.0f, offsetY, offsetZ);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);

    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, posterTexture);  // Bind poster texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white

    // Draw 2D plane
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, smallPlaneWidth / 2);
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}

void drawBuilding1SmallLeftPlane4() {
    glPushMatrix();    // Save current matrix
    // Translate to building 1 left face position
    glTranslatef(BLD1_X - BLD1_WIDTH / 30.5 - 37.0f, BLD1_Y + BLD1_HEIGHT / 2, BLD1_Z);

    const float smallPlaneWidth = 8.0f;     // Small plane width
    const float smallPlaneHeight = 1.0f;    // Small plane height

    const float offsetY = -12.5f;   // Y-axis offset
    const float offsetZ = 38.0f;    // Z-axis offset

    // Translate to specified position then rotate 25 degrees
    glTranslatef(0.0f, offsetY, offsetZ);
    glRotatef(25.0f, 0.0f, 1.0f, 0.0f);

    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, light1Texture);  // Bind light1 texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white

    // Draw 2D plane
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, smallPlaneWidth / 2);
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}


void drawBuilding1SmallLeftPlane5() {
    glPushMatrix();    // Save current matrix
    // Translate to building 1 left face position
    glTranslatef(BLD1_X - BLD1_WIDTH / 30.5 - 39.0f, BLD1_Y + BLD1_HEIGHT / 2, BLD1_Z);

    const float smallPlaneWidth = 4.0f;     // Small plane width
    const float smallPlaneHeight = 4.0f;    // Small plane height

    const float offsetY = -3.0f;    // Y-axis offset
    const float offsetZ = 22.5f;    // Z-axis offset

    // Translate to specified position then rotate -65 degrees
    glTranslatef(0.0f, offsetY, offsetZ);
    glRotatef(-65.0f, 0.0f, 1.0f, 0.0f);

    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, light2Texture);  // Bind light2 texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white

    // Draw 2D plane
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, smallPlaneWidth / 2);
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}


void drawBuilding1SmallLeftPlane6() {
    glPushMatrix();    // Save current matrix
    // Translate to building 1 left face position
    glTranslatef(BLD1_X - BLD1_WIDTH / 30.5 - 34.0f, BLD1_Y + BLD1_HEIGHT / 2, BLD1_Z);

    const float smallPlaneWidth = 4.5f;     // Small plane width
    const float smallPlaneHeight = 6.5f;    // Small plane height

    const float offsetY = -5.0f;    // Y-axis offset
    const float offsetZ = 20.0f;    // Z-axis offset

    // Translate to specified position then rotate -65 degrees
    glTranslatef(0.0f, offsetY, offsetZ);
    glRotatef(-65.0f, 0.0f, 1.0f, 0.0f);

    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, posterTexture);  // Bind poster texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white

    // Draw 2D plane
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, smallPlaneWidth / 2);
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}


void drawBuilding1SmallLeftPlane7() {
    glPushMatrix();    // Save current matrix
    // Translate to building 1 left face position
    glTranslatef(BLD1_X - BLD1_WIDTH / 30.5 - 41.2f, BLD1_Y + BLD1_HEIGHT / 2, BLD1_Z);

    const float smallPlaneWidth = 8.0f;     // Small plane width
    const float smallPlaneHeight = 1.0f;    // Small plane height

    const float offsetY = -12.5f;   // Y-axis offset
    const float offsetZ = 29.0f;    // Z-axis offset

    // Translate to specified position then rotate 25 degrees
    glTranslatef(0.0f, offsetY, offsetZ);
    glRotatef(25.0f, 0.0f, 1.0f, 0.0f);

    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, light1Texture);  // Bind light1 texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white

    // Draw 2D plane
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, smallPlaneWidth / 2);
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}

void drawBuilding1SmallLeftPlane8() {
    glPushMatrix();    // Save current matrix
    // Translate to building 1 left face position
    glTranslatef(BLD1_X - BLD1_WIDTH / 30.5 - 26.8f, BLD1_Y + BLD1_HEIGHT / 2, BLD1_Z);

    const float smallPlaneWidth = 2.0f;      // Small plane width
    const float smallPlaneHeight = 10.0f;    // Small plane height

    const float offsetY = -1.5f;    // Y-axis offset
    const float offsetZ = -2.0f;    // Z-axis offset

    // Translate to specified position then rotate 90 degrees
    glTranslatef(0.0f, offsetY, offsetZ);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);

    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, light3Texture);  // Bind light3 texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white

    // Draw 2D plane
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, smallPlaneWidth / 2);
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}


void drawBuilding1SmallLeftPlane9() {
    glPushMatrix();    // Save current matrix
    // Translate to building 1 left face position
    glTranslatef(BLD1_X - BLD1_WIDTH / 30.5 - 8.8f, BLD1_Y + BLD1_HEIGHT / 2, BLD1_Z);

    const float smallPlaneWidth = 2.0f;      // Small plane width
    const float smallPlaneHeight = 10.0f;    // Small plane height

    const float offsetY = 7.5f;     // Y-axis offset
    const float offsetZ = -66.0f;   // Z-axis offset

    // Translate to specified position then rotate 90 degrees
    glTranslatef(0.0f, offsetY, offsetZ);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);

    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, light3Texture);  // Bind light3 texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white

    // Draw 2D plane
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, smallPlaneWidth / 2);
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}


void drawBuilding1SmallLeftPlane10() {
    glPushMatrix();    // Save current matrix
    // Translate to building 1 left face position
    glTranslatef(BLD1_X - BLD1_WIDTH / 30.5 - 8.7f, BLD1_Y + BLD1_HEIGHT / 2, BLD1_Z);

    const float smallPlaneWidth = 2.0f;     // Small plane width
    const float smallPlaneHeight = 5.0f;    // Small plane height

    const float offsetY = -0.5f;    // Y-axis offset
    const float offsetZ = -66.0f;   // Z-axis offset

    // Translate to specified position then rotate 90 degrees
    glTranslatef(0.0f, offsetY, offsetZ);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);

    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, light4Texture);  // Bind light4 texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white

    // Draw 2D plane
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, smallPlaneWidth / 2);
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}


void drawBuilding1SmallLeftPlane11() {
    glPushMatrix();    // Save current matrix
    // Translate to building 1 left face position
    glTranslatef(BLD1_X - BLD1_WIDTH / 30.5 - 3.0f, BLD1_Y + BLD1_HEIGHT / 2, BLD1_Z);

    const float smallPlaneWidth = 6.5f;     // Small plane width
    const float smallPlaneHeight = 8.5f;    // Small plane height

    const float offsetY = 6.8f;     // Y-axis offset
    const float offsetZ = -75.5f;   // Z-axis offset

    // Translate to specified position then rotate 90 degrees
    glTranslatef(0.0f, offsetY, offsetZ);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);

    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, posterTexture);  // Bind poster texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white

    // Draw 2D plane
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, smallPlaneWidth / 2);
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}


void drawBuilding1SmallLeftPlane12() {
    glPushMatrix();    // Save current matrix
    // Translate to building 1 left face position
    glTranslatef(BLD1_X - BLD1_WIDTH / 30.5 + 4.2f, BLD1_Y + BLD1_HEIGHT / 2, BLD1_Z);

    const float smallPlaneWidth = 5.0f;     // Small plane width
    const float smallPlaneHeight = 5.0f;    // Small plane height

    const float offsetY = 8.8f;     // Y-axis offset
    const float offsetZ = -78.5f;   // Z-axis offset

    // Translate to specified position then rotate 90 degrees
    glTranslatef(0.0f, offsetY, offsetZ);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);

    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, light2Texture);  // Bind light2 texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white

    // Draw 2D plane
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, smallPlaneWidth / 2);
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}


void drawBuilding1SmallLeftPlane13() {
    glPushMatrix();    // Save current matrix
    // Translate to building 1 left face position
    glTranslatef(BLD1_X - BLD1_WIDTH / 30.5 + 7.2f, BLD1_Y + BLD1_HEIGHT / 2, BLD1_Z);

    const float smallPlaneWidth = 6.5f;     // Small plane width
    const float smallPlaneHeight = 8.5f;    // Small plane height

    const float offsetY = -1.8f;    // Y-axis offset
    const float offsetZ = -84.6f;   // Z-axis offset

    // Translate to specified position then rotate 90 degrees
    glTranslatef(0.0f, offsetY, offsetZ);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);

    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, poster2Texture);  // Bind poster2 texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white

    // Draw 2D plane
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, smallPlaneWidth / 2);
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}

void drawBuilding1SmallLeftPlane14() {
    glPushMatrix();    // Save current matrix
    // Translate to building 1 left face position
    glTranslatef(BLD1_X - BLD1_WIDTH / 30.5 + 0.9f, BLD1_Y + BLD1_HEIGHT / 2, BLD1_Z);

    const float smallPlaneWidth = 2.0f;     // Small plane width
    const float smallPlaneHeight = 5.0f;    // Small plane height

    const float offsetY = 2.5f;     // Y-axis offset
    const float offsetZ = -33.0f;   // Z-axis offset

    // Translate to specified position then rotate 90 degrees
    glTranslatef(0.0f, offsetY, offsetZ);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);

    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, light4Texture);  // Bind light4 texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white

    // Draw 2D plane
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, smallPlaneWidth / 2);
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}
void drawBuilding1SmallLeftPlane16() {
    glPushMatrix();    // Save current matrix
    // Translate to building 1 left face position
    glTranslatef(BLD1_X - BLD1_WIDTH / 2.0 + 1.8f, BLD1_Y + BLD1_HEIGHT / 2, BLD1_Z);

    const float smallPlaneWidth = 8.5f;      // Small plane width
    const float smallPlaneHeight = 16.5f;    // Small plane height

    const float offsetY = 1.0f;     // Y-axis offset
    const float offsetZ = 31.0f;    // Z-axis offset

    // Translate to specified position
    glTranslatef(0.0f, offsetY, offsetZ);

    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, poster2Texture);  // Bind poster2 texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white

    // Draw 2D plane
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, smallPlaneWidth / 2);
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}


void drawBuilding1SmallLeftPlane17() {
    glPushMatrix();    // Save current matrix
    // Translate to building 1 left face position
    glTranslatef(BLD1_X - BLD1_WIDTH / 2.0 + 1.8f, BLD1_Y + BLD1_HEIGHT / 2, BLD1_Z);

    const float smallPlaneWidth = 2.0f;      // Small plane width
    const float smallPlaneHeight = 10.0f;    // Small plane height

    const float offsetY = 1.0f;     // Y-axis offset
    const float offsetZ = 14.0f;    // Z-axis offset

    // Translate to specified position (no rotation)
    glTranslatef(0.0f, offsetY, offsetZ);

    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, light3Texture);  // Bind light3 texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white

    // Draw 2D plane
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, smallPlaneWidth / 2);
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}


void drawBuilding1SmallLeftPlane18() {
    glPushMatrix();    // Save current matrix
    // Translate to building 1 left face position
    glTranslatef(BLD1_X - BLD1_WIDTH / 2.0 - 1.8f, BLD1_Y + BLD1_HEIGHT / 2, BLD1_Z);

    const float smallPlaneWidth = 50.0f;     // Small plane width
    const float smallPlaneHeight = 0.3f;     // Small plane height (very thin)

    const float offsetY = 6.5f;     // Y-axis offset
    const float offsetZ = -0.5f;    // Z-axis offset

    // Translate to specified position then rotate -95 degrees
    glTranslatef(0.0f, offsetY, offsetZ);
    glRotatef(-95.0f, 0.0f, 1.0f, 0.0f);

    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, light5Texture);  // Bind light5 texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white

    // Draw 2D plane
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, smallPlaneWidth / 2);
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}


void drawBuilding1SmallLeftPlane19() {
    glPushMatrix();    // Save current matrix
    // Translate to building 1 left face position
    glTranslatef(BLD1_X - BLD1_WIDTH / 2.0 - 1.8f, BLD1_Y + BLD1_HEIGHT / 2, BLD1_Z);

    const float smallPlaneWidth = 50.0f;     // Small plane width
    const float smallPlaneHeight = 0.3f;     // Small plane height (very thin)

    const float offsetY = -11.7f;   // Y-axis offset
    const float offsetZ = -25.0f;   // Z-axis offset

    // Translate to specified position then rotate -75 degrees
    glTranslatef(0.0f, offsetY, offsetZ);
    glRotatef(-75.0f, 0.0f, 1.0f, 0.0f);

    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, light5Texture);  // Bind light5 texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white

    // Draw 2D plane
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, smallPlaneWidth / 2);
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}

void drawBuilding1SmallLeftPlane20() {
    glPushMatrix();    // Save current matrix
    // Translate to building 1 left face position
    glTranslatef(BLD1_X - BLD1_WIDTH / 30.5 - 37.0f, BLD1_Y + BLD1_HEIGHT / 2, BLD1_Z);

    const float smallPlaneWidth = 50.0f;     // Small plane width
    const float smallPlaneHeight = 0.3f;     // Small plane height (very thin)

    const float offsetY = 0.0f;      // Y-axis offset
    const float offsetZ = 38.0f;     // Z-axis offset

    // Translate to specified position then rotate 25 degrees
    glTranslatef(0.0f, offsetY, offsetZ);
    glRotatef(25.0f, 0.0f, 1.0f, 0.0f);

    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, light5Texture);  // Bind light5 texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white

    // Draw 2D plane
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, smallPlaneWidth / 2);
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}


void drawBuilding1SmallLeftPlane21() {
    glPushMatrix();    // Save current matrix
    // Translate to building 1 left face position
    glTranslatef(BLD1_X - BLD1_WIDTH / 30.5 - 37.0f, BLD1_Y + BLD1_HEIGHT / 2, BLD1_Z);

    const float smallPlaneWidth = 14.0f;     // Small plane width
    const float smallPlaneHeight = 0.3f;     // Small plane height (very thin)

    const float offsetY = 0.0f;      // Y-axis offset
    const float offsetZ = 21.3f;     // Z-axis offset

    // Translate to specified position then rotate -65 degrees
    glTranslatef(0.0f, offsetY, offsetZ);
    glRotatef(-65.0f, 0.0f, 1.0f, 0.0f);

    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, light5Texture);  // Bind light5 texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white

    // Draw 2D plane
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, smallPlaneWidth / 2);
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}


void drawBuilding1SmallLeftPlane22() {
    glPushMatrix();    // Save current matrix
    // Translate to building 1 left face position
    glTranslatef(BLD1_X - BLD1_WIDTH / 30.5 - 37.0f, BLD1_Y + BLD1_HEIGHT / 2, BLD1_Z);

    const float smallPlaneWidth = 32.0f;     // Small plane width
    const float smallPlaneHeight = 0.3f;     // Small plane height (very thin)

    const float offsetY = 0.0f;      // Y-axis offset
    const float offsetZ = 42.6f;     // Z-axis offset

    // Translate to specified position then rotate -65 degrees
    glTranslatef(0.0f, offsetY, offsetZ);
    glRotatef(-65.0f, 0.0f, 1.0f, 0.0f);

    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, light5Texture);  // Bind light5 texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white

    // Draw 2D plane
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, smallPlaneWidth / 2);
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}

void drawBuilding1SmallLeftPlane23() {
    glPushMatrix();    // Save current matrix
    // Translate to building 1 left face position
    glTranslatef(BLD1_X - BLD1_WIDTH / 30.5 - 36.6f, BLD1_Y + BLD1_HEIGHT / 2, BLD1_Z);

    const float smallPlaneWidth = 7.0f;     // Small plane width
    const float smallPlaneHeight = 5.0f;    // Small plane height

    const float offsetY = -6.5f;    // Y-axis offset
    const float offsetZ = 38.0f;    // Z-axis offset

    // Translate to specified position then rotate 25 degrees
    glTranslatef(0.0f, offsetY, offsetZ);
    glRotatef(25.0f, 0.0f, 1.0f, 0.0f);

    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, mapTexture);  // Bind map texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white

    // Draw 2D plane
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, smallPlaneWidth / 2);
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}


void drawBuilding1SmallLeftPlane24() {
    glPushMatrix();    // Save current matrix
    // Translate to building 1 left face position
    glTranslatef(BLD1_X - BLD1_WIDTH / 30.5 + 2.5f, BLD1_Y + BLD1_HEIGHT / 2, BLD1_Z);

    const float smallPlaneWidth = 0.3f;      // Small plane width (very narrow)
    const float smallPlaneHeight = 40.0f;    // Small plane height

    const float offsetY = -6.0f;    // Y-axis offset
    const float offsetZ = -24.9f;   // Z-axis offset

    // Translate to specified position then rotate 90 degrees
    glTranslatef(0.0f, offsetY, offsetZ);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);

    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, light5Texture);  // Bind light5 texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white

    // Draw 2D plane
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, smallPlaneWidth / 2);
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}


void drawBuilding1SmallLeftPlane25() {
    glPushMatrix();    // Save current matrix
    // Translate to building 1 left face position
    glTranslatef(BLD1_X - BLD1_WIDTH / 30.5 - 22.0f, BLD1_Y + BLD1_HEIGHT / 2, BLD1_Z);

    const float smallPlaneWidth = 0.3f;      // Small plane width (very narrow)
    const float smallPlaneHeight = 46.0f;    // Small plane height

    const float offsetY = -6.0f;    // Y-axis offset
    const float offsetZ = -13.3f;   // Z-axis offset

    // Translate to specified position then rotate 90 degrees
    glTranslatef(0.0f, offsetY, offsetZ);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);

    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, light5Texture);  // Bind light5 texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white

    // Draw 2D plane
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, smallPlaneWidth / 2);
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}


void drawBuilding1SmallLeftPlane26() {
    glPushMatrix();    // Save current matrix
    // Translate to building 1 left face position
    glTranslatef(BLD1_X - BLD1_WIDTH / 30.5 - 27.8f, BLD1_Y + BLD1_HEIGHT / 2, BLD1_Z);

    const float smallPlaneWidth = 0.3f;      // Small plane width (very narrow)
    const float smallPlaneHeight = 46.0f;    // Small plane height

    const float offsetY = -6.0f;    // Y-axis offset
    const float offsetZ = 0.3f;     // Z-axis offset

    // Translate to specified position then rotate 90 degrees
    glTranslatef(0.0f, offsetY, offsetZ);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);

    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, light5Texture);  // Bind light5 texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white

    // Draw 2D plane
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, smallPlaneWidth / 2);
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}


void drawBuilding1SmallLeftPlane27() {
    glPushMatrix();    // Save current matrix
    // Translate to building 1 left face position
    glTranslatef(BLD1_X - BLD1_WIDTH / 30.5 - 30.8f, BLD1_Y + BLD1_HEIGHT / 2, BLD1_Z);

    const float smallPlaneWidth = 400.0f;    // Small plane width
    const float smallPlaneHeight = 406.0f;   // Small plane height
    const float offsetY = -19.9f;   // Y-axis offset
    const float offsetZ = 0.3f;     // Z-axis offset

    // Translate to specified position then perform complex rotation
    glTranslatef(0.0f, offsetY, offsetZ);
    // First rotate 90 degrees around Y-axis, then 90 degrees around X-axis
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);

    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, groundTexture);  // Bind ground texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white

    // Draw 2D plane
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, -smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, smallPlaneHeight / 2, smallPlaneWidth / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -smallPlaneHeight / 2, smallPlaneWidth / 2);
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}

void drawBuilding1FrontPlane() {
    glPushMatrix();    // Save current matrix
    glTranslatef(BLD1_X, BLD1_Y + BLD1_HEIGHT / 2, BLD1_Z + BLD1_DEPTH / 2 + 0.01f);  // Translate to building front face
    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, buildingTexture);  // Bind building texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-BLD1_WIDTH / 2, -BLD1_HEIGHT / 2, 0.0f);   // Bottom-left corner
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-BLD1_WIDTH / 2, BLD1_HEIGHT / 2, 0.0f);    // Top-left corner
    glTexCoord2f(1.0f, 1.0f); glVertex3f(BLD1_WIDTH / 2, BLD1_HEIGHT / 2, 0.0f);     // Top-right corner
    glTexCoord2f(1.0f, 0.0f); glVertex3f(BLD1_WIDTH / 2, -BLD1_HEIGHT / 2, 0.0f);    // Bottom-right corner
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}

// Add textured 2D plane to building 2 front (Z-axis forward)
void drawBuilding2FrontPlane() {
    glPushMatrix();    // Save current matrix
    glTranslatef(BLD2_X, BLD2_Y + BLD2_HEIGHT / 2, BLD2_Z + BLD2_DEPTH / 2 + 0.01f);  // Translate to building front face
    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, buildingTexture);  // Bind building texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-BLD2_WIDTH / 2, -BLD2_HEIGHT / 2, 0.0f);   // Bottom-left corner
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-BLD2_WIDTH / 2, BLD2_HEIGHT / 2, 0.0f);    // Top-left corner
    glTexCoord2f(1.0f, 1.0f); glVertex3f(BLD2_WIDTH / 2, BLD2_HEIGHT / 2, 0.0f);     // Top-right corner
    glTexCoord2f(1.0f, 0.0f); glVertex3f(BLD2_WIDTH / 2, -BLD2_HEIGHT / 2, 0.0f);    // Bottom-right corner
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}

// Add textured 2D plane to building 2 right (X-axis right)
void drawBuilding2RightPlane() {
    glPushMatrix();    // Save current matrix
    glTranslatef(BLD2_X + BLD2_WIDTH / 2 + 0.01f, BLD2_Y + BLD2_HEIGHT / 2, BLD2_Z);  // Translate to building right face
    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, buildingTexture);  // Bind building texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -BLD2_HEIGHT / 2, -BLD2_DEPTH / 2);   // Back-bottom corner
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, BLD2_HEIGHT / 2, -BLD2_DEPTH / 2);    // Back-top corner
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, BLD2_HEIGHT / 2, BLD2_DEPTH / 2);     // Front-top corner
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -BLD2_HEIGHT / 2, BLD2_DEPTH / 2);    // Front-bottom corner
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}

// Add textured 2D plane to building 3 front (Z-axis forward)
void drawBuilding3FrontPlane() {
    glPushMatrix();    // Save current matrix
    glTranslatef(BLD3_X, BLD3_Y + BLD3_HEIGHT / 2, BLD3_Z + BLD3_DEPTH / 2 + 0.01f);  // Translate to building front face
    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, buildingTexture);  // Bind building texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-BLD3_WIDTH / 2, -BLD3_HEIGHT / 2, 0.0f);   // Bottom-left corner
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-BLD3_WIDTH / 2, BLD3_HEIGHT / 2, 0.0f);    // Top-left corner
    glTexCoord2f(1.0f, 1.0f); glVertex3f(BLD3_WIDTH / 2, BLD3_HEIGHT / 2, 0.0f);     // Top-right corner
    glTexCoord2f(1.0f, 0.0f); glVertex3f(BLD3_WIDTH / 2, -BLD3_HEIGHT / 2, 0.0f);    // Bottom-right corner
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}

// Add textured 2D plane to building 3 right (X-axis right)
void drawBuilding3RightPlane() {
    glPushMatrix();    // Save current matrix
    glTranslatef(BLD3_X + BLD3_WIDTH / 2 + 0.01f, BLD3_Y + BLD3_HEIGHT / 2, BLD3_Z);  // Translate to building right face
    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, buildingTexture);  // Bind building texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -BLD3_HEIGHT / 2, -BLD3_DEPTH / 2);   // Back-bottom corner
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, BLD3_HEIGHT / 2, -BLD3_DEPTH / 2);    // Back-top corner
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, BLD3_HEIGHT / 2, BLD3_DEPTH / 2);     // Front-top corner
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -BLD3_HEIGHT / 2, BLD3_DEPTH / 2);    // Front-bottom corner
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}

// Add textured 2D plane to building 4 front (Z-axis forward)
void drawBuilding4FrontPlane() {
    glPushMatrix();    // Save current matrix
    glTranslatef(BLD4_X, BLD4_Y + BLD4_HEIGHT / 2, BLD4_Z + BLD4_DEPTH / 2 + 0.1f);  // Translate to building front face
    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, buildingTexture);  // Bind building texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-BLD4_WIDTH / 2, -BLD4_HEIGHT / 2, 0.0f);   // Bottom-left corner
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-BLD4_WIDTH / 2, BLD4_HEIGHT / 2, 0.0f);    // Top-left corner
    glTexCoord2f(1.0f, 1.0f); glVertex3f(BLD4_WIDTH / 2, BLD4_HEIGHT / 2, 0.0f);     // Top-right corner
    glTexCoord2f(1.0f, 0.0f); glVertex3f(BLD4_WIDTH / 2, -BLD4_HEIGHT / 2, 0.0f);    // Bottom-right corner
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}

// Add textured 2D plane to building 4 right (X-axis right)
void drawBuilding4RightPlane() {
    glPushMatrix();    // Save current matrix
    glTranslatef(BLD4_X + BLD4_WIDTH / 2 + 0.01f, BLD4_Y + BLD4_HEIGHT / 2, BLD4_Z);  // Translate to building right face
    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, buildingTexture);  // Bind building texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -BLD4_HEIGHT / 2, -BLD4_DEPTH / 2);   // Back-bottom corner
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, BLD4_HEIGHT / 2, -BLD4_DEPTH / 2);    // Back-top corner
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, BLD4_HEIGHT / 2, BLD4_DEPTH / 2);     // Front-top corner
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -BLD4_HEIGHT / 2, BLD4_DEPTH / 2);    // Front-bottom corner
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}

// Add textured 2D plane to building 4 left (X-axis left)
void drawBuilding4LeftPlane() {
    glPushMatrix();    // Save current matrix
    glTranslatef(BLD4_X - BLD4_WIDTH / 2 - 0.01f, BLD4_Y + BLD4_HEIGHT / 2, BLD4_Z);  // Translate to building left face
    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, buildingTexture);  // Bind building texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -BLD4_HEIGHT / 2, BLD4_DEPTH / 2);    // Front-bottom corner
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, BLD4_HEIGHT / 2, BLD4_DEPTH / 2);     // Front-top corner
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, BLD4_HEIGHT / 2, -BLD4_DEPTH / 2);    // Back-top corner
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -BLD4_HEIGHT / 2, -BLD4_DEPTH / 2);   // Back-bottom corner
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}

// Add textured 2D plane to building 5 front (Z-axis forward)
void drawBuilding5FrontPlane() {
    glPushMatrix();    // Save current matrix
    glTranslatef(BLD5_X, BLD5_Y + BLD5_HEIGHT / 2, BLD5_Z + BLD5_DEPTH / 2 + 0.1f);  // Translate to building front face
    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, buildingTexture);  // Bind building texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-BLD5_WIDTH / 2, -BLD5_HEIGHT / 2, 0.0f);   // Bottom-left corner
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-BLD5_WIDTH / 2, BLD5_HEIGHT / 2, 0.0f);    // Top-left corner
    glTexCoord2f(1.0f, 1.0f); glVertex3f(BLD5_WIDTH / 2, BLD5_HEIGHT / 2, 0.0f);     // Top-right corner
    glTexCoord2f(1.0f, 0.0f); glVertex3f(BLD5_WIDTH / 2, -BLD5_HEIGHT / 2, 0.0f);    // Bottom-right corner
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}

// Add textured 2D plane to building 5 right (X-axis right)
void drawBuilding5RightPlane() {
    glPushMatrix();    // Save current matrix
    glTranslatef(BLD5_X + BLD5_WIDTH / 2 + 0.01f, BLD5_Y + BLD5_HEIGHT / 2, BLD5_Z);  // Translate to building right face
    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, buildingTexture);  // Bind building texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -BLD5_HEIGHT / 2, -BLD5_DEPTH / 2);   // Back-bottom corner
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, BLD5_HEIGHT / 2, -BLD5_DEPTH / 2);    // Back-top corner
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, BLD5_HEIGHT / 2, BLD5_DEPTH / 2);     // Front-top corner
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -BLD5_HEIGHT / 2, BLD5_DEPTH / 2);    // Front-bottom corner
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}

// Add textured 2D plane to building 5 left (X-axis left)
void drawBuilding5LeftPlane() {
    glPushMatrix();    // Save current matrix
    glTranslatef(BLD5_X - BLD5_WIDTH / 2 - 0.01f, BLD5_Y + BLD5_HEIGHT / 2, BLD5_Z);  // Translate to building left face
    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, buildingTexture);  // Bind building texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -BLD5_HEIGHT / 2, BLD5_DEPTH / 2);    // Front-bottom corner
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, BLD5_HEIGHT / 2, BLD5_DEPTH / 2);     // Front-top corner
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, BLD5_HEIGHT / 2, -BLD5_DEPTH / 2);    // Back-top corner
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -BLD5_HEIGHT / 2, -BLD5_DEPTH / 2);   // Back-bottom corner
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}

// Add textured 2D plane to building 6 front (Z-axis forward)
void drawBuilding6FrontPlane() {
    glPushMatrix();    // Save current matrix
    glTranslatef(BLD6_X, BLD6_Y + BLD6_HEIGHT / 2, BLD6_Z + BLD6_DEPTH / 2 + 0.01f);  // Translate to building front face
    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, buildingTexture);  // Bind building texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-BLD6_WIDTH / 2, -BLD6_HEIGHT / 2, 0.0f);   // Bottom-left corner
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-BLD6_WIDTH / 2, BLD6_HEIGHT / 2, 0.0f);    // Top-left corner
    glTexCoord2f(1.0f, 1.0f); glVertex3f(BLD6_WIDTH / 2, BLD6_HEIGHT / 2, 0.0f);     // Top-right corner
    glTexCoord2f(1.0f, 0.0f); glVertex3f(BLD6_WIDTH / 2, -BLD6_HEIGHT / 2, 0.0f);    // Bottom-right corner
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}

// Add textured 2D plane to building 6 left (X-axis left)
void drawBuilding6LeftPlane() {
    glPushMatrix();    // Save current matrix
    glTranslatef(BLD6_X - BLD6_WIDTH / 2 - 0.01f, BLD6_Y + BLD6_HEIGHT / 2, BLD6_Z);  // Translate to building left face
    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, buildingTexture);  // Bind building texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -BLD6_HEIGHT / 2, BLD6_DEPTH / 2);    // Front-bottom corner
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, BLD6_HEIGHT / 2, BLD6_DEPTH / 2);     // Front-top corner
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, BLD6_HEIGHT / 2, -BLD6_DEPTH / 2);    // Back-top corner
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -BLD6_HEIGHT / 2, -BLD6_DEPTH / 2);   // Back-bottom corner
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}

// Add textured 2D plane to building 7 left (X-axis left)
void drawBuilding7LeftPlane() {
    glPushMatrix();    // Save current matrix
    glTranslatef(BLD7_X - BLD7_WIDTH / 2 - 0.01f, BLD7_Y + BLD7_HEIGHT / 2, BLD7_Z);  // Translate to building left face
    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, buildingTexture);  // Bind building texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -BLD7_HEIGHT / 2, BLD7_DEPTH / 2);    // Front-bottom corner
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, BLD7_HEIGHT / 2, BLD7_DEPTH / 2);     // Front-top corner
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, BLD7_HEIGHT / 2, -BLD7_DEPTH / 2);    // Back-top corner
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -BLD7_HEIGHT / 2, -BLD7_DEPTH / 2);   // Back-bottom corner
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}

// Add textured 2D plane to building 8 left (X-axis left)
void drawBuilding8LeftPlane() {
    glPushMatrix();    // Save current matrix
    glTranslatef(BLD8_X - BLD8_WIDTH / 2 - 0.01f, BLD8_Y + BLD8_HEIGHT / 2, BLD8_Z);  // Translate to building left face
    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, buildingTexture);  // Bind building texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -BLD8_HEIGHT / 2, BLD8_DEPTH / 2);    // Front-bottom corner
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, BLD8_HEIGHT / 2, BLD8_DEPTH / 2);     // Front-top corner
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, BLD8_HEIGHT / 2, -BLD8_DEPTH / 2);    // Back-top corner
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -BLD8_HEIGHT / 2, -BLD8_DEPTH / 2);   // Back-bottom corner
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}

// Add textured 2D plane to building 7 front (Z-axis forward)
void drawBuilding7FrontPlane() {
    glPushMatrix();    // Save current matrix
    glTranslatef(BLD7_X, BLD7_Y + BLD7_HEIGHT / 2, BLD7_Z + BLD7_DEPTH / 2 + 0.1f);  // Translate to building front face
    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, buildingTexture);  // Bind building texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-BLD7_WIDTH / 2, -BLD7_HEIGHT / 2, 0.0f);   // Bottom-left corner
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-BLD7_WIDTH / 2, BLD7_HEIGHT / 2, 0.0f);    // Top-left corner
    glTexCoord2f(1.0f, 1.0f); glVertex3f(BLD7_WIDTH / 2, BLD7_HEIGHT / 2, 0.0f);     // Top-right corner
    glTexCoord2f(1.0f, 0.0f); glVertex3f(BLD7_WIDTH / 2, -BLD7_HEIGHT / 2, 0.0f);    // Bottom-right corner
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}

// Add textured 2D plane to building 8 front (Z-axis forward)
void drawBuilding8FrontPlane() {
    glPushMatrix();    // Save current matrix
    glTranslatef(BLD8_X, BLD8_Y + BLD8_HEIGHT / 2, BLD8_Z + BLD8_DEPTH / 2 + 0.1f);  // Translate to building front face
    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, buildingTexture);  // Bind building texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-BLD8_WIDTH / 2, -BLD8_HEIGHT / 2, 0.0f);   // Bottom-left corner
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-BLD8_WIDTH / 2, BLD8_HEIGHT / 2, 0.0f);    // Top-left corner
    glTexCoord2f(1.0f, 1.0f); glVertex3f(BLD8_WIDTH / 2, BLD8_HEIGHT / 2, 0.0f);     // Top-right corner
    glTexCoord2f(1.0f, 0.0f); glVertex3f(BLD8_WIDTH / 2, -BLD8_HEIGHT / 2, 0.0f);    // Bottom-right corner
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}

// Add textured 2D plane to building 9 front (Z-axis forward)
void drawBuilding9FrontPlane() {
    glPushMatrix();    // Save current matrix
    glTranslatef(BLD9_X, BLD9_Y + BLD9_HEIGHT / 2, BLD9_Z + BLD9_DEPTH / 2 + 0.1f);  // Translate to building front face
    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, buildingTexture);  // Bind building texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-BLD9_WIDTH / 2, -BLD9_HEIGHT / 2, 0.0f);   // Bottom-left corner
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-BLD9_WIDTH / 2, BLD9_HEIGHT / 2, 0.0f);    // Top-left corner
    glTexCoord2f(1.0f, 1.0f); glVertex3f(BLD9_WIDTH / 2, BLD9_HEIGHT / 2, 0.0f);     // Top-right corner
    glTexCoord2f(1.0f, 0.0f); glVertex3f(BLD9_WIDTH / 2, -BLD9_HEIGHT / 2, 0.0f);    // Bottom-right corner
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}

// Add textured 2D plane to building 9 right (X-axis right)
void drawBuilding9RightPlane() {
    glPushMatrix();    // Save current matrix
    glTranslatef(BLD9_X + BLD9_WIDTH / 2 + 0.01f, BLD9_Y + BLD9_HEIGHT / 2, BLD9_Z);  // Translate to building right face
    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, buildingTexture);  // Bind building texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -BLD9_HEIGHT / 2, -BLD9_DEPTH / 2);   // Back-bottom corner
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, BLD9_HEIGHT / 2, -BLD9_DEPTH / 2);    // Back-top corner
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, BLD9_HEIGHT / 2, BLD9_DEPTH / 2);     // Front-top corner
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -BLD9_HEIGHT / 2, BLD9_DEPTH / 2);    // Front-bottom corner
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}

// Add textured 2D plane to building 9 left (X-axis left)
void drawBuilding9LeftPlane() {
    glPushMatrix();    // Save current matrix
    glTranslatef(BLD9_X - BLD9_WIDTH / 2 - 0.01f, BLD9_Y + BLD9_HEIGHT / 2, BLD9_Z);  // Translate to building left face
    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, buildingTexture);  // Bind building texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -BLD9_HEIGHT / 2, BLD9_DEPTH / 2);    // Front-bottom corner
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, BLD9_HEIGHT / 2, BLD9_DEPTH / 2);     // Front-top corner
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, BLD9_HEIGHT / 2, -BLD9_DEPTH / 2);    // Back-top corner
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -BLD9_HEIGHT / 2, -BLD9_DEPTH / 2);   // Back-bottom corner
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}

// Add textured 2D plane to building 10 left (X-axis left)
void drawBuilding10LeftPlane() {
    glPushMatrix();    // Save current matrix
    glTranslatef(BLD10_X - BLD10_WIDTH / 2 - 0.01f, BLD10_Y + BLD10_HEIGHT / 2, BLD10_Z);  // Translate to building left face
    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, buildingTexture);  // Bind building texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -BLD10_HEIGHT / 2, BLD10_DEPTH / 2);  // Front-bottom corner
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, BLD10_HEIGHT / 2, BLD10_DEPTH / 2);   // Front-top corner
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, BLD10_HEIGHT / 2, -BLD10_DEPTH / 2);  // Back-top corner
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -BLD10_HEIGHT / 2, -BLD10_DEPTH / 2); // Back-bottom corner
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}

// ====================== Building 14 Top and Bottom Plane Drawing Functions ======================
// Add a 2D plane above the top of building 14
void drawBuilding14TopTopPlane() {
    glPushMatrix();    // Save current matrix
    // Translate to building 14 position
    glTranslatef(BLD14_X, BLD14_Y, BLD14_Z);
    // Rotate 25 degrees (consistent with building 14's rotation)
    glRotatef(25.0f, 0.0f, 1.0f, 0.0f);
    // Move upward to above the top (half of building 14 height + half of building 14 height)
    glTranslatef(0.0f, BLD14_HEIGHT + 0.01f, 0.0f);

    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, subwayTexture);  // Use subway ground texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    // Draw downward-facing face (since plane is above building top, looking down at building)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-BLD14_WIDTH / 2, 0.0f, -BLD14_DEPTH / 2);   // Left-back corner
    glTexCoord2f(1.0f, 0.0f); glVertex3f(BLD14_WIDTH / 2, 0.0f, -BLD14_DEPTH / 2);    // Right-back corner
    glTexCoord2f(1.0f, 1.0f); glVertex3f(BLD14_WIDTH / 2, 0.0f, BLD14_DEPTH / 2);     // Right-front corner
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-BLD14_WIDTH / 2, 0.0f, BLD14_DEPTH / 2);    // Left-front corner
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}

// Add a 2D plane below the bottom of building 14
void drawBuilding14BottomBottomPlane() {
    glPushMatrix();    // Save current matrix
    // Translate to building 14 position
    glTranslatef(BLD14_X, BLD14_Y, BLD14_Z);
    // Rotate 25 degrees (consistent with building 14's rotation)
    glRotatef(25.0f, 0.0f, 1.0f, 0.0f);
    // Move downward to below the bottom (half of building 14 height, opposite direction)
    glTranslatef(0.0f, -BLD14_HEIGHT / 2 - 0.01f, 0.0f);

    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, subwayTexture);  // Use same subway texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    // Draw upward-facing face (since plane is below building bottom, looking up at building)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-BLD14_WIDTH / 2, 0.0f, -BLD14_DEPTH / 2);   // Left-back corner
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-BLD14_WIDTH / 2, 0.0f, BLD14_DEPTH / 2);    // Left-front corner
    glTexCoord2f(1.0f, 1.0f); glVertex3f(BLD14_WIDTH / 2, 0.0f, BLD14_DEPTH / 2);     // Right-front corner
    glTexCoord2f(1.0f, 0.0f); glVertex3f(BLD14_WIDTH / 2, 0.0f, -BLD14_DEPTH / 2);    // Right-back corner
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}

// ====================== Other Buildings' Textured 2D Plane Drawing Functions (using subway_wall texture) ======================

// Add an equally-sized 2D plane to the right of building 11's right face
void drawBuilding11RightPlane() {
    glPushMatrix();    // Save current matrix
    // Translate to building 11 position
    glTranslatef(BLD11_X, BLD11_Y, BLD11_Z);
    // Rotate 25 degrees (consistent with building 11's rotation)
    glRotatef(25.0f, 0.0f, 1.0f, 0.0f);
    // Move right to the right side of the right face (half of building 11 width)
    glTranslatef(BLD11_WIDTH / 2 + 0.01f, BLD11_HEIGHT / 2, 0.0f);

    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, subwayWallTexture);  // Use subway_wall wall texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    // Draw left-facing face (since plane is to the right of building right face, looking left at building)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -BLD11_HEIGHT / 2, -BLD11_DEPTH / 2);   // Back-bottom corner
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -BLD11_HEIGHT / 2, BLD11_DEPTH / 2);    // Front-bottom corner
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, BLD11_HEIGHT / 2, BLD11_DEPTH / 2);     // Front-top corner
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, BLD11_HEIGHT / 2, -BLD11_DEPTH / 2);    // Back-top corner
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}

// Add an equally-sized 2D plane behind building 12's back face
void drawBuilding12BackPlane() {
    glPushMatrix();    // Save current matrix
    // Translate to building 12 position
    glTranslatef(BLD12_X, BLD12_Y, BLD12_Z);
    // Rotate 25 degrees (consistent with building 12's rotation)
    glRotatef(25.0f, 0.0f, 1.0f, 0.0f);
    // Move back to behind the back face (half of building 12 depth)
    glTranslatef(0.0f, BLD12_HEIGHT / 2, -BLD12_DEPTH / 2 - 0.01f);

    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, subwayWallTexture);  // Use subway_wall wall texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    // Draw forward-facing face (since plane is behind building back face, looking forward at building)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-BLD12_WIDTH / 2, -BLD12_HEIGHT / 2, 0.0f);   // Bottom-left corner
    glTexCoord2f(1.0f, 0.0f); glVertex3f(BLD12_WIDTH / 2, -BLD12_HEIGHT / 2, 0.0f);    // Bottom-right corner
    glTexCoord2f(1.0f, 1.0f); glVertex3f(BLD12_WIDTH / 2, BLD12_HEIGHT / 2, 0.0f);     // Top-right corner
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-BLD12_WIDTH / 2, BLD12_HEIGHT / 2, 0.0f);    // Top-left corner
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}

// Add an equally-sized 2D plane in front of building 13's front face
void drawBuilding13FrontPlane() {
    glPushMatrix();    // Save current matrix
    // Translate to building 13 position
    glTranslatef(BLD13_X, BLD13_Y, BLD13_Z);
    // Rotate 25 degrees (consistent with building 13's rotation)
    glRotatef(25.0f, 0.0f, 1.0f, 0.0f);
    // Move forward to in front of the front face (half of building 13 depth)
    glTranslatef(0.0f, BLD13_HEIGHT / 2, BLD13_DEPTH / 2 + 0.01f);

    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, subwayWallTexture);  // Use subway_wall wall texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    // Draw backward-facing face (since plane is in front of building front face, looking backward at building)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-BLD13_WIDTH / 2, -BLD13_HEIGHT / 2, 0.0f);   // Bottom-left corner
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-BLD13_WIDTH / 2, BLD13_HEIGHT / 2, 0.0f);    // Top-left corner
    glTexCoord2f(1.0f, 1.0f); glVertex3f(BLD13_WIDTH / 2, BLD13_HEIGHT / 2, 0.0f);     // Top-right corner
    glTexCoord2f(1.0f, 0.0f); glVertex3f(BLD13_WIDTH / 2, -BLD13_HEIGHT / 2, 0.0f);    // Bottom-right corner
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}

// Add an equally-sized 2D plane below building 15's bottom face
void drawBuilding15BottomPlane() {
    glPushMatrix();    // Save current matrix
    // Translate to building 15 position
    glTranslatef(BLD15_X, BLD15_Y, BLD15_Z);
    // Rotate 25 degrees (consistent with building 15's rotation)
    glRotatef(25.0f, 0.0f, 1.0f, 0.0f);
    // Move down to below the bottom face (half of building 15 height)
    glTranslatef(0.0f, -BLD15_HEIGHT / 2 - 0.01f, 0.0f);

    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, subwayWallTexture);  // Use subway_wall wall texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    // Draw upward-facing face (since plane is below building bottom face, looking up at building)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-BLD15_WIDTH / 2, 0.0f, -BLD15_DEPTH / 2);   // Left-back corner
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-BLD15_WIDTH / 2, 0.0f, BLD15_DEPTH / 2);    // Left-front corner
    glTexCoord2f(1.0f, 1.0f); glVertex3f(BLD15_WIDTH / 2, 0.0f, BLD15_DEPTH / 2);     // Right-front corner
    glTexCoord2f(1.0f, 0.0f); glVertex3f(BLD15_WIDTH / 2, 0.0f, -BLD15_DEPTH / 2);    // Right-back corner
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}

// Add an equally-sized 2D plane to the left of building 16's left face
void drawBuilding16LeftPlane() {
    glPushMatrix();    // Save current matrix
    // Translate to building 16 position
    glTranslatef(BLD16_X, BLD16_Y, BLD16_Z);
    // Rotate 25 degrees (consistent with building 16's rotation)
    glRotatef(25.0f, 0.0f, 1.0f, 0.0f);
    // Move left to the left side of the left face (half of building 16 width)
    glTranslatef(-BLD16_WIDTH / 2 - 0.01f, BLD16_HEIGHT / 2, 0.0f);

    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, subwayWallTexture);  // Use subway_wall wall texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    // Draw right-facing face (since plane is to the left of building left face, looking right at building)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -BLD16_HEIGHT / 2, BLD16_DEPTH / 2);   // Front-bottom corner
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, BLD16_HEIGHT / 2, BLD16_DEPTH / 2);    // Front-top corner
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, BLD16_HEIGHT / 2, -BLD16_DEPTH / 2);   // Back-top corner
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -BLD16_HEIGHT / 2, -BLD16_DEPTH / 2);  // Back-bottom corner
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}

// Add an equally-sized 2D plane above building 16's top face
void drawBuilding16TopPlane() {
    glPushMatrix();    // Save current matrix
    // Translate to building 16 position
    glTranslatef(BLD16_X, BLD16_Y, BLD16_Z);
    // Rotate 25 degrees (consistent with building 16's rotation)
    glRotatef(25.0f, 0.0f, 1.0f, 0.0f);
    // Move up to above the top face (half of building 16 height, with additional offset)
    glTranslatef(-0.0f, BLD16_HEIGHT / 2 + 2.71f, 0.0f);

    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, subwayWallTexture);  // Use subway_wall wall texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    // Draw downward-facing face (since plane is above building top face, looking down at building)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-BLD16_WIDTH / 2, 0.0f, -BLD16_DEPTH / 2);   // Left-back corner
    glTexCoord2f(1.0f, 0.0f); glVertex3f(BLD16_WIDTH / 2, 0.0f, -BLD16_DEPTH / 2);    // Right-back corner
    glTexCoord2f(1.0f, 1.0f); glVertex3f(BLD16_WIDTH / 2, 0.0f, BLD16_DEPTH / 2);     // Right-front corner
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-BLD16_WIDTH / 2, 0.0f, BLD16_DEPTH / 2);    // Left-front corner
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}

// Add an equally-sized 2D plane below building 17's bottom face
void drawBuilding17BottomPlane() {
    glPushMatrix();    // Save current matrix
    // Translate to building 17 position
    glTranslatef(BLD17_X, BLD17_Y, BLD17_Z);
    // Rotate 25 degrees (consistent with building 17's rotation)
    glRotatef(25.0f, 0.0f, 1.0f, 0.0f);
    // Move down to below the bottom face (half of building 17 height)
    glTranslatef(-0.1f, -BLD17_HEIGHT / 30.0f, 0.0f);

    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, subwayWallTexture);  // Use subway_wall wall texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    // Draw upward-facing face (since plane is below building bottom face, looking up at building)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-BLD17_WIDTH / 2, 0.0f, -BLD17_DEPTH / 2);   // Left-back corner
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-BLD17_WIDTH / 2, 0.0f, BLD17_DEPTH / 2);    // Left-front corner
    glTexCoord2f(1.0f, 1.0f); glVertex3f(BLD17_WIDTH / 2, 0.0f, BLD17_DEPTH / 2);     // Right-front corner
    glTexCoord2f(1.0f, 0.0f); glVertex3f(BLD17_WIDTH / 2, 0.0f, -BLD17_DEPTH / 2);    // Right-back corner
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}

// Add an equally-sized 2D plane to the left of building 17's left face
void drawBuilding17LeftPlane() {
    glPushMatrix();    // Save current matrix
    // Translate to building 17 position
    glTranslatef(BLD17_X, BLD17_Y, BLD17_Z);
    // Rotate 25 degrees (consistent with building 17's rotation)
    glRotatef(25.0f, 0.0f, 1.0f, 0.0f);
    // Move left to the left side of the left face (half of building 17 width)
    glTranslatef(-BLD17_WIDTH / 2 - 0.001f, BLD17_HEIGHT / 2, 0.0f);

    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, subwayWallTexture);  // Use subway_wall wall texture
    glColor3f(1.0f, 1.0f, 1.0f);  // Set white
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    // Draw right-facing face (since plane is to the left of building left face, looking right at building)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -BLD17_HEIGHT / 2, BLD17_DEPTH / 2);   // Front-bottom corner
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, BLD17_HEIGHT / 2, BLD17_DEPTH / 2);    // Front-top corner
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, BLD17_HEIGHT / 2, -BLD17_DEPTH / 2);   // Back-top corner
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -BLD17_HEIGHT / 2, -BLD17_DEPTH / 2);  // Back-bottom corner
    glEnd();            // End drawing
    glDisable(GL_TEXTURE_2D);  // Disable texture
    glPopMatrix();     // Restore matrix
}

// ====================== Teapot Drawing Function ======================
// Draw teapot (silver)
void drawTeapot() {
    float currentTeapotY = teapotRaised ? TEAPOT_INITIAL_Y + TEAPOT_OFFSET : TEAPOT_INITIAL_Y;  // Calculate teapot height based on state
    glPushMatrix();    // Save current matrix
    glTranslatef(-2.5f, currentTeapotY, 10.0f);  // Translate to teapot position
    glScalef(0.6f, 0.6f, 0.6f);  // Scale teapot size
    glColor3f(0.75f, 0.75f, 0.75f);  // Set silver color
    glutSolidTeapot(1.0);  // Draw teapot
    glPopMatrix();     // Restore matrix
}

// ====================== Robot Drawing Function ======================
// Draw robot
void drawRobot() {
    glPushMatrix();    // Save current matrix
    glTranslatef(-3.0f, 8.5f, 7.4f);  // Translate to robot position
    glRotatef(25.0f, 0.0f, 1.0f, 0.0f);  // Rotate 25 degrees around Y-axis
    glScalef(0.6f, 0.6f, 0.6f);  // Scale robot size

    float darkGray[] = { 0.2f, 0.2f, 0.2f };    // Dark gray array
    float black[] = { 0.05f, 0.05f, 0.05f };    // Black array
    float lightGray[] = { 0.35f, 0.35f, 0.35f };// Light gray array

    // 1. Head (black)
    glPushMatrix();    // Save matrix
    glTranslatef(0.0f, 8.0f, 0.0f);  // Translate to head position
    glScalef(2.0f, 2.5f, 2.0f);      // Scale head size
    glColor3fv(black);               // Set black color
    glutSolidCube(1.0f);             // Draw cube as head
    glPopMatrix();     // Restore matrix

    // 2. Torso (dark gray)
    glPushMatrix();    // Save matrix
    glTranslatef(0.0f, 4.5f, 0.0f);  // Translate to torso position
    glScalef(3.0f, 4.0f, 2.0f);      // Scale torso size
    glColor3fv(darkGray);            // Set dark gray color
    glutSolidCube(1.0f);             // Draw cube as torso
    glPopMatrix();     // Restore matrix

    // ============== Left Arm: forearm moves upward ==============
    glPushMatrix();    // Save torso coordinate system

    glTranslatef(-2.5f, 5.0f, 0.0f);  // Translate to left shoulder position

    // Upper arm
    glPushMatrix();    // Save matrix
    glScalef(1.0f, 2.5f, 1.0f);      // Scale upper arm size
    glColor3fv(darkGray);            // Set dark gray color
    glutSolidCube(1.0f);             // Draw cube as upper arm

    // Elbow position - move upward (changed from -1.25 to -1.0)
    glPushMatrix();    // Save matrix
    glTranslatef(0.0f, -1.0f, 0.0f);  // Key modification: move upward 0.25 units

    // Forearm
    glPushMatrix();    // Save matrix
    if (leftArmRaised) {              // If left arm is raised state
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);  // Rotate -90 degrees around X-axis (raise upward)
    }
    glScalef(0.7f, 1.2f, 0.7f);      // Scale forearm size
    glColor3fv(lightGray);           // Set light gray color
    glutSolidCube(1.0f);             // Draw cube as forearm

    // Wrist position
    glPushMatrix();    // Save matrix
    glTranslatef(0.0f, -0.6f, 0.0f);  // Translate to wrist position

    // Hand
    glPushMatrix();    // Save matrix
    glScalef(0.5f, 0.5f, 0.5f);      // Scale hand size
    glColor3fv(black);               // Set black color
    glutSolidCube(1.0f);             // Draw cube as hand
    glPopMatrix();     // Restore matrix (hand)

    glPopMatrix();     // Restore matrix (wrist position)
    glPopMatrix();     // Restore matrix (forearm)

    glPopMatrix();     // Restore matrix (elbow position)
    glPopMatrix();     // Restore matrix (upper arm)

    glPopMatrix();     // Restore matrix (back to torso coordinate system)

    // ============== Right Arm: forearm moves upward (symmetrical) ==============
    glPushMatrix();    // Save torso coordinate system

    glTranslatef(2.5f, 5.0f, 0.0f);  // Translate to right shoulder position

    // Upper arm
    glPushMatrix();    // Save matrix
    glScalef(1.0f, 2.5f, 1.0f);      // Scale upper arm size
    glColor3fv(darkGray);            // Set dark gray color
    glutSolidCube(1.0f);             // Draw cube as upper arm

    // Elbow position - move upward
    glPushMatrix();    // Save matrix
    glTranslatef(0.0f, -1.0f, 0.0f);  // Key modification: move upward 0.25 units

    // Forearm
    glPushMatrix();    // Save matrix
    glScalef(0.7f, 1.2f, 0.7f);      // Scale forearm size
    glColor3fv(lightGray);           // Set light gray color
    glutSolidCube(1.0f);             // Draw cube as forearm

    // Wrist position
    glPushMatrix();    // Save matrix
    glTranslatef(0.0f, -0.6f, 0.0f);  // Translate to wrist position

    // Hand
    glPushMatrix();    // Save matrix
    glScalef(0.5f, 0.5f, 0.5f);      // Scale hand size
    glColor3fv(black);               // Set black color
    glutSolidCube(1.0f);             // Draw cube as hand
    glPopMatrix();     // Restore matrix (hand)

    glPopMatrix();     // Restore matrix (wrist position)
    glPopMatrix();     // Restore matrix (forearm)

    glPopMatrix();     // Restore matrix (elbow position)
    glPopMatrix();     // Restore matrix (upper arm)

    glPopMatrix();     // Restore matrix (back to torso coordinate system)

    // ============== Left Leg Hierarchical Modeling ==============
    glPushMatrix();    // Save torso coordinate system

    glTranslatef(-1.0f, 1.0f, 0.0f);  // Translate to left hip position

    // Thigh
    glPushMatrix();    // Save matrix
    glScalef(1.1f, 2.2f, 1.1f);      // Scale thigh size
    glColor3fv(darkGray);            // Set dark gray color
    glutSolidCube(1.0f);             // Draw cube as thigh

    // Knee position
    glPushMatrix();    // Save matrix
    glTranslatef(0.0f, -1.1f, 0.0f);  // Translate to knee position

    // Calf
    glPushMatrix();    // Save matrix
    glScalef(0.9f, 1.5f, 0.9f);      // Scale calf size
    glColor3fv(lightGray);           // Set light gray color
    glutSolidCube(1.0f);             // Draw cube as calf

    // Ankle position
    glPushMatrix();    // Save matrix
    glTranslatef(0.0f, -0.75f, 0.0f);  // Translate to ankle position

    // Foot
    glPushMatrix();    // Save matrix
    glScalef(1.3f, 0.6f, 1.8f);      // Scale foot size
    glColor3fv(black);               // Set black color
    glutSolidCube(1.0f);             // Draw cube as foot
    glPopMatrix();     // Restore matrix (foot)

    glPopMatrix();     // Restore matrix (ankle position)
    glPopMatrix();     // Restore matrix (calf)

    glPopMatrix();     // Restore matrix (knee position)
    glPopMatrix();     // Restore matrix (thigh)

    glPopMatrix();     // Restore matrix (back to torso coordinate system)

    // ============== Right Leg Hierarchical Modeling (symmetrical) ==============
    glPushMatrix();    // Save torso coordinate system

    glTranslatef(1.0f, 1.0f, 0.0f);  // Translate to right hip position

    // Thigh
    glPushMatrix();    // Save matrix
    glScalef(1.1f, 2.2f, 1.1f);      // Scale thigh size
    glColor3fv(darkGray);            // Set dark gray color
    glutSolidCube(1.0f);             // Draw cube as thigh

    // Knee position
    glPushMatrix();    // Save matrix
    glTranslatef(0.0f, -1.1f, 0.0f);  // Translate to knee position

    // Calf
    glPushMatrix();    // Save matrix
    glScalef(0.9f, 1.5f, 0.9f);      // Scale calf size
    glColor3fv(lightGray);           // Set light gray color
    glutSolidCube(1.0f);             // Draw cube as calf

    // Ankle position
    glPushMatrix();    // Save matrix
    glTranslatef(0.0f, -0.75f, 0.0f);  // Translate to ankle position

    // Foot
    glPushMatrix();    // Save matrix
    glScalef(1.3f, 0.6f, 1.8f);      // Scale foot size
    glColor3fv(black);               // Set black color
    glutSolidCube(1.0f);             // Draw cube as foot
    glPopMatrix();     // Restore matrix (foot)

    glPopMatrix();     // Restore matrix (ankle position)
    glPopMatrix();     // Restore matrix (calf)

    glPopMatrix();     // Restore matrix (knee position)
    glPopMatrix();     // Restore matrix (thigh)

    glPopMatrix();     // Restore matrix (back to torso coordinate system)

    glPopMatrix();     // Restore matrix (back to robot initial coordinate system)
}

// ====================== Star-Related Parameters and Functions ======================

// Star structure definition
struct Star {
    float x, y, z;        // Star position coordinates
    float brightness;     // Brightness (0.0 - 1.0)
    float pulseSpeed;     // Pulse speed (controls flickering frequency)
    float pulsePhase;     // Pulse phase (controls flickering start point)
    float size;           // Star size
    float r, g, b;        // Star color (white or light blue)
};

// Star count and parameters
const int NUM_STARS = 500;           // Number of stars
const float SKY_HEIGHT = 120.0f;     // Sky height
const float SKY_RADIUS = 150.0f;     // Sky radius
const float STAR_MIN_SIZE = 0.1f;    // Minimum star size
const float STAR_MAX_SIZE = 1.2f;    // Maximum star size
const float STAR_MIN_BRIGHTNESS = 0.2f;  // Minimum star brightness
const float STAR_MAX_BRIGHTNESS = 1.0f;  // Maximum star brightness
const float PULSE_SPEED_MIN = 0.3f;  // Minimum pulse speed
const float PULSE_SPEED_MAX = 3.0f;  // Maximum pulse speed

// Star array
Star stars[NUM_STARS];

// ====================== Star Initialization Function ======================
// Initialize parameters for all stars
void initStars() {
    for (int i = 0; i < NUM_STARS; i++) {
        // Randomly generate star position (hemispherical sky)
        float angle1 = static_cast<float>(rand()) / RAND_MAX * 2.0f * M_PI;  // Horizontal angle (0-2¦Ð)
        float angle2 = static_cast<float>(rand()) / RAND_MAX * M_PI / 2.0f;  // Vertical angle (0-¦Ð/2, only in upper hemisphere)
        float distance = SKY_RADIUS * (0.7f + static_cast<float>(rand()) / RAND_MAX * 0.3f);  // Distance (70%-100% radius)

        // Calculate spherical coordinates to Cartesian coordinates
        stars[i].x = cosf(angle1) * cosf(angle2) * distance;  // X coordinate
        stars[i].z = sinf(angle1) * cosf(angle2) * distance;  // Z coordinate
        stars[i].y = GROUND_Y + SKY_HEIGHT / 2 +               // Y coordinate (sky center height)
            sinf(angle2) * distance * 0.5f +                  // Offset based on vertical angle
            static_cast<float>(rand()) / RAND_MAX * SKY_HEIGHT / 4;  // Random height offset

        // Randomly generate star parameters
        stars[i].brightness = STAR_MIN_BRIGHTNESS +
            static_cast<float>(rand()) / RAND_MAX *
            (STAR_MAX_BRIGHTNESS - STAR_MIN_BRIGHTNESS);  // Initial brightness
        stars[i].pulseSpeed = PULSE_SPEED_MIN +
            static_cast<float>(rand()) / RAND_MAX *
            (PULSE_SPEED_MAX - PULSE_SPEED_MIN);          // Pulse speed
        stars[i].pulsePhase = static_cast<float>(rand()) / RAND_MAX * 2.0f * M_PI;  // Pulse phase
        stars[i].size = STAR_MIN_SIZE +
            static_cast<float>(rand()) / RAND_MAX *
            (STAR_MAX_SIZE - STAR_MIN_SIZE);              // Star size

        // Randomly generate star color
        int colorType = rand() % 100;  // Random number 0-99
        if (colorType < 65) {  // 65% white stars
            float whiteShade = 0.8f + static_cast<float>(rand()) / RAND_MAX * 0.2f;  // White tone (0.8-1.0)
            stars[i].r = whiteShade;
            stars[i].g = whiteShade;
            stars[i].b = whiteShade;
        }
        else if (colorType < 85) {  // 20% light blue stars
            stars[i].r = 0.7f + static_cast<float>(rand()) / RAND_MAX * 0.2f;  // R component (0.7-0.9)
            stars[i].g = 0.8f + static_cast<float>(rand()) / RAND_MAX * 0.2f;  // G component (0.8-1.0)
            stars[i].b = 1.0f;                                                 // B component (1.0)
        }
        else if (colorType < 95) {  // 10% light yellow stars
            stars[i].r = 1.0f;                                                 // R component (1.0)
            stars[i].g = 1.0f;                                                 // G component (1.0)
            stars[i].b = 0.7f + static_cast<float>(rand()) / RAND_MAX * 0.3f;  // B component (0.7-1.0)
        }
        else {  // 5% light red stars
            stars[i].r = 1.0f;                                                 // R component (1.0)
            stars[i].g = 0.7f + static_cast<float>(rand()) / RAND_MAX * 0.3f;  // G component (0.7-1.0)
            stars[i].b = 0.7f + static_cast<float>(rand()) / RAND_MAX * 0.3f;  // B component (0.7-1.0)
        }
    }
}

// ====================== Star Update Function ======================
// Update flickering state of all stars
void updateStars() {
    static float time = 0.0f;  // Static time variable, continuously accumulates
    time += 0.016f;  // Assuming 60FPS, increase about 0.016 seconds per frame

    for (int i = 0; i < NUM_STARS; i++) {
        // Calculate pulsating brightness (sine wave)
        float pulse = 0.5f + 0.5f * sinf(time * stars[i].pulseSpeed + stars[i].pulsePhase);
        stars[i].brightness = STAR_MIN_BRIGHTNESS +
            pulse * (STAR_MAX_BRIGHTNESS - STAR_MIN_BRIGHTNESS);

        // Randomly generate flickering effect (5¡ë probability)
        if (rand() % 1000 < 5) {
            stars[i].brightness = 1.0f;  // Suddenly brighten
            if (rand() % 10 == 0) {      // 10% probability of being brighter
                stars[i].brightness = 1.5f;  // Super bright flicker
            }
        }
    }
}

// ====================== Single Star Drawing Function ======================
// Draw a single star
void drawStar(const Star& star) {
    glPushMatrix();    // Save current matrix
    glTranslatef(star.x, star.y, star.z);  // Translate to star position

    glDisable(GL_DEPTH_TEST);  // Disable depth test (stars always in front)
    glEnable(GL_BLEND);        // Enable blending (achieve glowing effect)
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);  // Set blending function (accumulate glow)

    float currentSize = star.size * (0.8f + star.brightness * 0.4f);  // Calculate current size based on brightness

    // Draw core (brightest part)
    glColor4f(star.r, star.g, star.b, star.brightness * 0.8f);  // Set color and transparency
    glutSolidSphere(currentSize * 0.3f, 8, 8);  // Draw small sphere as core

    // Draw middle glow
    glColor4f(star.r, star.g, star.b, star.brightness * 0.4f);  // Slightly darker color
    glutSolidSphere(currentSize * 0.6f, 8, 8);  // Draw medium sphere

    // Draw outer glow
    glColor4f(star.r, star.g, star.b, star.brightness * 0.2f);  // Even darker color
    glutSolidSphere(currentSize * 1.0f, 8, 8);  // Draw large sphere

    // If particularly bright, draw extra glow
    if (star.brightness > 1.0f) {
        glColor4f(star.r, star.g, star.b, (star.brightness - 1.0f) * 0.3f);  // Super bright glow
        glutSolidSphere(currentSize * 1.5f, 8, 8);  // Draw extra large sphere
    }

    glDisable(GL_BLEND);   // Disable blending
    glEnable(GL_DEPTH_TEST);  // Enable depth test

    glPopMatrix();     // Restore matrix
}

// ====================== All Stars Drawing Function ======================
// Draw all stars
void drawStars() {
    glPushMatrix();    // Save current matrix

    // Set star viewing matrix (follows camera rotation)
    glLoadIdentity();  // Reset matrix
    float yawRad = cameraYaw * M_PI / 180.0f;     // Convert yaw angle to radians
    float pitchRad = cameraPitch * M_PI / 180.0f; // Convert pitch angle to radians
    float centerX = cameraX + sinf(yawRad) * cosf(pitchRad);  // Calculate view center X
    float centerY = cameraY + sinf(pitchRad);                // Calculate view center Y
    float centerZ = cameraZ - cosf(yawRad) * cosf(pitchRad);  // Calculate view center Z
    gluLookAt(cameraX, cameraY, cameraZ, centerX, centerY, centerZ, 0.0f, 1.0f, 0.0f);  // Set viewing matrix

    for (int i = 0; i < NUM_STARS; i++) {  // Iterate through all stars
        drawStar(stars[i]);  // Draw each star
    }

    glPopMatrix();     // Restore matrix
}

// ====================== OpenGL Initialization Function ======================
// Initialize OpenGL state
void init() {
    glEnable(GL_DEPTH_TEST);        // Enable depth test
    glDepthFunc(GL_LESS);           // Set depth test function (pass if less than current depth value)
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);  // Set clear screen color (dark gray)
    glEnable(GL_COLOR_MATERIAL);    // Enable color material
    initTexture();                  // Initialize textures
    initStars();                    // Initialize stars
}

// ====================== Ground Drawing Function ======================
// Draw gray grid ground
void drawGrayGround() {
    glPushMatrix();    // Save current matrix
    glTranslatef(0.0f, GROUND_Y, 0.0f);  // Translate to ground height

    // Draw ground fill (large quadrilateral)
    glColor3f(GRAY_FILL, GRAY_FILL, GRAY_FILL);  // Set fill color
    glBegin(GL_QUADS);  // Begin drawing quadrilateral
    glVertex3f(-GRID_SIZE * CELL_SIZE, 0.0f, -GRID_SIZE * CELL_SIZE);  // Left-back corner
    glVertex3f(GRID_SIZE * CELL_SIZE, 0.0f, -GRID_SIZE * CELL_SIZE);   // Right-back corner
    glVertex3f(GRID_SIZE * CELL_SIZE, 0.0f, GRID_SIZE * CELL_SIZE);    // Right-front corner
    glVertex3f(-GRID_SIZE * CELL_SIZE, 0.0f, GRID_SIZE * CELL_SIZE);   // Left-front corner
    glEnd();            // End drawing

    // Draw grid lines
    glColor3f(GRAY_GRID, GRAY_GRID, GRAY_GRID);  // Set grid line color
    glLineWidth(1.0f);  // Set line width
    // Draw X-direction grid lines
    for (int x = -GRID_SIZE; x <= GRID_SIZE; x++) {
        glBegin(GL_LINES);  // Begin drawing line
        glVertex3f(x * CELL_SIZE, 0.01f, -GRID_SIZE * CELL_SIZE);  // Start point (slightly above ground)
        glVertex3f(x * CELL_SIZE, 0.01f, GRID_SIZE * CELL_SIZE);   // End point
        glEnd();          // End drawing
    }
    // Draw Z-direction grid lines
    for (int z = -GRID_SIZE; z <= GRID_SIZE; z++) {
        glBegin(GL_LINES);  // Begin drawing line
        glVertex3f(-GRID_SIZE * CELL_SIZE, 0.01f, z * CELL_SIZE);  // Start point
        glVertex3f(GRID_SIZE * CELL_SIZE, 0.01f, z * CELL_SIZE);   // End point
        glEnd();          // End drawing
    }

    glPopMatrix();     // Restore matrix
}

// ====================== Generic Building Drawing Function ======================
// Draw a rectangular building
void drawBuilding(
    float x, float z, float y,        // Position coordinates
    float width, float depth, float height,  // Dimensions
    float grayWall,                   // Wall grayscale
    float rotateY = 0.0f              // Rotation angle (optional)
) {
    glPushMatrix();    // Save current matrix
    glTranslatef(x, y, z);  // Translate to building position
    if (rotateY != 0.0f) {  // If rotation angle exists
        glRotatef(rotateY, 0.0f, 1.0f, 0.0f);  // Rotate around Y-axis
    }
    glColor3f(grayWall, grayWall, grayWall);  // Set wall color
    glPushMatrix();    // Save matrix
    glTranslatef(0.0f, height / 2, 0.0f);  // Translate to building center (height centered)
    glScalef(width, height, depth);        // Scale building dimensions
    glutSolidCube(1.0f);                   // Draw cube
    glPopMatrix();     // Restore matrix
    glPopMatrix();     // Restore matrix
}

// ====================== Window Resize Function ======================
// Called when window size changes
void reshape(int width, int height) {
    glViewport(0, 0, width, height);  // Set viewport to entire window
    glMatrixMode(GL_PROJECTION);      // Switch to projection matrix
    glLoadIdentity();                 // Reset projection matrix
    gluPerspective(60.0f, (float)width / height, 0.1f, 2000.0f);  // Set perspective projection
    glMatrixMode(GL_MODELVIEW);       // Switch back to model-view matrix
}

// ====================== Mouse Control Function ======================
// Called when mouse button is pressed/released
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {  // If left button
        mouseLeftDown = (state == GLUT_DOWN);  // Update left button pressed state
        lastMouseX = x;  // Record current mouse X position
        lastMouseY = y;  // Record current mouse Y position
    }
}

// ====================== Mouse Motion Function ======================
// Called when mouse moves (for controlling camera rotation)
void mouseMotion(int x, int y) {
    if (mouseLeftDown) {  // If left button pressed
        float deltaX = x - lastMouseX;  // Calculate X direction movement delta
        float deltaY = y - lastMouseY;  // Calculate Y direction movement delta
        cameraYaw += deltaX * 0.1f;     // Update yaw angle (left/right look)
        cameraPitch -= deltaY * 0.1f;   // Update pitch angle (up/down look, note minus sign direction)
        if (cameraPitch > 85.0f) cameraPitch = 85.0f;    // Limit pitch angle upper bound
        if (cameraPitch < -85.0f) cameraPitch = -85.0f;  // Limit pitch angle lower bound
        lastMouseX = x;  // Update previous frame mouse X position
        lastMouseY = y;  // Update previous frame mouse Y position
        glutPostRedisplay();  // Request redraw
    }
}

// ====================== Keyboard Control Function ======================
// Called when keyboard key is pressed
void keyboard(unsigned char key, int x, int y) {
    if (key == 27) {  // ESC key (ASCII 27)
        // Release all texture pixel data memory
        if (pixelData) {
            free(pixelData);
        }
        if (subwayPixelData) {
            free(subwayPixelData);
        }
        if (subwayWallPixelData) {
            free(subwayWallPixelData);
        }
        exit(0);  // Exit program
    }
    else if (key == 'a' || key == 'A') {  // A key
        leftArmRaised = !leftArmRaised;  // Toggle left arm raised state
        teapotRaised = !teapotRaised;    // Toggle teapot raised state
        glutPostRedisplay();  // Request redraw
    }
}

// ====================== Main Drawing Function ======================
// Main rendering function
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear color and depth buffers
    glLoadIdentity();  // Reset model-view matrix

    // Calculate camera viewing direction
    float yawRad = cameraYaw * M_PI / 180.0f;     // Convert yaw angle to radians
    float pitchRad = cameraPitch * M_PI / 180.0f; // Convert pitch angle to radians
    float centerX = cameraX + sinf(yawRad) * cosf(pitchRad);  // View center X
    float centerY = cameraY + sinf(pitchRad);                // View center Y
    float centerZ = cameraZ - cosf(yawRad) * cosf(pitchRad);  // View center Z
    // Set camera position and viewing direction
    gluLookAt(cameraX, cameraY, cameraZ, centerX, centerY, centerZ, 0.0f, 1.0f, 0.0f);

    drawGrayGround();  // Draw ground
    drawStars();       // Draw stars

    // Draw all buildings and their textured planes
    drawBuilding(BLD1_X, BLD1_Z, BLD1_Y, BLD1_WIDTH, BLD1_DEPTH, BLD1_HEIGHT, BLD1_GRAY);
    drawBuilding1LeftPlane();
    drawBuilding1FrontPlane();
    drawBuilding1SmallLeftPlane();
    drawBuilding1SmallLeftPlane2();
    drawBuilding1SmallLeftPlane3();
    drawBuilding1SmallLeftPlane4();
    drawBuilding1SmallLeftPlane5();
    drawBuilding1SmallLeftPlane6();
    drawBuilding1SmallLeftPlane7();
    drawBuilding1SmallLeftPlane8();
    drawBuilding1SmallLeftPlane9();
    drawBuilding1SmallLeftPlane10();
    drawBuilding1SmallLeftPlane11();
    drawBuilding1SmallLeftPlane12();
    drawBuilding1SmallLeftPlane13();
    drawBuilding1SmallLeftPlane14();
    drawBuilding1SmallLeftPlane15();
    drawBuilding1SmallLeftPlane16();
    drawBuilding1SmallLeftPlane17();
    drawBuilding1SmallLeftPlane18();
    drawBuilding1SmallLeftPlane19();
    drawBuilding1SmallLeftPlane20();
    drawBuilding1SmallLeftPlane21();
    drawBuilding1SmallLeftPlane22();
    drawBuilding1SmallLeftPlane23();
    drawBuilding1SmallLeftPlane24();
    drawBuilding1SmallLeftPlane25();
    drawBuilding1SmallLeftPlane26();
    drawBuilding1SmallLeftPlane27();

    drawBuilding(BLD2_X, BLD2_Z, BLD2_Y, BLD2_WIDTH, BLD2_DEPTH, BLD2_HEIGHT, BLD2_GRAY);
    drawBuilding2FrontPlane();
    drawBuilding2RightPlane();

    drawBuilding(BLD3_X, BLD3_Z, BLD3_Y, BLD3_WIDTH, BLD3_DEPTH, BLD3_HEIGHT, BLD3_GRAY);
    drawBuilding3FrontPlane();
    drawBuilding3RightPlane();

    drawBuilding(BLD4_X, BLD4_Z, BLD4_Y, BLD4_WIDTH, BLD4_DEPTH, BLD4_HEIGHT, BLD4_GRAY);
    drawBuilding4FrontPlane();
    drawBuilding4RightPlane();
    drawBuilding4LeftPlane();

    drawBuilding(BLD5_X, BLD5_Z, BLD5_Y, BLD5_WIDTH, BLD5_DEPTH, BLD5_HEIGHT, BLD5_GRAY);
    drawBuilding5FrontPlane();
    drawBuilding5RightPlane();
    drawBuilding5LeftPlane();

    drawBuilding(BLD6_X, BLD6_Z, BLD6_Y, BLD6_WIDTH, BLD6_DEPTH, BLD6_HEIGHT, BLD6_GRAY);
    drawBuilding6FrontPlane();
    drawBuilding6LeftPlane();

    drawBuilding(BLD7_X, BLD7_Z, BLD7_Y, BLD7_WIDTH, BLD7_DEPTH, BLD7_HEIGHT, BLD7_GRAY);
    drawBuilding7LeftPlane();
    drawBuilding7FrontPlane();

    drawBuilding(BLD8_X, BLD8_Z, BLD8_Y, BLD8_WIDTH, BLD8_DEPTH, BLD8_HEIGHT, BLD8_GRAY);
    drawBuilding8LeftPlane();
    drawBuilding8FrontPlane();

    drawBuilding(BLD9_X, BLD9_Z, BLD9_Y, BLD9_WIDTH, BLD9_DEPTH, BLD9_HEIGHT, BLD9_GRAY);
    drawBuilding9FrontPlane();
    drawBuilding9RightPlane();
    drawBuilding9LeftPlane();

    drawBuilding(BLD10_X, BLD10_Z, BLD10_Y, BLD10_WIDTH, BLD10_DEPTH, BLD10_HEIGHT, BLD10_GRAY);
    drawBuilding10LeftPlane();

    // Draw rotated buildings and their textured planes
    drawBuilding(BLD11_X, BLD11_Z, BLD11_Y, BLD11_WIDTH, BLD11_DEPTH, BLD11_HEIGHT, BLD11_GRAY, 25.0f);
    drawBuilding11RightPlane();

    drawBuilding(BLD12_X, BLD12_Z, BLD12_Y, BLD12_WIDTH, BLD12_DEPTH, BLD12_HEIGHT, BLD12_GRAY, 25.0f);
    drawBuilding12BackPlane();

    drawBuilding(BLD13_X, BLD13_Z, BLD13_Y, BLD13_WIDTH, BLD13_DEPTH, BLD13_HEIGHT, BLD13_GRAY, 25.0f);
    drawBuilding13FrontPlane();

    drawBuilding(BLD14_X, BLD14_Z, BLD14_Y, BLD14_WIDTH, BLD14_DEPTH, BLD14_HEIGHT, BLD14_GRAY, 25.0f);
    drawBuilding14TopTopPlane();
    drawBuilding14BottomBottomPlane();

    drawBuilding(BLD15_X, BLD15_Z, BLD15_Y, BLD15_WIDTH, BLD15_DEPTH, BLD15_HEIGHT, BLD15_GRAY, 25.0f);
    drawBuilding15BottomPlane();

    drawBuilding(BLD16_X, BLD16_Z, BLD16_Y, BLD16_WIDTH, BLD16_DEPTH, BLD16_HEIGHT, BLD16_GRAY, 25.0f);
    drawBuilding16LeftPlane();
    drawBuilding16TopPlane();

    drawBuilding(BLD17_X, BLD17_Z, BLD17_Y, BLD17_WIDTH, BLD17_DEPTH, BLD17_HEIGHT, BLD17_GRAY, 25.0f);
    drawBuilding17BottomPlane();
    drawBuilding17LeftPlane();

    // Draw dark gray buildings
    drawBuilding(BLD18_X, BLD18_Z, BLD18_Y, BLD18_WIDTH, BLD18_DEPTH, BLD18_HEIGHT, BLD18_GRAY, -95.0f);
    drawBuilding(BLD19_X, BLD19_Z, BLD19_Y, BLD19_WIDTH, BLD19_DEPTH, BLD19_HEIGHT, BLD19_GRAY, -75.0f);

    drawBuilding(BLD20_X, BLD20_Z, BLD20_Y, BLD20_WIDTH, BLD20_DEPTH, BLD20_HEIGHT, BLD20_GRAY, 25.0f);
    drawBuilding(BLD21_X, BLD21_Z, BLD21_Y, BLD21_WIDTH, BLD21_DEPTH, BLD21_HEIGHT, BLD21_GRAY, 25.0f);

    drawCustomLines();  // Draw custom lines
    drawCableCars();    // Draw all cable cars
    drawPlane();        // Draw aircraft
    drawTrain();        // Draw train
    drawRobot();        // Draw robot
    drawTeapot();       // Draw teapot

    glutSwapBuffers();  // Swap double buffers (display rendering result)
}

// ====================== Timer Function ======================
// Periodically update dynamic objects in scene
void timer(int value) {
    updateStars();         // Update star flickering state
    trainProgress += TRAIN_SPEED;  // Update train progress
    if (trainProgress >= 1.0f) {   // If progress exceeds 1.0
        trainProgress -= 1.0f;     // Reset to 0.0 (loop)
    }

    updateCableCars();  // Update cable car positions
    updatePlane();      // Update aircraft position

    glutPostRedisplay();  // Request redraw
    glutTimerFunc(16, timer, 0);  // Set next timer call (approx. 60FPS)
}

// ====================== Main Function ======================
// Program entry point
int main(int argc, char** argv) {
    srand(static_cast<unsigned int>(time(nullptr)));  // Set random seed to current time
    glutInit(&argc, argv);  // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  // Set display mode (double buffer, RGB, depth buffer)
    glutInitWindowSize(800, 600);  // Set window size
    glutCreateWindow("CPT205 homework2");  // Create window and set title

    init();  // Initialize OpenGL

    // Register callback functions
    glutDisplayFunc(display);     // Display callback
    glutReshapeFunc(reshape);     // Window resize callback
    glutKeyboardFunc(keyboard);   // Keyboard callback
    glutMouseFunc(mouse);         // Mouse button callback
    glutMotionFunc(mouseMotion);  // Mouse motion callback
    glutTimerFunc(0, timer, 0);   // Timer callback (start immediately)

    glutMainLoop();  // Enter GLUT main loop

    return 0;  // Program normal exit
}