#ifndef _DEMO_MORPHOLOGY_H_
#define _DEMO_MORPHOLOGY_H_


#include "Morphology.h"

//-------------------------------------
void demoBinaryDilation();
void demoBinaryErosion();
void demoBinaryOpening();
void demoBinaryClosing();

void demoFillingRegion();
void demoSkeleton();
void demoThinning();
void demoThickening();
void demoConvexHull();
void demoBinaryBoundaryExtraction();
//Do hit & miss transform khó demo, tuy vậy được sử dụng trong thinning, thickenning nên ta sẽ đánh giá mức
//độ hiệu quả của nó dựa vào kết quả của thinning và thickening
//--------------------------------------
void demoGrayscaleDilation();
void demoGrayscaleErosion();
void demoGrayscaleOpening();
void demoGrayscaleClosing();
void demoMorphologyGradient();
void demoTopHat();

#endif