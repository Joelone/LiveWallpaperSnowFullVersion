#include <stdio.h>
#include <GLES/gl.h>
#include <string.h>
#include <android/log.h>

#include "common.h"
#include "Background.h"
#include "GLCommon.h"

#define LOG_TAG_BACKGROUND "Background"

//--------------------------------------------------------
// const variable
//--------------------------------------------------------
const int Background::BACKGROUND_VERTEX_NUM = 10;
const int Background::BACKGROUND_SKIN_NONE = 0;
const int Background::BACKGROUND_SKIN_GRADATION = 1;
const int Background::BACKGROUND_MOON_COOR_ADJ_VALUE = 0x20000;

//--------------------------------------------------------
// background color table
//--------------------------------------------------------
int Background_skin_none_color[]  = {
		 0,  0, 0, 0,
		 0,  0, 0, 0,
		 0,  0, 0, 0,
		 0,  0, 0, 0,
		 0,  0, 0, 0,
		 0,  0, 0, 0,
		 0,  0, 0, 0,
		 0,  0, 0, 0,
		 0,  0, 0, 0,
		 0,  0, 0, 0,
};

int Background_skin_gradation_color[]  = {
		 0,  0, 0, 0,
		 0,  0, 0, 0,
		 0,  0, 0, 0,
		 0,  0, 0, 0,
		 0,  0, 0, 0,
		 0,  0, 0, 0,
		 0,  0, 0, 0,
		 0,  0, 0, 0,
		 0x10000,  0x10000, 0x10000, 0x10000,
		 0x10000,  0x10000, 0x10000, 0x10000,
};

//--------------------------------------------------------
// moon vertices and coordinates
//--------------------------------------------------------
int Background_moon_vertices[] = {
		0,       0,				//����
		0x10000, 0,				//�E��
		0,       0x10000,		//����
		0x10000, 0x10000,		//�E��
};

int Background_moon_coordinates[] = {
		0,       0x25000, 0, //����
		0x20000, 0x25000, 0, //�E��
		0,       0x05000, 0, //����
		0x20000, 0x05000, 0  //�E��
};


//
//�R���X�g���N�^
//
Background::Background() {
	mpSquare = new int[BACKGROUND_VERTEX_NUM*CORDINATES_NUM];
	mpColor  = new int[BACKGROUND_VERTEX_NUM*COLOR_NUM];
	mpMoonSquare = new int[4*CORDINATES_NUM];
	mpTexture = NULL;
	mIsMoonVisible = false;
}

//
//�f�X�g���N�^
//
Background::~Background() {
	
	if( mpSquare != NULL ) {
		delete mpSquare;
	}
	
	if( mpColor != NULL ) {
		delete mpColor;	
	}

	if( mpTexture != NULL ) {
		delete mpTexture;
	}

	if( mpMoonSquare != NULL ) {
		delete mpMoonSquare;
	}
}

//
// ��ʏc����̃Z�b�g
//
int Background::setAspect(  int orientation, float vertical, float horizontal ) {
	mOrientation = orientation;
	mVertical    = vertical*ONE*3;
	mHorizontal  = horizontal*ONE*8;
	
	this->initialize();
}

//
// �w�i�p�^�[���ݒ�
//
int  Background::setPattern( int pattern ) {
	mPattern = pattern;
	
	return 0;
}

//
// ������
//
int Background::initialize( void ) {
	//--------------------------------------
	//�w�i�ݒ�
	//--------------------------------------
	int ypos1 = mVertical;
	int ypos2 = mVertical-mVertical/2;
	int ypos3 = 0;
	int ypos4 = -mVertical+mVertical/2;
	int yPos5 = -mVertical;
	
	//�w�i���c������5����
	int square[] = {
		-mHorizontal,   ypos1, 0,
		 mHorizontal,   ypos1, 0,
		-mHorizontal,   ypos2, 0,
		 mHorizontal,   ypos2, 0,
		-mHorizontal,   ypos3, 0,
		 mHorizontal,   ypos3, 0,
		-mHorizontal,   ypos4, 0,
		 mHorizontal,   ypos4, 0, 
		-mHorizontal,   yPos5, 0,
		 mHorizontal,   yPos5, 0
	};

	int* p_color;
	
	switch( mPattern ) {
	case BACKGROUND_SKIN_GRADATION:
		p_color = Background_skin_gradation_color;
		break;
	case BACKGROUND_SKIN_NONE:
	default:
		p_color = Background_skin_none_color;
		break;
	}

	
	memcpy( mpSquare, square, sizeof(square) );
	memcpy( mpColor,  p_color,  sizeof(int)*BACKGROUND_VERTEX_NUM*COLOR_NUM  );
	
	//--------------------------------------
	//���̐ݒ�
	//--------------------------------------
	int x_pos = -mMoonWidth/8;

	int moon_coordinates[] = {
		x_pos,            mVertical-BACKGROUND_MOON_COOR_ADJ_VALUE,		     0, //����
		x_pos+mMoonWidth, mVertical-BACKGROUND_MOON_COOR_ADJ_VALUE,		     0, //�E��
		x_pos,            mVertical-BACKGROUND_MOON_COOR_ADJ_VALUE+mMoonHeight, 0, //����
		x_pos+mMoonWidth, mVertical-BACKGROUND_MOON_COOR_ADJ_VALUE+mMoonHeight, 0, //�E��
	};

	memcpy( mpMoonSquare, moon_coordinates, sizeof(moon_coordinates));

	return R_NORMAL;
}

//
// �`��
//
int Background::draw( void ){

	glDisable(GL_DEPTH_TEST);

	glEnableClientState( GL_COLOR_ARRAY );
	glEnableClientState( GL_TEXTURE_COORD_ARRAY);

	//�w�i�`��
	glVertexPointer(3, GL_FIXED, 0, mpSquare);
	glColorPointer(4, GL_FIXED, 0, mpColor);
	glDrawArrays( GL_TRIANGLE_STRIP, 0, BACKGROUND_VERTEX_NUM );

	if( mIsMoonVisible == true ) {
		glEnable(GL_TEXTURE_2D);

		float attenuation[3] = { 0.0f, 0.5f, 1.0f };
		glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, attenuation);

		//���`��
		glBindTexture( GL_TEXTURE_2D, mTextureID);
		glVertexPointer(3, GL_FIXED, 0, mpMoonSquare);
		glTexCoordPointer(2, GL_FIXED, 0, Background_moon_vertices);
		glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );

		glDisable(GL_TEXTURE_2D);
	}

	glEnable(GL_DEPTH_TEST);
	glDisableClientState( GL_TEXTURE_COORD_ARRAY);
	glDisableClientState( GL_COLOR_ARRAY );




	return R_NORMAL;
}

//
// �e�N�X�`���ݒ�
//
int  Background::setupTexture( int width, int height, int* p_buf ) {
	if( mpTexture != NULL ) {
		delete mpTexture;
	}

	mpTexture = new GLubyte[width*height*4];
	
	mTextureID = glcLoadSetupTexture( width, height, p_buf, mpTexture );

	mMoonWidth = width*300;
	mMoonHeight = height*300;

	return R_NORMAL;
}

//
// ���̕\��/��\���ݒ�
//
int  Background::setMoonVisibility(  bool isVisible ) {
	mIsMoonVisible = isVisible;
	
	__android_log_print( ANDROID_LOG_DEBUG, "debug", "visible=%d", mIsMoonVisible );
	
	return R_NORMAL;
}
