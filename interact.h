
int print_welcome(){
    cout<<"this is a calculator by phoeagon"<<endl;
    cout<<" enter '?' for help, '#' to exit "<<endl;
}
int print_help(){
    cout<<"calculator help"<<endl;
    cout<<"eg:\n";
    cout<<">1+2\n3\n>(1+3)/3+4*4\n16.75\n";
    cout<<"[other operators: +-*/%]\n";
    cout<<"use brackets '()' to change priority";
    cout<<"[define a variable]\n a : 2+4\n  [all uninitialized variables equal 0]\n"<<flush;
    cout<<"[    and will cause a warning by default]";
    cout<<"[to exit] '#' "<<endl;
    cout<<"[ warning messages, set '_debug' to 0/1 will do.] _debug : 0\n"<<endl;
}
