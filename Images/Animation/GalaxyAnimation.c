/*
 * GalaxyAnimation.c
 *
 *  Created on: Apr 11, 2024
 *      Author: Richard Harrison
 */

#include <ti/grlib/grlib.h>

extern const Graphics_Image GALAXY_IMAGE_008BPP_UNCOMP;
extern const Graphics_Image GALAXY_IMAGE_018BPP_UNCOMP;
extern const Graphics_Image GALAXY_IMAGE_028BPP_UNCOMP;
extern const Graphics_Image GALAXY_IMAGE_038BPP_UNCOMP;
extern const Graphics_Image GALAXY_IMAGE_048BPP_UNCOMP;
extern const Graphics_Image GALAXY_IMAGE_058BPP_UNCOMP;
extern const Graphics_Image GALAXY_IMAGE_068BPP_UNCOMP;
extern const Graphics_Image GALAXY_IMAGE_078BPP_UNCOMP;
extern const Graphics_Image GALAXY_IMAGE_088BPP_UNCOMP;
extern const Graphics_Image GALAXY_IMAGE_098BPP_UNCOMP;
extern const Graphics_Image GALAXY_IMAGE_108BPP_UNCOMP;
extern const Graphics_Image GALAXY_IMAGE_118BPP_UNCOMP;
extern const Graphics_Image GALAXY_IMAGE_128BPP_UNCOMP;
extern const Graphics_Image GALAXY_IMAGE_138BPP_UNCOMP;
extern const Graphics_Image GALAXY_IMAGE_148BPP_UNCOMP;
extern const Graphics_Image GALAXY_IMAGE_158BPP_UNCOMP;
extern const Graphics_Image GALAXY_IMAGE_168BPP_UNCOMP;
extern const Graphics_Image GALAXY_IMAGE_178BPP_UNCOMP;
extern const Graphics_Image GALAXY_IMAGE_188BPP_UNCOMP;
extern const Graphics_Image GALAXY_IMAGE_198BPP_UNCOMP;
extern const Graphics_Image GALAXY_IMAGE_208BPP_UNCOMP;
extern const Graphics_Image GALAXY_IMAGE_218BPP_UNCOMP;
extern const Graphics_Image GALAXY_IMAGE_228BPP_UNCOMP;
extern const Graphics_Image GALAXY_IMAGE_238BPP_UNCOMP;
extern const Graphics_Image GALAXY_IMAGE_248BPP_UNCOMP;
extern const Graphics_Image GALAXY_IMAGE_258BPP_UNCOMP;
extern const Graphics_Image GALAXY_IMAGE_268BPP_UNCOMP;
extern const Graphics_Image GALAXY_IMAGE_278BPP_UNCOMP;
extern const Graphics_Image GALAXY_IMAGE_288BPP_UNCOMP;
extern const Graphics_Image GALAXY_IMAGE_298BPP_UNCOMP;
extern const Graphics_Image GALAXY_IMAGE_308BPP_UNCOMP;
extern const Graphics_Image GALAXY_IMAGE_318BPP_UNCOMP;
extern const Graphics_Image GALAXY_IMAGE_328BPP_UNCOMP;
extern const Graphics_Image GALAXY_IMAGE_338BPP_UNCOMP;
extern const Graphics_Image GALAXY_IMAGE_348BPP_UNCOMP;
extern const Graphics_Image GALAXY_IMAGE_358BPP_UNCOMP;
extern const Graphics_Image GALAXY_IMAGE_368BPP_UNCOMP;
extern const Graphics_Image GALAXY_IMAGE_378BPP_UNCOMP;
extern const Graphics_Image GALAXY_IMAGE_388BPP_UNCOMP;
extern const Graphics_Image GALAXY_IMAGE_398BPP_UNCOMP;
extern const Graphics_Image GALAXY_IMAGE_408BPP_UNCOMP;
extern const Graphics_Image GALAXY_IMAGE_418BPP_UNCOMP;
extern const Graphics_Image GALAXY_IMAGE_428BPP_UNCOMP;
extern const Graphics_Image GALAXY_IMAGE_438BPP_UNCOMP;


