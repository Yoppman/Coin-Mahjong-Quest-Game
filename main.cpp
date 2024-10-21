#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include <dirent.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>
#include <vector>
#include <string>
#include "freetype.h"
#include <SOIL/SOIL.h>



// This Holds All The Information For The Font That We Are Going To Create.
freetype::font_data our_font;
freetype::font_data font_2;
freetype::font_data num_font;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void displayfunc();
void DrawFilledCircle(float cx, float cy, float r);
void DrawCircle(float cx, float cy, float r);
void Drawline(float x1,float y1,float x2,float y2);
void Drawrectang(float x1,float x2,float y1,float y2);
void show_minus_Points(bool &touch, float x, float y, float current_time, int points);
void show_add_Points(bool &touch, float x, float y, float current_time, int points);
void startMenu();
void pauseMenu();
void gameoverMenu();
void display(void);
void drawText(char* text, FT_Face face);

float cnt1 = 300, cnt2 = 50;

// settings
const unsigned int w = 1350;
const unsigned int h = 720;
int gameTime=60;
//different  gameState of game
int menu=1,play=2,pause=3,over=4,gameexit=5;
float headRadius=40;                                     //player head radius
float coinRadius=50;                                    //coin radius
char str [100];
int game_state=menu;                                           //store the game state
float c1Speed=6,c2Speed=8,c3Speed=10,c4Speed=12,c5Speed=13;//Speed of  Five balls
float mj_speed = 10;
float ttime;                                                //store time passes
int t=0;                                                    //storing previous time
int i=0,j=0,k=0,l=0,m=0;                                     // use to set random position
int mj_position = 0;
int score=0;                                                 //store score
//double Yspeed=10.0f;                                        //speed of Coins
double Xspeed=60.0f;                                        //speed of player
GLuint      texture[50];                         // Storage For One Texture ( NEW )

// for random mj type
int mj_index_1 = rand() % 35 + 1;
int mj_index_2 = rand() % 35 + 1;
//for draw man head
int body_LEFT = 1;

//for showing dynamic points 
bool is_bomb = 0, is_touch_mj1 = 0, is_touch_mj2 = 0, is_touch_c1 = 0, is_touch_c2 = 0, is_touch_c3 = 0, is_touch_c4 = 0;
float bomb_startt = 0, bomb_x, bomb_y ;
float mj1_startt = 0, mj1_x , mj1_y;
float mj2_startt = 0, mj2_x , mj2_y;
float c1_startt = 0, c1_x, c1_y;
float c2_startt = 0, c2_x, c2_y;
float c3_startt = 0, c3_x, c3_y;
float c4_startt = 0, c4_x, c4_y;



struct Cir
{
    float Xc,Yc,radius;
};
struct Rect
{
    float Xc,Yc,left,right,top,bottom;
};

//structer of player
struct Pl
{

    Pl()
    {
      head={0,static_cast<float>(-0.7 * h),headRadius};
    }
  struct Cir head;
  struct Rect body;//={625,725,100,50};
  struct Rect leg;
};
struct Cir c1={75,720,coinRadius}; //first ball
struct Cir c2={300,720,coinRadius}; //second balls
struct Cir c3={550,720,coinRadius}; //third balls
struct Cir c4={800,720,coinRadius}; //second balls
struct Cir c5={1250,720,coinRadius}; //third balls
struct Pl player;
struct Rect wall={0,0,static_cast<float>(-0.5 *w),w,h,static_cast<float>(-0.95 * h )};
struct Rect mj_1 = {200, 300, 500, 600, 720, 570};
struct Rect mj_2 = {50, 300, 500, 600, 720, 570};



