#include <math.h>
#include <fstream>
#include <iostream>

#include <GL/glut.h>
#define PI 3.1415926536
#include "../lib/Vertex.cpp"
#include "TwoToThree.cpp"
#include "ThreeToTwo.cpp"

using namespace std;

/*Global variables*/

   bool first=true;
   int choice;
   bool choice2to3=true;
   bool choice3to2=true;
   float a ; float b ; float c ;
   float a1; float b1; float c1;
   float a2; float b2; float c2;
   float r_x=0.0, r_y=0.0;
   string d3_inFile, d2_inFile_xy, d2_inFile_yz, d2_inFile_zx; // Input Files

   int main_window, sub_window1, sub_window2, sub_window3, sub_window4;

void update()
{

   // while(true){

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
            return;
         }

      }

      first=false;

      } 

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

}


int ang=30;
 
/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */


void idle_fn(){
   int currentWindow = glutGetWindow();
   glutSetWindow(main_window);
   glutPostRedisplay();
   glutSetWindow(sub_window1);
   glutPostRedisplay();
   glutSetWindow(sub_window2);
   glutPostRedisplay();
   glutSetWindow(sub_window3);
   glutPostRedisplay();
   glutSetWindow(sub_window4);
   glutPostRedisplay();
   glutSetWindow(currentWindow); 
}


void display() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer
   // int ang = 30;

         int n=0;
         float n1,n2,n3,n4,n5,n6;
         ifstream inFile;


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
            // float x1 = (n1*cos(30*PI/180)+n2)-50.0; 
            // float y1 = (n3-n1*(sin(30*PI/180)))-50.0;
            // float x2 = (n4*cos(30*PI/180)+n5)-50.0; 
            // float y2 = (n6-n4*(sin(30*PI/180)))-50.0;
            float x1 = (n1*cos(ang*PI/180)+n2*sin((60+ang)*PI/180))-70.0; 
            float y1 = (n3*cos((30-ang)*PI/180)-n1*(sin(ang*PI/180)))-70.0;
            float x2 = (n4*cos(ang*PI/180)+n5*sin((60+ang)*PI/180))-70.0; 
            float y2 = (n6*cos((30-ang)*PI/180)-n4*(sin(ang*PI/180)))-70.0;
            glBegin(GL_LINES);
               // glVertex2f(x1/100.0, y1/100.0);
               // glVertex2f(x2/100.0, y2/100.0);
               glVertex2f(x1/150.0, y1/150.0);
               glVertex2f(x2/150.0, y2/150.0);
            glEnd();
            n--;
         }



 
   glFlush();  // Render now
}

void display1() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer
   // int ang = 30;

         int n=0, hidden;
         float n1,n2,n3,n4;
         ifstream inFile;


         inFile.open("./test/plot/ThreeToTwo/xy.txt");
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
            inFile >> hidden;
            if(hidden==0){
               glBegin(GL_LINES);
                  glVertex2f(n1/100.0, n2/100.0);
                  glVertex2f(n3/100.0, n4/100.0);
               glEnd();
            }
            else {
               glPushAttrib(GL_ENABLE_BIT); 
               // glPushAttrib is done to return everything to normal after drawing

               glLineStipple(1, 0x1111);  //[1]
               glEnable(GL_LINE_STIPPLE);
               glBegin(GL_LINES);
                  glVertex2f(n1/100.0, n2/100.0);
                  glVertex2f(n3/100.0, n4/100.0);
               glEnd();

               glPopAttrib();
            }
            n--;
         }
   glFlush();  // Render now
}

