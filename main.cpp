#include <GL/glut.h>
#include <math.h>
float starX = 0.0f;
float starY = -0.6f;
float circle1X = -0.6f;
float circle2X = 0.6f;
float circle3X = -0.6f;
int pass = 0;
int fail = 0;
bool rotation = false;
int direction = 1;


//ALI FATIH DURGUT 20190702068

void drawRivers(){

    glColor3f(0.0f, 0.0f, 1.0f);
    //first river
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, 0.3f);
    glVertex2f(1.0f, 0.3f);
    glVertex2f(1.0f, 0.5f);
    glVertex2f(-1.0f, 0.5f);
    glEnd();

    //second river
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.1f);
    glVertex2f(1.0f, -0.1f);
    glVertex2f(1.0f, 0.1f);
    glVertex2f(-1.0f, 0.1f);
    glEnd();

    //third river
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.3f);
    glVertex2f(1.0f, -0.3f);
    glVertex2f(1.0f, -0.5f);
    glVertex2f(-1.0f, -0.5f);
    glEnd();
}


void drawStar(){
    glPushMatrix();
    glTranslatef(starX, starY, 0.0f);
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f( 1.0, 0.11, 0.68);
    glVertex2f(0.0, 0.0);

    // create star
    for (int i = 0; i <= 10; ++i) {
        float angle = i * 2.0f * 3.14159f / 5.0f;
        float radius = (i % 2 == 0) ? 0.1f : 0.03f;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
}


void exitFunction(unsigned char key, int x, int y){
    switch(key) {
        case 'x':
            exit(0);
    }
    glutPostRedisplay();
}


void drawCircle(float x, float y, float radius){
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLE_FAN);

    for (int i = 0; i <= 360; i++){
        float angle = i * 3.1415926f / 180.0f;
        float x1 = x + (radius * cos(angle));
        float y1 = y + (radius * sin(angle));
        glVertex2f(x1, y1);
    }
    glEnd();
    glLineWidth(3.0f);
    glColor3f(0.0f, 0.0f, 0.0f);

    glBegin(GL_LINES);
    glVertex2f(x - radius, y);  //horizontal line
    glVertex2f(x + radius, y);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(x, y - radius);  //vertical line
    glVertex2f(x, y + radius);
    glEnd();
}


void drawFoliage(){
    for(float i = 0; i <= 1.8f; i+=0.3f){
        glPushMatrix();
        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_LINES);
        glVertex2f(-0.95f+i, -0.7f); //line
        glVertex2f(-0.95f+i, -1.0f);
        glEnd();
        glPopMatrix();

        glColor3f(1.0f, 1.0f, 0.0f);
        glBegin(GL_QUADS);
        glVertex2f(-0.9f+i, -1.0f);
        glVertex2f(-0.9f+i, -0.9f); //square
        glVertex2f(-0.8f+i, -0.9f);
        glVertex2f(-0.8f+i, -1.0f);

        glVertex2f(-0.9f+i, -0.8f);
        glVertex2f(-0.9f+i, -0.7f); //square
        glVertex2f(-0.8f+i, -0.7f);
        glVertex2f(-0.8f+i, -0.8f);
        glEnd();
    }
}

void moveCircles(int value){
    if(circle2X >= -0.8f && circle2X < -0.79f){
        rotation = true;
    }
    else if(circle2X <= 0.8f && circle2X > 0.79f){
        rotation = false;
    }

    if(rotation == true){
        direction = -1;
        circle1X -= 0.02f;
        circle2X += 0.02f;
        circle3X -= 0.02f;
    }
    else if(rotation == false){
        direction = 1;
        circle1X += 0.02f;
        circle2X -= 0.02f;
        circle3X += 0.02f;
    }
    glutPostRedisplay();
    glutTimerFunc(25, moveCircles, 0);
}

void checkCollisions(){
    float starRadius = 0.13f; // radius of the star
    float circleRadius = 0.1f; // radius of the circles

    if(starX >= circle1X - circleRadius && starX <= circle1X + circleRadius && starY < 0.6){
        starY += 0.4f;
        if(starY >= 0.6){
            pass+=1;
            fail=-1;
        }
    }
    else{
        starY = -0.6f;
        fail+=1;
    }

    glutPostRedisplay();
}

void keypress(int key, int x, int y){
    switch(key) {
        case GLUT_KEY_UP:
                checkCollisions();
    }
    glutPostRedisplay();
}

int angle = 0;
void timerFunc(int value){
    angle += 10;
    if(angle > 360){
        angle = 0;
    }
    glutTimerFunc(50,timerFunc,0);
    glutPostRedisplay();
}

void display(){
    glClearColor( 0.137255f, 0.556863f, 0.137255f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    drawRivers();

    glPushMatrix();
    glTranslatef(circle1X, 0.4f, 0.1f);
    glRotatef(-angle*direction,0,0,1);
    glTranslatef(-circle1X, -0.4f, -0.1f);
    drawCircle(circle1X, 0.4f, 0.1f);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(circle2X, 0.0f, 0.1f);
    glRotatef(angle*direction,0,0,1);
    glTranslatef(-circle2X, 0.0f, -0.1f);
    drawCircle(circle2X,0.0f, 0.1f);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(circle3X, -0.4f, 0.1f);
    glRotatef(-angle*direction,0,0,1);
    glTranslatef(-circle3X, 0.4f, -0.1f);
    drawCircle(circle1X, -0.4f, 0.1f);
    glPopMatrix();

    glColor3f(1.0f, 0.0f, 0.0f);
    float squareSize = 0.1f;
    float spacing = 0.02f;
    float startX = -1.0f;
    float startY = 0.9f;

    for(int i = 1;i <= fail; i++){
        float x = startX + i*(squareSize + spacing);
        glBegin(GL_QUADS);
        glVertex2f(x, startY);
        glVertex2f(x, startY - squareSize);
        glVertex2f(x + squareSize, startY - squareSize);
        glVertex2f(x + squareSize, startY);
        glEnd();
    }

    startX = 1.0f;
    for(int i = 1;i <= pass; i++){
        glColor3f(0.0f, 1.0f, 0.0f);
        float x = startX - i*(squareSize + spacing);
        glBegin(GL_QUADS);
        glVertex2f(x, startY);
        glVertex2f(x, startY - squareSize);
        glVertex2f(x - squareSize, startY - squareSize);
        glVertex2f(x - squareSize, startY);
        glEnd();
    }

    drawStar();
    drawFoliage();
    glutSwapBuffers();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(720, 640);
    glutCreateWindow("Red Dead Redemption 2");
    glutDisplayFunc(display);
    glutSpecialFunc(keypress);
    glutKeyboardFunc(exitFunction);
    glutTimerFunc(25, moveCircles, 0);
    glutTimerFunc(25, timerFunc, 0);
    glutMainLoop();
    return 0;
}