void DrawFilledCircle(float x,float y,float r)
{
    x = x/w;
    y = y/h;
    r = r/500;
    float r_texture = 0.45f;
    glDepthFunc(GL_ALWAYS); 
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0.5f, 0.5f);
    glVertex2f(x,y);
    int seg=1000;
    for(int i=0;i<=seg;i++)
    {
        double angle=i*2*3.14/seg;
        glTexCoord2f(0.5 +r_texture*cos(angle),0.5 +r_texture*sin(angle));
        glVertex2f(x+r*cos(angle),y+r*sin(angle));
    }
    glEnd();
}
void DrawManFace_L(float x,float y,float r)
{
    x = x/w;
    y = y/h;
    r = r/500;
    float r_texture = 0.45f;
    glBindTexture(GL_TEXTURE_2D, texture[39]);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1,1,1);
    glTexCoord2f(0.5f, 0.5f);
    glVertex2f(x,y);
    int seg=1000;
    for(int i=0;i<=seg;i++)
    {
        double angle=i*2*3.14/seg;
        glTexCoord2f(0.5 +r_texture*cos(angle),0.5 +r_texture*sin(angle));
        glVertex2f(x+r*cos(angle),y+r*sin(angle));
    }
    glEnd();
}
void DrawManFace_R(float x,float y,float r)
{
    x = x/w;
    y = y/h;
    r = r/500;
    float r_texture = 0.45f;
    glBindTexture(GL_TEXTURE_2D, texture[39]);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1,1,1);
    glTexCoord2f(0.5f, 0.5f);
    glVertex2f(x,y);
    int seg=1000;
    for(int i=seg;i>=0;i--)
    {
        double angle=i*2*3.14/seg;
        angle += 3.14;
        double angle1=(seg-i)*2*3.14/seg;

        glTexCoord2f(0.5 +r_texture*cos(angle),0.5 +r_texture*sin(angle));
        glVertex2f(x+r*cos(angle1),y+r*sin(angle1));
    }
    glEnd();
}
void DrawBombCircle(float x,float y,float r)
{
    x = x/w;
    y = y/h;
    r = r/500;
    //float r_texture = 0.3f;
    glColor4ub(255, 255, 255, 255);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendEquationSeparate(GL_MAX, GL_FUNC_ADD);
    glBindTexture(GL_TEXTURE_2D, texture[36]);
    // glBegin(GL_TRIANGLE_FAN);
    // glTexCoord2f(0.5f, 0.5f);
    // glVertex2f(x,y);
    // int seg=1000;
    // for(int i=0;i<=seg;i++)
    // {
    //     double angle=i*2*3.14/seg;
    //     glTexCoord2f(0.5 +r_texture*cos(angle),0.5 +r_texture*sin(angle));
    //     glVertex2f(x+r*cos(angle),y+r*sin(angle));
    // }
    // glEnd();
    glColor4f(1,1,1,1);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(x , y);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex2f(x + 0.2f, y);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex2f(x + 0.2f, y + 0.2f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex2f(x, y + 0.2f);  // Top Left Of The Texture and Quad
    glEnd();
    glDisable(GL_BLEND);
}
//Function to Draw Circle
void DrawCircle(float x, float y, float r){
    x = x/w;
    y = y/h;
    r = r/500;
	int i;
	int lineAmount = 100; //# of triangles used to draw circle

	//float radius = 0.8f; //radius
	float twicePi = 2.0f * 3.142;

	glBegin(GL_LINE_LOOP);
		for(i = 0; i <= lineAmount;i++) {
			glVertex2f(
			    x + (r * cos(i *  twicePi / lineAmount)),
			    y + (r * sin(i * twicePi / lineAmount))
			);
		}
	glEnd();
}
//function to draw Line
void Drawline(float x1,float y1,float x2,float y2)
{
    x1 = x1/w;
    x2 = x2/w;
    y1 = y1/h;
    y2 = y2/h;
    glBegin(GL_LINES);
    glVertex3f(x1,y1,0.0);
    glLineWidth(10);
    glVertex3f(x2,y2,0.0);
    glEnd();
}
//function to draw rectangle
void DrawMJrectang(float x1,float x2,float y1,float y2, int mj_index)
{
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_MAX);
    // glBlendEquationSeparate(GL_MAX, GL_DST_ALPHA);
    glBindTexture(GL_TEXTURE_2D, texture[mj_index]);
    glEnable(GL_TEXTURE_2D);        
    x1 = x1/w;
    x2 = x2/w;
    y1 = y1/h;
    y2 = y2/h;
    // glBegin(GL_QUADS);
    // glTexCoord2f(0.1f, 0.1f);             glVertex2f(x1,y1);
    // glTexCoord2f(0.1f, 0.75f);            glVertex2f(x1,y2);
    // glTexCoord2f(0.75f , 0.75f);          glVertex2f(x2,y2);
    // glTexCoord2f(0.75f , 0.1f);           glVertex2f(x2,y1);
    // glEnd();
    glBegin(GL_QUADS);
    glTexCoord2f(0.05f, 0.05f);             glVertex2f(x1,y1);
    glTexCoord2f(0.05f, 0.95f);            glVertex2f(x1,y2);
    glTexCoord2f(0.95f , 0.95f);          glVertex2f(x2,y2);
    glTexCoord2f(0.95f , 0.05f);           glVertex2f(x2,y1);
    glEnd();
    glDisable(GL_BLEND);
}
void Drawrectang(float x1,float x2,float y1,float y2)
{
    x1 = x1/w;
    x2 = x2/w;
    y1 = y1/h;
    y2 = y2/h;
    glColor3f(1, 0,0);
    glBegin(GL_QUADS);
    glVertex2f(x1,y1);
    glVertex2f(x1,y2);
    glVertex2f(x2,y2);
    glVertex2f(x2,y1);
    glEnd();
}
void DrawManBody(float x1,float x2,float y2,float y1)
{
    x1 = x1/w -0.1;
    x2 = x2/w + 0.1;
    y1 = y1/h - 0.1;
    y2 = y2/h ;
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_MAX);
    glColor3f(1, 1,1);
    glBindTexture(GL_TEXTURE_2D, texture[40]);               // Select Our Texture
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(x1,y1);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex2f(x2,y1);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex2f(x2,y2);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex2f(x1,y2);  // Top Left Of The Texture and Quad
    glEnd();
    glDisable(GL_BLEND);
}
// drawing player
void drawman()
{
    glColor3f(1,0,0);              //set the color of Head
    float xc=player.head.Xc;       //set the center of head
    float yc=player.head.Yc;
    float r=player.head.radius;    // set the radius of head
    //std::cout << xc <<" " << yc << " "<< r<< std::endl;
    if(body_LEFT == 1){
        DrawManFace_L(xc,yc,r);
    }
    else DrawManFace_R(xc,yc,r);
    //DrawManFace_R(xc,yc,r);          //drawing head
    //set coordinate of player body
    player.body.left=xc-r;
    player.body.right=xc+r;
    player.body.top=yc-r;
    player.body.bottom=yc-3*r;
    glColor3f(0,0.3,0.1);           // set color of player body part
    DrawManBody(player.body.left,player.body.right,player.body.top,player.body.bottom);
    // set leg part of body
    player.leg.left=xc-r/2;
    player.leg.right=xc+r/2;
    player.leg.top=yc-3*r;
    player.leg.bottom=yc-4*r;
    glColor3f(0,1,1);               // set leg color
    Drawrectang(player.leg.left,player.leg.right,player.leg.top,player.leg.bottom);
}
// drawing different coins
void drawMaJiang_1(int mj_index){
    glColor3f(1,1,1);
    DrawMJrectang(mj_1.Xc, mj_1.Xc + 150, mj_1.Yc, mj_1.Yc + 200, mj_index);
}
void drawMaJiang_2(int mj_index){
    glColor3f(1,1,1);
    DrawMJrectang(mj_2.Xc, mj_2.Xc + 150, mj_2.Yc, mj_2.Yc + 200, mj_index);
}

