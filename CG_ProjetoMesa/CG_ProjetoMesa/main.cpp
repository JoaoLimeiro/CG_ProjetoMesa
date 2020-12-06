/*
 
 Computação Gráfica 2020
 
 João Limeiro 2017262387
 
 --------------   Instruções   --------------

 T ou t -> o tampo de mesa adicional do lado esquerdo sobe até estar completamente reto
 Y ou y -> o tampo de mesa adicional do lado esquerdo desde até estar debaixo da mesa
 G ou g -> o tampo de mesa adicional do lado direito sobe até estar completamente reto
 H ou h -> o tampo de mesa adicional do lado direito desde até estar debaixo da mesa
 R ou r -> abre os dois tampos de mesa adicionais ate estarem completamente retos
 F ou f -> colhe os dois tampos de mesa adicionais ate estarem debaixo da mesa
 M ou m -> abre a gaveta ate uma certa posição
 N ou n -> fecha a gaveta
 Setas -> move a camara
 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <math.h>
#define GL_SILENCE_DEPRECATION
#include <GL/glew.h>
#include <GLUT/glut.h>

//--------------------------------- Definir cores
#define BLUE     0.0, 0.0, 1.0, 1.0
#define RED      1.0, 0.0, 0.0, 1.0
#define YELLOW   1.0, 1.0, 0.0, 1.0
#define GREEN    0.0, 1.0, 0.0, 1.0
#define WHITE    1.0, 1.0, 1.0, 1.0
#define BLACK    0.0, 0.0, 0.0, 1.0

//--------------------------------------- Garante a inclusao do GLEW / openGL / glu no link
#pragma comment(lib,"glew32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"opengl32.lib")


#include "RgbImage.h"
#define PI         3.14159

void initMaterials(int material);
char Materiais[18][30] = {
    "Esmerald",  "Jade",  "obsidian",    "Pearl",        "Ruby",
    "Turquoise", "Brass", "Bronze",      "Chrome",       "Copper",
    "Gold",      "Silver","blackPlastic","cyankPlastic", "greenPlastic",
    "redPlastic", "whitePlastic","yellowPlastic" };

//------------------------------------------ DefiniÁ„o dos ficheiros dos shaders: vertices + fragmentos
char filenameV[] = "Vshader_bin1.txt";
char filenameF[] = "Fshader_bin1.txt";






//================================================================================
//===========================================================Variaveis e constantes

static GLfloat vertices[] = {
    /*
                              2,9,16_________6,10,19
                                   /|       /
                                  / |      /|
                           1,8,12/__|_____/ | <- 5,11,15
                                 |  |_____|_|7,18,22
                                 | 3,17,23| /
                          0,13,20|________|/4,14,21
                                 
    */
    //__________________________________ Esquerda
            0,   0,  0.125,    // 0
            0,   2,  0.125,    // 1
            0,   2,      0,    // 2
            0,   0,      0,    // 3
    //__________________________________ Direita
        0.125,   0,  0.125,    // 4
        0.125,   2,  0.125,    // 5
        0.125,   2,      0,    // 6
        0.125,   0,      0,    // 7
    //__________________________________ Cima
            0,   2,  0.125,     // 8
            0,   2,      0,     // 9
        0.125,   2,      0,     // 10
        0.125,   2,  0.125,     // 11
    //__________________________________ Frente
            0,   2,  0.125,     // 12
            0,   0,  0.125,     // 13
        0.125,   0,  0.125,     // 14
        0.125,   2,  0.125,     // 15
    //__________________________________ Back
            0,   2,      0,     // 16
            0,   0,      0,     // 17
        0.125,   0,      0,     // 18
        0.125,   2,      0,     // 19
    //__________________________________ Baixo
            0,   0,  0.125,     // 20
        0.125,   0,  0.125,     // 21
        0.125,   0,      0,     // 22
            0,   0,      0,     // 23
};

