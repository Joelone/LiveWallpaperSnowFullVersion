
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <GLES/gl.h>
#include <android/log.h>
#include <math.h>

#include "common.h"
#include "Particle.h"
#include "Matrix.h"
#include "GLCommon.h"


#define lrand() (rand()*rand())
#define LRAND_MAX 0x3FFF0001 //7FFF*7FFFF

//#define GetRandom()  (((rand()*rand()) % (ONE*4)) - (ONE*2) )

#define GetRandom(RANGE, OFFSET) (int)(( rand() % RANGE ) - (RANGE / 2)) + OFFSET

//コンストラクタ
Particle::Particle(){
	__android_log_print( ANDROID_LOG_DEBUG, "Native:Particle", "Create");
	mParticleNum = 0;
	mParticleSpeed = 0;

	mParticleData.p_pos = NULL;
	mParticleData.p_vector_x = NULL;
	mParticleData.p_vector_y = NULL;
//	mpParticleCoordinates = NULL;
	mpParticleColors = NULL;
	mpTexture = NULL;
}

//デストラクタ
Particle::~Particle() {
	__android_log_print( ANDROID_LOG_DEBUG, "Native:Particle", "Destroy");


	if( mpTexture != NULL ) {
		delete[] mpTexture;
		mpTexture = NULL;
	}
}

void Particle::initPosition( int particle_no, PARTICLE_HEIGHT_POSITION_E h_pos ) {
	mParticleData.p_pos[particle_no].x = GetRandom( 0x80000, 0 );
	if( h_pos == PARTICLE_HEIGHT_POSITION_RANDOM ) {
		mParticleData.p_pos[particle_no].y = GetRandom( 0x90000, 0 );
	}
	else {
		mParticleData.p_pos[particle_no].y = 0x60000;
	}
	mParticleData.p_pos[particle_no].z = GetRandom( 0x80000, 0x00000);

	getVector( &mParticleData.p_vector_x[particle_no],
			   &mParticleData.p_vector_y[particle_no]);

}

int Particle::getVector( int* p_x, int* p_y ) {
	if( ( p_x == NULL ) || ( p_y == NULL ) ) {
		return R_PARAMETER;
	}
	int vector_x = 0;
	int vector_y =  GetRandom( mParticleSpeed, mParticleSpeed );
	int degree = GetRandom(30, 0);

	//回転
	Matrix::rotate2D( &vector_x, &vector_y, degree );

	*p_x = vector_x;
	*p_y = vector_y;

	return R_NORMAL;
}

//初期化
int Particle::initialize( void ) {
	if( mParticleNum == 0 ) {
		return R_SYSTEM;
	}

	//メモリ解放
	releaseMemory();

	//メモリ取得
	getMemory( mParticleNum );

	//Initialize particle cordinates
	for( int i = 0; i < mParticleNum ; i++ ) {
		initPosition( i, PARTICLE_HEIGHT_POSITION_RANDOM);

		mpParticleColors[i*4]   = ONE;
		mpParticleColors[i*4+1] = ONE;
		mpParticleColors[i*4+2] = ONE;
		mpParticleColors[i*4+3] = ONE;
	}

	return R_NORMAL;
}

int Particle::getMemory( int particle_num ) {
	if( particle_num <= 0 ) {
		return R_PARAMETER;
	}
	__android_log_print( ANDROID_LOG_DEBUG, "Native:getMemory", "num=%d", particle_num);
	mpParticleColors      = new int[ particle_num * COLOR_NUM ];

	mParticleData.p_pos = new PARTICLE_POSITION[ particle_num * CORDINATES_NUM ];
	mParticleData.p_vector_x = new int[ particle_num ];
	mParticleData.p_vector_y = new int[ particle_num ];

	return R_NORMAL;
}

int Particle::releaseMemory( void ) {
	__android_log_print( ANDROID_LOG_DEBUG, "Native:releaseMemory", "rel");

	if( mpParticleColors != NULL ) {
		delete[] mpParticleColors;
		mpParticleColors = NULL;
	}

	if( mParticleData.p_pos != NULL ) {
		delete[] mParticleData.p_pos;
		mParticleData.p_pos = NULL;
	}

	if( mParticleData.p_vector_x != NULL ) {
		delete[] mParticleData.p_vector_x;
		mParticleData.p_vector_x = NULL;
	}

	if( mParticleData.p_vector_y != NULL ) {
		delete[] mParticleData.p_vector_y;
		mParticleData.p_vector_y = NULL;
	}

	return R_NORMAL;
}



int Particle::setupTexture( int width, int height, int* p_int_image  ) {
	if( mpTexture != NULL ) {
		delete mpTexture;
	}

	mpTexture = new GLubyte[width*height*4];
	
	glTexEnvi(GL_POINT_SPRITE_OES, GL_COORD_REPLACE_OES, GL_TRUE);
	mTextureID = glcLoadSetupTexture( width, height, p_int_image, mpTexture );

	return R_NORMAL;
}

int Particle::setNum( int num ) {
	mParticleNum = num;
	return R_NORMAL;
}

int Particle::setSpeed( int speed ) {
	mParticleSpeed = speed;
	return R_NORMAL;
}

//描画
int Particle::draw( void ) {
	int y;

#if 1 //screen capture用のコンパイルスイッチ
	for( int i = 0; i < mParticleNum ; i++ ) {
		mParticleData.p_pos[i].x += mParticleData.p_vector_x[i];
		mParticleData.p_pos[i].y -= mParticleData.p_vector_y[i];
		if( mParticleData.p_pos[i].y < (-ONE*5) ) {
			initPosition( i, PARTICLE_HEIGHT_POSITION_TOP);
		}
	}
#endif

	glPointSize(256);

	//glDisable(GL_DEPTH_TEST);

	glDepthMask(GL_FALSE);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_POINT_SPRITE_OES);

	glBindTexture(GL_TEXTURE_2D, mTextureID);

	//　ブレンディング有効化
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	float attenuation[3] = { 0.0f, 0.5f, 1.0f };
	glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, attenuation);

	glVertexPointer(3, GL_FIXED, 0, mParticleData.p_pos);
	glColorPointer(4, GL_FIXED, 0, mpParticleColors);
	glDrawArrays( GL_POINTS, 0, mParticleNum );

	glDisable(GL_BLEND);
	glDisable(GL_POINT_SPRITE_OES);
	glDisable(GL_TEXTURE_2D);

	glDepthMask(GL_TRUE);
//	glEnable(GL_DEPTH_TEST);
//	glBindTexture(GL_TEXTURE_2D, 0);

	return R_NORMAL;
}