void drawcoin1()
{
    //glColor3f(1,0,0);
    DrawFilledCircle(c1.Xc,c1.Yc,c1.radius);
}
void drawcoin2()
{
    //glColor3f(0,1,0);
    DrawFilledCircle(c2.Xc,c2.Yc,c2.radius);
}
void drawcoin3()
{
    //glColor3f(1,0,1);
    DrawFilledCircle(c3.Xc,c3.Yc,c3.radius);
}
void drawcoin4()
{
    //glColor3f(1,1,0);
    DrawFilledCircle(c4.Xc,c4.Yc,c4.radius);
}
void drawBomb()
{
    glColor3f(1,1,1);
    DrawBombCircle(c5.Xc,c5.Yc,c5.radius);
}
void drawScene()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(1,1,0);
    drawcoin1();
    drawcoin2();
    drawcoin3();
    drawcoin4();
    drawBomb();
    drawMaJiang_1(mj_index_1);
    drawMaJiang_2(mj_index_2);
}
//check Collision between coin and player
int coin_player(struct Cir c)
{
    float d1=(c.Xc-player.head.Xc);
    float d2=(c.Yc-player.head.Yc);
    float d=sqrt(d1*d1+d2*d2);
    float parameter = 0.58;
    if(c.Yc > player.head.Yc){
        if(parameter * d<=c.radius+player.head.radius)
        return 1;
    }
    else{
        if(parameter * d<=c.radius+player.head.radius)
        return 1;
    }
    return 0;
}
int mj_player(struct Rect mj){
    float centerx = mj.Xc + 75;
    float centery = mj.Yc + 100;
    float d1=(centerx-player.head.Xc);
    float d2=(centery-player.head.Yc);
    float d=sqrt(d1*d1+d2*d2);
    if(centery > player.head.Yc && d < player.head.radius + 125){
        return 1;
    }
    else if (centery < player.head.Yc){
        d1 = 4 * player.head.radius - 100;
        d2 = player.head.radius + 75;
        float max_d=sqrt(d1*d1+d2*d2);
        if(d < max_d)return 1;
    }
    return 0;
}
int bomb_player(struct Cir c){
    float centerx = c.Xc + 0.1 * w;
    float centery = c.Yc + 0.1 * h;
    float d1=(centerx-player.head.Xc);
    float d2=(centery-player.head.Yc);
    float d=sqrt(d1*d1+d2*d2);
    if(centery > player.head.Yc && d < player.head.radius + 100){
        return 1;
    }
    else if (centery < player.head.Yc){
        d1 = 4 * player.head.radius - 100;
        d2 = player.head.radius + 75;
        float max_d=sqrt(d1*d1+d2*d2);
        if(d < max_d)return 1;
    }
    return 0;
    
}
//Check collision between Coins and balls
int coin_wall(struct Cir c)
{
    if(c.Yc<=wall.bottom)
        return 1;
    return 0;
}
int mj_wall(struct Rect r)
{
    if(r.Yc<=wall.bottom)
        return 1;
    return 0;
}
//check collision of coins from wall or player
void check_player_mj_1()
{
    if(mj_wall(mj_1))
    {

        mj_1.Yc=750;
        mj_position=75 + rand()%(int)(2 * w-2*75) - w ;
        mj_1.Xc=mj_position;
        mj_index_1 = rand() % 35 + 1;
        drawMaJiang_1(mj_index_1);


    }
    if(mj_player(mj_1))
    {
        is_touch_mj1 = 1;
        mj1_x = mj_1.Xc;
        mj1_y = mj_1.Yc;
        mj1_startt = ttime;
        mj_1.Yc=750;
        mj_position=75 + rand()%(int)(2 * w-2*75) - w;
        mj_1.Xc=mj_position;
        mj_index_1 = rand() % 35 + 1;
        drawMaJiang_1(mj_index_1);
        score += 3;
    }
    show_add_Points(is_touch_mj1, mj1_x, mj1_y, mj1_startt, 3);
}
void check_player_mj_2()
{
    if(mj_wall(mj_2))
    {

        mj_2.Yc=750;
        mj_position=75 + rand()%(int)(2 * w-2*75) - w;
        mj_2.Xc=mj_position;
        mj_index_2 = rand() % 35 + 1;
        drawMaJiang_2(mj_index_2);
    }
    if(mj_player(mj_2))
    {
        is_touch_mj2 = 1;
        mj2_x = mj_2.Xc;
        mj2_y = mj_2.Yc;
        mj2_startt = ttime;
        mj_2.Yc=750;
        mj_position=75 + rand()%(int)(2 * w-2*75) - w;
        mj_2.Xc=mj_position;
        mj_index_2 = rand() % 35 + 1;
        drawMaJiang_2(mj_index_2);
        score += 3;
    }
    show_add_Points(is_touch_mj2, mj2_x, mj2_y, mj2_startt, 3);
}
void check_player_c1()
{
    if(coin_wall(c1))
    {
        c1.Yc=750;
        i=c1.radius+rand()%(int)(2 * w-2*c1.radius) - w;
        c1.Xc=i;
        drawcoin1();
    }
    if(coin_player(c1))
    {
        is_touch_c1 = 1;
        c1_x = c1.Xc;
        c1_y = c1.Yc;
        c1_startt = ttime;
        c1.Yc=750;
        i=c1.radius+rand()%(int)(2 * w-2*c1.radius) - w;
        c1.Xc=i;
        drawcoin2();
        score++;
    }
    show_add_Points(is_touch_c1, c1_x, c1_y, c1_startt, 1);
    
}
void check_player_c2()
{
    if(coin_wall(c2))
    {

        c2.Yc=750;
        j=c2.radius+rand()%(int)(2 * w-2*c2.radius) - w;
        c2.Xc=j;
        drawcoin1();
    }
    if(coin_player(c2))
    {
        is_touch_c2 = 1;
        c2_x = c2.Xc;
        c2_y = c2.Yc;
        c2_startt = ttime;
        c2.Yc=750;
        j=c2.radius+rand()%(int)(2 * w-2*c2.radius) - w;
        c2.Xc=j;
        drawcoin2();
        score++;
    }
    show_add_Points(is_touch_c2, c2_x, c2_y, c2_startt, 1);
}
void check_player_c3()
{
    if(coin_wall(c3))
    {
        c3.Yc=750;
        k=c3.radius+rand()%(int)(2 * w - 2 * c3.radius) - w;
        c3.Xc=k;
        drawcoin4();
    }
    if(coin_player(c3))
    {
        is_touch_c3 = 1;
        c3_x = c3.Xc;
        c3_y = c3.Yc;
        c3_startt = ttime;
        c3.Yc=750;
        k=c3.radius+rand()%(int)(2 * w - 2 * c3.radius) - w;
        c3.Xc=k;
        drawcoin3();
        score++;
    }
        show_add_Points(is_touch_c3, c3_x, c3_y, c3_startt, 1);
}
void check_player_c4()
{
    if(coin_wall(c4))
    {
        c4.Yc=750;
        l=c4.radius+rand()%(int)(2*w-2*c4.radius) -w;
        c4.Xc=l;
        drawcoin3();
    }
    if(coin_player(c4))
    {
        is_touch_c4 = 1;
        c4_x = c4.Xc;
        c4_y = c4.Yc;
        c4_startt = ttime;
        c4.Yc=750;
        l=c4.radius+rand()%(int)(2*w-2*c4.radius) -w;
        c4.Xc=l;
        drawcoin4();
        score++;
    }
    show_add_Points(is_touch_c4, c4_x, c4_y, c4_startt, 1);
}
void check_player_bomb()
{
    if(coin_wall(c5))
    {

        c5.Yc=750;
        m=c5.radius+rand()%(int)(2*w-2*c5.radius)-w;
        c5.Xc=m;
        drawBomb();
    }
    if(bomb_player(c5))
    {
        is_bomb = 1;
        bomb_x = c5.Xc;
        bomb_y = c5.Yc;
        bomb_startt = ttime;
        c5.Yc=750;
        m=c5.radius+rand()%(int)(2*w-2*c5.radius)-w;
        c5.Xc=m;
        drawBomb();
        score -= 5;
    }
    show_minus_Points(is_bomb, bomb_x, bomb_y, bomb_startt, 5);
}
void show_minus_Points(bool &touch, float x, float y, float current_time, int points){
    if(touch){
        float time_diff = ttime - current_time;
        glColor3f(1, 0, 0);
        freetype::print(our_font, x/(2*w) + 0.5f, y/(2*h) + 0.5f - time_diff/3 * 0.1f,"-%dE", points);
        if(time_diff > 2){
            touch = 0;
        }   
    }
}   
void show_add_Points(bool &touch, float x, float y, float current_time, int points){
    if(touch){
        float time_diff = ttime - current_time;
        glColor3f(1, 1, 0);
        freetype::print(our_font, x/(2*w) + 0.5f, y/(2*h) + 0.5f - time_diff/3 * 0.1f,"+%dE", points);
        if(time_diff > 2){
            touch = 0;
        }   
    }
}
//call all collision function to detect the collision
void checkCollision()
{
    check_player_c1();
    check_player_c2();
    check_player_c3();
    check_player_c4();
    check_player_bomb();
    check_player_mj_1();
    check_player_mj_2();
}
//display startMenu
void startMenu()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glLoadIdentity();
    glColor3f(0.0f,0.0f,1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(-1.0f, 1.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(1.0f, -1.0f);
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glColor3f(1,0,0);
    int wx=2*w/4;
    int hy=2*h/4;
    Drawline(-wx,hy,wx,hy);
    Drawline(wx,hy,wx,-hy);
    Drawline(wx,-hy,-wx,-hy);
    Drawline(-wx,-hy,-wx,hy);
    glPopMatrix();
    glColor3f(1,1,1);
    glBindTexture(GL_TEXTURE_2D, texture[42]);               // Select Our Texture
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Top Left Of The Texture and Quad
    glEnd();
    glColor3ub(189, 63, 0);
    freetype::print(font_2, 0.2f, 0.85f, "Coin Catcher Game -version onee");
    glColor3ub(255, 255, 128);
    glBindTexture(GL_TEXTURE_2D, texture[37]);               // Select Our Texture
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f,  1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f, -0.5f,  1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f,  0.5f,  1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f,  0.5f,  1.0f);  // Top Left Of The Texture and Quad
    glEnd();
    glColor3ub(255, 255, 0);
    freetype::print(our_font, 0.3f, 0.78f, "Press 'S' For START             Press 'E' For EXITT");
    freetype::print(our_font, 0.05f, 0.43f, "STAET Game  ---> SS\0");
    freetype::print(our_font, 0.8f, 0.43f, "EXIT  Game  ---> ES\0");
    glColor3ub(255,255,0);
    freetype::print(our_font, 0.25f, 0.16f, "Use YOUR KEYBOARD LEFT RIGHT arrow KEYs to controll\0");
    glColor3ub(255,0,0); 
    freetype::print(our_font, 0.32f, 0.10f, "Hint:A KEY and D KEY are allowed tool\0");
    glColor3ub(255,255,0);
    freetype::print(our_font, 0.27f, 0.05f, "You ONLY have 60 seconds to PLAY Take Your TimeS\0");
}
// display pauseMenu
void pauseMenu()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glLoadIdentity();
    glColor3f(0,0,0);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(-1.0f, 1.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(1.0f, -1.0f);
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glColor3f(1,0,0);
    int wx=2*w/4;
    int hy=2*h/4;
    Drawline(-wx,hy,wx,hy);
    Drawline(wx,hy,wx,-hy);
    Drawline(wx,-hy,-wx,-hy);
    Drawline(-wx,-hy,-wx,hy);
    glColor3f(1,1,1);
    glBindTexture(GL_TEXTURE_2D, texture[43]);               // Select Our Texture
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.9f, -0.3f,  1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( -0.3f, -0.3f,  1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( -0.3f,  0.8f,  1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.9f,  0.8f,  1.0f);  // Top Left Of The Texture and Quad
    glEnd();
    glPopMatrix();
    glColor3f(1,0,0);
    freetype::print(our_font, 0.4f + 0.15f, 0.7f, "BACK TO GAME   ---> Press 1S");
    glColor3f(1,1,1);
    freetype::print(our_font, 0.398f + 0.15f, 0.705f, "BACK TO GAME   ---> Press 1S");
    glColor3f(1,0,0);
    freetype::print(our_font, 0.4f + 0.15f, 0.50f, " NEW GAME       ---> Press 2S");
    glColor3f(1,1,1);
    freetype::print(our_font, 0.398f + 0.15f, 0.505f, " NEW GAME       ---> Press 2S");
    glColor3f(1,0,0);
    freetype::print(our_font, 0.4f + 0.15f, 0.30f, " EXIT GAME      ---> Press 3S");
    glColor3f(1,1,1);
    freetype::print(our_font, 0.398f + 0.15f, 0.305f, " EXIT GAME      ---> Press 3S");
}
//display gameoverMenu
void gameoverMenu()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glLoadIdentity();
    glColor3f(0,0,0);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(-1.0f, 1.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(1.0f, -1.0f);
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glColor3f(1,1,1);
    glBindTexture(GL_TEXTURE_2D, texture[41]);               // Select Our Texture
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f,  1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f,  1.0f);  // Top Left Of The Texture and Quad
    glEnd();

    int wx=2*w/4;
    int hy=2*h/4;
    Drawline(-wx,hy,wx,hy);
    Drawline(wx,hy,wx,-hy);
    Drawline(wx,-hy,-wx,-hy);
    Drawline(-wx,-hy,-wx,hy);
    glPopMatrix();
    glColor3f(1,0,0);
    freetype::print(num_font, 0.38f, 0.7f, "--------GAME OVER--------");
    glColor3f(1,1,0);
    if (score > 30){
        freetype::print(our_font, 0.40f, 0.6f, "CONGRATULATIONSS"); 
    }
    glColor3f(1,0,0);
    freetype::print(our_font, 0.4f, 0.5f, "YOUR SCORE is:s");
    if(score > 30)glColor3f(1,1,0);
    if(score < 0 )score = 0;
    freetype::print(num_font, 0.55f, 0.5f, "%ds", score);
    glColor3f(1,1,1);
    freetype::print(our_font, 0.38f, 0.4f, " NEW GAME       ---> Press 2S");
    freetype::print(our_font, 0.38f, 0.3f, " EXIT GAME       ---> Press 3S");
}

