#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

void _INIT ProgramInit(void)
{
	Enable=1;
	count=0;
	speed=0;

	fb_motor.dt = 0.01; 
	fb_motor.ke=2;
	fb_motor.Tm=0.07; 
	fb_motor2.dt=0.01;
	fb_motor2.ke=1;
	fb_motor2.Tm=0.07;
	
	fb_controller.dt=0.01; 
	fb_controller.k_p=1.4; 
	fb_controller.k_i=20;
	fb_controller.max_abs_value=24;
}

void _CYCLIC ProgramCyclic(void)
{
	if(Enable == 1)
	{
		count +=10;
		if (count >= 500 && count <= 2000) speed = 40;
		else speed = 5;
	}
	
	else speed = 0;
	fb_controller.e=speed-fb_motor.w;
	fb_motor2.u=speed*fb_motor2.ke;
	fb_motor.u=fb_controller.u*fb_motor.ke;
	FB_Regulator(&fb_controller);
	FB_motor(&fb_motor);
	FB_motor(&fb_motor2);
}

void _EXIT ProgramExit(void)
{

}