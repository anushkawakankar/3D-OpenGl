#include "main.h"
#include "timer.h"
#include "ball.h"
#include "sea.h"
#include "checkpoint.h"
#include "volcano.h"
#include "numbers.h"
#include "ring.h"
#include "bomb.h"
#include "cannon.h"
#include "bullet.h"
#include "compass.h"
#include "powerups.h"
// #include "sky.h"

using namespace std;

GLMatrices Matrices;
GLMatrices Matrices1;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball1;
Sea sea;
Checkpoint checks[15];
Volcano volcano[10];
Numbers alt[5],sp[5],fl[5];
Ring ring[5];
Bomb bomb;
Cannon cannon[15];
Bullet bullet[15];
Compass compass;
Powerups powerups[20];

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
float floorHeight=-1.7;
int score =0;
int bomb_flag=0;
int t=0;
float camera_view[3]={0,4,10};
float target_view[3]={0,1,0};
int view = 1;
int bomb_num =0;
float cam_distance = 300.0;
int active_cannon = 0;
bool canbool = true;
float lol[2][15];
clock_t beam_start[15], beam_end[15];
// double camera_rotation_angle = 100;
int i;

Timer t60(1.0 / 60);



void draw() {
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram (programID);

    glm::vec3 eye(camera_view[0], camera_view[1], camera_view[2]);

   glm::vec3 target (target_view[0], target_view[1], target_view[2]);
   // glm::vec3 eye(0,0,15);
   // glm::vec3 target (0,0,0);
   glm::vec3 up (0,1,0);

   glm::vec3 eye1(-3,6,4);
  glm::vec3 target1(-3,6,0);
   // Compute Camera matrix (view)
   Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
   Matrices1.view = glm::lookAt( eye1, target1, up );
   // Don't change unless you are sure!!
   glm::mat4 VP = Matrices.projection * Matrices.view;

   glm::mat4 MVP;  // MVP = Projection * View * Model
   glm::mat4 VP1 = Matrices1.projection * Matrices1.view;

   glm::mat4 MVP1;


    // Scene render

    sea.draw(VP);
    // checks[0].draw(VP);
    for(i=0;i<15;i++)
    {
        cannon[i].draw(VP);
        checks[i].draw(VP);
        beam_start[i] = clock();
        if((beam_start[i]-beam_end[i]/CLOCKS_PER_SEC) >= 2)
        {
          if(abs(ball1.position.x-cannon[i].position.x)<=2 && abs(ball1.position.z-cannon[i].position.z)<=2)
          {
            bullet[i].active = true;
          }
        }
    }
    for(i=0;i<15;i++)
    {
      // bullet[i] = Bullet(lol[0][i],1,lol[1][i]);
      if(bullet[i].active )
      {
        bullet[i].draw(VP);
        // printf("printing %d\n",i);
      }
    }
    ball1.draw(VP);
    for(i=0;i<10;i++)
    {
      volcano[i].draw(VP);
    }
    for(i=0;i<5;i++)
    {
      ring[i].draw(VP);
    }
    for(i=0;i<20;i++)
    {
      if(powerups[i].active)
        powerups[i].draw(VP);
    }
    compass = Compass(0,2.8,ball1.rotationy);
    compass.draw(VP1);



    int talt,tfuel,tspeed;
    talt = ball1.position.y*100;
    tfuel = ball1.fuel;
    tspeed = ball1.speed*100;

    if(ball1.position.y <= -1 || ball1.fuel <= 2)
    {
      printf("You crashed!\n");
      exit(0);
    }

    int units = talt%10;
    talt/=10;
    alt[4] = Numbers(-3.5,3.8);
    alt[4].draw(VP1,units);
    int tens = talt%10;
    talt/=10;
    alt[3] = Numbers(-4,3.8);
    alt[3].draw(VP1,tens);
    int hundreds = talt%10;
    alt[2] = Numbers(-4.5,3.8);
    alt[2].draw(VP1,hundreds);
    alt[1] = Numbers(-5,3.8);
    alt[1].draw(VP1,13);
    alt[0] = Numbers(-5.5,3.8);
    alt[0].draw(VP1,10);


    int funits = tfuel%10;
    tfuel/=10;
    fl[4] = Numbers(-3.5,3.2);
    fl[4].draw(VP1,funits);
    int ftens = tfuel%10;
    tfuel/=10;
    fl[3] = Numbers(-4,3.2);
    fl[3].draw(VP1,ftens);
    int fhuns = tfuel%10;
    fl[2] = Numbers(-4.5,3.2);
    fl[2].draw(VP1,fhuns);
    fl[1] = Numbers(-5,3.2);
    fl[1].draw(VP1,13);
    fl[0] = Numbers(-5.5,3.2);
    fl[0].draw(VP1,11);

    int sunits = tspeed%10;
    tspeed/=10;
    sp[4] = Numbers(-3.5,2.6);
    sp[4].draw(VP1,sunits);
    int stens = tspeed%10;
    tspeed/=10;
    sp[3] = Numbers(-4,2.6);
    sp[3].draw(VP1,stens);
    int shunds = tspeed%10;
    sp[2] = Numbers(-4.5,2.6);
    sp[2].draw(VP1,shunds);
    sp[1] = Numbers(-5,2.6);
    sp[1].draw(VP1,13);
    sp[0] = Numbers(-5.5,2.6);
    sp[0].draw(VP1,12);
}

