
#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "WallpaperObject.h"
#include "NDKParticle.h"

typedef struct {
	int x, y, z;
}PARTICLE_POSITION;

typedef struct{
	PARTICLE_POSITION* p_pos;
	int*		   p_vector_x;
	int*		   p_vector_y;
}PARTICLE_DATA;

typedef struct {
	int vector_x;
	int vector_max;
	int on_time;
	int interval;
}PARTICLE_WIND;

typedef enum {
	PARTICLE_HEIGHT_POSITION_RANDOM,
	PARTICLE_HEIGHT_POSITION_TOP,
}PARTICLE_HEIGHT_POSITION_E;



class Particle : public WallpaperObject{
public:
	Particle();
	~Particle();

	//WallpaperObject I/F
	int  initialize( void );
	int  draw( void );

	int setAspect( int orientation, float vertical, float horizontal ) {
		return 0;
	}

	int  setupTexture( int width, int height, int* p_int_image  );
	int  loadTexutre( void );

	void initPosition( int particle_no, PARTICLE_HEIGHT_POSITION_E h_pos );
	int  getVector( int* p_x, int* p_y );
	int  setNum( int num );
	int  setSpeed( int speed );

	int  getMemory( int particle_num );
	int  releaseMemory( void );



private:
	int  			mParticleNum;		//Particle Number
	int  			mParticleSpeed;		//Particle Speed
	PARTICLE_DATA 	mParticleData;		//Particle Data(Position,Vector)
	int* 			mpParticleColors;	//Particle Color
	GLubyte* 		mpTexture;			//Texture Data(32bit bitmap)
	GLuint 			mTextureID;			//Texture ID
};

#endif//__PARTICLE_H__
