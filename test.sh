#!/bin/bash
echo "2+.3;2*3;2/3;2%4;#" | ./bin/Debug/calc 
echo "1+2*3-4;#" | ./bin/Debug/calc 
echo "-5*-8;#" | ./bin/Debug/calc 
echo "[-2+5^3!];#" | ./bin/Debug/calc 
echo "125_L_675;125_L_675;125*765;#" | ./bin/Debug/calc 
echo "_precision=12;abs(-5);[-5*2^3!];#" | ./bin/Debug/calc 
echo "a=sin(b=28)^(1/2);a&(-a);#" | ./bin/Debug/calc 
echo "8^^3;10&3;#" | ./bin/Debug/calc 
echo " sin _pi ;cos(_pi);tan _pi;cot 2;sec 2;csc 2;#" | ./bin/Debug/calc 
echo " exp _pi; cosh( _pi );#" | ./bin/Debug/calc 
echo "invert 2;ln(_e); ln( 10 ) ; log10 (100);#" | ./bin/Debug/calc 
echo "10_C_3 ; 10_L_3;#" | ./bin/Debug/calc 
echo "10.5_C_3 ; 1.2_L_3;#" | ./bin/Debug/calc 
echo "_type_strict = 0 ; 10.5_C_3 ; 1.2_L_3;#" | ./bin/Debug/calc 
echo "a+2 ; b=2/a ; _var_strict = 0 ; b=2+a; _var_strict = 2 ; b=2+a;#" | ./bin/Debug/calc 
echo "floor(1.5);ceil(0.9);round(1.6);#" | ./bin/Debug/calc 
echo "cos cos cos cos cos cos cos cos cos 1;#" | ./bin/Debug/calc
echo "#" | ./bin/Debug/calc 
