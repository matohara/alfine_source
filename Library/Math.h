#ifndef __TSULIB_MATH_INCLUDE__
#define __TSULIB_MATH_INCLUDE__


#define TSU_PI (3.1415926536f)
#ifndef PI
#define PI TSU_PI
#endif // !PI

#define DegToRad( degree ) ( degree / 180.0f * TSU_PI )
#define RadToDeg( radian ) ( radian / TSU_PI * 180.0f )


#define ROOT2 (1.4142135624f)


#define Absolute( value ) ( value < 0 ? -value : value )


#endif // !__TSULIB_MATH_INCLUDE__
