#include <GLES/gl.h>
#include "GLCommon.h"


/*
	�e�N�X�`���[�̃Z�b�g�A�b�v
*/
GLuint glcLoadSetupTexture( int width, int height, int* p_src_data, GLubyte* p_dst_data ) {
	if( ( p_src_data == NULL ) ||
		( p_dst_data == NULL ) ) {
		return GLC_ERROR;
	}
	
	GLuint texture_id;
	
	int data_size = width*height;
	
	//ARGB�l��Byte�^�ɓ���ւ���Ƌ��ɁA�l�𔽓]
	for( int i = 0; i < data_size; i++ ) {
		p_dst_data[i*4  ] = (p_src_data[i] & 0x00FF0000) >> 16;
		p_dst_data[i*4+1] = (p_src_data[i] & 0x0000FF00) >> 8;
		p_dst_data[i*4+2] = (p_src_data[i] & 0x000000FF);
		p_dst_data[i*4+3] = (p_src_data[i] & 0xFF000000) >> 24;
	}

	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	/* �e�N�X�`�����g��E�k��������@�̎w�� */
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	/* �e�N�X�`���̌J��Ԃ����@�̎w�� */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, p_dst_data);

	return texture_id;
}