void tick_input(GLFWwindow *window) {
  int left  = glfwGetKey(window, GLFW_KEY_LEFT);
  int right = glfwGetKey(window, GLFW_KEY_RIGHT);
  int up = glfwGetKey(window, GLFW_KEY_UP);
  int down = glfwGetKey(window, GLFW_KEY_DOWN);
  int zoom_out = glfwGetKey(window, GLFW_KEY_MINUS);
  int zoom_in = glfwGetKey(window, GLFW_KEY_EQUAL);
  int w = glfwGetKey(window, GLFW_KEY_W);
  int s = glfwGetKey(window, GLFW_KEY_S);
  int q = glfwGetKey(window, GLFW_KEY_Q);
  int e = glfwGetKey(window, GLFW_KEY_E);
  int a = glfwGetKey(window, GLFW_KEY_A);
  int d = glfwGetKey(window, GLFW_KEY_D);
  int space = glfwGetKey(window, GLFW_KEY_SPACE);
  int n = glfwGetKey(window, GLFW_KEY_N);
  int p = glfwGetKey(window, GLFW_KEY_P);
  int t = glfwGetKey(window, GLFW_KEY_T);
  int h = glfwGetKey(window, GLFW_KEY_H);
  int f = glfwGetKey(window, GLFW_KEY_F);
  int b = glfwGetKey(window, GLFW_KEY_B);

  if(b && bomb_num<50)
  {
    bomb_flag++;
    // printf("%d num %d flag\n",bomb_num,bomb_flag);
  }
  if(h)
  {
    view=4;
    changeview();
  }

  if(f)
  {
    view = 1;
    changeview();
  }
  if(t)
  {
    view = 2;
    changeview();
  }
  if(p)
  {
    view = 3;
    changeview();
  }
  if(s)
  {
    ball1.speed =0;
  }
  ball1.speed = 0.1;

    if(w)
    {
      ball1.rotationz = 0;
      // ball1.position.z -= 0.2 ;

      ball1.speed += 0.02;
      ball1.position.x -= ball1.speed * sin(ball1.rotationy*M_PI/180);
      ball1.position.z -= ball1.speed * cos(ball1.rotationy*M_PI/180);
      camera_view[2] -= ball1.speed;
    }
    ball1.speed = 0.1;
    if(q)
    {
      ball1.rotationy += 1;
    }
    if(e)
    {
      ball1.rotationy -= 1;
    }

    if(a)
    {
      // ball1.rotationy += 1;
      ball1.rotationz += 1;
    }
    if(d)
    {
      // ball1.rotationy -= 1;
      ball1.rotationz -= 1;
    }

    if(space && ball1.position.y <= 5)
    {
      if(ball1.rotationx <= 3)
        ball1.rotationx += 0.9;
      ball1.position.y += 0.02;
      ball1.position.z -= ball1.speed;
      camera_view[2] -= ball1.speed;
    }
    if(n )
    {
      if(ball1.rotationx >= -3)
        ball1.rotationx -= 1.8;
      ball1.position.y -= 0.02;
      ball1.position.z -= ball1.speed;
      camera_view[2] -= ball1.speed;
    }

   if (zoom_out) {
       if(screen_zoom - 0.01 >= 0.02) {
           screen_zoom -= 0.01;
           reset_screen();
       }
   }
   if (zoom_in) {
       if(screen_zoom + 0.01 <= 1.0) {
           screen_zoom += 0.01;
           reset_screen();
       }
   }
   if(left && view == 1)
   {
     camera_view[0] -= 0.5;
   }
   if(right && view == 1)
   {
     camera_view[0] += 0.5;
   }
   if(up && view == 1)
   {
     camera_view[1] += 0.5;
   }
   if(down && view == 1)
   {
     camera_view[1] -= 0.5;
   }

    for(i=0;i<15;i++)
    {
      if(ball1.position.z < checks[i].position.z)
      {
        checks[i].arrow = false;
        checks[i+1].arrow = true;
      }
      if(detect_collision(ball1.bounding_box(),checks[i].bounding_box()) && checks[i].active)
      {
        score+=10;
        checks[i].active = false;
        // if(ball1.position.z < checks[i].position.z)
        // checks[i].arrow = false;
        // checks[i+1].arrow = true;
      }
    }
    if(ball1.position.z < checks[14].position.z)
    {
      printf("COURSE COMPLETED\n");
      exit(0);

    }
    for(i = 0 ; i<10; i++)
      detect_volcano(i);

    for(i=0;i<5;i++)
    {
      if(detect_ring(i))
      {
        score += 25;
        ring[i].active = false;
      }
    }
    for(i=0;i<15;i++)
    {
      if(detect_collision(ball1.bounding_box(),bullet[i].bounding_box()) && bullet[i].active)
      {
        beam_end[i] = clock();
          bullet[i].active=false;

        printf("You touched a cannon laser beam!\n");
        exit(0);
      }
    }
    for(i=0;i<20;i++)
    {
      if(powerups[i].active && detect_collision(ball1.bounding_box(), powerups[i].bounding_box()))
      {
        powerups[i].active = false;
        ball1.fuel = 900;
      }
    }
  }


