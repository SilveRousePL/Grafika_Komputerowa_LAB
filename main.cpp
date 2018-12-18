#include <iostream>
#include "Egg.hpp"
#include "Pyramid.hpp"
#include "Axes.hpp"
#include "gl/glut.h"
#define M_PI 3.14159265358979323846

Egg egg = Egg(100);
Pyramid pyramid = Pyramid(3);
Axes axes = Axes(5);

int showModel = 1;

static GLfloat viewer[] = { 0.0, 0.0, 10.0 };
static GLdouble upY = 1.0;
static GLfloat R = 10.0;
static GLfloat thetax = 0.0;
static GLfloat thetay = 0.0;

static GLfloat pix2angle;     // przelicznik pikseli na stopnie

static GLint status = 0;       // stan klawiszy myszy

static int x_pos_old = 0;       // poprzednia pozycja kursora myszy
static int y_pos_old = 0;       // poprzednia pozycja kursora myszy

static int delta_x = 0;        // ró¿nica pomiêdzy pozycj¹ bie¿¹c¹ i poprzedni¹ kursora myszy 
static int delta_y = 0;        // ró¿nica pomiêdzy pozycj¹ bie¿¹c¹ i poprzedni¹ kursora myszy 

GLfloat light_position[] = { 0.0, 3.0, 0.0, 1.0 };

void Mouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		x_pos_old = x;         // przypisanie aktualnie odczytanej pozycji kursora jako pozycji poprzedniej
		y_pos_old = y;
		status = 1;          // wciêniêty zosta³ lewy klawisz myszy
	}
	else if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		x_pos_old = x;         // przypisanie aktualnie odczytanej pozycji kursora jako pozycji poprzedniej
		y_pos_old = y;
		status = 2;
	}
	else {
		status = 0;          // nie zosta³ wciêniêty ¿aden klawisz 
	}
}

void Motion(GLsizei x, GLsizei y)
{
	delta_x = x - x_pos_old;     // obliczenie ró¿nicy po³o¿enia kursora myszy
	delta_y = y - y_pos_old;
	x_pos_old = x;            // podstawienie bie¿¹cego po³o¿enia jako poprzednie
	y_pos_old = y;

	glutPostRedisplay();     // przerysowanie obrazu sceny
}

void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);

	if (status == 1)
	{
		thetax += delta_x * pix2angle * 0.02;
		thetay += delta_y * pix2angle * 0.02;

		/*if (thetay > 360)
			thetay -= 360;
		else if (thetay < 0)
			thetay += 360;*/

		if (thetay > 2 * M_PI)
			thetay -= 2 * M_PI;
		else if (thetay < 0)
			thetay += 2 * M_PI;

		if (thetay > M_PI / 2 && thetay < 3 * M_PI / 2)
			upY = -1.0;
		else
			upY = 1.0;
	}
	else if (status == 2)
	{
		R += delta_y * 0.1;
		if (R < 5.0)
			R = 5.0;
	}

	viewer[0] = R * cos(thetax)*cos(thetay);
	viewer[1] = R * sin(thetay);
	viewer[2] = R * sin(thetax)*cos(thetay);

	light_position[0] = R * cos(thetax)*cos(thetay);
	light_position[1] = R * sin(thetay);
	light_position[2] = (R+10) * sin(thetax)*cos(thetay);

	gluLookAt(viewer[0], viewer[1], viewer[2], 0.0, 0.0, 0.0, 0.0, upY, 0.0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	if(showModel == 1)
		pyramid.draw();
	if(showModel == 2)
		egg.draw();
	//axes.draw();
	glFlush();
	glutSwapBuffers();
}

void Keyboard(unsigned char key, int x, int y) {
	if (key == '1')
		egg.setModel(1);
	if (key == '2')
		egg.setModel(2);
	if (key == '3')
		egg.setModel(3);
	if (key == '4')
		egg.setModel(4);
	if (key == 'q')
		pyramid.toggleSide(0);
	if (key == 'w')
		pyramid.toggleSide(1);
	if (key == 'e')
		pyramid.toggleSide(2);
	if (key == 'r')
		pyramid.toggleSide(3);
	if (key == 't')
		pyramid.toggleSide(4);
	if (key == 'k') {
		if (glIsEnabled(GL_CULL_FACE))
			glDisable(GL_CULL_FACE);
		else glEnable(GL_CULL_FACE);
	}
	if (key == 'n')
		showModel = 1;
	if (key == 'm')
		showModel = 2;
	RenderScene();
}

