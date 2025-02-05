/******************************************************************************
*                        ETSI TS 103 634 V1.5.1                               *
*              Low Complexity Communication Codec Plus (LC3plus)              *
*                                                                             *
* Copyright licence is solely granted through ETSI Intellectual Property      *
* Rights Policy, 3rd April 2019. No patent licence is granted by implication, *
* estoppel or otherwise.                                                      *
******************************************************************************/

#include "functions.h"
#include "fft/iis_fft.c"
#include "fft/iisfft.c"
#include "fft/cfft.c"

void fft_init(Fft* fft, int length)
{
    HANDLE_IIS_FFT handle = NULL;
    IIS_FFT_ERROR error = 0;
    assert(length % 2 == 0);
    
    fft->length = length;
    
    error = LC3_IIS_CFFT_Create(&handle, length, IIS_FFT_FWD);
    
    assert(error == IIS_FFT_NO_ERROR);
    fft->handle = handle;
}

void fft_free(Fft* fft)
{
    IIS_FFT_ERROR error = 0;
    
    if (fft) {
        error = LC3_IIS_CFFT_Destroy((HANDLE_IIS_FFT *) &fft->handle);
        
        assert(error == IIS_FFT_NO_ERROR);
        memset(fft, 0, sizeof(*fft));
    }
}

void real_fft_free(Fft* fft)
{
    IIS_FFT_ERROR error = 0;

    if (fft) {
        error = LC3_IIS_RFFT_Destroy((HANDLE_IIS_FFT *) &fft->handle);

        assert(error == IIS_FFT_NO_ERROR);
        memset(fft, 0, sizeof(*fft));
    }
}

void real_fft_init(Fft* fft, LC3_INT32 length, HANDLE_IIS_FFT *handle)
{
    IIS_FFT_ERROR error = IIS_FFT_NO_ERROR;
    assert(length % 4 == 0); /* due to current limitation of core complex FFTs*/

    fft->length = length;

    error = LC3_IIS_RFFT_Create(handle, length, IIS_FFT_FWD);
    assert(error == IIS_FFT_NO_ERROR);
    fft->handle = *handle;
}


void real_ifft_init(Fft* fft, LC3_INT32 length, HANDLE_IIS_FFT *handle)
{
    IIS_FFT_ERROR error = IIS_FFT_NO_ERROR;
    assert(length % 4 == 0); /* due to current limitation of core complex FFTs*/

    fft->length = length;

    error = LC3_IIS_RFFT_Create(handle, length, IIS_FFT_BWD);

    assert(error == IIS_FFT_NO_ERROR);
    fft->handle = *handle;
}

void fft_apply(Fft* fft, const Complex* input, Complex* output)
{
    IIS_FFT_ERROR error = 0;
    error = LC3_IIS_FFT_Apply_CFFT(fft->handle, input, output);
    
    assert(error == IIS_FFT_NO_ERROR);
}


void real_fft_apply(Fft* fft, const LC3_FLOAT* input, LC3_FLOAT* output)
{
    IIS_FFT_ERROR error = IIS_FFT_NO_ERROR;
    
    UNUSED(error);

    error = LC3_IIS_FFT_Apply_RFFT(fft->handle, input, output);  

    assert(error == IIS_FFT_NO_ERROR);
}

