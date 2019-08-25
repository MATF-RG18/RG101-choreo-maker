#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#define NUM_OF_LINES 30


char buffer[20]; /*String u kom se cuva procitana linija*/
int size=30;
int read; /*Indikator da se citaju linije iz faljla*/
static float cam_x, cam_y, cam_z; /*Koordinate kamere*/
FILE* fptr; 

static int timer_active,id,i,j,line,go; 
static int nextLine1,nextLine2,nextLine3,nextLine4,nextLine5,nextLine6,nextLine7,nextLine8;
static float x1_f,z1_f,x1_t,z1_t, /* Promenljive u kojima se cuvaju tacke od kojih treba da krene lopta i  do kojih  treba da dodje*/
             x2_f,z2_f,x2_t,z2_t,
             x3_f,z3_f,x3_t,z3_t,
             x4_f,z4_f,x4_t,z4_t,
             x5_f,z5_f,x5_t,z5_t,
             x6_f,z6_f,x6_t,z6_t,
             x7_f,z7_f,x7_t,z7_t,
             x8_f,z8_f,x8_t,z8_t; 
static float a1,b1,a2,b2,a3,b3,a4,b4,a5,b5,a6,b6,a7,b7,a8,b8; /*Promenljive za vektore*/
static float lines1[NUM_OF_LINES][2],lines2[NUM_OF_LINES][2],lines3[NUM_OF_LINES][2],lines4[NUM_OF_LINES][2], /*Matrice u kojima se cuvaju koordinate plesaca*/
             lines5[NUM_OF_LINES][2],lines6[NUM_OF_LINES][2],lines7[NUM_OF_LINES][2],lines8[NUM_OF_LINES][2];


static void onDisplay(void);
static void onTimer1(int value); /* Funkcije za pomeranje za svakog plesaca*/
static void onTimer2(int value);
static void onTimer3(int value);
static void onTimer4(int value);
static void onTimer5(int value);
static void onTimer6(int value);
static void onTimer7(int value);
static void onTimer8(int value);
static void onKeyboard(unsigned char key, int x, int y);
static void horizontalLines(); /*Funkcija koja crta horizontalne linije*/
static void verticalLines(); /*Funkcijakoja crta vertikalne linije*/    
static void xNumbers(); /* Funkcija koja ispisuje brojeve na x-osi*/
static void zNumbers(); /*Funkcija koja ispisuje brojeve na z-osi*/
static void podium(); /*Funkcija koja crta podijum*/
static void initialize(); /*Funkcija za inicijalizaciju*/







int main(int argc, char** argv)
{
    
   /*Inicijalizuje se GLUT*/
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glEnable(GL_DEPTH_TEST);
    
   /*Kreira se prozor*/
   
    glutInitWindowSize(1500, 900);
    glutInitWindowPosition(250,90);
    glutCreateWindow("ChoreoMaker");
    
    
    glutDisplayFunc(onDisplay);
    glutKeyboardFunc(onKeyboard);
    
    
    /*OpenGL inicijalizacija*/
    glClearColor(0, 0, 0.125, 0);

   /*Ukljucuje se svetlo*/ 
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    /*Proveravamo da li korisnik zeli da cita linije iz fajla*/
    if(argc!=1)
        if(argv[1][1]=='r')
            read=1;
    
    /*Inicijalizacija*/
    initialize();
    
    /*Onemoguceno je kretanje na pocetku*/
    timer_active=0;
    
    /*Program ulazi u glavnu petlju*/
    glutMainLoop();
   
   
   return 0;
}

static void onDisplay(void)
{
    /*Brise se prethodni sadrzaj prozora*/
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(0, 0, 1500, 900);

    /* Podesava se projekcija. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(
            7,
            1500/(float)900,
            1, 25);

    /* Podesava se tacka pogleda. */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
            cam_x, cam_y, cam_z,
            0, 0, 0,
            0, 1, 0
        );
    
    
    /*Iscrtavanje podijuma*/
    glPushMatrix();
    glDisable(GL_LIGHTING);
    podium();
    glEnable(GL_LIGHTING);
    glPopMatrix();
   
    
    /*Postavljanje svetla za lopte (plesace)*/
    GLfloat sphere_specular[] = { 0.2,0.2,0.2, 0 };
    GLfloat sphere_diffuse[] = { 0.5,1,1,1 }; 
    GLfloat sphere_ambient[] = { 0.3,0.1,0.15, 0 }; 
    GLfloat shininess[] = { 10 }; 
    GLfloat light_pos[] = { 1, 2, 0, 1};
    
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glMaterialfv(GL_FRONT, GL_AMBIENT, sphere_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, sphere_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, sphere_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, shininess);
    
    /*Iscrtavanje lopti i njihovih brojeva*/
    /*1*/
    glPushMatrix();
    glTranslatef(x1_f,0,z1_f);
    glColor3f(0.3,0.1,0.2);
    glutSolidSphere(0.025,100,100);
    glColor3f(0, 0, 0.125); 
    glRasterPos3f(-0.005,-0.005,0);
    char*c1="1";
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c1);
    glPopMatrix();
    
    /*2*/
    glPushMatrix();
    glTranslatef(x2_f,0,z2_f);
    glColor3f(0.3,0.1,0.2);
    glutSolidSphere(0.025,100,100);
    glColor3f(0, 0, 0.125); 
    glRasterPos3f(-0.005,-0.005,0);
    char*c2="2";
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c2);
    glPopMatrix();


    /*3*/
    glPushMatrix();
    glTranslatef(x3_f,0,z3_f);
    glColor3f(0.3,0.1,0.2);
    glutSolidSphere(0.025,100,100);
    glColor3f(0, 0, 0.125); 
    glRasterPos3f(-0.005,-0.005,0);
    char*c3="3";
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c3);
    glPopMatrix();
    
    /*4*/
    glPushMatrix();
    glTranslatef(x4_f,0,z4_f);
    glColor3f(0.3,0.1,0.2);
    glutSolidSphere(0.025,100,100);
    glColor3f(0, 0, 0.125); 
    glRasterPos3f(-0.005,-0.005,0);
    char*c4="4";
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c4);
    glPopMatrix();
    
    
    /*5*/
    glPushMatrix();
    glTranslatef(x5_f,0,z5_f);
    glColor3f(0.3,0.1,0.2);
    glutSolidSphere(0.025,100,100);
    glColor3f(0, 0, 0.125); 
    glRasterPos3f(-0.005,-0.005,0);
    char*c5="5";
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c5);
    glPopMatrix();
    
    
    /*6*/
    glPushMatrix();
    glTranslatef(x6_f,0,z6_f);
    glColor3f(0.3,0.1,0.2);
    glutSolidSphere(0.025,100,100);
    glColor3f(0, 0, 0.125); 
    glRasterPos3f(-0.005,-0.005,0);
    char*c6="6";
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c6);
    glPopMatrix();
    
    
    /*7*/
    glPushMatrix();
    glTranslatef(x7_f,0,z7_f);
    glColor3f(0.3,0.1,0.2);
    glutSolidSphere(0.025,100,100);
    glColor3f(0, 0, 0.125); 
    glRasterPos3f(-0.005,-0.005,0);
    char*c7="7";
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c7);
    glPopMatrix();
    
    
    /*8*/
    glPushMatrix();
    glTranslatef(x8_f,0,z8_f);
    glColor3f(0.3,0.1,0.2);
    glutSolidSphere(0.025,100,100);
    glColor3f(0, 0, 0.125); 
    glRasterPos3f(-0.005,-0.005,0);
    char*c8="8";
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c8);
    glPopMatrix();
    
    
    
    /*Salje se nova slika na ekran*/
    glutSwapBuffers();
}


