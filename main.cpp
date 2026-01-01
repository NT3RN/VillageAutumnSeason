#include <windows.h> // for MS Windows
#include <GL/glut.h>
#include <math.h>

// Variables for animation
float carPosition = -12.0f;
float wheelAngle = 0.0f;
float carSpeed = 0.05f;

// Sun/Moon Animation Variables
float sunY = -11.0f;
float cloudPosRight = 0.0f;
float cloudPosLeft = 0.0f;

// Day/Night State
bool isDay = true; // true = Day, false = Night

// Speed Limits
const float MAX_SPEED = 0.2f;
const float MIN_SPEED = -0.1f;

void circle(float radius, float xc, float yc, int r, int g, int b) {
    glBegin(GL_POLYGON);
    for(int i=0;i<200;i++) {
        glColor3ub(r,g,b);
        float pi=3.1416;
        float A=(i*2*pi)/200;
        float x = radius * cos(A);
        float y = radius * sin(A);
        glVertex2f(x+xc,y+yc);
    }
    glEnd();
}

void oval(float radiusX, float radiusY, float xc, float yc, int r, int g, int b) {
    glColor3ub(r,g,b);
    glBegin(GL_POLYGON);
    for(int i = 0; i < 200; i++) {
        float pi = 3.1416;
        float angle = (2 * pi * i) / 200;
        float x = radiusX * cos(angle);
        float y = radiusY * sin(angle);
        glVertex2f(xc + x, yc + y);
    }
    glEnd();
}

void rectangle(float x1, float y1, float x2, float y2){
    glBegin(GL_POLYGON);
    glVertex2f(x1,y1);
    glVertex2f(x2,y1);
    glVertex2f(x2,y2);
    glVertex2f(x1,y2);
    glEnd();
}
void customRectangle(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4){
    glBegin(GL_POLYGON);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
    glVertex2f(x3,y3);
    glVertex2f(x4,y4);
    glEnd();
}
void triangle(float x1, float y1,float x2, float y2,float x3, float y3){
    glBegin(GL_POLYGON);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
    glVertex2f(x3,y3);
    glEnd();
}

//background (Modified for Night Mode)
void road(){
    if(isDay) {
        glColor3ub(128,128,128); // Day Gray
    }
    else {
        glColor3ub(60, 60, 60);  // Night Dark Gray
    }

    rectangle(-10,-10,10,-6);

    // Road lines (Dimmer at night)
    if(isDay) {
        glColor3ub(255,255,255);
    }
    else {
        glColor3ub(180, 180, 180);
    }

    rectangle(-10,-7.6,-7.2,-8);
    rectangle(-6,-7.6,-3.2,-8);
    rectangle(-2,-7.6,0.8,-8);
    rectangle(1.9,-7.6,4.8,-8);
    rectangle(6,-7.6, 8.8, -8 );
}

// Hills (Modified for Night Mode)
void hills(){
    if(isDay) {
        glColor3ub(95, 84, 38); // Day Brown
    }
    else {
        glColor3ub(45, 34, 18); // Night Dark Brown
    }

    triangle(-10,4,-2.4,4,-8,7);
    triangle(-8,4,-4,7.5,0,4);
    triangle(-5,4,-1,6.5,2,4);
    triangle(0,4,4,8.5,6,4);
    triangle(4,4,8,7,12,4);
    triangle(-8,4,-13,7,-14,4);
}

// Field (Modified for Night Mode)
void field(){
    if(isDay) {
        glColor3ub(117, 177, 0); // Day Green
    }
    else {
        glColor3ub(30, 60, 0);   // Night Dark Green
    }
    rectangle(-10,-6,10,4);
}

// Sky (Modified for Night Mode)
void sky(){
    if(isDay) {
        glColor3ub(90, 171, 214); // Day Blue
    }
    else {
        glColor3ub(25, 25, 112);  // Night Midnight Blue
    }
    rectangle(-10,4,10,10);
}

