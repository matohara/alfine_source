//=============================================================================
//
// �J�E���g���� <Counter.h>
// Author : �� �i�V
//
//=============================================================================
#ifndef __COUNTER_H_INCLUDE__
#define __COUNTER_H_INCLUDE__


#include "ObjectBase2D.h"
#include "LinkLibrary.h"


class CountDown : public UI2DNumber
{
	UIBackGround Back;		// �u���b�N�o�b�N
	D3DXCOLOR    Color;		// �J���[
	float        Curve;		// �A�j���[�V�����p
	int          Interval;	// �\���Ԋu
	int          Counter;	// �����J�E���^�[
	int          Time;		// �\������

public:
	CountDown();

	void Set(int inter, int time, float posX, float posY, float sizX, float sizY, const char *texture);
	void Set(int inter, int time, float sizX, float sizY, const char *texture);
	void Set(int inter, int time, float sizX, float sizY);
	int  Count();
	bool ActiveCheck();

	int Animation();

private:

};




#endif