static GLfloat normais[] = {
    //ÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖ x=tam (Esquerda)
        -1.0,  0.0,  0.0,
        -1.0,  0.0,  0.0,
        -1.0,  0.0,  0.0,
        -1.0,  0.0,  0.0,
    //ÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖ x=tam (Direita)
        1.0,  0.0,  0.0,
        1.0,  0.0,  0.0,
        1.0,  0.0,  0.0,
        1.0,  0.0,  0.0,
    //ÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖ y=tam (Cima)
        0.0,  1.0,  0.0,
        0.0,  1.0,  0.0,
        0.0,  1.0,  0.0,
        0.0,  1.0,  0.0,
    //ÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖ y=tam (Frente)
        0.0,  0.0,  1.0,
        0.0,  0.0,  1.0,
        0.0,  0.0,  1.0,
        0.0,  0.0,  1.0,
    //ÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖ y=tam (Back)
        0.0,  0.0,  -1.0,
        0.0,  0.0,  -1.0,
        0.0,  0.0,  -1.0,
        0.0,  0.0,  -1.0,
    //ÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖ y=tam (Baixo)
        0.0,  -1.0,  0.0,
        0.0,  -1.0,  0.0,
        0.0,  -1.0,  0.0,
        0.0,  -1.0,  0.0,
};
//------------------------------------------------------------ Cores
static GLfloat cor[] = {
    //____________________________x=tam (Esquerda) -
    0.40,  0.26, 0.13,    // 0
    0.40,  0.26, 0.13,    // 1
    0.40,  0.26, 0.13,    // 2
    0.40,  0.26, 0.13,    // 3
    0.40,  0.26, 0.13,    // 0
    0.40,  0.26, 0.13,    // 1
    0.40,  0.26, 0.13,    // 2
    0.40,  0.26, 0.13,    // 3
    0.40,  0.26, 0.13,    // 0
    0.40,  0.26, 0.13,    // 1
    0.40,  0.26, 0.13,    // 2
    0.40,  0.26, 0.13,    // 3
    0.40,  0.26, 0.13,    // 0
    0.40,  0.26, 0.13,    // 1
    0.40,  0.26, 0.13,    // 2
    0.40,  0.26, 0.13,    // 3
    0.40,  0.26, 0.13,    // 0
    0.40,  0.26, 0.13,    // 1
    0.40,  0.26, 0.13,    // 2
    0.40,  0.26, 0.13,    // 3
    0.40,  0.26, 0.13,    // 0
    0.40,  0.26, 0.13,    // 1
    0.40,  0.26, 0.13,    // 2
    0.40,  0.26, 0.13,    // 3
};
static GLfloat arrayTexture[] = {
0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1,  0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1, 0,0, 1,0, 1,1, 0,1
};

//=========================================================== FACES DA MESA
GLint   frenteVisivel = 0;
static GLuint     cima[] = { 8, 11, 10,  9 };       // regra da mao direita
static GLuint     esquerda[] = { 0, 1, 2, 3 };
static GLuint     esquerdaGaveta[] = { 0, 3, 2, 1 };
static GLuint     direita[] = { 4, 7, 6, 5 };
static GLuint     frente[] = { 12, 13, 14, 15 };
static GLuint     frenteGaveta[] = { 12, 15, 14, 13 };
static GLuint     back[] = { 16, 19, 18, 17 };
static GLuint     backGaveta[] = { 16, 17, 18, 19 };
static GLuint     baixo[] = { 20, 23, 22, 21 };
static GLuint     baixoGaveta[] = { 20, 21, 22, 23 };


GLfloat startForce = 2.5;
GLfloat gravity = 1;
GLfloat r = 50; // ball radius

//------------------------------------------------------------ Objectos (sistema coordenadas)
GLint        wScreen = 800, hScreen = 600;            //.. janela (pixeis)
GLfloat        xC = 10.0, yC = 10.0, zC = 10.0;        //.. Mundo  (unidades mundo)

//------------------------------------------------------------ Visualizacao/Observador
GLfloat  rVisao = 10.0, aVisao = 0.5 * PI, incVisao = 0.1;
GLfloat  angPersp = 100.0;
GLfloat  obsPini[] = {10, 5.0, (GLfloat)0.5 * xC };
GLfloat  obsPfin[] = { obsPini[0] - rVisao * cos(aVisao), obsPini[1], obsPini[2] - rVisao * sin(aVisao)};


GLfloat xPosition = 0, yPosition = 0, zPosition = 0;
GLfloat angleEsqTampo = 90, angleDirTampo = 90, translateGaveta = 0;

//------------------------------------------------------------ Texturas (5 texturas)
GLuint   texture[5];
RgbImage imag;
//---------------------------------------------------- AMBIENTE - fixa
GLint   Dia = 1;     //:::   'D'
GLfloat intensidadeDia = 0.7;
GLfloat luzGlobalCorAmb[4] = { intensidadeDia, intensidadeDia,intensidadeDia, 1.0 };   //