//timer function
void Timer()
{
    c1.Yc-= c1Speed * (0.5 + ttime/120);
    c2.Yc-= c2Speed * (0.5 + ttime/120);
    c3.Yc-= c3Speed * (0.5 + ttime/120);
    c4.Yc-= c4Speed * (0.5 + ttime/120);
    c5.Yc-= c5Speed * (0.5 + ttime/120);
    mj_1.Yc -= mj_speed * (0.5 + ttime/120);
    mj_2.Yc -= mj_speed * (0.5 + ttime/120);
    ttime+=0.016;
}

int drawGameText()                                     // Here's Where We Do All The Drawing
{
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                 // Clear Screen And Depth Buffer
    glLoadIdentity();                                   // Reset The Current Modelview Matrix
    glTranslatef(0.0f,0.0f,-1.0f);                              // Move One Unit Into The Screen

 
    // Here We Print Some Text Using Our Freetype Font
    // The Only Really Important Command Is The Actual Print() Call,
    // But For The Sake Of Making The Results A Bit More Interesting
    // I Have Put In Some Code To Rotate And Scale The Text.
 
    // Red Text
    glColor3ub(255,255,0);
 
    glPushMatrix();
    glLoadIdentity();
    // glRotatef(cnt1,0,0,1);
    glScalef(0.1f,0.1f,1);
    // glTranslatef(-1000,0,0);

    //freetype::print(font_2, 0.3f, 0.9f, "ABCDEFGHIJKLMNOPQRSTUVWXYZ - %7.2f", cnt1);
    // glColor3ub(189, 63, 0);
    glColor3ub(255, 209, 5);
    freetype::print(num_font, 0.43f, 0.88f, "SCOREE");
    freetype::print(num_font, 0.47f, 0.78f, "%ds", score);
    glColor3ub(255,255,255);
    freetype::print(num_font, 0.02f, 0.9f, "%.1fs", 60 - ttime);
    glPopMatrix();
    freetype::print(our_font, 0.8f, 0.94f, "P : Pause       E : EXITT");
 
    // Uncomment This To Test Out Print's Ability To Handle Newlines.
 
    return 1;                                        // Everything Went OK
}