/*Kretanje prve lopte (plesaca)*/
static void onTimer1(int value) 
{
    /*Provera da li je pokrenuta dobra funkcija*/
    if(value!=1)
        return;
   
    /*Uvecavanje koordinata plesaca*/
    x1_f+=a1;
    z1_f+=b1;
    
    /*Provere da li je dosao do tacke do koje treba da dodje*/
    if(a1>0)
    {
        if(x1_f >= x1_t)
        {
            /*Provera da li je dosao do poslednje tacke, ako jeste prekida se kretanje */
            if(lines1[nextLine1][0]==-1 && lines1[nextLine1][1]==-1)
            {
                timer_active=0;
                /*Obezbedjujemo da kada se opet pokrene simulacija, ona krene od pocetka*/
                go=0;
            }
            
            /*Pocetna tacka dobija vrednost trenutne tacke, trenutnih koordinata*//*Sledaca na koju treba da stigne se uzima iz matrice u kojoj se cuvaju koordinate plesaca*/
            x1_f=x1_t;
            z1_f=z1_t;
            
            /*Sledaca na koju treba da stigne se uzima iz matrice u kojoj se cuvaju koordinate plesaca*/
            x1_t=lines1[nextLine1][0];
            z1_t=lines1[nextLine1][1];
            
            /*Izracunava se vrednost vektora */
            a1=(x1_t-x1_f)/100;
            b1=(z1_t-z1_f)/100;
            
            /*Prelazi se na sledecu vrstu u matrici koja cuva koordinate*/
            nextLine1++;
        }
    }
    /*Postupak je isti samo se drugacije proverava da li je igac dosao do zeljene tacke*/
    else if(a1<0)
    {
        if(x1_f <= x1_t)
        {
            if(lines1[nextLine1][0]==-1 && lines1[nextLine1][1]==-1)
            {
                timer_active=0;
                go=0;
            }
            
            x1_f=x1_t;
            z1_f=z1_t;
            
            x1_t=lines1[nextLine1][0];
            z1_t=lines1[nextLine1][1];
            
            a1=(x1_t-x1_f)/100;
            b1=(z1_t-z1_f)/100;
            
            nextLine1++;
        }
    }
    else if(a1==0 && b1==0)
    {
            if(lines1[nextLine1][0]==-1 && lines1[nextLine1][1]==-1)
            {
                timer_active=0;
                go=0;
                
                
            }
        
            x1_f=x1_t;
            z1_f=z1_t;
            
            x1_t=lines1[nextLine1][0];
            z1_t=lines1[nextLine1][1];
            
            a1=(x1_t-x1_f)/100;
            b1=(z1_t-z1_f)/100;
            
            nextLine1++;
    }
    else if(a1==0 && b1>0)
    {
        if(z1_f >= z1_t)
        {
            if(lines1[nextLine1][0]==-1 && lines1[nextLine1][1]==-1)
            {
                timer_active=0;
                go=0;
            }
            
            x1_f=x1_t;
            z1_f=z1_t;
            
            x1_t=lines1[nextLine1][0];
            z1_t=lines1[nextLine1][1];
            
            a1=(x1_t-x1_f)/100;
            b1=(z1_t-z1_f)/100;
            
            nextLine1++;
        }
    }
    else if(a1==0 && b1<0)
    {
        if(z1_f <= z1_t)
        {
            if(lines1[nextLine1][0]==-1 && lines1[nextLine1][1]==-1)
            {
                timer_active=0;
                go=0;
            }
            
            x1_f=x1_t;
            z1_f=z1_t;
            
            x1_t=lines1[nextLine1][0];
            z1_t=lines1[nextLine1][1];
            
            a1=(x1_t-x1_f)/100;
            b1=(z1_t-z1_f)/100;
            
            nextLine1++;
        }
    }
    
    /*Salje se slika na ekran*/
    glutPostRedisplay();
     
    if(timer_active)
        glutTimerFunc(50,onTimer1,1);
}