void tick_elements() {
    ball1.tick();
    camera_view[0] -= ball1.speed * sin(ball1.rotationy*M_PI/180);
    camera_view[1] = ball1.position.y + 4;
    camera_view[2] -= ball1.speed * cos(ball1.rotationy*M_PI/180);
    target_view[0]= ball1.position.x;
    target_view[1] = ball1.position.y;
    target_view[2] = ball1.position.z;
    for(i=0;i<15;i++)
    {
      cannon[i].tick();
      bullet[i].tick2();
    }
    for(i=0;i<20;i++)
      powerups[i].tick();
    // bomb.tick();
}
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball1= Ball(0, 2);
    sea = Sea(-2);
    float xc, zc;
    float canx,canz;
    zc = 0;
    float temp=5;
    // checks[0] = Checkpoint(0,1,15);
    // float lol[2][15];
    for(i=0;i<15;i++)
    {

      xc = RandomFloat(-10.0,10.0);
      // zc = RandomFloat(temp, temp +20);
      checks[i] = Checkpoint(xc,1,temp);
      canx= xc - RandomFloat(-1.0,1.0);
      canz = temp - RandomFloat(-1.0,1.0);
      cannon[i] = Cannon(canx,1,canz);
      bullet[i] = Bullet(canx,1,canz);
      lol[0][i]=canx;
      lol[1][i]=canz;
      temp-=20;
    }
    checks[0].arrow = true;

    temp =5;
    for(i=0;i<10;i++)
    {
      xc = RandomFloat(-10.0,10.0);
      zc = RandomFloat(temp, temp +20);
      volcano[i] = Volcano(xc,1,zc);
      temp-=20;
    }
    temp = 5;
    // ring[0] = Ring(5,-10);
    for(i=0;i<5;i++)
    {
      xc = RandomFloat(-15.0,15.0);
      zc = RandomFloat(temp, temp+30);
      ring[i] = Ring(xc,zc);
      temp-=30;
    }
    temp=10;
    float yc=0;
    for(i=0;i<20;i++)
    {
      xc = RandomFloat(-7.0,7.0);
      yc = RandomFloat(1.0,4.0);
      zc = RandomFloat(temp,temp+15);
      powerups[i] = Powerups(xc,yc,zc);
      temp-=15;
    }
    // for(i=0;i<50;i++)
      bomb = Bomb(checks[0].position.x-2,3,checks[0].position.z,0);//ball1.position.x,ball1.position.y,ball1.position.z,ball1.rotationy);


    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
    Matrices1.MatrixID = glGetUniformLocation(programID, "MVP1");

    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;


    window = initGLFW(width, height);

    initGL (window, width, height);


    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
          t++;
          // printf("%d\n",t%50);
          if(t%50 == 0)
            canbool = true;
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
            char titleString[128];
            sprintf(titleString,"Score = %d",score);
            glfwSetWindowTitle(window,titleString);
            // printf("%d\n",score);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float lmao = 4/screen_zoom;
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::perspective(glm::radians(45.0f),1.0f,0.1f,100.0f);
    Matrices1.projection = glm::ortho(left,right,bottom,top,0.1f,500.0f);
}

float RandomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

bool detect_checkpoint(int i)
{
//   if(i==0)
//     printf("%f %f\n",abs(checks[i].position.x - ball1.position.x),abs(checks[i].position.z - ball1.position.z));
  if( abs(checks[i].position.x - ball1.position.x) <= 0.5 && (checks[i].position.z - ball1.position.z)<=0.5 && checks[i].active) //abs(checks[i].position.x - ball1.position.x) <= 0.05 &&
    return true;
  return false;
}

void changeview()
{
  // view = (view+1) % 4;
  // printf("%d\n",view);
  if(view == 1) //follow
  {
    camera_view[0] = ball1.position.x + 2*sin(ball1.rotationy*M_PI/180);
    camera_view[1] = ball1.position.y + 4;
    camera_view[2] = ball1.position.z + 10 +2*cos(ball1.rotationy*M_PI/180);
    target_view[0]= ball1.position.x - 2*sin(ball1.rotationy*M_PI/180);
    target_view[1] = ball1.position.y;
    target_view[2] = ball1.position.z - 2*cos(ball1.rotationy*M_PI/180);
  }
  else if(view == 2) //tower
  {
    camera_view[0] = ball1.position.x + 20;
    camera_view[1] = 20;
    camera_view[2] = ball1.position.z + 20;
    target_view[0]= ball1.position.x;
    target_view[1] = ball1.position.y;
    target_view[2] = ball1.position.z;
  }
  if(view==3) //plane
  {
    camera_view[0] = ball1.position.x;
    camera_view[1] = ball1.position.y +1 ;
    camera_view[2] = ball1.position.z;
    target_view[0]= ball1.position.x - 2*sin(ball1.rotationy*M_PI/180);
    target_view[1] = ball1.position.y+1;
    target_view[2] = ball1.position.z - 2*cos(ball1.rotationy*M_PI/180);
  }
  if(view == 4) //top view
  {
    camera_view[0] = ball1.position.x;
    camera_view[1] = ball1.position.y + 10;
    camera_view[2] = ball1.position.z + 1;
    target_view[0]= ball1.position.x - 2*sin(ball1.rotationy*M_PI/180);
    target_view[1] = ball1.position.y;
    target_view[2] = ball1.position.z - 2*cos(ball1.rotationy*M_PI/180);
  }

}

void detect_volcano(int i)
{
  if(abs(ball1.position.x - volcano[i].position.x)<=0.3 && abs(ball1.position.z-volcano[i].position.z)<=0.3)
  {
    printf("TOO CLOSE\n");
  }
}

bool detect_ring(int i)
{
  if(abs(ball1.position.x - ring[i].position.x)<=1.5 && abs(ball1.position.y - ring[i].position.y)<= 1.5 && abs(ball1.position.z - ring[i].position.z) <= 0.25 && ring[i].active)
  {
    printf("touched ring %d\n",i);
    return true;
  }
  return false;
}