/*************************************************************************************/
 // Funkcja wczytuje dane obrazu zapisanego w formacie TGA w pliku o nazwie 
 // FileName, alokuje pamiêæ i zwraca wskaŸnik (pBits) do bufora w którym 
 // umieszczone s¹ dane. 
 // Ponadto udostêpnia szerokoœæ (ImWidth), wysokoœæ (ImHeight) obrazu
 // tekstury oraz dane opisuj¹ce format obrazu wed³ug specyfikacji OpenGL 
 // (ImComponents) i (ImFormat).
 // Jest to bardzo uproszczona wersja funkcji wczytuj¹cej dane z pliku TGA.
 // Dzia³a tylko dla obrazów wykorzystuj¹cych 8, 24, or 32 bitowy kolor.
 // Nie obs³uguje plików w formacie TGA kodowanych z kompresj¹ RLE.
/*************************************************************************************/

GLbyte *LoadTGAImage(const char *FileName, GLint *ImWidth, GLint *ImHeight, GLint *ImComponents, GLenum *ImFormat)
{
	/*************************************************************************************/
	// Struktura dla nag³ówka pliku  TGA
#pragma pack(1)            
	typedef struct
	{
		GLbyte    idlength;
		GLbyte    colormaptype;
		GLbyte    datatypecode;
		unsigned short    colormapstart;
		unsigned short    colormaplength;
		unsigned char     colormapdepth;
		unsigned short    x_orgin;
		unsigned short    y_orgin;
		unsigned short    width;
		unsigned short    height;
		GLbyte    bitsperpixel;
		GLbyte    descriptor;
	}TGAHEADER;
#pragma pack(8)
	FILE *pFile;
	TGAHEADER tgaHeader;
	unsigned long lImageSize;
	short sDepth;
	GLbyte    *pbitsperpixel = NULL;
	/*************************************************************************************/
	// Wartoœci domyœlne zwracane w przypadku b³êdu 
	*ImWidth = 0;
	*ImHeight = 0;
	*ImFormat = GL_BGR_EXT;
	*ImComponents = GL_RGB8;

#pragma warning(suppress : 4996)
	pFile = fopen(FileName, "rb");
	if (pFile == NULL)
		return NULL;
	/*************************************************************************************/
	// Przeczytanie nag³ówka pliku 
	fread(&tgaHeader, sizeof(TGAHEADER), 1, pFile);
	/*************************************************************************************/
	// Odczytanie szerokoœci, wysokoœci i g³êbi obrazu 
	*ImWidth = tgaHeader.width;
	*ImHeight = tgaHeader.height;
	sDepth = tgaHeader.bitsperpixel / 8;
	/*************************************************************************************/
	// Sprawdzenie, czy g³êbia spe³nia za³o¿one warunki (8, 24, lub 32 bity) 
	if (tgaHeader.bitsperpixel != 8 && tgaHeader.bitsperpixel != 24 && tgaHeader.bitsperpixel != 32)
		return NULL;
	/*************************************************************************************/
	// Obliczenie rozmiaru bufora w pamiêci
	lImageSize = tgaHeader.width * tgaHeader.height * sDepth;
	/*************************************************************************************/
	// Alokacja pamiêci dla danych obrazu
	pbitsperpixel = (GLbyte*)malloc(lImageSize * sizeof(GLbyte));
	if (pbitsperpixel == NULL)
		return NULL;
	if (fread(pbitsperpixel, lImageSize, 1, pFile) != 1)
	{
		free(pbitsperpixel);
		return NULL;
	}
	/*************************************************************************************/
	// Ustawienie formatu OpenGL
	switch (sDepth)
	{
	case 3:
		*ImFormat = GL_BGR_EXT;
		*ImComponents = GL_RGB8;
		break;
	case 4:
		*ImFormat = GL_BGRA_EXT;
		*ImComponents = GL_RGBA8;
		break;
	case 1:
		*ImFormat = GL_LUMINANCE;
		*ImComponents = GL_LUMINANCE8;
		break;
	};
	fclose(pFile);
	return pbitsperpixel;
}

/*************************************************************************************/

void ChangeSize(GLsizei horizontal, GLsizei vertical) {
	pix2angle = 360.0 / (float)horizontal;  // przeliczenie pikseli na stopnie
	pix2angle = 360.0 / (float)vertical;  // przeliczenie pikseli na stopnie
	GLfloat AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	if (vertical == 0)
		vertical = 1;
	glViewport(0, 0, horizontal, vertical);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, 1.0, 1.0, 30.0);
	glViewport(0, (vertical - horizontal) / 2, horizontal, horizontal);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutSwapBuffers();
}

