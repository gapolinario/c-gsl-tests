This folder has an assortment of test functions of the GSL library and others

elliptic.c has a comparison between Complete Elliptic Integrals calculated with the GSL library and the MyMathLibrary, found online
elliptic-2.c has only the online version, which I sent to Maiara
elliptic-3.c a modification of the online version, remove a conditional to make it faster, but there is no difference. it is important to compile correctly, without linking to the GSL library, this makes a consistent difference of 1s in execution time (at n=1e8) 