//---------------------------------------------------- TETO
GLint   ligaTeto = 1;         //:::   'T'
GLfloat intensidadeT = 0.8;  //:::   'I'
GLint   luzR = 1;              //:::   'R'
GLint   luzG = 1;             //:::   'G'
GLint   luzB = 1;             //:::   'B'
GLfloat localPos[4] = { 0, 0.0, 0, 1.0 };   // no teto e é uma luz pontual pois tem w 1.0 se fosse direcional era 0
GLfloat localCorAmb[4] = {(GLfloat) luzR*intensidadeT,(GLfloat)luzG*intensidadeT,(GLfloat)luzB*intensidadeT, 1.0 };
GLfloat localCorDif[4] = {(GLfloat) luzR*intensidadeT,(GLfloat)luzG*intensidadeT,(GLfloat)luzB*intensidadeT, 1.0 };
GLfloat localCorEsp[4] = {(GLfloat) luzR*intensidadeT,(GLfloat)luzG*intensidadeT,(GLfloat)luzB*intensidadeT, 1.0 };


GLint   ligaFoco = 1;
GLfloat focoCutoff = 4.0;
GLfloat focoExponent = 10.0;
GLfloat focoPini[4] = {0, 5, 3, 1.0};
GLfloat focoPfim[4] = {0, 2, 0, 1.0};
GLfloat focoDir[4] = {focoPfim[0] - focoPini[0], focoPfim[1] - focoPini[1], focoPfim[2] - focoPini[2], 0.0};
GLint   focoLuzR = 1;              //:::   'R'
GLint   focoLuzG = 1;             //:::   'G'
GLint   focoLuzB = 1;             //:::   'B'
GLfloat focoCorAmb[4] = {(GLfloat) focoLuzR,(GLfloat)focoLuzG,(GLfloat)focoLuzB, 0.0 };
GLfloat focoCorDif[4] = {(GLfloat) focoLuzR,(GLfloat)focoLuzG,(GLfloat)focoLuzB, 0.0 };
GLfloat focoCorEsp[4] = {(GLfloat) focoLuzR,(GLfloat)focoLuzG,(GLfloat)focoLuzB, 0.0 };

//Transparência
GLint Transp = 0;

GLfloat   quadS = 6.0;

//nr do material
GLint     material = 8;

//Para a esfera
GLUquadric *quad;

//ligar ou desligar a malha
GLint ligaMalha = 1;

//================================================================================
//=========================================================================== INIT

//ÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖ Textura Quadro
void initLights(void) {
    //ÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖ Ambiente
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCorAmb);
    //ÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖ Teto
    glLightfv(GL_LIGHT0, GL_POSITION, localPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, localCorAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, localCorDif);
    glLightfv(GL_LIGHT0, GL_SPECULAR, localCorEsp);
    
//    Foco
    glLightfv(GL_LIGHT1, GL_POSITION, focoPini);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, focoDir);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, focoCutoff);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, focoExponent);
    glLightfv(GL_LIGHT1, GL_AMBIENT, focoCorAmb);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, focoCorDif);
    glLightfv(GL_LIGHT1, GL_SPECULAR, focoCorEsp);
}


GLint  uniOp;
GLint  uniDir = 0;

float  opcao = -45;
GLint uniPosition;
GLfloat uniCount = 0;
float  Direcao[] = { 1, 0, 0 };
GLint flagCount = 0;

GLuint text;
GLint textLoc;


char* VertexShaderSource;
char* FragmentShaderSource;
GLuint  VertexShader, FragmentShader;
GLuint  ShaderProgram;

/*  SHADER */

char* readShaderFile(char* FileName) {

    char* DATA = NULL;
    int   flength = 0;
    FILE* filepoint;

    filepoint = fopen(FileName, "r");
    if (filepoint) {
        fseek(filepoint, 0, SEEK_END);
        flength = ftell(filepoint);
        rewind(filepoint);

        DATA = (char*)malloc(sizeof(char) * (flength + 1));
        flength = fread(DATA, sizeof(char), flength, filepoint);

        DATA[flength] = '\0';
        fclose(filepoint);
        return DATA;
    }
    else {
        printf(" --------  Error while reading  %s ", FileName);
        return DATA;
    }
}