void myInit() {
	// Zmienne dla obrazu tekstury
	GLbyte *pBytes;
	GLint ImWidth, ImHeight, ImComponents;
	GLenum ImFormat;
	/*************************************************************************************/
// Definicja materia³u z jakiego zrobiony jest czajnik 

	GLfloat mat_ambient[] = { 0.1, 0.1, 0.1, 1.0 }; // wspó³czynniki dla œwiat³a otoczenia
	GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 }; // wspó³czynniki œwiat³a rozproszonego
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 }; // wspó³czynniki dla œwiat³a odbitego                
	GLfloat mat_shininess = { 20.0 }; // wspó³czynnik n opisuj¹cy po³ysk powierzchni

/*************************************************************************************/
// Definicja Ÿród³a œwiat³a
	//GLfloat light_position0[] = { -15.0, 0.0, 0.0, 1.0 }; // po³o¿enie Ÿród³a
	GLfloat light_ambient0[] = { 1.0, 1.0, 1.0, 1.0 }; // sk³adowe intensywnoœci œwiecenia Ÿród³a œwiat³a otoczenia
	GLfloat light_diffuse0[] = { 1.0, 1.0, 1.0, 1.0 }; // sk³adowe intensywnoœci œwiecenia Ÿród³a œwiat³a powoduj¹cego odbicie dyfuzyjne
	GLfloat light_specular0[] = { 1.0, 1.0, 1.0, 1.0 }; // sk³adowe intensywnoœci œwiecenia Ÿród³a œwiat³a powoduj¹cego odbicie kierunkowe
	GLfloat att_constant0 = { 1.0 }; //sk³adowa sta³a ds dla modelu zmian oœwietlenia w funkcji odleg³oœci od Ÿród³a
	GLfloat att_linear0 = { 0.05 }; // sk³adowa liniowa dl dla modelu zmian oœwietlenia w funkcji odleg³oœci od Ÿród³a
	GLfloat att_quadratic0 = { 0.001 }; // sk³adowa kwadratowa dq dla modelu zmian oœwietlenia w funkcji odleg³oœci od Ÿród³a

/*************************************************************************************/
// Ustawienie parametrów materia³u i Ÿród³a œwiat³a

/*************************************************************************************/
// Ustawienie patrametrów materia³u

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

	/*************************************************************************************/
	// Ustawienie parametrów Ÿród³a

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, att_constant0);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, att_linear0);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, att_quadratic0);

	/*************************************************************************************/
	// Ustawienie opcji systemu oœwietlania sceny 

	glShadeModel(GL_SMOOTH); // w³aczenie ³agodnego cieniowania
	glEnable(GL_LIGHTING);   // w³aczenie systemu oœwietlenia sceny 
	glEnable(GL_LIGHT0);     // w³¹czenie Ÿród³a o numerze 0
	glEnable(GL_DEPTH_TEST); // w³¹czenie mechanizmu z-bufora 

/*************************************************************************************/
	// Teksturowanie bêdzie prowadzone tyko po jednej stronie œciany 
	glEnable(GL_CULL_FACE);
	/*************************************************************************************/
	//  Przeczytanie obrazu tekstury z pliku o nazwie tekstura.tga
	pBytes = LoadTGAImage("textures/D1_t.tga", &ImWidth, &ImHeight, &ImComponents, &ImFormat);
	/*************************************************************************************/
	// Zdefiniowanie tekstury 2-D 
	glTexImage2D(GL_TEXTURE_2D, 0, ImComponents, ImWidth, ImHeight, 0, ImFormat, GL_UNSIGNED_BYTE, pBytes);
	/*************************************************************************************/
	// Zwolnienie pamiêci
	free(pBytes);
	/*************************************************************************************/
	// W³¹czenie mechanizmu teksturowania
	glEnable(GL_TEXTURE_2D);
	/*************************************************************************************/
	// Ustalenie trybu teksturowania
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	/*************************************************************************************/
	// Okreœlenie sposobu nak³adania tekstur
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

int main(int argc, char** argv) {
	srand(time(NULL));

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Jajko");
	glutDisplayFunc(RenderScene);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutKeyboardFunc(Keyboard);

	glutReshapeFunc(ChangeSize);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	myInit();
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}
