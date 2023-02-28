/******************************************************************************
*                        ETSI TS 103 634 V1.4.1                               *
*              Low Complexity Communication Codec Plus (LC3plus)              *
*                                                                             *
* Copyright licence is solely granted through ETSI Intellectual Property      *
* Rights Policy, 3rd April 2019. No patent licence is granted by implication, *
* estoppel or otherwise.                                                      *
******************************************************************************/
                                                                               

/* guard against unindended includes */
#ifndef INCLUDED_FROM_IISFFT_C
#error "this file must not be included"
#endif

static void fft384(LC3_FLOAT* restrict in)
{
    const LC3_INT table1[384] = {
        0,   256, 128, 129, 1,   257, 258, 130, 2,   3,   259, 131, 132, 4,   260, 261, 133, 5,   6,   262, 134, 135,
        7,   263, 264, 136, 8,   9,   265, 137, 138, 10,  266, 267, 139, 11,  12,  268, 140, 141, 13,  269, 270, 142,
        14,  15,  271, 143, 144, 16,  272, 273, 145, 17,  18,  274, 146, 147, 19,  275, 276, 148, 20,  21,  277, 149,
        150, 22,  278, 279, 151, 23,  24,  280, 152, 153, 25,  281, 282, 154, 26,  27,  283, 155, 156, 28,  284, 285,
        157, 29,  30,  286, 158, 159, 31,  287, 288, 160, 32,  33,  289, 161, 162, 34,  290, 291, 163, 35,  36,  292,
        164, 165, 37,  293, 294, 166, 38,  39,  295, 167, 168, 40,  296, 297, 169, 41,  42,  298, 170, 171, 43,  299,
        300, 172, 44,  45,  301, 173, 174, 46,  302, 303, 175, 47,  48,  304, 176, 177, 49,  305, 306, 178, 50,  51,
        307, 179, 180, 52,  308, 309, 181, 53,  54,  310, 182, 183, 55,  311, 312, 184, 56,  57,  313, 185, 186, 58,
        314, 315, 187, 59,  60,  316, 188, 189, 61,  317, 318, 190, 62,  63,  319, 191, 192, 64,  320, 321, 193, 65,
        66,  322, 194, 195, 67,  323, 324, 196, 68,  69,  325, 197, 198, 70,  326, 327, 199, 71,  72,  328, 200, 201,
        73,  329, 330, 202, 74,  75,  331, 203, 204, 76,  332, 333, 205, 77,  78,  334, 206, 207, 79,  335, 336, 208,
        80,  81,  337, 209, 210, 82,  338, 339, 211, 83,  84,  340, 212, 213, 85,  341, 342, 214, 86,  87,  343, 215,
        216, 88,  344, 345, 217, 89,  90,  346, 218, 219, 91,  347, 348, 220, 92,  93,  349, 221, 222, 94,  350, 351,
        223, 95,  96,  352, 224, 225, 97,  353, 354, 226, 98,  99,  355, 227, 228, 100, 356, 357, 229, 101, 102, 358,
        230, 231, 103, 359, 360, 232, 104, 105, 361, 233, 234, 106, 362, 363, 235, 107, 108, 364, 236, 237, 109, 365,
        366, 238, 110, 111, 367, 239, 240, 112, 368, 369, 241, 113, 114, 370, 242, 243, 115, 371, 372, 244, 116, 117,
        373, 245, 246, 118, 374, 375, 247, 119, 120, 376, 248, 249, 121, 377, 378, 250, 122, 123, 379, 251, 252, 124,
        380, 381, 253, 125, 126, 382, 254, 255, 127, 383};
    const LC3_INT table2[384] = {
        0,   128, 256, 3,   131, 259, 6,   134, 262, 9,   137, 265, 12,  140, 268, 15,  143, 271, 18,  146, 274, 21,
        149, 277, 24,  152, 280, 27,  155, 283, 30,  158, 286, 33,  161, 289, 36,  164, 292, 39,  167, 295, 42,  170,
        298, 45,  173, 301, 48,  176, 304, 51,  179, 307, 54,  182, 310, 57,  185, 313, 60,  188, 316, 63,  191, 319,
        66,  194, 322, 69,  197, 325, 72,  200, 328, 75,  203, 331, 78,  206, 334, 81,  209, 337, 84,  212, 340, 87,
        215, 343, 90,  218, 346, 93,  221, 349, 96,  224, 352, 99,  227, 355, 102, 230, 358, 105, 233, 361, 108, 236,
        364, 111, 239, 367, 114, 242, 370, 117, 245, 373, 120, 248, 376, 123, 251, 379, 126, 254, 382, 129, 257, 1,
        132, 260, 4,   135, 263, 7,   138, 266, 10,  141, 269, 13,  144, 272, 16,  147, 275, 19,  150, 278, 22,  153,
        281, 25,  156, 284, 28,  159, 287, 31,  162, 290, 34,  165, 293, 37,  168, 296, 40,  171, 299, 43,  174, 302,
        46,  177, 305, 49,  180, 308, 52,  183, 311, 55,  186, 314, 58,  189, 317, 61,  192, 320, 64,  195, 323, 67,
        198, 326, 70,  201, 329, 73,  204, 332, 76,  207, 335, 79,  210, 338, 82,  213, 341, 85,  216, 344, 88,  219,
        347, 91,  222, 350, 94,  225, 353, 97,  228, 356, 100, 231, 359, 103, 234, 362, 106, 237, 365, 109, 240, 368,
        112, 243, 371, 115, 246, 374, 118, 249, 377, 121, 252, 380, 124, 255, 383, 127, 258, 2,   130, 261, 5,   133,
        264, 8,   136, 267, 11,  139, 270, 14,  142, 273, 17,  145, 276, 20,  148, 279, 23,  151, 282, 26,  154, 285,
        29,  157, 288, 32,  160, 291, 35,  163, 294, 38,  166, 297, 41,  169, 300, 44,  172, 303, 47,  175, 306, 50,
        178, 309, 53,  181, 312, 56,  184, 315, 59,  187, 318, 62,  190, 321, 65,  193, 324, 68,  196, 327, 71,  199,
        330, 74,  202, 333, 77,  205, 336, 80,  208, 339, 83,  211, 342, 86,  214, 345, 89,  217, 348, 92,  220, 351,
        95,  223, 354, 98,  226, 357, 101, 229, 360, 104, 232, 363, 107, 235, 366, 110, 238, 369, 113, 241, 372, 116,
        244, 375, 119, 247, 378, 122, 250, 381, 125, 253};

    const LC3_INT  L    = 384;
    const LC3_INT  A    = 3;
    const LC3_INT  B    = 128;
    const LC3_INT* idx1 = table1;
    const LC3_INT* idx2 = table2;

    LC3_INT   k, l;
    LC3_FLOAT temp[256], out[768];

    for (k = 0; k < A; k++) {
        for (l = 0; l < B; l++) {
            temp[2 * l]     = in[2 * *idx1];
            temp[2 * l + 1] = in[2 * *idx1 + 1];
            idx1 += A;
        }

        fft128(temp); /* 128-point FFT */
        idx1 -= L;

        for (l = 0; l < B; l++) {
            in[2 * *idx1]     = temp[2 * l];
            in[2 * *idx1 + 1] = temp[2 * l + 1];
            idx1 += A;
        }

        idx1 -= L - 1;
    }

    idx1 -= A;

    for (k = 0; k < B; k++) {
        for (l = 0; l < A; l++) {
            temp[2 * l]     = in[2 * *idx1];
            temp[2 * l + 1] = in[2 * *idx1++ + 1];
        }

        fft3(temp); /* 3-point FFT */

        for (l = 0; l < A; l++) {
            out[2 * *idx2]       = temp[2 * l];
            out[2 * *idx2++ + 1] = temp[2 * l + 1];
        }
    }

    memmove(in, out, 2 * L * sizeof(LC3_FLOAT));
}