/*Sce onTimer funkcije isto funkcionisu, samo su u pitanju drugi plesaci*/
static void onTimer2(int value)
{
    if(value!=2)
        return;
    
    
    x2_f+=a2;
    z2_f+=b2;
    
    
    
    if(a2>0)
    {
        if(x2_f >= x2_t)
        {
            if(lines2[nextLine2][0]==-1 && lines2[nextLine2][1]==-1)
                timer_active=0;
            
            
            x2_f=x2_t;
            z2_f=z2_t;
            
            x2_t=lines2[nextLine2][0];
            z2_t=lines2[nextLine2][1];
            
            a2=(x2_t-x2_f)/100;
            b2=(z2_t-z2_f)/100;
            
            nextLine2++;
        }
    }
    else if(a2<0)
    {
        if(x2_f <= x2_t)
        {
            if(lines2[nextLine2][0]==-1 && lines2[nextLine2][1]==-1)
                timer_active=0;
             
            
            x2_f=x2_t;
            z2_f=z2_t;
            
            x2_t=lines2[nextLine2][0];
            z2_t=lines2[nextLine2][1];
            
            a2=(x2_t-x2_f)/100;
            b2=(z2_t-z2_f)/100;
            
            nextLine2++;
        }
    }
    else if(a2==0 && b2==0)
    {
            if(lines2[nextLine2][0]==-1 && lines2[nextLine2][1]==-1)
                timer_active=0;
            
        
            x2_f=x2_t;
            z2_f=z2_t;
            
            x2_t=lines2[nextLine2][0];
            z2_t=lines2[nextLine2][1];
            
            a2=(x2_t-x2_f)/100;
            b2=(z2_t-z2_f)/100;
            
            nextLine2++;
    }
    else if(a2==0 && b2>0)
    {
        if(z2_f >= z2_t)
        {
            if(lines2[nextLine2][0]==-1 && lines2[nextLine2][1]==-1)
                timer_active=0;
             
            
            x2_f=x2_t;
            z2_f=z2_t;
            
            x2_t=lines2[nextLine2][0];
            z2_t=lines2[nextLine2][1];
            
            a2=(x2_t-x2_f)/100;
            b2=(z2_t-z2_f)/100;
            
            nextLine2++;
        }
    }
    else if(a2==0 && b2<0)
    {
        if(z2_f <= z2_t)
        {
            if(lines2[nextLine2][0]==-1 && lines2[nextLine2][1]==-1)
                timer_active=0;
            
            x2_f=x2_t;
            z2_f=z2_t;
            
            x2_t=lines2[nextLine2][0];
            z2_t=lines2[nextLine2][1];
            
            a2=(x2_t-x2_f)/100;
            b2=(z2_t-z2_f)/100;
            
            nextLine2++;
        }
    }
    
    
   
    glutPostRedisplay();
     
    if(timer_active)
        glutTimerFunc(50,onTimer2,2);
}

static void onTimer3(int value)
{
    if(value!=3)
        return;
   
    x3_f+=a3;
    z3_f+=b3;
    
    
    
    if(a3>0)
    {
        if(x3_f >= x3_t)
        {
            if(lines3[nextLine3][0]==-1 && lines3[nextLine3][1]==-1)
                timer_active=0;
            
            
            x3_f=x3_t;
            z3_f=z3_t;
            
            x3_t=lines3[nextLine3][0];
            z3_t=lines3[nextLine3][1];
            
            a3=(x3_t-x3_f)/100;
            b3=(z3_t-z3_f)/100;
            
            nextLine3++;
        }
    }
    else if(a3<0)
    {
        if(x3_f <= x3_t)
        {
            if(lines3[nextLine3][0]==-1 && lines3[nextLine3][1]==-1)
                timer_active=0;
            
            
            x3_f=x3_t;
            z3_f=z3_t;
            
            x3_t=lines3[nextLine3][0];
            z3_t=lines3[nextLine3][1];
            
            a3=(x3_t-x3_f)/100;
            b3=(z3_t-z3_f)/100;
            
            nextLine3++;
        }
    }
    else if(a3==0 && b3==0)
    {
            if(lines3[nextLine3][0]==-1 && lines3[nextLine3][1]==-1)
                timer_active=0;
            
        
            x3_f=x3_t;
            z3_f=z3_t;
            
            x3_t=lines3[nextLine3][0];
            z3_t=lines3[nextLine3][1];
            
            a3=(x3_t-x3_f)/100;
            b3=(z3_t-z3_f)/100;
            
            nextLine3++;
    }
    else if(a3==0 && b3>0)
    {
        if(z3_f >= z3_t)
        {
            if(lines3[nextLine3][0]==-1 && lines3[nextLine3][1]==-1)
                timer_active=0;
            
            
            x3_f=x3_t;
            z3_f=z3_t;
            
            x3_t=lines3[nextLine3][0];
            z3_t=lines3[nextLine3][1];
            
            a3=(x3_t-x3_f)/100;
            b3=(z3_t-z3_f)/100;
            
            nextLine3++;
        }
    }
    else if(a3==0 && b3<0)
    {
        if(z3_f <= z3_t)
        {
            if(lines3[nextLine3][0]==-1 && lines3[nextLine3][1]==-1)
                timer_active=0;
            
            
            x3_f=x3_t;
            z3_f=z3_t;
            
            x3_t=lines3[nextLine3][0];
            z3_t=lines3[nextLine3][1];
            
            a3=(x3_t-x3_f)/100;
            b3=(z3_t-z3_f)/100;
            
            nextLine3++;
        }
    }
    
    glutPostRedisplay();
     
    if(timer_active)
        glutTimerFunc(50,onTimer3,3);
}