int LoadGLTextures()                                    // Load Bitmaps And Convert To Textures
{
    /* load an image file directly as a new OpenGL texture */
    texture[0] = SOIL_load_OGL_texture
        (
        "image/lovepik-gold-coin-png-image_400321087_wh1200.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
        );
 
    if(texture[0] == 0)
        return false;

    int file_count = 1;
    DIR * dirp;
    struct dirent * entry;
    char filename[100];
    dirp = opendir("image/MJ"); /* There should be error handling after this */
    while ((entry = readdir(dirp)) != NULL) {
        if (entry->d_type == DT_REG) { /* If the entry is a regular file */
            sprintf(filename, "image/MJ/%s", entry->d_name);
            //printf("%s\n", filename);
            texture[file_count] = SOIL_load_OGL_texture
                (
                filename,
                SOIL_LOAD_AUTO,
                SOIL_CREATE_NEW_ID,
                SOIL_FLAG_INVERT_Y
                );
            if(texture[file_count] == 0)return false;
            glBindTexture(GL_TEXTURE_2D, texture[file_count]);
            file_count++;   
        }
    }
    printf("%d ", file_count);
    closedir(dirp);
    // file count is 36
    texture[file_count] = SOIL_load_OGL_texture
        (
        "image/pngtree-bomb-bomb-cartoon-png-image_5393332.jpeg",
        3,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
        );
    if(texture[file_count] == 0)
        return false;
    file_count ++;
    //37
    texture[file_count] = SOIL_load_OGL_texture
        (
        "image/649cb025f8f7132d89c24be808f690f2.jpeg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
        );
    if(texture[file_count] == 0)
        return false;
    file_count ++;
    //38
    texture[file_count] = SOIL_load_OGL_texture
        (
        "image/mahjong.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
        );
    if(texture[file_count] == 0)
        return false;
    file_count ++;
    //39
    texture[file_count] = SOIL_load_OGL_texture
        (
        "image/face-circle-emoticon-kawaii-style-vector-illustration-design-H8P79Y.jpeg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
        );
    if(texture[file_count] == 0)
        return false;
    file_count ++;
    //40
    texture[file_count] = SOIL_load_OGL_texture
        (
        "image/official.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
        );
    if(texture[file_count] == 0)
        return false;
    file_count ++;
    //41
    texture[file_count] = SOIL_load_OGL_texture
        (
        "image/ending_bg.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
        );
    if(texture[file_count] == 0)
        return false;
    file_count ++;
    //42
    texture[file_count] = SOIL_load_OGL_texture
        (
        "image/startbg.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
        );
    if(texture[file_count] == 0)
        return false;
    file_count ++;
    //43
    texture[file_count] = SOIL_load_OGL_texture
        (
        "image/pause.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
        );
    if(texture[file_count] == 0)
        return false;
    file_count ++;

    // Typical Texture Generation Using Data From The Bitmap
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
 
    return true;                                        // Return Success
}

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    if(!glfwInit()){
        std::cout << "Fail to init glfw!" << std::endl;
    }
    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(w, h, "Coin Collect Game", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //texture Loading
    if (!LoadGLTextures())                          // Jump To Texture Loading Routine ( NEW )
    {
        std::cout << "Failed to Load GL Textures" << std::endl;
        return -1;                           // If Texture Didn't Load Return FALSE ( NEW )
    }
    glEnable(GL_TEXTURE_2D);                        // Enable Texture Mapping ( NEW )

    //Freetype initialization
    std::string str = "fonts/Lato-SemiboldItalic.ttf";
    std::string str1 = "fonts/IcecreamypersonaluseBold-3zgoy.otf";
    std::string str2 = "fonts/justme54s_jersey-m54/Jersey M54.ttf";
    char filename[str.length() + 1];
    char filename1[str1.length() + 1];
    char filename2[str2.length() + 1];
    strcpy(filename, str.c_str());
    strcpy(filename1, str1.c_str());
    strcpy(filename2, str2.c_str());
    our_font.init(filename, 40); 
    font_2.init(filename1, 90); 
    num_font.init(filename2, 90);





    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        glClearColor(0.2f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        display();
        Timer();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    our_font.clean();
    font_2.clean();
    num_font.clean();
    return 0;
}

// main display function
void display(void)
 {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //clear the buffer
    glLoadIdentity();
    if(game_state==menu)
    {
        score=0;
        ttime=0;
        startMenu();
    }
    if(game_state==play)
    {

        t=ttime;
        glPushMatrix();
        glLoadIdentity();
        glColor3f(1,1,1);
        glPopMatrix();
        glBindTexture(GL_TEXTURE_2D, texture[38]);               // Select Our Texture
        glColor3f(0.3,0.3,0.3);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);  // Top Right Of The Texture and Quad
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Top Left Of The Texture and Quad
        glEnd();
        drawman();
        drawGameText();
        drawScene();
        checkCollision();
        if(score < 0)game_state = over;
    }
    if((int)ttime==gameTime)
    {
        ttime=0;    //reset the timepassed
        game_state=over;
    }
    if(game_state==pause)
    {
        ttime=t;         //pause the timer
        pauseMenu();
    }
    if(game_state==over)
    {
        gameoverMenu();
    }
    if(game_state==gameexit)
    {
        exit(0);
    }
    glFlush();
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if((glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS | glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)  && player.head.Xc < (w - headRadius))
    { 
        body_LEFT = 0;
        player.head.Xc += 0.52*Xspeed;
    }
    if((glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS| glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS )&& player.head.Xc > (headRadius-w))
    {
        body_LEFT = 1;
        player.head.Xc  -= 0.52*Xspeed;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        if(game_state==menu){game_state=play;}
    }
    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){
        return;
    }
    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS){
        if(game_state == menu){game_state=gameexit;}
        if(game_state == play){game_state = over;}
    }
    if(glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS){
        if(game_state==play){game_state=pause;}
    }
    if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS){
        if(game_state==pause){game_state=play;}
    }
    if(glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS){
         if(game_state==pause || game_state==over){game_state=menu;}
    }
    if(glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS){
        if(game_state==pause || game_state==over){game_state=gameexit;}
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

