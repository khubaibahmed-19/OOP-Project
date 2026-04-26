#include"customer.h"
#include<iostream>
customer::customer(string cnic, string name, string password, string r, string g, string c, string n):user(cnic, name, password){
    role=r;
    gender=g;
    city=c;
    number=n;
}
int customer::showMenu(){
    int choice;
    cout<<"Welcome : "<<getName()<<endl;
    cout<<"Sessions Completed : "<<sessionCount<<endl;
    cout<<"------------------------------------------"<<endl;
    cout<<"1) Browse Filter Catalog"<<endl;
    cout<<"2) Load Image"<<endl;
    cout<<"3) Build Filter Pipeline"<<endl;
    cout<<"4) Apply Pipeline and save "<<endl;
    cout<<"5) View my session history"<<endl;
    cout<<"6) Logout"<<endl;
    cin>>choice;
    return choice;
}
string customer::getRole(){
    return role;
}
void customer::BuildPipeline(){
    cout << "Available Filters:" << endl;
    cout << "01 Grayscale          [Pixel Transform]  Enabled" << endl;
    cout << "02 Invert             [Pixel Transform]  Enabled" << endl;
    cout << "03 Brightness Adjust  [Pixel Transform]  Enabled" << endl;
    cout << "04 Contrast Stretch   [Pixel Transform]  Enabled" << endl;
    cout << "05 Red Channel Only   [Pixel Transform]  Enabled" << endl;
    cout << "06 Green Channel Only [Pixel Transform]  Enabled" << endl;
    cout << "07 Blue Channel Only  [Pixel Transform]  Enabled" << endl;
    cout << "08 Box Blur (3x3)     [Spatial Filter]   Enabled" << endl;
    cout << "09 Flip Horizontal    [Geometric]        Enabled" << endl;
    cout << "10 Flip Vertical      [Geometric]        Enabled" << endl;
    cout << "" << endl;
    cout << "Enter filter ID to add (0 to finish): ";
}