static void onTimer4(int value)
{
    if(value!=4)
        return;
    
    x4_f+=a4;
    z4_f+=b4;
    
    
    
    if(a4>0)
    {
        if(x4_f >= x4_t)
        {
            if(lines4[nextLine4][0]==-1 && lines4[nextLine4][1]==-1)
                timer_active=0;
            
            
            x4_f=x4_t;
            z4_f=z4_t;
            
            x4_t=lines4[nextLine4][0];
            z4_t=lines4[nextLine4][1];
            
            a4=(x4_t-x4_f)/100;
            b4=(z4_t-z4_f)/100;
            
            nextLine4++;
        }
    }
    else if(a4<0)
    {
        if(x4_f <= x4_t)
        {
            if(lines4[nextLine4][0]==-1 && lines4[nextLine4][1]==-1)
                timer_active=0;
            
            
            x4_f=x4_t;
            z4_f=z4_t;
            
            x4_t=lines4[nextLine4][0];
            z4_t=lines4[nextLine4][1];
            
            a4=(x4_t-x4_f)/100;
            b4=(z4_t-z4_f)/100;
            
            nextLine4++;
        }
    }
    else if(a4==0 && b4==0)
    {
            if(lines4[nextLine4][0]==-1 && lines4[nextLine4][1]==-1)
                timer_active=0;
            
        
            x4_f=x4_t;
            z4_f=z4_t;
            
            x4_t=lines4[nextLine4][0];
            z4_t=lines4[nextLine4][1];
            
            a4=(x4_t-x4_f)/100;
            b4=(z4_t-z4_f)/100;
            
            nextLine4++;
    }
    else if(a4==0 && b4>0)
    {
        if(z4_f >= z4_t)
        {
            if(lines4[nextLine4][0]==-1 && lines4[nextLine4][1]==-1)
                timer_active=0;
            
            
            x4_f=x4_t;
            z4_f=z4_t;
            
            x4_t=lines4[nextLine4][0];
            z4_t=lines4[nextLine4][1];
            
            a4=(x4_t-x4_f)/100;
            b4=(z4_t-z4_f)/100;
            
            nextLine4++;
        }
    }
    else if(a4==0 && b4<0)
    {
        if(z4_f <= z4_t)
        {
            if(lines4[nextLine4][0]==-1 && lines4[nextLine4][1]==-1)
                timer_active=0;
            
            
            x4_f=x4_t;
            z4_f=z4_t;
            
            x4_t=lines4[nextLine4][0];
            z4_t=lines4[nextLine4][1];
            
            a4=(x4_t-x4_f)/100;
            b4=(z4_t-z4_f)/100;
            
            nextLine4++;
        }
    }
    
   
    glutPostRedisplay();
     
    if(timer_active)
        glutTimerFunc(50,onTimer4,4);
}

static void onTimer5(int value)
{
    if(value!=5)
        return;
   
    x5_f+=a5;
    z5_f+=b5;
    
    
    
    if(a5>0)
    {
        if(x5_f >= x5_t)
        {
            if(lines5[nextLine5][0]==-1 && lines5[nextLine5][1]==-1)
                timer_active=0;
            
            
            x5_f=x5_t;
            z5_f=z5_t;
            
            x5_t=lines5[nextLine5][0];
            z5_t=lines5[nextLine5][1];
            
            a5=(x5_t-x5_f)/100;
            b5=(z5_t-z5_f)/100;
            
            nextLine5++;
        }
    }
    else if(a5<0)
    {
        if(x5_f <= x5_t)
        {
            if(lines5[nextLine5][0]==-1 && lines5[nextLine5][1]==-1)
                timer_active=0;
            
            
            x5_f=x5_t;
            z5_f=z5_t;
            
            x5_t=lines5[nextLine5][0];
            z5_t=lines5[nextLine5][1];
            
            a5=(x5_t-x5_f)/100;
            b5=(z5_t-z5_f)/100;
            
            nextLine5++;
        }
    }
    else if(a5==0 && b5==0)
    {
            if(lines5[nextLine5][0]==-1 && lines5[nextLine5][1]==-1)
                timer_active=0;
            
        
            x5_f=x5_t;
            z5_f=z5_t;
            
            x5_t=lines5[nextLine5][0];
            z5_t=lines5[nextLine5][1];
            
            a5=(x5_t-x5_f)/100;
            b5=(z5_t-z5_f)/100;
            
            nextLine5++;
    }
    else if(a5==0 && b5>0)
    {
        if(z5_f >= z5_t)
        {
            if(lines5[nextLine5][0]==-1 && lines5[nextLine5][1]==-1)
                timer_active=0;
            
            
            x5_f=x5_t;
            z5_f=z5_t;
            
            x5_t=lines5[nextLine5][0];
            z5_t=lines5[nextLine5][1];
            
            a5=(x5_t-x5_f)/100;
            b5=(z5_t-z5_f)/100;
            
            nextLine5++;
        }
    }
    else if(a5==0 && b5<0)
    {
        if(z5_f <= z5_t)
        {
            if(lines5[nextLine5][0]==-1 && lines5[nextLine5][1]==-1)
                timer_active=0;
            
            
            x5_f=x5_t;
            z5_f=z5_t;
            
            x5_t=lines5[nextLine5][0];
            z5_t=lines5[nextLine5][1];
            
            a5=(x5_t-x5_f)/100;
            b5=(z5_t-z5_f)/100;
            
            nextLine5++;
        }
    }
    
    glutPostRedisplay();
     
    if(timer_active)
        glutTimerFunc(50,onTimer5,5);
}

static void onTimer6(int value)
{
    if(value!=6)
        return;
   
    
    x6_f+=a6;
    z6_f+=b6;
    
    
    
    if(a6>0)
    {
        if(x6_f >= x6_t)
        {
            if(lines6[nextLine6][0]==-1 && lines6[nextLine6][1]==-1)
                timer_active=0;
            
            
            x6_f=x6_t;
            z6_f=z6_t;
            
            x6_t=lines6[nextLine6][0];
            z6_t=lines6[nextLine6][1];
            
            a6=(x6_t-x6_f)/100;
            b6=(z6_t-z6_f)/100;
            
            nextLine6++;
        }
    }
    else if(a6<0)
    {
        if(x6_f <= x6_t)
        {
            if(lines6[nextLine6][0]==-1 && lines6[nextLine6][1]==-1)
                timer_active=0;
            
            
            x6_f=x6_t;
            z6_f=z6_t;
            
            x6_t=lines6[nextLine6][0];
            z6_t=lines6[nextLine6][1];
            
            a6=(x6_t-x6_f)/100;
            b6=(z6_t-z6_f)/100;
            
            nextLine6++;
        }
    }
    else if(a6==0 && b6==0)
    {
            if(lines6[nextLine6][0]==-1 && lines6[nextLine6][1]==-1)
                timer_active=0;
            
        
            x6_f=x6_t;
            z6_f=z6_t;
            
            x6_t=lines6[nextLine6][0];
            z6_t=lines6[nextLine6][1];
            
            a6=(x6_t-x6_f)/100;
            b6=(z6_t-z6_f)/100;
            
            nextLine6++;
    }
    else if(a6==0 && b6>0)
    {
        if(z6_f >= z6_t)
        {
            if(lines6[nextLine6][0]==-1 && lines6[nextLine6][1]==-1)
                timer_active=0;
            
            
            x6_f=x6_t;
            z6_f=z6_t;
            
            x6_t=lines6[nextLine6][0];
            z6_t=lines6[nextLine6][1];
            
            a6=(x6_t-x6_f)/100;
            b6=(z6_t-z6_f)/100;
            
            nextLine6++;
        }
    }
    else if(a6==0 && b6<0)
    {
        if(z6_f <= z6_t)
        {
            if(lines6[nextLine6][0]==-1 && lines6[nextLine6][1]==-1)
                timer_active=0;
            
            x6_f=x6_t;
            z6_f=z6_t;
            
            x6_t=lines6[nextLine6][0];
            z6_t=lines6[nextLine6][1];
            
            a6=(x6_t-x6_f)/100;
            b6=(z6_t-z6_f)/100;
            
            nextLine6++;
        }
    } 
    
    
    glutPostRedisplay();
     
    if(timer_active)
        glutTimerFunc(50,onTimer6,6);
}

