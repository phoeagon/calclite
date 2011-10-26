README

	*General
CalcLight is a light-weight calculator designed to impletment a small subset of C/C++ for mathematical purposes.
Sytax in CalcLight is case-sensitive.

	*Commands 
	#	- exit program
	?	- print help 

	*Operators:
CalcLight supports a subset of C/C++ operators and uses a very similiar grammar as well. Some complement also.

[Difference from C/C++ and Complement]
	[syntax]	[note]
-----------------------------------------------------
	[x]		absolute value of x
	x!		factorial
	~x		logic NOT [instead of bitwise]
	@x		bitwise NOT
	a^b		pow(a,b) [instead of XOR]
	a^^b		a^b [bitwise XOR]
	(a)_C_(b)	binomial coefficents
			[ C(a,b) a>=b]
	(a)_P_(b)	permutation 
			[ P(a,b) a>=b]
	(a)_G_(b)	gcd
	[greatest common divisor]
	(a)_L_(b)	lcm
	[lowest common multiple]			

[Full List of Operators]
[low]	[syntax]	[associativity]	[note]
------------------------------------------------------
	=		R		assignment
	& | ^^		L		<bitwise> 
					AND,OR,XOR
	> < == >= <=	L		<comparision>
	+-@~		L		plus,minus
					<bitwise>not
					<logic>  not
	/%		L		division,modulus
	* _C_				multiply,
					binomial number
	_P_				permutation
	_G_ _L_				gcd , lcm
	<unary>+-	R		positive
					negative
	^		R		power
	!		L		factorial
	()[]		L		bracket
					absolute value
------------------------------------------------------
[high priority]

	*Expression and Return Value
Boolean values are returned as 1 or 0.
"-5*-8" yields 40, (inhuman)
"cos _pi" yields -1
assignments return their variables assigned
	
	*Functions:

CalcLight supports a subset of C/C++ functions along with some complements.
This is a list of functions supported.
note that they are all unary functions and some applies to integers only.
	[function]	[C/C++ equilivant]
-----------------------------------------------------
	sin		/** C++ uses radian unit*/
	cos	/**	rad for all trig functions */
	tan
	cot
	sec
	sec
	exp
	ln		ln(x)=log(x)
	log		
	log2		log2(x)=log(x)/log(2)
	log10		log10(x)=log(x)/log(10)
	rand		rand()=rand()%x
	dtor		degree to radian
	rtod		radian to degree
	sqrt
	floor
	ceil
	sinh
	cosh
	tanh
	asin		/**arcsin*/
	acos
	atan
	sign		sign(x)=x/abs(x)
	signpow		signpow(x)=(-1)^x
	invert		invert(x)=1/x
	abs
	round
------------------------------------------------

	*functions are not required to use brackets 
	to indicate their variable
		cos _pi = -1;	
	but just be sure if it raises ambiguity.

	*Variables

Variables must start with an english letter or underline'_', and must contain only letters, digits and '_'.
Variables, if not defined or assigned before, as automatically initiated to 0 and will cause a warning message.
variables that start with '_' can be system variables. you can edit them, but only with great caution.

	[System Variables]
	[var]			[note]
---------------------------------------------
	_pi			pi
	_e			e
	_phi			sqrt(5)+1/2

	_debug 		whether print _debug info
	_precision		set precision for output
	<still precision is limited by double type>

	_type_strict		1:	<default>
		reject non-integer values 
		for integer-defined operations
				0:
		auto-truncate non-integer values 
			if needed

	_var_strict		0:
			no prompt even if undefined 
		variables involved
				1:	<default>
			prompt if undefined variables
		encountered but auto evaluated it to 0
				2:
			raise error if undefined 
		variables encountered
-----------------------------------------------

