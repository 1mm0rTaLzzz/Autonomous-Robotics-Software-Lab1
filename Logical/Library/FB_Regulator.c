/*
#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "Library.h"
#ifdef __cplusplus
	};
#endif
 TODO: Add your comment here 
void FB_Regulator(struct FB_Regulator* inst)
{
	//dt = 0.002;
	//k_i = 0.16;
	//k_p = 0.0064;
	

	REAL a = inst->e * inst->k_p;
	REAL b = inst->e * inst->k_i;
	if (a > 24) a = 24;
	if (a < -24) a = -24;
	
	inst->integrator.in = b + inst->iyOld;
	FB_integrator(&(inst->integrator));
	
	REAL sum = a + inst->integrator.out;
	inst->u = sum;
	if (inst->u > inst->max_abs_value) inst->max_abs_value;
	if (inst->u < -inst->max_abs_value) -inst->max_abs_value;
	inst->iyOld = inst->u - sum;
	

}
*/
#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
#include "Library.h"
#ifdef __cplusplus
	};
#endif
/* TODO: Add your comment here */
void FB_Regulator(struct FB_Regulator* inst)
{
	/*TODO: Add your code here*/
	inst->integrator.in = inst->e*inst->k_i*inst->dt + inst->iyOld;
	FB_integrator(&(inst->integrator)); 
	
	inst->e_p = inst->e*inst->k_p;
	
	if (inst->e_p < inst->max_abs_value || inst->e_p > -inst->max_abs_value);
	else 
	{
		if (inst->e_p > 0) inst->e_p = inst->max_abs_value;
		else inst->e_p = -inst->max_abs_value;
	}
	
	inst->e_p += inst->integrator.out;
	if (inst->e_p < inst->max_abs_value || inst->e_p > -inst->max_abs_value)
		inst->u = inst->e_p;
	else
	{
		if (inst->e_p > 0) inst->u = inst->max_abs_value;
		else inst ->u = -inst->max_abs_value;
	}
	
	inst->iyOld = inst->u - inst->e_p;
}