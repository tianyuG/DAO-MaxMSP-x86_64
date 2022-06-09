/* Common header files ********************************************************/
#include "cleaner~common.h"

/* The common 'new instance' routine ******************************************/
void *cleaner_common_new(t_cleaner *x, short argc, t_atom *argv)
{
#ifdef TARGET_IS_MAX
    /* Create inlets */
    dsp_setup((t_pxobject *)x, NUM_INLETS);

    /* Create signal outlets */
    outlet_new((t_object *)x, "signal");

    /* Avoid sharing memory among audio vectors */
    x->obj.z_misc |= Z_NO_INPLACE;

#elif TARGET_IS_PD
    /* Create inlets */
    inlet_new(&x->obj, &x->obj.ob_pd, gensym("signal"), gensym("signal"));
    inlet_new(&x->obj, &x->obj.ob_pd, gensym("signal"), gensym("signal"));

    /* Create signal outlets */
    outlet_new(&x->obj, gensym("signal"));

#endif

    /* Initialize input arguments */
    float threshold_value = DEFAULT_THRESHOLD;
    float attenuation_value = DEFAULT_ATTENUATION;

    /* Parse passed arguments */
    if (argc > A_THRESHOLD) {
        threshold_value = atom_getfloatarg(A_THRESHOLD, argc, argv);
    }
    if (argc > A_ATTENUATION) {
        attenuation_value = atom_getfloatarg(A_ATTENUATION, argc, argv);
    }

    /* Check validity of passed arguments */
    if (threshold_value < MINIMUM_THRESHOLD) {
        threshold_value = MINIMUM_THRESHOLD;
        post("cleaner~ • Invalid argument: Minimum threshold value set to %.4f", threshold_value);
    }
    else if (threshold_value > MAXIMUM_THRESHOLD) {
        threshold_value = MAXIMUM_THRESHOLD;
        post("cleaner~ • Invalid argument: Maximum threshold value set to %.4f", threshold_value);
    }
    if (attenuation_value < MINIMUM_ATTENUATION) {
        attenuation_value = MINIMUM_ATTENUATION;
        post("cleaner~ • Invalid argument: Minimum attenuation value set to %.4f", attenuation_value);
    }
    else if (attenuation_value > MAXIMUM_ATTENUATION) {
        attenuation_value = MAXIMUM_ATTENUATION;
        post("cleaner~ • Invalid argument: Maximum attenuation value set to %.4f", attenuation_value);
    }

    /* Initialize some state variables */
    x->fs = sys_getsr();
    x->threshold_value = threshold_value;
    x->attenuation_value = attenuation_value;

    /* Print message to Max window */
    post("cleaner~ • Object was created");

    /* Return a pointer to the new object */
    return x;
}

/* The 'free instance' routine ************************************************/
void cleaner_free(t_cleaner *x)
{
#ifdef TARGET_IS_MAX
    /* Remove the object from the DSP chain */
    dsp_free((t_pxobject *)x);
#endif

    /* Print message to Max window */
    post("cleaner~ • Memory was freed");
}

/******************************************************************************/

void cleaner_dsp(t_cleaner *x, t_object *dsp64,
                   short *count,
                   double samplerate,
                   long maxvectorsize,
                   long flags)
{
    object_method(dsp64, gensym("dsp_add64"), x, cleaner_perform, 0, NULL);
    post("cleaner~ • Executing dsp64 routine");
}

void cleaner_perform(t_cleaner *x, t_object *dsp64,
                       double **ins, long numins,
                       double **outs, long numouts,
                       long vectorsize,
                       long flags,
                       void *userparams)
{
    t_double *input = ins[I_INPUT];
    t_double *threshold = ins[I_THRESHOLD];
    t_double *attenuation = ins[I_ATTENUATION];
    t_double *output = outs[O_OUTPUT];
    
    long n = vectorsize;
    
    double maxamp = 0.0;
    double threshold_value;
    double attenuation_value;
    
    for (int ii = 0; ii < n; ii++) {
        if (maxamp < input[ii]) {
            maxamp = input[ii];
        }
    }

    if (x->threshold_connected) {
        threshold_value = (*threshold) * maxamp;
    } else {
        threshold_value = x->threshold_value * maxamp;
    }

    if (x->attenuation_connected) {
        attenuation_value = (*attenuation);
    } else {
        attenuation_value = x->attenuation_value;
    }

    for (int ii = 0; ii < n; ii++) {
        if (input[ii] < threshold_value) {
            input[ii] *= attenuation_value;
        }
        output[ii] = input[ii];
    }
}

/******************************************************************************/
