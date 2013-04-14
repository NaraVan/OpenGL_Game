#pragma once
#include <gl\glut.h>

/******************
 * This is a class that tries to keep texture calls together, it probably could be static or done entirely differently
 * @author N. Van Rossum
 ******************/


class dragonflyTextures
{
private:
	GLfloat headDf[4];
	GLfloat headAm[4];
	GLfloat headSp[4];
	GLfloat headEm[4];

	GLfloat headShininess;
	
	GLfloat eyeDf[4];
	GLfloat eyeAm[4];
	GLfloat eyeSp[4];
	GLfloat eyeEm[4];
	
	GLfloat eyeShininess;

	GLfloat mouthDf[4];
	GLfloat mouthAm[4];
	GLfloat mouthSp[4];
	GLfloat mouthEm[4];
	
	GLfloat mouthShininess;

	GLfloat wingDf[4];
	GLfloat wingAm[4];
	GLfloat wingSp[4];
	GLfloat wingEm[4];
	
	GLfloat wingShininess;

	GLfloat bodyDf[4];
	GLfloat bodyAm[4];
	GLfloat bodySp[4];
	GLfloat bodyEm[4];
	
	GLfloat bodyShininess;

	GLfloat tailDf[4];
	GLfloat tailAm[4];
	GLfloat tailSp[4];
	GLfloat tailEm[4];
	
	GLfloat tailShininess;

public:
	dragonflyTextures(void);
	~dragonflyTextures(void);
	
	void headTextureStart();
	void headTextureEnd();
	
	void eyeTextureStart();
	void eyeTextureEnd();

	void mouthTextureStart();
	void mouthTextureEnd();

	void wingTexturStart();
	void wingTexturEnd();

	void bodyTextureStart();
	void bodyTextureEnd();

	void tailBallTextureStart();
	void tailBallTextureEnd();

};