//============================================= 2. Criar, compilar, linkar, e usar
void BuiltShader(void) {

    // GLEW_ARB_vertex_shader;
    // GLEW_ARB_fragment_shader;

    //......................................................... Criar
    VertexShader = glCreateShader(GL_VERTEX_SHADER);
    FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    VertexShaderSource = readShaderFile(filenameV);
    FragmentShaderSource = readShaderFile(filenameF);

    const char* VS = VertexShaderSource;
    const char* FS = FragmentShaderSource;
    glShaderSource(VertexShader, 1, &VS, NULL);
    glShaderSource(FragmentShader, 1, &FS, NULL);
    free(VertexShaderSource);
    free(FragmentShaderSource);

    //......................................................... Compilar
    glCompileShaderARB(VertexShader);
    glCompileShaderARB(FragmentShader);

    //......................................................... Criar e Linkar
    ShaderProgram = glCreateProgramObjectARB();
    glAttachShader(ShaderProgram, VertexShader);
    glAttachShader(ShaderProgram, FragmentShader);
    glLinkProgram(ShaderProgram);

    //......................................................... Usar
    glUseProgramObjectARB(ShaderProgram);
}


void InitShader(void) {
    //------------------------ Criar+linkar
    BuiltShader();
    uniPosition = glGetUniformLocation(ShaderProgram, "PositionNumber");
    glUniform1f (uniPosition, uniCount);
   
    glUniform1f(uniOp, opcao);
    glUniform3fv(uniDir, 1, Direcao);
    
    Direcao[0] = cos((3.14*opcao/180.0));
    Direcao[2] = sin((3.14 * opcao / 180.0));
    
    uniDir = glGetUniformLocation(ShaderProgram, "Direcao");
    glUniform3fv(uniDir, 1, Direcao);
    uniOp = glGetUniformLocation(ShaderProgram, "opcao");
    glUniform1f (uniOp, opcao);
    
    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, texture[1]);
    
    //glActiveTexture(GL_TEXTURE0);
    //textLoc = glGetUniformLocation(ShaderProgram, "text");
    //glUniform1i(textLoc, 0);
   
}


//============================================= 3.Libertar os Shaders
void DeInitShader(void) {
    
    glDetachShader(ShaderProgram, VertexShader);
    glDetachShader(ShaderProgram, FragmentShader);
    glDeleteShader(ShaderProgram);
    glUseProgram(0);
}










void initTexturas()
{
    //----------------------------------------- Tampo da mesa
    glGenTextures(1, &texture[0]);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    imag.LoadBmpFile("blackwood.bmp");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
        (GLfloat)imag.GetNumCols(),
        (GLfloat)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
        imag.ImageData());
    
    //----------------------------------------- Chao
    glGenTextures(1, &texture[1]);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    imag.LoadBmpFile("pedra.bmp");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
        (GLfloat)imag.GetNumCols(),
        (GLfloat)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
        imag.ImageData());
    
    //----------------------------------------- Parede
       glGenTextures(1, &texture[2]);
       glBindTexture(GL_TEXTURE_2D, texture[2]);
       imag.LoadBmpFile("mordenGreyWall.bmp");
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
       glTexImage2D(GL_TEXTURE_2D, 0, 3,
           (GLfloat)imag.GetNumCols(),
           (GLfloat)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
           imag.ImageData());
    
    //----------------------------------------- Parede
          glGenTextures(1, &texture[3]);
          glBindTexture(GL_TEXTURE_2D, texture[3]);
          imag.LoadBmpFile("post.bmp");
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
          glTexImage2D(GL_TEXTURE_2D, 0, 3,
              (GLfloat)imag.GetNumCols(),
              (GLfloat)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
              imag.ImageData());
    
    //----------------------------------------- Parede
            glGenTextures(1, &texture[4]);
            glBindTexture(GL_TEXTURE_2D, texture[4]);
            imag.LoadBmpFile("blueWall.bmp");
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexImage2D(GL_TEXTURE_2D, 0, 3,
                (GLfloat)imag.GetNumCols(),
                (GLfloat)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                imag.ImageData());
}



void inicializa(void)
{
    glClearColor(WHITE);        //ÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖApagar
    glShadeModel(GL_SMOOTH);    //ÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖInterpolacao de cores
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);    //ÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖProfundidade
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    initLights();
    initMaterials(3);
    initTexturas();
    
    glVertexPointer(3, GL_FLOAT, 0, vertices); //ÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖVertexArrays: vertices + normais + cores
    glEnableClientState(GL_VERTEX_ARRAY);
    glNormalPointer(GL_FLOAT, 0, normais);
    glEnableClientState(GL_NORMAL_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, cor);
    glEnableClientState(GL_COLOR_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, 0, arrayTexture);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
}