void display2() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer
   // int ang = 30;

         int n=0, hidden;
         float n1,n2,n3,n4;
         ifstream inFile;


         inFile.open("./test/plot/ThreeToTwo/yz.txt");
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
            inFile >> hidden;
            if(hidden==0){
               glBegin(GL_LINES);
                  glVertex2f(n1/100.0, n2/100.0);
                  glVertex2f(n3/100.0, n4/100.0);
               glEnd();
            }
            else {
               glPushAttrib(GL_ENABLE_BIT); 
               // glPushAttrib is done to return everything to normal after drawing

               glLineStipple(1, 0x1111);  //[1]
               glEnable(GL_LINE_STIPPLE);
               glBegin(GL_LINES);
                  glVertex2f(n1/100.0, n2/100.0);
                  glVertex2f(n3/100.0, n4/100.0);
               glEnd();

               glPopAttrib();
            }
            n--;
         }
   glFlush();  // Render now
}

void display3() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer
   // int ang = 30;

         int n=0, hidden;
         float n1,n2,n3,n4;
         ifstream inFile;


         inFile.open("./test/plot/ThreeToTwo/zx.txt");
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
            inFile >> hidden;
            if(hidden==0){
               glBegin(GL_LINES);
                  glVertex2f(n1/100.0, n2/100.0);
                  glVertex2f(n3/100.0, n4/100.0);
               glEnd();
            }
            else {
               glPushAttrib(GL_ENABLE_BIT); 
               // glPushAttrib is done to return everything to normal after drawing

               glLineStipple(1, 0x1111);  //[1]
               glEnable(GL_LINE_STIPPLE);
               glBegin(GL_LINES);
                  glVertex2f(n1/100.0, n2/100.0);
                  glVertex2f(n3/100.0, n4/100.0);
               glEnd();

               glPopAttrib();
            }            n--;
         }
   glFlush();  // Render now
}

void Special_Keys (int key, int x, int y)
{
    switch (key) {
 
       case GLUT_KEY_LEFT :  r_x=-0.1;r_y= 0.0;  break;
       case GLUT_KEY_RIGHT:  r_x= 0.1;r_y= 0.0;  break;
       case GLUT_KEY_UP   :  r_x= 0.0;r_y= 0.1;  break;
       case GLUT_KEY_DOWN :  r_x= 0.0;r_y=-0.1;  break;
       case GLUT_KEY_PAGE_UP : ang+=5;r_x= 0.0;r_y= 0.0; break;
       case GLUT_KEY_PAGE_DOWN : ang-=5;r_x= 0.0;r_y= 0.0; break;
 
       // default: printf ("   Special key %c == %d\n", key, key);
    }

    update();

    display();
    display1();
    display2();
    display3();
 
    glutPostRedisplay();
}
 
/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
   update();
   glutInit(&argc, argv);                 // Initialize GLUT
   glutInitWindowSize(670, 670);   // Set the window's initial width & height
   glutInitWindowPosition(0, 0); // Position the window's initial top-left corner
   main_window = glutCreateWindow("COP290"); // Create a window with the given title
   
   sub_window1 = glutCreateSubWindow(main_window,10,10,320,320);
   if(choice2to3==true)
      glutDisplayFunc(display); // Register display callback handler for window re-paint
   glutSpecialFunc  (Special_Keys);
   // glutIdleFunc(idle_fn);

   sub_window2 = glutCreateSubWindow(main_window,340,10,320,320);
   if(choice3to2==true)
      glutDisplayFunc(display1); // Register display callback handler for window re-paint
   glutSpecialFunc  (Special_Keys);
   // glutIdleFunc(idle_fn);

   sub_window3 = glutCreateSubWindow(main_window,10,340,320,320);
   if(choice3to2==true)
      glutDisplayFunc(display2); // Register display callback handler for window re-paint
   glutSpecialFunc  (Special_Keys);
   // glutIdleFunc(idle_fn);

   sub_window4 = glutCreateSubWindow(main_window,340,340,320,320);
   if(choice3to2==true)
      glutDisplayFunc(display3); // Register display callback handler for window re-paint
   glutSpecialFunc  (Special_Keys);
   // glutIdleFunc(idle_fn);

   glutIdleFunc(idle_fn);


   glutMainLoop();           // Enter the infinitely event-processing loop
   return 0;
}