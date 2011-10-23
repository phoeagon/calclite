
int print_welcome(){
    cout<<"this is a calculator by phoeagon"<<endl;
    cout<<" enter '?' for help, '#' to exit "<<endl;
}
int print_help(){
    cout<<"calculator help"<<endl;
    cout<<"eg:\n";
    cout<<">1+2\n3\n>(1+3)/3+4*4\n16.75\n>2+2^3*3!^2\n290\n";
    cout<<"[other operators: +-*/%^!]\n";
    cout<<"use brackets '()' to change priority, |x| to get absolute value of x.\n";
    cout<<"[note that '5*-2' is not allowed ]\n";
    cout<<"[bigger,smaller,equal : > , < , ~ ]\n";
    cout<<"[define a variable]\n>a : 2+4\n6\n  [all uninitialized variables equal 0]\n"<<flush;
    cout<<"[    and will cause a warning by default]\n";
    cout<<"[system variable: _pi, _e, _phi ]\n//you can edit them but it's not recommended!\n";
    cout<<"[environment variable: _debug, _warning] either 0 or 1\n";
    cout<<"Priority & associativity:\n   (low) assign[R], ><~[L], +-[L], */%[L], ^[R] , ![L] , ()||[L] (High) \n";
    cout<<" [set precision:] _precision : 5\n";
    cout<<"[to exit] '#' "<<endl;

    cout<<endl;
}