void miniroad(){
    if(isDay) {
        glColor3ub(219, 204, 201);
    }
    else {
        glColor3ub(100, 90, 90); // Darker at night
    }

    customRectangle(-10,-0.4,-10,-1.6,-7,-0.7,-7.2,0.2);
    customRectangle(-7,-.7,-7.2,.2,-4.2,-.2,-4.6,-1.4);
    customRectangle(-4.6,-1.4,-3.8,-1.7,-3.5,1.2,-4,1.7);
    customRectangle(-3.5,1.2,-4,1.7,-3,4,-2.7,4);
    customRectangle(-3.5,2,-3.7,1.7,0,0,0.2,1);
    customRectangle(0,0,0,1,8,3,8,2.3);
    customRectangle(8,3,8,2.3,10,1.6,10,3);
}

void sun(){
    circle(1.5,0,8,255, 170, 51);
    circle(1,0,8,255,150,34);
}

// NEW: Moon Function
void moon(){
    // White glowing circle
    circle(1.2, 0, 8, 240, 240, 240);
    // Light gray craters
    circle(0.3, -0.4, 8.2, 200, 200, 200);
    circle(0.2, 0.5, 8.5, 200, 200, 200);
}

// NEW: Stars Function
void stars(){
    glColor3ub(255, 255, 255);
    glPointSize(2.0);
    glBegin(GL_POINTS);
        glVertex2f(-8, 9); glVertex2f(-5, 8); glVertex2f(-2, 9.5);
        glVertex2f(2, 9); glVertex2f(5, 8.5); glVertex2f(8, 9.2);
        glVertex2f(-9, 6); glVertex2f(0, 7); glVertex2f(9, 6.5);
        glVertex2f(-6, 5); glVertex2f(4, 5.5);
    glEnd();
}

//two different clouds
void cloud1(float cx, float cy) {
    int r, g, b;
    if(isDay) {
        r=255; g=255; b=255;
    }
    else {
        r=100; g=100; b=120; // Darker clouds at night
    }

    oval(1.5, 0.8, cx, cy, r, g, b);
    oval(1.2, 0.9, cx - 1.0, cy - 0.2, r, g, b);
    oval(1.2, 0.9, cx + 1.0, cy - 0.2, r, g, b);
    circle(0.8, cx - 0.5, cy + 0.5, r, g, b);
    circle(0.9, cx + 0.5, cy + 0.6, r, g, b);
}

void cloud2(float cx, float cy) {
    int r, g, b;
    if(isDay) {
        r=240; g=248; b=255;
    }
    else {
        r=90; g=90; b=110; // Darker clouds at night
    }

    oval(2.5, 0.4, cx, cy, r, g, b);
    oval(1.8, 0.3, cx - 1, cy + 0.1, r, g, b);
    oval(1.8, 0.3, cx + 1.2, cy - 0.1, r, g, b);
}


//trees
void tree1(float x, float y) {
    glColor3ub(80, 50, 20);
    rectangle(x - 0.15, y, x + 0.15, y + 1.5);
    if(isDay) {
        glColor3ub(124, 139, 34);
    }
    else {
        glColor3ub(60, 70, 20); // Darker leaves
    }

    triangle(x - 0.8, y + 1.0, x + 0.8, y + 1.0, x, y + 2.5);
    triangle(x - 0.6, y + 1.8, x + 0.6, y + 1.8, x, y + 3.0);
}

void tree2(float x, float y) {
    glColor3ub(101, 67, 33);
    rectangle(x - 0.25, y, x + 0.25, y + 2.0);

    if(isDay) {
        circle(1.0, x, y + 2.2, 255, 140, 0);
    }
    else {
        circle(1.0, x, y + 2.2, 150, 80, 0);
    }

    if(isDay) {
        circle(0.8, x - 0.6, y + 1.8, 205, 92, 92);
    }
    else {
        circle(0.8, x - 0.6, y + 1.8, 100, 40, 40);
    }

    if(isDay) {
        circle(0.8, x + 0.6, y + 1.8, 210, 105, 30);
    }
    else {
        circle(0.8, x + 0.6, y + 1.8, 100, 50, 15);
    }
}