GLvoid resize(GLsizei width, GLsizei height)
{
    wScreen = width;
    hScreen = height;
    glViewport(0, 0, wScreen*2, hScreen*2);
    glutPostRedisplay();
}

void drawMalha(){
    
    GLfloat num = 150;
    GLfloat addToY = vertices[esquerda[1]*3+1] - vertices[esquerda[3]*3+1];
    addToY /= num;
    GLfloat addToZ = vertices[esquerda[1]*3+2] - vertices[esquerda[3]*3+2];
    addToZ /= num;
    
    GLfloat addToTex = 1/num;
    
    GLfloat firstTexVertX = 0;
    GLfloat secndTexVertX = addToTex;
    GLfloat firstTexVertY = 0;
    GLfloat secndTexVertY = addToTex;
    
    GLfloat arrayY[4];
    GLfloat arrayZ[4];
    
    arrayY[0] = vertices[esquerda[3]*3+1];
    arrayY[1] = vertices[esquerda[3]*3+1] + addToY;
    arrayY[2] = vertices[esquerda[3]*3+1] + addToY;
    arrayY[3] = vertices[esquerda[3]*3+1];
    
    arrayZ[0] = vertices[esquerda[3]*3+2] + addToZ;
    arrayZ[1] = vertices[esquerda[3]*3+2] + addToZ;
    arrayZ[2] = vertices[esquerda[3]*3+2];
    arrayZ[3] = vertices[esquerda[3]*3+2];
    
    
    
    glBegin(GL_QUADS);
    for(float i = 0.0; i < num; i++){
        for(float j = 0.0; j < num; j++){
                glTexCoord2f(firstTexVertX, firstTexVertY); glVertex3f(vertices[esquerda[0]*3], arrayY[0], arrayZ[0]);
                glTexCoord2f(secndTexVertX, firstTexVertY); glVertex3f(vertices[esquerda[1]*3], arrayY[1], arrayZ[1]);
                glTexCoord2f(secndTexVertX, secndTexVertY); glVertex3f(vertices[esquerda[2]*3], arrayY[2], arrayZ[2]);
                glTexCoord2f(firstTexVertX, secndTexVertY); glVertex3f(vertices[esquerda[3]*3], arrayY[3], arrayZ[3]);
                
            arrayZ[0] += addToZ; arrayZ[1] += addToZ; arrayZ[2] += addToZ; arrayZ[3] += addToZ;
            firstTexVertY += addToTex; secndTexVertY += addToTex;
            
        }
        arrayY[0] += addToY; arrayY[1] += addToY; arrayY[2] += addToY; arrayY[3] += addToY;
        arrayZ[0] = vertices[esquerda[3]*3+2] + addToZ; arrayZ[1] = vertices[esquerda[3]*3+2] + addToZ;
        arrayZ[2] = vertices[esquerda[3]*3+2]; arrayZ[3] = vertices[esquerda[3]*3+2];
        firstTexVertY = 0; secndTexVertY = addToTex;
        firstTexVertX += addToTex; secndTexVertX += addToTex;
    }
    glEnd();
    
}

void drawChao() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glPushMatrix();
        glTranslatef(0, 0, 1);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f);    glVertex3i(-xC, 0, -xC-3);
            glTexCoord2f(1.0f, 0.0f);    glVertex3i(-xC, 0, xC+3);
            glTexCoord2f(1.0f, 1.0f);    glVertex3i(xC, 0, xC+3);
            glTexCoord2f(0.0f, 1.0f);    glVertex3i(xC, 0, -xC-3);
        glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void drawParede() {
    initMaterials(3);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glPushMatrix();
        glTranslatef(-5, 5, 1);
        glRotatef(-180, 1.0, 0.0, 0.0);
        glRotatef(-90, 0.0, 0.0, 1.0);
    
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f);    glVertex3i(-xC, 0, -xC-3);
            glTexCoord2f(1.0f, 0.0f);    glVertex3i(-xC, 0, xC+3);
            glTexCoord2f(1.0f, 1.0f);    glVertex3i(xC, 0, xC+3);
            glTexCoord2f(0.0f, 1.0f);    glVertex3i(xC, 0, -xC-3);
        glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void drawParedeMaterial() {
    if(Transp)
        glEnable(GL_BLEND);
    
    
    
    glPushMatrix();
        glTranslatef(-3, 5, 1);
        initMaterials(18);
        glRotatef(-180, 1.0, 0.0, 0.0);
        glRotatef(-90, 0.0, 0.0, 1.0);
    
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f);    glVertex3i(-xC, 0, -xC-3);
            glTexCoord2f(1.0f, 0.0f);    glVertex3i(-xC, 0, xC+3);
            glTexCoord2f(1.0f, 1.0f);    glVertex3i(xC, 0, xC+3);
            glTexCoord2f(0.0f, 1.0f);    glVertex3i(xC, 0, -xC-3);
        glEnd();
    glPopMatrix();
    if(Transp)
        glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}