static void onTimer7(int value)
{
    if(value!=7)
        return;
   
    
    x7_f+=a7;
    z7_f+=b7;
    
    
    
    if(a7>0)
    {
        if(x7_f >= x7_t)
        {
            if(lines7[nextLine7][0]==-1 && lines7[nextLine7][1]==-1)
                timer_active=0;
            
            
            x7_f=x7_t;
            z7_f=z7_t;
            
            x7_t=lines7[nextLine7][0];
            z7_t=lines7[nextLine7][1];
            
            a7=(x7_t-x7_f)/100;
            b7=(z7_t-z7_f)/100;
            
            nextLine7++;
        }
    }
    else if(a7<0)
    {
        if(x7_f <= x7_t)
        {
            if(lines7[nextLine7][0]==-1 && lines7[nextLine7][1]==-1)
                timer_active=0;
            
            x7_f=x7_t;
            z7_f=z7_t;
            
            x7_t=lines7[nextLine7][0];
            z7_t=lines7[nextLine7][1];
            
            a7=(x7_t-x7_f)/100;
            b7=(z7_t-z7_f)/100;
            
            nextLine7++;
        }
    }
    else if(a7==0 && b7==0)
    {
            if(lines7[nextLine7][0]==-1 && lines7[nextLine7][1]==-1)
                timer_active=0;
            
        
            x7_f=x7_t;
            z7_f=z7_t;
            
            x7_t=lines7[nextLine7][0];
            z7_t=lines7[nextLine7][1];
            
            a7=(x7_t-x7_f)/100;
            b7=(z7_t-z7_f)/100;
            
            nextLine7++;
    }
    else if(a7==0 && b7>0)
    {
        if(z7_f >= z7_t)
        {
            if(lines7[nextLine7][0]==-1 && lines7[nextLine7][1]==-1)
                timer_active=0;
            
            
            x7_f=x7_t;
            z7_f=z7_t;
            
            x7_t=lines7[nextLine7][0];
            z7_t=lines7[nextLine7][1];
            
            a7=(x7_t-x7_f)/100;
            b7=(z7_t-z7_f)/100;
            
            nextLine7++;
        }
    }
    else if(a7==0 && b7<0)
    {
        if(z7_f <= z7_t)
        {
            if(lines7[nextLine7][0]==-1 && lines7[nextLine7][1]==-1)
                timer_active=0;
            
            
            x7_f=x7_t;
            z7_f=z7_t;
            
            x7_t=lines7[nextLine7][0];
            z7_t=lines7[nextLine7][1];
            
            a7=(x7_t-x7_f)/100;
            b7=(z7_t-z7_f)/100;
            
            nextLine7++;
        }
    }
    
    
    glutPostRedisplay();
     
    if(timer_active)
        glutTimerFunc(50,onTimer7,7);
}

static void onTimer8(int value)
{
    if(value!=8)
        return;
   
    x8_f+=a8;
    z8_f+=b8;
    
    
    
    if(a8>0)
    {
        if(x8_f >= x8_t)
        {
            if(lines8[nextLine8][0]==-1 && lines8[nextLine8][1]==-1)
                timer_active=0;
            
            
            x8_f=x8_t;
            z8_f=z8_t;
            
            x8_t=lines8[nextLine8][0];
            z8_t=lines8[nextLine8][1];
            
            a8=(x8_t-x8_f)/100;
            b8=(z8_t-z8_f)/100;
            
            nextLine8++;
        }
    }
    else if(a8<0)
    {
        if(x8_f <= x8_t)
        {
            if(lines8[nextLine8][0]==-1 && lines8[nextLine8][1]==-1)
                timer_active=0;
            
            
            x8_f=x8_t;
            z8_f=z8_t;
            
            x8_t=lines8[nextLine8][0];
            z8_t=lines8[nextLine8][1];
            
            a8=(x8_t-x8_f)/100;
            b8=(z8_t-z8_f)/100;
            
            nextLine8++;
        }
    }
    else if(a8==0 && b8==0)
    {
            if(lines8[nextLine8][0]==-1 && lines8[nextLine8][1]==-1)
                timer_active=0;
            
            
            x8_f=x8_t;
            z8_f=z8_t;
            
            x8_t=lines8[nextLine8][0];
            z8_t=lines8[nextLine8][1];
            
            a8=(x8_t-x8_f)/100;
            b8=(z8_t-z8_f)/100;
            
            nextLine8++;
    }
    else if(a8==0 && b8>0)
    {
        if(z8_f >= z8_t)
        {
            if(lines8[nextLine8][0]==-1 && lines8[nextLine8][1]==-1)
                timer_active=0;
            
            
            x8_f=x8_t;
            z8_f=z8_t;
            
            x8_t=lines8[nextLine8][0];
            z8_t=lines8[nextLine8][1];
            
            a8=(x8_t-x8_f)/100;
            b8=(z8_t-z8_f)/100;
            
            nextLine8++;
        }
    }
    else if(a8==0 && b8<0)
    {
        if(z8_f <= z8_t)
        {
            if(lines8[nextLine8][0]==-1 && lines8[nextLine8][1]==-1)
                timer_active=0;
            
            
            x8_f=x8_t;
            z8_f=z8_t;
            
            x8_t=lines8[nextLine8][0];
            z8_t=lines8[nextLine8][1];
            
            a8=(x8_t-x8_f)/100;
            b8=(z8_t-z8_f)/100;
            
            nextLine8++;
        }
    }
    
    glutPostRedisplay();
     
    if(timer_active)
        glutTimerFunc(50,onTimer8,8);
}



