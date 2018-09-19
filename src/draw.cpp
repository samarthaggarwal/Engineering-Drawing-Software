#include <math.h>
#include <QtCore>
#include <QtGui>
#include <fstream>
#include <iostream>

#define PI 3.1415926536
#include "../lib/Vertex.cpp"
#include "TwoToThree.cpp"
#include "ThreeToTwo.cpp"

using namespace std;
using namespace Qt;

int main(int argc, char *argv[])
{

   bool first=true;
   int choice;
   bool choice2to3=true;
   bool choice3to2=true;
   float a ; float b ; float c ;
   float a1; float b1; float c1;
   float a2; float b2; float c2;
   float r_x=0.0, r_y=0.0;
   string d3_inFile, d2_inFile_xy, d2_inFile_yz, d2_inFile_zx; // Input Files

   while(true){

      /*  Three_To_Two Starts */

      if(first){

      d3_inFile = "./test/input/ThreeToTwo/in.txt";
      d2_inFile_xy = "./test/input/TwoToThree/xy.txt";
      d2_inFile_yz = "./test/input/TwoToThree/yz.txt";
      d2_inFile_zx = "./test/input/TwoToThree/zx.txt";

      int ask;
      cout << "To use default files PRESS 1 else PRESS ANYKEY" << endl;
      cin >> ask;

      if (ask!=1){
         int ask2;
         cout << "For 3D to 2D PRESS 1" << endl;
         cout << "For 2D to 3D PRESS 2" << endl;
         cout << "For Both PRESS 3" << endl;
         cout << "Default : Both" << endl;
         cin >> ask2;

         if(ask2==1){
            choice3to2 = true;
            choice2to3 = false;
         }
         else if(ask2==2){
            choice3to2 = false;
            choice2to3 = true;
         }
         else{
            choice3to2 = true;
            choice2to3 = true;
         }

         string tempss;

         if (choice3to2==true){

            cout << "Enter the absolute path of 3D input File (without spaces) :" << endl;
            cout << "(default: ./test/input/ThreeToTwo/in.txt ) -> 0 and ENTER" << endl;
            tempss = "";
            cin >> tempss;
            if(tempss.compare("0")){
               d3_inFile = tempss;
               // cout << "Yes" << tempss;
            } 
            // else {
            //    cout << "No" << tempss;
            // }

         }


         if(choice2to3==true){

            cout << "Enter the absolute path of XY 2D input File (without spaces) :" << endl;
            cout << "(default: ./test/input/TwoToThree/xy.txt ) -> 0 and ENTER" << endl;
            tempss = "";
            cin >> tempss;
            if(tempss.compare("0")){
               d2_inFile_xy = tempss;
               // cout << "Yes" << tempss;
            }

            cout << "Enter the absolute path of YZ 2D input File (without spaces) :" << endl;
            cout << "(default: ./test/input/TwoToThree/yz.txt ) -> 0 and ENTER" << endl;
            tempss = "";
            cin >> tempss;
            if(tempss.compare("0")){
               d2_inFile_yz = tempss;
               // cout << "Yes" << tempss;
            }

            cout << "Enter the absolute path of ZX 2D input File (without spaces) :" << endl;
            cout << "(default: ./test/input/TwoToThree/zx.txt ) -> 0 and ENTER" << endl;
            tempss = "";
            cin >> tempss;
            if(tempss.compare("0")){
               d2_inFile_zx = tempss;
               // cout << "Yes" << tempss;
            }

         }
      }

      if(choice3to2==true){
         // choice;
         a = 1.0; b = 0.0; c = 0.0;
         a1= 0.0; b1= 1.0; c1= 0.0;
         a2= 0.0; b2= 0.0; c2= 1.0;

         // Choice for user for input

         cout << "1. Normal Orthographic Projections :" << endl;
         cout << "2. Specify normal vector (new z-axis) only :" << endl;
         cout << "3. Specify all new axes vectors :" << endl << endl;
         cout << "Enter 1, 2 or 3 :" << endl << endl;
         cin >> choice;

         if(choice==1){
            a = 1.0; b = 0.0; c = 0.0;
            a1= 0.0; b1= 1.0; c1= 0.0;
            a2= 0.0; b2= 0.0; c2= 1.0;
         }
         else if (choice==2){
            cout << "Enter the coefficients of normal vector of the plane :" << endl;
            cout << "Enter 'a' (coefficients of i):" << endl;
            cin >> a;
            cout << "Enter 'b' (coefficients of j):" << endl;
            cin >> b;
            cout << "Enter 'c' (coefficients of k):" << endl;
            cin >> c;

            //a*a1 + b*b1 + c*c1 = 0
            if(c!=0){
               a1 = 1.0; b1 = 0.0; c1 = (-1)*(a*a1 + b*b1)/c;
               a2 = 0.0; b2 = 1.0; c2 = (-1)*(a*a2 + b*b2)/c;
            } else if(a!=0){
               b1 = 1.0; c1 = 0.0; a1 = (-1)*(b*b1 + c*c1)/a;
               b2 = 0.0; c2 = 1.0; a2 = (-1)*(b*b2 + c*c2)/a;
            } else if(b!=0){
               c1 = 1.0; a1 = 0.0; b1 = (-1)*(a*a1 + c*c1)/b;
               c2 = 0.0; a2 = 1.0; b2 = (-1)*(a*a2 + c*c2)/b;
            }

         } else if (choice==3){
            cout << "Enter the coefficients of z-axis of the plane :" << endl;
            cout << "Enter 'a_z' (coefficients of i):" << endl;
            cin >> a;
            cout << "Enter 'b_z' (coefficients of j):" << endl;
            cin >> b;
            cout << "Enter 'c_z' (coefficients of k):" << endl;
            cin >> c;

            cout << "Enter the coefficients of y-axis of the plane :" << endl;
            cout << "Enter 'a_y' (coefficients of i):" << endl;
            cin >> a1;
            cout << "Enter 'b_y' (coefficients of j):" << endl;
            cin >> b1;
            cout << "Enter 'c_y' (coefficients of k):" << endl;
            cin >> c1;

            cout << "Enter the coefficients of x-axis of the plane :" << endl;
            cout << "Enter 'a_x' (coefficients of i):" << endl;
            cin >> a2;
            cout << "Enter 'b_x' (coefficients of j):" << endl;
            cin >> b2;
            cout << "Enter 'c_x' (coefficients of k):" << endl;
            cin >> c2;

         } else {
            cout << "Invalid Choice";
            return 1;
         }

      }

      first=false;

      } else {

         // Rotation options

         if(choice3to2==true){

            cout << "Enter Type of Rotation :(Only available for orthographic projections) " << endl;
            cout << "0 : Left" << endl;
            cout << "1 : Right" << endl;
            cout << "2 : Up" << endl;
            cout << "3 : Down" << endl << endl;
            int rot=0;
            cin >> rot;
            if(rot==0){
               r_x=0.1;
            } else if(rot==1){
               r_x=-0.1;
            } else if(rot==2){
               r_y=0.1;
            } else if(rot==3){
               r_y=-0.1;
            } else {
               cout << "Invalid ! (Set to No rotation)" << endl;
            }

         }

      }

      // Proportional Change

      // a*=(1-r_x-r_y);
      // b*=(1+r_x);
      // c*=(1+r_y);

      // a1*=(1-r_x-r_y);
      // b1*=(1+r_x);
      // c1*=(1+r_y);

      // a2*=(1-r_x-r_y);
      // b2*=(1+r_x);
      // c2*=(1+r_y);

      // Absolute Change

      a-=(r_x+r_y);
      b+=(r_x);
      c+=(r_y);

      a1-=(r_x+r_y);
      b1+=(r_x);
      c1+=(r_y);

      a2-=(r_x+r_y);
      b2+=(r_x);
      c2+=(r_y);

      // Normalization

      float normal = sqrt(a*a + b*b + c*c);
      if(normal > 0){
         a /= normal;
         b /= normal;
         c /= normal;
      }

      normal = sqrt(a1*a1 + b1*b1 + c1*c1);
      if(normal > 0){
         a1 /= normal;
         b1 /= normal;
         c1 /= normal;
      }

      normal = sqrt(a2*a2 + b2*b2 + c2*c2);
      if(normal > 0){
         a2 /= normal;
         b2 /= normal;
         c2 /= normal;
      }

      // Input fot 3D to 2D

      if(choice3to2==true){

         Three_To_Two check1;
         check1.getInput(d3_inFile);
         check1.setPlane(a,b,c);
         check1.shift_origin(true,true);
         check1.scale(1,true,true);
         check1.project();
         check1.writeOutput("./test/output/ThreeToTwo/xy.txt");
         check1.plotOutput("./test/plot/ThreeToTwo/xy.txt");

         Three_To_Two check2;
         check2.getInput(d3_inFile);
         check2.setPlane(a1,b1,c1);
         check2.shift_origin(true,true);
         check2.scale(1,true,true);
         check2.project();
         check2.writeOutput("./test/output/ThreeToTwo/yz.txt");
         check2.plotOutput("./test/plot/ThreeToTwo/yz.txt");

         Three_To_Two check3;
         check3.getInput(d3_inFile);
         check3.setPlane(a2,b2,c2);
         check3.shift_origin(true,true);
         check3.scale(1,true,true);
         check3.project();
         check3.writeOutput("./test/output/ThreeToTwo/zx.txt");
         check3.plotOutput("./test/plot/ThreeToTwo/zx.txt");

      }

      /*  Three_To_Two Ends */





      /*  Two_To_Three Starts */

      if(choice2to3==true){
         Two_To_Three check;
         check.getInput(d2_inFile_xy,d2_inFile_yz,d2_inFile_zx);
         check.expand();
         // cout << check.exp_xy.size() << endl;
         check.eliminate();
         // cout << check.exp_xy.size() << endl;
         check.find_all();
         // cout << check.model["a"].label << " : " << check.model["a"].x << ", " << check.model["a"].y << ", " << check.model["a"].z << endl;
         // cout << check.model["e"].label << " : " << check.model["e"].x << ", " << check.model["e"].y << ", " << check.model["e"].z << endl;
         check.edges_all();
         // cout << check.edges.size() << endl;
         check.writeOutput("./test/output/TwoToThree/out3d.txt");
         check.plotOutput("./test/plot/TwoToThree/plot_3d.txt");
      }

      /*  Two_To_Three Ends */



      /* Qt Application Starts */


      QApplication app(argc, argv);
      QWidget *Main_Window = new QWidget;
      QLabel *l1 = new QLabel;
      QLabel *l2 = new QLabel;
      QLabel *l3 = new QLabel;
      QLabel *l4 = new QLabel;
      // l1.setGeometry(QRectF(10,10,30,80));

      QPushButton *button = new QPushButton;
      button->setText("Rotate");
      QObject::connect(button, SIGNAL(clicked()), &app, SLOT(quit()));

      l1->setStyleSheet("border: 2px solid black;");
      l1->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
      l2->setStyleSheet("border: 2px solid black;");
      l2->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
      l3->setStyleSheet("border: 2px solid black;");
      l3->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
      l4->setStyleSheet("border: 2px solid black;");
      l4->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
      // l1->setBorder(1);

      QPicture pi1, pi2, pi3, pi4;
      QPainter p1(&pi1);
      QPainter p2(&pi2);
      QPainter p3(&pi3);
      QPainter p4(&pi4);

      p1.setRenderHint(QPainter::Antialiasing);
      p1.setPen(QPen(Qt::black, 5, Qt::SolidLine, Qt::RoundCap));

      p2.setRenderHint(QPainter::Antialiasing);
      // p2.setPen(QPen(Qt::black, 5, Qt::SolidLine, Qt::RoundCap));

      p3.setRenderHint(QPainter::Antialiasing);
      // p3.setPen(QPen(Qt::black, 5, Qt::SolidLine, Qt::RoundCap));

      p4.setRenderHint(QPainter::Antialiasing);
      // p4.setPen(QPen(Qt::black, 5, Qt::SolidLine, Qt::RoundCap));

      int n=0, hidden;
      float n1,n2,n3,n4,n5,n6;
      ifstream inFile;
      
      /*  2D plotting Starts */

      if(choice3to2==true){

         // inFile.open("./test/plot/ThreeToTwo/plot.txt");
         inFile.open("./test/plot/ThreeToTwo/xy.txt");
         if (!inFile) {
             cout << "Unable to open xy file << endl << endl";
             exit(1); // terminate with error
         }

         n=0;
         inFile >> n;

         while(n>0){
            inFile >> n1;
            inFile >> n2;
            inFile >> n3;
            inFile >> n4;
            inFile >> hidden;
            if(hidden==1)
               p2.setPen(QPen(Qt::black, 5, Qt::DotLine, Qt::RoundCap));
            else
               p2.setPen(QPen(Qt::black, 5, Qt::SolidLine, Qt::RoundCap));
            p2.drawLine(n1, n2, n3, n4);
            n--;
         }
         inFile.close();

         inFile.open("./test/plot/ThreeToTwo/yz.txt");
         if (!inFile) {
             cout << "Unable to open yz file << endl << endl";
             exit(1); // terminate with error
         }

         n=0;
         inFile >> n;
         // cout<<n<<endl;

         while(n>0){
            inFile >> n1;
            inFile >> n2;
            inFile >> n3;
            inFile >> n4;
            inFile >> hidden;
            if(hidden==1)
               p3.setPen(QPen(Qt::black, 5, Qt::DotLine, Qt::RoundCap));
            else
               p3.setPen(QPen(Qt::black, 5, Qt::SolidLine, Qt::RoundCap));
            p3.drawLine(n1, n2, n3, n4);
            n--;
         }
         inFile.close();

         inFile.open("./test/plot/ThreeToTwo/zx.txt");
         if (!inFile) {
             cout << "Unable to open zx file << endl << endl";
             exit(1); // terminate with error
         }

         n=0;
         inFile >> n;

         while(n>0){
            inFile >> n1;
            inFile >> n2;
            inFile >> n3;
            inFile >> n4;
            inFile >> hidden;
            if(hidden==1)
               p4.setPen(QPen(Qt::black, 5, Qt::DotLine, Qt::RoundCap));
            else
               p4.setPen(QPen(Qt::black, 5, Qt::SolidLine, Qt::RoundCap));
            p4.drawLine(n1, n2, n3, n4);
            n--;
         }
         inFile.close();

      }


      /*  2D plotting Ends */

      /*  3D plotting Starts */

      if(choice2to3==true){

         inFile.open("./test/plot/TwoToThree/plot_3d.txt");
         if (!inFile) {
             cout << "Unable to open 3D file << endl << endl";
             exit(1); // terminate with error
         }

         n=0;
         inFile >> n;

         while(n>0){
            inFile >> n1;
            inFile >> n2;
            inFile >> n3;
            inFile >> n4;
            inFile >> n5;
            inFile >> n6;
            float x1 = (n1*cos(30*PI/180)+n2); 
            float y1 = (n3-n1*(sin(30*PI/180)));
            float x2 = (n4*cos(30*PI/180)+n5); 
            float y2 = (n6-n4*(sin(30*PI/180)));
            // cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
            p1.drawLine(x1,y1,x2,y2);
            n--;
         }

      }

      /*  3D plotting Ends */

      p1.end(); // Don't forget this line!
      p2.end(); // Don't forget this line!
      p3.end(); // Don't forget this line!
      p4.end(); // Don't forget this line!

      l1->setPicture(pi1);
      l2->setPicture(pi2);
      l3->setPicture(pi3);
      l4->setPicture(pi4);

      l1->setFixedSize(400,300);
      l2->setFixedSize(400,300);
      l3->setFixedSize(400,300);
      l4->setFixedSize(400,300);

      QGridLayout *layout = new QGridLayout;
      layout->addWidget(l1, 0, 0);
      layout->addWidget(l2, 0, 1);
      layout->addWidget(l3, 1, 0);
      layout->addWidget(l4, 1, 1);
      layout->addWidget(button, 2, 0, 2, 2);

      Main_Window->setLayout(layout);

      Main_Window->show();
      app.exec();

   }
}