void tree3(float x, float y) {
    glColor3ub(90, 60, 30);
    rectangle(x - 0.4, y, x + 0.4, y + 3.0);
    glColor3ub(90, 60, 30);
    triangle(x - 0.4, y + 1.8, x - 0.4, y + 2.2, x - 1.2, y + 2.8);
    triangle(x + 0.4, y + 2.0, x + 0.4, y + 2.4, x + 1.2, y + 2.9);

    if(isDay) {
        circle(1.4, x - 0.9, y + 3.0, 184, 134, 11);
    }
    else {
        circle(1.4, x - 0.9, y + 3.0, 90, 65, 5);
    }

    if(isDay) {
        circle(1.4, x + 0.9, y + 3.0, 160, 82, 45);
    }
    else {
        circle(1.4, x + 0.9, y + 3.0, 80, 40, 20);
    }

    if(isDay) {
        circle(1.6, x, y + 4.0, 255, 69, 0);
    }
    else {
        circle(1.6, x, y + 4.0, 120, 30, 0);
    }
}

// huts
void hut1(float x, float y){
    glColor3ub(184, 134, 11);
    rectangle(x, y, x+2.0, y+1.5);
    glColor3ub(139, 69, 19);
    triangle(x-0.2, y+1.5, x+2.2, y+1.5, x+1.0, y+2.5);
    glColor3ub(101, 67, 33);
    rectangle(x+0.8, y, x+1.2, y+0.8);

    if(isDay) {
        glColor3ub(135, 206, 235);
    }
    else {
        glColor3ub(255, 255, 0); // Windows light up at night
    }

    rectangle(x+0.2, y+0.9, x+0.6, y+1.3);
    rectangle(x+1.4, y+0.9, x+1.8, y+1.3);
}

void hut2(float x, float y) {
    glColor3ub(100, 149, 237);
    rectangle(x, y, x+2.5, y+2.0);
    glColor3ub(60, 60, 60);
    triangle(x-0.3, y+2.0, x+2.8, y+2.0, x+1.25, y+3.5);
    glColor3ub(101, 67, 33);
    rectangle(x+0.2, y, x+0.8, y+1.2);

    if(isDay) {
        glColor3ub(255, 255, 0);
    }
    else {
        glColor3ub(255, 255, 100); // Brighter light at night
    }

    rectangle(x+1.5, y+0.8, x+2.0, y+1.5);
}

void hut3(float x, float y) {
    glColor3ub(178, 34, 34);
    rectangle(x, y, x+3.5, y+2.5);
    glColor3ub(40, 40, 40);
    triangle(x-0.5, y+2.5, x+4.0, y+2.5, x+1.75, y+4.2);
    glColor3ub(139, 69, 19);
    rectangle(x+1.2, y, x+2.2, y+1.5);

    if(isDay) {
        glColor3ub(173, 216, 230);
    }
    else {
        glColor3ub(255, 255, 0); // Light up
    }

    rectangle(x+0.3, y+1.0, x+0.9, y+1.8);
    rectangle(x+2.5, y+1.0, x+3.1, y+1.8);
}

void school(float x, float y) {
    //main body
    glColor3ub(230, 230, 230);
    rectangle(x, y, x+3.8, y+2.0);
    //roof
    glColor3ub(60, 60, 60);
    rectangle(x-0.1, y+2.0, x+3.9, y+2.15);
    //glass window
    if(isDay) {
        glColor3ub(135, 206, 250);
    }
    else {
        glColor3ub(100, 100, 150); // Darker glass at night
    }

    //2nd floor
    rectangle(x+0.2, y+1.2, x+3.6, y+1.7);
    //first floor
    rectangle(x+0.2, y+0.4, x+1.5, y+0.9);
    rectangle(x+2.3, y+0.4, x+3.6, y+0.9);

    //main gate
    glColor3ub(40, 40, 40); //frame
    rectangle(x+1.6, y, x+2.2, y+1.0);

    if(isDay) {
        glColor3ub(100, 149, 237);
    }
    else {
        glColor3ub(50, 50, 100);
    }

    rectangle(x+1.65, y, x+2.15, y+0.95);
    glColor3ub(255, 165, 0); // Orange
    rectangle(x+1.5, y+1.0, x+2.3, y+1.1);
}