static void onKeyboard(unsigned char key, int x, int y)
{
    /*Reakcije na tasturu*/
    switch (key) {
    /*esc*/
    case 27:
        /* Zavrsava se program. */
        exit(0);
        break;

    case 'S':
        /*Otvara se falj u oji se ispisuju zabelezene koordinate plesaca, tj linije*/
        fptr=fopen("lines.txt","w");
        if(fptr==NULL)
            printf("problem sa otvaranjem fajla\n");
        /*U jednom redu se cuvaju po jedan par koordinata za svakog plesaca */
        for(i=0; i<=line; i++)
            fprintf(fptr,"%.2f %.2f , %.2f %.2f , %.2f %.2f , %.2f %.2f , %.2f %.2f , %.2f %.2f , %.2f %.2f , %.2f %.2f \n", lines1[i][0], lines1[i][1], lines2[i][0], lines2[i][1], lines3[i][0], lines3[i][1], lines4[i][0], lines4[i][1], lines5[i][0], lines5[i][1], lines6[i][0], lines6[i][1], lines7[i][0], lines7[i][1], lines8[i][0], lines8[i][1] );
        fclose(fptr);
        break;
        
    case 'g':
    case 'G':
        /* Pokrece se simulacijaukoliko do sada nije pokretana, tjproverava da li je simulacija zaustavljana pa treba na nastavi ili treba da pocne od pocetka */
        if(go==0)
        {
            /* Koordinate za lopte (plesace)*/
            
            /*1*/
            z1_f=lines1[0][1]; /*Postavlja pocetnu tacku iz koje krece*/
            x1_f=lines1[0][0];
            z1_t=lines1[1][1]; /*Postavlja tacku do koje treba da dojde*/
            x1_t=lines1[1][0];
            a1=(x1_t-x1_f)/100; /*Racuna vektor pravca*/
            b1=(z1_t-z1_f)/100;
            
            /*2*/
            x2_f=lines2[0][0];
            z2_f=lines2[0][1];
            x2_t=lines2[1][0];
            z2_t=lines2[1][1];
            a2=(x2_t-x2_f)/100;
            b2=(z2_t-z2_f)/100;
            
            /*3*/
            z3_f=lines3[0][1];
            x3_f=lines3[0][0];
            x3_t=lines3[1][0];
            z3_t=lines3[1][1];
            a3=(x3_t-x3_f)/100;
            b3=(z3_t-z3_f)/100;
            
            /*4*/
            z4_f=lines4[0][1];
            x4_f=lines4[0][0];
            x4_t=lines4[1][0];
            z4_t=lines4[1][1];
            a4=(x4_t-x4_f)/100;
            b4=(z4_t-z4_f)/100;
            
            /*5*/
            z5_f=lines5[0][1];
            x5_f=lines5[0][0];
            x5_t=lines5[1][0];
            z5_t=lines5[1][1];
            a5=(x5_t-x5_f)/100;
            b5=(z5_t-z5_f)/100;
            
            /*6*/
            z6_f=lines6[0][1];
            x6_f=lines6[0][0];
            x6_t=lines6[1][0];
            z6_t=lines6[1][1];
            a6=(x6_t-x6_f)/100;
            b6=(z6_t-z6_f)/100;
            
            /*7*/
            z7_f=lines7[0][1];
            x7_f=lines7[0][0];
            x7_t=lines7[1][0];
            z7_t=lines7[1][1];
            a7=(x7_t-x7_f)/100;
            b7=(z7_t-z7_f)/100;
            
            /*8*/
            z8_f=lines8[0][1];
            x8_f=lines8[0][0];
            x8_t=lines8[1][0];
            z8_t=lines8[1][1];
            a8=(x8_t-x8_f)/100;
            b8=(z8_t-z8_f)/100;
            
            /*Promenljive koje se krecu kroz matrice koordinata postavlja na dva jer je vec uzeo vrednosti iz prve dve vrste*/
            nextLine1=2;
            nextLine2=2;
            nextLine3=2;
            nextLine4=2;
            nextLine5=2;
            nextLine6=2;
            nextLine7=2;
            nextLine8=2;
        }
        go=1;
        /*Poziv funkcija koje pokrecu lopte*/
        if (!timer_active) {
            glutTimerFunc(50, onTimer1, 1);
            glutTimerFunc(50, onTimer2, 2);
            glutTimerFunc(50, onTimer3, 3);
            glutTimerFunc(50, onTimer4, 4);
            glutTimerFunc(50, onTimer5, 5);
            glutTimerFunc(50, onTimer6, 6);
            glutTimerFunc(50, onTimer7, 7);
            glutTimerFunc(50, onTimer8, 8);
            timer_active = 1;
            
            
        }
        break;

    case 's':
        /* Zaustavlja se simulacija */
        timer_active = 0;
        break;
    /*Bira se koji igrc se pomera*/    
    case '1':
        id=1;
        break;
        
    case '2':
        id=2;
        break;
        
    case '3':
        id=3;
        break;
        
    case '4':
        id=4;
        break;
        
    case '5':
        id=5;
        break;
        
    case '6':
        id=6;
        break;
        
    case '7':
        id=7;
        break;
        
    case '8':
        id=8;
        break;
        
    case 'b':
        /*U zavisnosti od toga koji plesac je odabran pomera se za pola metra unazad (u realnosti)*/
        if(id==1)
            z1_f-=0.05;
        if(id==2)
            z2_f-=0.05;
        if(id==3)
            z3_f-=0.05;
        if(id==4)
            z4_f-=0.05;
        if(id==5)
            z5_f-=0.05;
        if(id==6)
            z6_f-=0.05;
        if(id==7)
            z7_f-=0.05;
        if(id==8)
            z8_f-=0.05;
        
        /*Salje se slika na ekran*/
        glutPostRedisplay();
        break;
      
    /*U zavisnosti od toga koji plesac je odabran pomera se za pola metra unapred (u realnosti)*/    
    case 'f':
        if(id==1)
            z1_f+=0.05;
        if(id==2)
            z2_f+=0.05;
        if(id==3)
            z3_f+=0.05;
        if(id==4)
            z4_f+=0.05;
        if(id==5)
            z5_f+=0.05;
        if(id==6)
            z6_f+=0.05;
        if(id==7)
            z7_f+=0.05;
        if(id==8)
            z8_f+=0.05;
        
        /*Salje se slika na ekran*/
        glutPostRedisplay();
        break;
        
    /*U zavisnosti od toga koji plesac je odabran pomera se za pola metra ulevo (u realnosti)*/
    case 'l':
        if(id==1)
            x1_f-=0.05;
        if(id==2)
            x2_f-=0.05;
        if(id==3)
            x3_f-=0.05;
        if(id==4)
            x4_f-=0.05;
        if(id==5)
            x5_f-=0.05;
        if(id==6)
            x6_f-=0.05;
        if(id==7)
            x7_f-=0.05;
        if(id==8)
            x8_f-=0.05;
        
        /*Salje se slika na ekran*/
        glutPostRedisplay();
        break;
       
    /*U zavisnosti od toga koji plesac je odabran pomera se za pola metra udesno (u realnosti)*/
    case 'r':
        if(id==1)
            x1_f+=0.05;
        if(id==2)
            x2_f+=0.05;
        if(id==3)
            x3_f+=0.05;
        if(id==4)
            x4_f+=0.05;
        if(id==5)
            x5_f+=0.05;
        if(id==6)
            x6_f+=0.05;
        if(id==7)
            x7_f+=0.05;
        if(id==8)
            x8_f+=0.05;
        
        /*Salje se slika na ekran*/
        glutPostRedisplay();
        break;
    
        
    case 'n':
        
        /*Cuvaju se trenutne pozicije lopti (plesaca)*/
        line+=1;
        lines1[line][0]=x1_f;
        lines1[line][1]=z1_f;
        lines2[line][0]=x2_f;
        lines2[line][1]=z2_f;
        lines3[line][0]=x3_f;
        lines3[line][1]=z3_f;
        lines4[line][0]=x4_f;
        lines4[line][1]=z4_f;
        lines5[line][0]=x5_f;
        lines5[line][1]=z5_f;
        lines6[line][0]=x6_f;
        lines6[line][1]=z6_f;
        lines7[line][0]=x7_f;
        lines7[line][1]=z7_f;
        lines8[line][0]=x8_f;
        lines8[line][1]=z8_f;
        break;
    
    /*Restaruje se program*/
    case 'R':
        /*Vrsi se inicijalizacija*/
        initialize();
        
        /*Salje se slika na ekran*/
        glutPostRedisplay();
        break;
        
        
    /*Kamera se pomera na gore*/    
    case 'p':
        if(cam_y<5) 
        {    
            cam_y+=0.1;
            cam_z-=0.035;
           
        }
         
         /*Salje se slika na ekran*/
        glutPostRedisplay();
        break;

    /*Kamera se pomera na dole*/    
    case 'P':
        if(cam_y>1) 
        {    
            cam_y-=0.1;
            cam_z+=0.035;
           
        }
         
        /*Salje se slika na ekran*/
        glutPostRedisplay();
        break;
        
        
  /*Kamera se pomera udesno*/
  case 't':
        if(cam_x<5 && cam_z>0) 
        {    
            cam_x+=0.2;
            cam_z-=0.23;
           
        }
         
        /*Salje se slika na ekran*/ 
        glutPostRedisplay();
        break;
        
  /*Kamera se pomera ulevo*/
  case 'T':
        if(cam_x>4/5 && cam_z<6) 
        {    
            cam_x-=0.2;
            cam_z+=0.23;
           
        }
        
        /*Salje se slika na ekran*/
        glutPostRedisplay();
        break;
    }
}