void drawParedeEste() {
    initMaterials(3);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glPushMatrix();
        glTranslatef(-5, 5, 10);
        glRotatef(90, 0.0, 1.0, 0.0);
        glRotatef(-180, 1.0, 0.0, 0.0);
        glRotatef(-90, 0.0, 0.0, 1.0);
    
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f);    glVertex3i(-xC, 0, -xC-3);
            glTexCoord2f(2.0f, 0.0f);    glVertex3i(-xC, 0, xC+3);
            glTexCoord2f(2.0f, 2.0f);    glVertex3i(xC, 0, xC+3);
            glTexCoord2f(0.0f, 2.0f);    glVertex3i(xC, 0, -xC-3);
        glEnd();
    glPopMatrix();
    
    glDisable(GL_TEXTURE_2D);
}

void drawParedeOeste() {
    initMaterials(3);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    glPushMatrix();
    glTranslatef(-5, 5, -10);
        glRotatef(-90, 0.0, 1.0, 0.0);
        glRotatef(-180, 1.0, 0.0, 0.0);
        glRotatef(-90, 0.0, 0.0, 1.0);
    
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f);    glVertex3i(-xC, 0, -xC-3);
            glTexCoord2f(4.0f, 0.0f);    glVertex3i(-xC, 0, xC+3);
            glTexCoord2f(4.0f, 4.0f);    glVertex3i(xC, 0, xC+3);
            glTexCoord2f(0.0f, 4.0f);    glVertex3i(xC, 0, -xC-3);
        glEnd();
    
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void drawRectangle(int rectangulo, int malha) {
   
    if(rectangulo == 1){
        
        glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima);   // desenhar uma das faces da mesa
        if(malha && ligaMalha){
            drawMalha();
        }else{
            glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda);
        }
        glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita);
        glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente);
        glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, back);
        glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo);
    }else{
        glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerdaGaveta);
        glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita);
        glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frenteGaveta);
        glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, backGaveta);
        glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixoGaveta);
    }
        
    
    
}


void drawScene() {

    //=================================================== Qual o lado visivel ???
    if (frenteVisivel == 0){
        glDisable(GL_CULL_FACE);
//        glEnable(GL_CULL_FACE);
//        glCullFace(GL_BACK);  //.. o de tras È eliminado
    }
    else if(frenteVisivel == 1)
        glCullFace(GL_FRONT);  //.. o de frente È eliminado
    else
        glDisable(GL_CULL_FACE);
    
    
    glPushMatrix();
        initMaterials(material);
        glTranslatef(xPosition, yPosition, zPosition);
        glScalef(2, 2, 2);
        drawRectangle(1, 0);
        glPushMatrix();
            glTranslatef(2, 0, 0);
            drawRectangle(1, 0);
            glTranslatef(0, 0, 3);
            drawRectangle(1, 0);
        glPopMatrix();
        glTranslatef(0, 0, 3);
        drawRectangle(1, 0);
    glPopMatrix();
    glPushMatrix();
    
        initMaterials(3);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture[0]);
        glTranslatef(0, 4.01, 0);
        glRotatef(-90, 0.0, 0.0, 1.0);
        glScalef(1, 2.13, 50);
        drawRectangle(1, 1);
    
    
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0,3.875,0);
        glRotatef(angleEsqTampo, 1.0, 0.0, 0.0);
        glScalef(34 , 1, 1);
        drawRectangle(1, 0);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0,3.875,6.255);
        glRotatef(-angleDirTampo, 1.0, 0.0, 0.0);
        glTranslatef(0, 0, -0.125);
        glScalef(34 , 1, 1);
        drawRectangle(1, 0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(2 + translateGaveta,3.3,2.35);
    glScalef(18 , 0.3, 13);
        drawRectangle(0, 0);
    
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
        InitShader();
        //initMaterials(12);
        glTranslatef(1.5,2,-8);
        quad = gluNewQuadric();
        gluSphere(quad,2,100,20);
    DeInitShader();
    glLinkProgram(NULL);
    glPopMatrix();
    
    initMaterials(3);
    
}