// flower bush
void flowerBush(float x, float y) {
    circle(0.3, x, y, 34, 139, 34);
    circle(0.25, x-0.25, y-0.1, 34, 139, 34);
    circle(0.25, x+0.25, y-0.1, 34, 139, 34);
    // flowers
    circle(0.08, x-0.1, y+0.1, 255, 105, 180); // pink
    circle(0.08, x+0.2, y, 255, 255, 0);        // yellow
    circle(0.08, x-0.2, y-0.1, 255, 0, 0);      // red
}

void bench(float x, float y) {
    glColor3ub(101, 67, 33);
    // Legs
    rectangle(x+0.2, y, x+0.3, y+0.4);
    rectangle(x+1.2, y, x+1.3, y+0.4);
    // Seat
    rectangle(x, y+0.4, x+1.5, y+0.55);
    // Backrest
    rectangle(x, y+0.8, x+1.5, y+1.0);
    rectangle(x+0.3, y+0.55, x+0.4, y+0.8);
    rectangle(x+1.1, y+0.55, x+1.2, y+0.8);
}

void car() {
    glColor3ub(220, 20, 60);
    glBegin(GL_POLYGON);
        glVertex2f(-0.6, -8.3);
        glVertex2f( 3.0, -8.3);
        glVertex2f( 3.0, -8.0);
        glVertex2f( 2.8, -7.8);
        glVertex2f( 2.2, -7.6);
        glVertex2f( 1.5, -6.9);
        glVertex2f( 0.5, -6.9);
        glVertex2f(-0.3, -7.6);
        glVertex2f(-0.6, -7.8);
    glEnd();
    glColor3ub(50, 50, 50);
    glBegin(GL_POLYGON);
        glVertex2f(0.6, -7.05);
        glVertex2f(1.35, -7.05);
        glVertex2f(1.35, -7.5);
        glVertex2f(0.0, -7.5);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f(1.45, -7.05);
        glVertex2f(1.8, -7.3);
        glVertex2f(2.1, -7.5);
        glVertex2f(1.45, -7.5);
    glEnd();
    glColor3ub(220, 20, 60);
    rectangle(-0.5, -7.8, -0.4, -7.5);
    rectangle(-0.6, -7.5, -0.2, -7.4);

    //headlight
    glColor3ub(255, 255, 200);
    circle(0.15, 2.85, -8.0, 255, 255, 200);

    // Headlight Beam (Only visible at night)
    if (!isDay) {
        // Semi-transparent yellow beam
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4ub(255, 255, 200, 100);
        glBegin(GL_TRIANGLES);
            glVertex2f(2.9, -8.0); // Light source
            glVertex2f(6.0, -7.0); // Top beam
            glVertex2f(6.0, -9.0); // Bottom beam
        glEnd();
        glDisable(GL_BLEND);
    }

    // --- REAR WHEEL (Rotating) ---
    glPushMatrix();
    glTranslatef(0.5, -8.4, 0); // Pivot
    glRotatef(wheelAngle, 0, 0, 1);
    glTranslatef(-0.5, 8.4, 0); // Back

    //black tire
    circle(0.36, 0.5, -8.4, 0, 0, 0);
    //white shade
    circle(0.20, 0.5, -8.4, 220, 220, 220);
    //spoke
    glColor3ub(0, 0, 0);
    glLineWidth(2.0);
    glBegin(GL_LINES);
        glVertex2f(0.5, -8.2); glVertex2f(0.5, -8.6);
        glVertex2f(0.3, -8.4); glVertex2f(0.7, -8.4);
    glEnd();
    glPopMatrix();

    // --- FRONT WHEEL (Rotating) ---
    glPushMatrix();
    glTranslatef(2.2, -8.4, 0); // Pivot
    glRotatef(wheelAngle, 0, 0, 1);
    glTranslatef(-2.2, 8.4, 0); // Back

    circle(0.36, 2.2, -8.4, 0, 0, 0); // Tire
    circle(0.20, 2.2, -8.4, 220, 220, 220); // Hubcap

    glColor3ub(0, 0, 0);
    glLineWidth(2.0);
    glBegin(GL_LINES);
        glVertex2f(2.2, -8.2); glVertex2f(2.2, -8.6);
        glVertex2f(2.0, -8.4); glVertex2f(2.4, -8.4);
    glEnd();
    glPopMatrix();
}