/*Funkcija koja crta horizontalne linije*/
static void horizontalLines()
{
    /*Postavlja se boja linija*/
    glColor3f(0.8, 0.8, 0.8);
    
    /*Iscrtavaju se linije*/
    glBegin(GL_LINES);
    glVertex3f(0.4, 0, 0);
    glVertex3f(-0.4, 0, 0);
    
    glVertex3f(0.4, 0, 0.1);
    glVertex3f(-0.4, 0, 0.1);
    
    glVertex3f(0.4, 0, 0.2);
    glVertex3f(-0.4, 0, 0.2);
    
    glVertex3f(0.4, 0, 0.3);
    glVertex3f(-0.4, 0, 0.3);
    
    glVertex3f(0.4, 0, -0.1);
    glVertex3f(-0.4, 0, -0.1);
    
    glVertex3f(0.4, 0, -0.2);
    glVertex3f(-0.4, 0, -0.2);
    
    glVertex3f(0.4, 0, -0.3);
    glVertex3f(-0.4, 0, -0.3);
    glEnd();
        
}




/*Funkcijakoja crta vertikalne linije*/
static void verticalLines()
{
    /*Postavlja se boja linija*/
    glColor3f(0.8, 0.8, 0.8);
    
    /*Iscrtavaju se linije*/
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0.4);
    glVertex3f(0, 0, -0.4);
    
    glVertex3f(0.1, 0, 0.4);
    glVertex3f(0.1, 0, -0.4);
    
    glVertex3f(0.2, 0, 0.4);
    glVertex3f(0.2, 0, -0.4);
    
    glVertex3f(0.3, 0, 0.4);
    glVertex3f(0.3, 0, -0.4);
    
    glVertex3f(-0.1, 0, 0.4);
    glVertex3f(-0.1, 0, -0.4);
    
    glVertex3f(-0.2, 0, 0.4);
    glVertex3f(-0.2, 0, -0.4);
    
    glVertex3f(-0.3, 0, 0.4);
    glVertex3f(-0.3, 0, -0.4);
    glEnd();
}