Graphics_Image* getGalaxyImageToRender(double time) {
    switch ((int) (time / 0.07)) {
    case 0:
        return &GALAXY_IMAGE_008BPP_UNCOMP;
    case 1:
        return &GALAXY_IMAGE_018BPP_UNCOMP;
    case 2:
        return &GALAXY_IMAGE_028BPP_UNCOMP;
    case 3:
        return &GALAXY_IMAGE_038BPP_UNCOMP;
    case 4:
        return &GALAXY_IMAGE_048BPP_UNCOMP;
    case 5:
        return &GALAXY_IMAGE_058BPP_UNCOMP;
    case 6:
        return &GALAXY_IMAGE_068BPP_UNCOMP;
    case 7:
        return &GALAXY_IMAGE_078BPP_UNCOMP;
    case 8:
        return &GALAXY_IMAGE_088BPP_UNCOMP;
    case 9:
        return &GALAXY_IMAGE_098BPP_UNCOMP;
    case 10:
        return &GALAXY_IMAGE_108BPP_UNCOMP;
    case 11:
        return &GALAXY_IMAGE_118BPP_UNCOMP;
    case 12:
        return &GALAXY_IMAGE_128BPP_UNCOMP;
    case 13:
        return &GALAXY_IMAGE_138BPP_UNCOMP;
    case 14:
        return &GALAXY_IMAGE_148BPP_UNCOMP;
    case 15:
        return &GALAXY_IMAGE_158BPP_UNCOMP;
    case 16:
        return &GALAXY_IMAGE_168BPP_UNCOMP;
    case 17:
        return &GALAXY_IMAGE_178BPP_UNCOMP;
    case 18:
        return &GALAXY_IMAGE_188BPP_UNCOMP;
    case 19:
        return &GALAXY_IMAGE_198BPP_UNCOMP;
    case 20:
        return &GALAXY_IMAGE_208BPP_UNCOMP;
    case 21:
        return &GALAXY_IMAGE_218BPP_UNCOMP;
    case 22:
        return &GALAXY_IMAGE_228BPP_UNCOMP;
    case 23:
        return &GALAXY_IMAGE_238BPP_UNCOMP;
    case 24:
        return &GALAXY_IMAGE_248BPP_UNCOMP;
    case 25:
        return &GALAXY_IMAGE_258BPP_UNCOMP;
    case 26:
        return &GALAXY_IMAGE_268BPP_UNCOMP;
    case 27:
        return &GALAXY_IMAGE_278BPP_UNCOMP;
    case 28:
        return &GALAXY_IMAGE_288BPP_UNCOMP;
    case 29:
        return &GALAXY_IMAGE_298BPP_UNCOMP;
    case 30:
        return &GALAXY_IMAGE_308BPP_UNCOMP;
    case 31:
        return &GALAXY_IMAGE_318BPP_UNCOMP;
    case 32:
        return &GALAXY_IMAGE_328BPP_UNCOMP;
    case 33:
        return &GALAXY_IMAGE_338BPP_UNCOMP;
    case 34:
        return &GALAXY_IMAGE_348BPP_UNCOMP;
    case 35:
        return &GALAXY_IMAGE_358BPP_UNCOMP;
    case 36:
        return &GALAXY_IMAGE_368BPP_UNCOMP;
    case 37:
        return &GALAXY_IMAGE_378BPP_UNCOMP;
    case 38:
        return &GALAXY_IMAGE_388BPP_UNCOMP;
    case 39:
        return &GALAXY_IMAGE_398BPP_UNCOMP;
    case 40:
        return &GALAXY_IMAGE_408BPP_UNCOMP;
    case 41:
        return &GALAXY_IMAGE_418BPP_UNCOMP;
    case 42:
        return &GALAXY_IMAGE_428BPP_UNCOMP;
    case 43:
        return &GALAXY_IMAGE_438BPP_UNCOMP;
    default:
        return &GALAXY_IMAGE_008BPP_UNCOMP;
    }

    return &GALAXY_IMAGE_008BPP_UNCOMP;
}