//======================================================================== ILUMINCCAO
void iluminacao() {
    if (ligaTeto)  glEnable(GL_LIGHT0);
    else             glDisable(GL_LIGHT0);
}

void iluminacaoFoco() {
    if (ligaFoco)  glEnable(GL_LIGHT1);
    else             glDisable(GL_LIGHT1);
}

void display(void) {
        
    //================================================================= N„o modificar !!!!!!!!!!!!
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, hScreen / 4, wScreen / 6, hScreen / 5);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-xC, xC, -xC, xC, -zC, zC);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 5, 0, 0, 0, 0, 0, 0, -1);

    //ÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖÖObjectos
    drawChao();
    drawParede();
    drawParedeEste();
    drawParedeOeste();
    drawScene();
    //================================================================= Viewport2
    glViewport(wScreen / 5, 0, (GLint) wScreen*2, (GLint) hScreen*2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(angPersp, (float)wScreen / hScreen, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(obsPini[0], obsPini[1], obsPini[2], obsPfin[0], obsPfin[1], obsPfin[2], 0, 1, 0);
    //--------------------- desenha objectos
    iluminacao();
    iluminacaoFoco();
    drawChao();
    drawParede();
    drawParedeEste();
    drawParedeOeste();
    drawScene();
    drawParedeMaterial();
    
    
    
    //. . . . . . . . . . . . . . . . . . . . .  Actualizacao
    glutSwapBuffers();
}

void updateVisao() {
    obsPfin[0] = obsPini[0] + rVisao * cos(aVisao);
    obsPfin[2] = obsPini[2] - rVisao * sin(aVisao);
    glutPostRedisplay();
}

void updateLuz() {
    localCorAmb[0] = luzR * intensidadeT;
    localCorAmb[1] = luzG * intensidadeT;
    localCorAmb[2] = luzB * intensidadeT;
    localCorDif[0] = luzR * intensidadeT;
    localCorDif[1] = luzG * intensidadeT;
    localCorDif[2] = luzB * intensidadeT;
    localCorEsp[0] = luzR * intensidadeT;
    localCorEsp[1] = luzG * intensidadeT;
    localCorEsp[2] = luzB * intensidadeT;;
    glLightfv(GL_LIGHT0, GL_AMBIENT, localCorAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, localCorDif);
    glLightfv(GL_LIGHT0, GL_SPECULAR, localCorEsp);
}

//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y) {


    switch (key) {
    case 't':
    case 'T':
            if(angleEsqTampo < 270)
                angleEsqTampo = angleEsqTampo + 5;
        glutPostRedisplay();
        break;
            
    case 'y':
    case 'Y':
            if(angleEsqTampo > 90)
                angleEsqTampo = angleEsqTampo - 5;
        glutPostRedisplay();
        break;
            
    case 'g':
    case 'G':
            if(angleDirTampo < 270)
                angleDirTampo = angleDirTampo + 5;
        glutPostRedisplay();
        break;
            
    case 'h':
    case 'H':
            if(angleDirTampo > 90)
                angleDirTampo = angleDirTampo - 5;
        glutPostRedisplay();
        break;
    case 'r':
    case 'R':
            if(angleEsqTampo < 270)
                angleEsqTampo = angleEsqTampo + 5;
            if(angleDirTampo < 270)
                angleDirTampo = angleDirTampo + 5;
        glutPostRedisplay();
        break;
    case 'f':
    case 'F':
            if(angleEsqTampo > 90)
                angleEsqTampo = angleEsqTampo - 5;
            if(angleDirTampo > 90)
                angleDirTampo = angleDirTampo - 5;
        glutPostRedisplay();
        break;
            
    case 'm':
    case 'M':
            if(translateGaveta < 1)
                translateGaveta  = translateGaveta + 0.1;
        glutPostRedisplay();
           break;
            
    case 'n':
    case 'N':
            if(translateGaveta > 0)
                translateGaveta  = translateGaveta - 0.1;
        glutPostRedisplay();
           break;
            
    case 'd':
    case 'D':
            Dia = !Dia;
            if (Dia) { luzGlobalCorAmb[0] = 0.7;   luzGlobalCorAmb[1] = 0.7;   luzGlobalCorAmb[2] = 0.7;}
            else     { luzGlobalCorAmb[0] = 0.2;   luzGlobalCorAmb[1] = 0.2;   luzGlobalCorAmb[2] = 0.2;}
            glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCorAmb);
            glutPostRedisplay();
            break;
    
        //--------------------------- TETO
        case 'c':
        case 'C':
            ligaTeto = !ligaTeto;
            updateLuz();
            glutPostRedisplay();
            break;
        case 'z':
        case 'Z':
            ligaFoco = !ligaFoco;
            updateLuz();
            glutPostRedisplay();
            break;
            //--------------------------- Iluminacaoda sala
        case 'i':
        case 'I':
            intensidadeT = intensidadeT + 0.1;
            if (intensidadeT > 1.1) intensidadeT = 0;
            updateLuz();
            glutPostRedisplay();
            break;
        case 'v':
        case 'V':
            luzR = (luzR + 1) % 2;
            updateLuz();
            glutPostRedisplay();
            break;
        case 'a':
        case 'A':
            luzG = (luzG + 1) % 2;
            updateLuz();
            glutPostRedisplay();
            break;
        case 'q':
        case 'Q':
            luzB = (luzB + 1) % 2;
            updateLuz();
            glutPostRedisplay();
            break;
        case 'p':
        case 'P':
            Transp = !Transp;
            glutPostRedisplay();
            break;
            
        case 'w':
        case 'W':
            initMaterials(19);
            glutPostRedisplay();
            break;
        case 'e':
        case 'E':
            initMaterials(20);
            glutPostRedisplay();
            break;
        case 'l':
        case 'L':
            material = (material + 1) % 18;
            initMaterials(material);
            glutPostRedisplay();
            break;
        case 'x':
        case 'X':
            ligaMalha = !ligaMalha;
            glutPostRedisplay();
            break;
        case 'o':
        case 'O':
            if (uniCount > 10){
                flagCount = 1;
            }else if (uniCount < 0){
                flagCount = 0;
            }
            
            if(flagCount == 0){
                if(uniCount < 2){
                    uniCount = uniCount + 1;
                }else if(uniCount < 4){
                    uniCount = uniCount + 0.7;
                }else if(uniCount < 9){
                    uniCount = uniCount + 0.5;
                }else
                    uniCount = uniCount + 0.2;
            }else{
                if(uniCount > 9){
                    uniCount = uniCount - 0.25;
                }else if(uniCount > 4){
                    uniCount = uniCount - 0.5;
                }else
                    uniCount = uniCount - 1;
            }
            
            glutPostRedisplay();
            break;
        case 'b':
        case 'B':
            opcao = opcao+10;
            glutPostRedisplay();
            break;
        
        //--------------------------- Escape
    case 27:
        exit(0);
        break;
    }

}