/* Funkcija koja ispisuje brojeve na x-osi*/
static void xNumbers()
{
    /*Postavlja se boja*/
    glColor3f(0.8, 0.8, 0.8); 
    
    /*Ispisuju se brojevi*/
    glRasterPos3f(0,0,0.43);
    char*c="0";
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    
    glRasterPos3f(0.1,0,0.43);
    char*jc="1";
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *jc);
    
    
    
    glRasterPos3f(0.2,0,0.43);
    char*dc="2";
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *dc);
    
    
    glRasterPos3f(0.3,0,0.43);
    char*tc="3";
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *tc);
    
    
    
    glRasterPos3f(0.4,0,0.43);
    char*cc="4";
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *cc);
    
    
    glRasterPos3f(-0.1,0,0.43);
    char*mjc;
    for(mjc = "-1"; *mjc != '\0'; mjc++)
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *mjc);
    
    
    glRasterPos3f(-0.2,0,0.43);
    char*mdc;
    for(mdc = "-2"; *mdc != '\0'; mdc++)
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *mdc);
    
    
    glRasterPos3f(-0.3,0,0.43);
    char* mtc;
    for(mtc = "-3"; *mtc != '\0'; mtc++)
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *mtc);
    
    
    glRasterPos3f(-0.4,0,0.43);
    char*mcc;
    for(mcc = "-4"; *mcc != '\0'; mcc++)
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *mcc);
}




/*Funkcija koja ispisuje brojeve na z-osi*/
static void zNumbers()
{
    /*Postavlja se boja*/
    glColor3f(0.8, 0.8, 0.8); 
    
    /*Ispisuju se brojevi*/
    glRasterPos3f(-0.42,0,0);
    char*c="0";
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    
    glRasterPos3f(-0.42,0,0.1);
    char*jc="1";
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *jc);
    
    
    
    glRasterPos3f(-0.42,0,0.2);
    char*dc="2";
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *dc);
    
    
    glRasterPos3f(-0.42,0,0.3);
    char*tc="3";
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *tc);
    
    
    
    glRasterPos3f(-0.42,0,0.4);
    char*cc="4";
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *cc);
    
    
    glRasterPos3f(-0.43, 0,-0.1);
    char* mjc;
    for( mjc = "-1"; *mjc != '\0'; mjc++)
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *mjc);
    
    
    glRasterPos3f(-0.43,0,-0.2);
    char*mdc;
    for( mdc = "-2"; *mdc != '\0'; mdc++)
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *mdc);
    
    
    glRasterPos3f(-0.43,0,-0.3);
    char* mtc;
    for(mtc = "-3"; *mtc != '\0'; mtc++)
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *mtc);
    
    
    glRasterPos3f(-0.43,0,-0.4);
    char*mcc;
    for(mcc = "-4"; *mcc != '\0'; mcc++)
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *mcc);
} 




/*Funkcija koja crta podijum*/
static void podium()
{   
   
        
    
    /*Iscrtavanje polja oblika kvadrata (8m sirine i 8m dubine)*/
    glBegin(GL_POLYGON);
    /*Postavlja se boja*/
    glColor3f(1, 1, 0.7);
    
    glVertex3f(-0.4, 0, -0.4); 
    glVertex3f(-0.4, 0, 0.4); 
    glVertex3f( 0.4, 0, 0.4); 
    glVertex3f( 0.4, 0, -0.4); 

    glEnd();
    
    glPushMatrix();
    /*Iscrtavanje  linija*/
    verticalLines();
    horizontalLines();
    
    /*Ispisivanje brojeva*/
    xNumbers();
    zNumbers();
    
    glPopMatrix();
   
    /*Iscrtava se krstic na centru*/
    glPushMatrix();
    glColor3f(0, 0, 0.125);
    glBegin(GL_LINES);
    glVertex3f(0,0,0.025);
    glVertex3f(0,0,-0.025);
    
    glVertex3f(0.025,0,0);
    glVertex3f(-0.025,0,0);
    glEnd();
    glPopMatrix();
    
    
    
    
    
}
static void initialize()
{
    
   /*Postavljaju se vrednosti u matricama zacuvanje koordinata na -1 */ 
   for(i=0; i<30; i++)
        for(j=0; j<2; j++)
        {
            lines1[i][j]=-1;
            lines2[i][j]=-1;
            lines3[i][j]=-1;
            lines4[i][j]=-1;
            lines5[i][j]=-1;
            lines6[i][j]=-1;
            lines7[i][j]=-1;
            lines8[i][j]=-1;
        }
      
    
    /*Ako je korisnik naveo opciju da zeli da cita koordinate iz fajla*/
    if(read==1)
    {
        /*Otvara se fajl*/
        fptr=fopen("lines.txt", "r");
        if(fptr==NULL)
            printf("Problem sa otvaranjem datoteke\n");
        line=0;
    
        /*Citaju se koordinate red po red */
        while(fscanf(fptr,"%f %f , %f %f , %f %f , %f %f , %f %f , %f %f , %f %f , %f %f", &lines1[line][0],  &lines1[line][1],&lines2[line][0],  &lines2[line][1],&lines3[line][0],  &lines3[line][1],&lines4[line][0],  &lines4[line][1] , &lines5[line][0],  &lines5[line][1], &lines6[line][0],  &lines6[line][1], &lines7[line][0],  &lines7[line][1], &lines8[line][0],  &lines8[line][1])==16)
        {  
            line++;
        }
        
        line--;
        fclose(fptr);
    }
    
    else line=-1;
    
    /*Nije pokretana animacija*/
    go=0;
    
    /*Inicajne vrednosti kamere*/
    cam_y=3;
    cam_x=4/5;
    cam_z=6;
    
    /*Postavljaju se pocetne koordinate za iscrtavanje lopti*/
    
    /*1*/            
    x1_f=-0.4;
    z1_f=-0.4;
    
    /*2*/
    x2_f=-0.3;
    z2_f=-0.4;
    
    /*3*/
    x3_f=-0.2;
    z3_f=-0.4;
    
    /*4*/
    x4_f=-0.1;
    z4_f=-0.4;
    
    
    /*5*/
    x5_f=0.1;
    z5_f=-0.4;
    
    
    /*6*/
    x6_f=0.2;
    z6_f=-0.4;
    
    
    /*7*/
    x7_f=0.3;
    z7_f=-0.4;
    
    
    /*8*/
    x8_f=0.4;
    z8_f=-0.4; 
}
