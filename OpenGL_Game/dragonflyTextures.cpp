#include "dragonflyTextures.h"


dragonflyTextures::dragonflyTextures(void)
{
	GLfloat dull = 10;
	GLfloat norm = 50;
	GLfloat shiny = 100;

	headDf[0] =.5;	headDf[1] =.5;	headDf[2] =.5;	headDf[3] = 1;
	headSp[0] = 1;	headSp[1] =.5;	headSp[2] = 0;	headSp[3] = 1;
	headAm[0] = 0;	headAm[1] = 0;	headAm[2] = 0;	headAm[3] = 1;
	headEm[0] = 0;	headEm[1] = 0;	headEm[2] = 0;	headEm[3] = 1;	

	headShininess = dull;

	eyeDf[0] = 1;	eyeDf[1] =.5;	eyeDf[2] = 0;	eyeDf[3] = 1;
	eyeSp[0] = 1;	eyeSp[1] = 1;	eyeSp[2] = 0;	eyeSp[3] = 1;
	eyeAm[0] = 0;	eyeAm[1] = 0;	eyeAm[2] =.3;	eyeAm[3] = 1;
	eyeEm[0] = 0;	eyeEm[1] = 0;	eyeEm[2] = 0;	eyeEm[3] = 1;
	
	eyeShininess = shiny;

	mouthDf[0] =.5;	mouthDf[1] = 0;	mouthDf[2] = 0;	mouthDf[3] = 1;
	mouthSp[0] = 1;	mouthSp[1] = 0;	mouthSp[2] = 0;	mouthSp[3] = 1;
	mouthAm[0] = 0;	mouthAm[1] = 0;	mouthAm[2] = 0;	mouthAm[3] = 1;
	mouthEm[0] = 0;	mouthEm[1] = 0;	mouthEm[2] = 0;	mouthEm[3] = 1;
	
	mouthShininess = norm;

	wingDf[0] = 0;	wingDf[1] =.5;	wingDf[2] = 1;	wingDf[3] = 1;
	wingSp[0] = 1;	wingSp[1] =.5;	wingSp[2] = 0;	wingSp[3] = 1;
	wingAm[0] = 0;	wingAm[1] = 0;	wingAm[2] = 0;	wingAm[3] = 1; // Best when dark
	wingEm[0] = 0;	wingEm[1] = 0;	wingEm[2] = 0;	wingEm[3] = 1; //only for glowing things
	
	wingShininess = dull;

	bodyDf[0] =.5;	bodyDf[1] =.5;	bodyDf[2] =.5;	bodyDf[3] = 1;
	bodySp[0] = 1;	bodySp[1] =.5;	bodySp[2] = 0;	bodySp[3] = 1;
	bodyAm[0] = 0;	bodyAm[1] = 0;	bodyAm[2] = 0;	bodyAm[3] = 1;
	bodyEm[0] = 0;	bodyEm[1] = 0;	bodyEm[2] = 0;	bodyEm[3] = 1;	
	
	bodyShininess = dull;

	tailDf[0] = 0;	tailDf[1] = 1;	tailDf[2] = 0;	tailDf[3] = 1;
	tailSp[0] = 0;	tailSp[1] = 1;	tailSp[2] = 1;	tailSp[3] = 1;
	tailAm[0] =.3;	tailAm[1] = 0;	tailAm[2] = 0;	tailAm[3] = 1;
	tailEm[0] = 0;	tailEm[1] = 0;	tailEm[2] = 0;	tailEm[3] = 1;	
	
	tailShininess = shiny;

}


dragonflyTextures::~dragonflyTextures(void)
{
}


	
void dragonflyTextures::headTextureStart(){
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, headDf);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, headAm);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, headSp);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, headEm);	
	glMaterialf(GL_FRONT, GL_SHININESS, headShininess);
}
void dragonflyTextures::headTextureEnd(){}
	
void dragonflyTextures::eyeTextureStart(){
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, eyeDf);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, eyeAm);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, eyeSp);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, eyeEm);
	glMaterialf(GL_FRONT, GL_SHININESS, eyeShininess);
}
void dragonflyTextures::eyeTextureEnd(){}

void dragonflyTextures::mouthTextureStart(){
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mouthDf);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mouthAm);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mouthSp);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mouthEm);
	glMaterialf(GL_FRONT, GL_SHININESS, mouthShininess);
}
void dragonflyTextures::mouthTextureEnd(){}

void dragonflyTextures::wingTexturStart(){
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, wingDf);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, wingAm);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, wingSp);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, wingEm);
	glMaterialf(GL_FRONT, GL_SHININESS, wingShininess);
}
void dragonflyTextures::wingTexturEnd(){}

void dragonflyTextures::bodyTextureStart(){
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, bodyDf);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, bodyAm);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, bodySp);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, bodyEm);
	glMaterialf(GL_FRONT, GL_SHININESS, bodyShininess);
}
void dragonflyTextures::bodyTextureEnd(){}

void dragonflyTextures::tailBallTextureStart(){
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, tailDf);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, tailAm);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, tailSp);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, tailEm);
	glMaterialf(GL_FRONT, GL_SHININESS, tailShininess);
}
void dragonflyTextures::tailBallTextureEnd(){}