void teclasNotAscii(int key, int x, int y) {
    //.. observador pode andar ‡ volda da cena  (setas esquerda / direita)
    //.. observador pode andar para cima e para baixo (setas cima / baixo )

   if (key == GLUT_KEY_UP) {
            obsPini[0] = obsPini[0] + incVisao * cos(aVisao);
            obsPini[2] = obsPini[2] - incVisao * sin(aVisao);
        }
        if (key == GLUT_KEY_DOWN) {
            obsPini[0] = obsPini[0] - incVisao * cos(aVisao);
            obsPini[2] = obsPini[2] + incVisao * sin(aVisao);
        }
        if (key == GLUT_KEY_LEFT)
            aVisao = (aVisao + 0.1);
        if (key == GLUT_KEY_RIGHT)
            aVisao = (aVisao - 0.1);
    
        obsPfin[0] = obsPini[0] + rVisao * cos(aVisao);
        obsPfin[2] = obsPini[2] - rVisao * sin(aVisao);
    glutPostRedisplay();
}


//======================================================= MAIN
//======================================================= MAIN
int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(wScreen, hScreen);
    glutInitWindowPosition(400, 100);
    glutCreateWindow("Teclas com funções -> 'r'   'f'   'g'   't'   'h'   'y'   'm'   'n'   'SETAS' mais info nas primeiras linhas do codigo ");

    inicializa();
    
    //------------------------------------  GLEW
    GLenum err = glewInit();
    //InitShader();
    //DeInitShader();
        
    
    glutSpecialFunc(teclasNotAscii);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}