// Handle Mouse Click for Day/Night Transition
void handleMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        isDay = !isDay; // Toggle Day/Night
    }
}

// Function to handle arrow keys with SPEED LIMITS
void handleSpecialKey(int key, int x, int y) {
    if (key == GLUT_KEY_UP) {
        if (carSpeed < MAX_SPEED) { // Max speed check
            carSpeed += 0.01f;
        }
    } else if (key == GLUT_KEY_DOWN) {
        if (carSpeed > MIN_SPEED) { // Min speed check
            carSpeed -= 0.01f;
        }
    }
}

// Update function for animation
void update(int value) {
    // 1. Car Physics
    carPosition += carSpeed;
    wheelAngle -= (carSpeed * 100.0f);

    if(carPosition > 15.0) {
        carPosition = -15.0;
    }
    else if(carPosition < -15.0) {
        carPosition = 15.0;
    }

    // 2. Sun Rise Animation (FULL LOOP)
    sunY += 0.03f; // Sun rising speed
    if(sunY > 11.0f) {
        sunY = -11.0f;
    }

    // 3. Cloud Movement Animation
    // Move Right ->
    cloudPosRight += 0.02f;
    if(cloudPosRight > 20.0f) {
        cloudPosRight = -20.0f;
    }

    // Move Left <-
    cloudPosLeft -= 0.03f;
    if(cloudPosLeft < -20.0f) {
        cloudPosLeft = 20.0f;
    }

    glutPostRedisplay();
    glutTimerFunc(20, update, 0);
}

void display() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    sky();
    if(!isDay) {
        stars(); // Draw stars only at night
    }

    // --- SUN or MOON (Animated) ---
    glPushMatrix();
    glTranslatef(0.0f, sunY, 0.0f); // Move celestial body Up
    if(isDay) {
        sun();
    }
    else {
        moon();
    }
    glPopMatrix();

    hills();
    field();
    miniroad();

    // --- CLOUDS GROUP 1 (Moving Right ->) ---
    glPushMatrix();
    glTranslatef(cloudPosRight, 0.0f, 0.0f);
    cloud1(-6, 8);
    cloud1(5, 7.5);
    glPopMatrix();

    // --- CLOUDS GROUP 2 (Moving Left <-) ---
    glPushMatrix();
    glTranslatef(cloudPosLeft, 0.0f, 0.0f);
    cloud2(7, 7);
    cloud2(-3, 8.5);
    glPopMatrix();

    //scene objects
    school(-1.5, 2.0);
    flowerBush(-1.2, 2.0);
    flowerBush(-1.5, 1.9);
    flowerBush(2.0, 2.0);
    flowerBush(2.2,2.0);

    hut1(-7.0, 2.0);
    tree1(-4.0, 2.5);
    tree1(6.8, 2.0);
    hut1(5.0, 1.0);

    tree2(-8.0, 1.5);
    hut2(0.0, -2.5);
    flowerBush(2.3, -2.5);
    tree2(3.5, -2.5);

    road();

    hut3(-5.0, -5.5);
    bench(-2, -6);
    tree3(7.0, -6.0);

    // Animate Car
    glPushMatrix();
    glTranslatef(carPosition, 0.0f, 0.0f);
    car();
    glPopMatrix();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Autumn Village");
    gluOrtho2D(-10,10,-10,10);
    glutDisplayFunc(display);

    glutSpecialFunc(handleSpecialKey);
    glutMouseFunc(handleMouse); // Register mouse click

    glutTimerFunc(20, update, 0);
    glutMainLoop();
    return 0;
}
