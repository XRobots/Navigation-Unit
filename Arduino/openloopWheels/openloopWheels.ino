// ** open loop - cmd_vel only

#include "ros.h"
#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>
#include <ros/time.h>

ros::NodeHandle nh;


float wheel1;
float wheel2;

float wheel1a;
float wheel2a;

float demandx;
float demandz;

float speed_act_left; // actual left wheel speed in m/s
float speed_act_right; // actual right wheel speed in m/s

unsigned long currentMillis;
unsigned long previousMillis;
int loopTime = 10;

// wheel encoder interrupts

#define encoder0PinA 2      // encoder 1
#define encoder0PinB 3

#define encoder1PinA 18     // encoder 2
#define encoder1PinB 19

volatile long encoder0Pos = 0;    // encoder 1
volatile long encoder1Pos = 0;    // encoder 2


// ** ROS callback & subscriber **

void velCallback(  const geometry_msgs::Twist& vel)
{
     demandx = vel.linear.x;
     demandz = vel.angular.z;

     demandx = constrain(demandx,-1,1);     // try to keep it under control
     demandz = constrain(demandz,-1,1);

     demandx = demandx * 350;
     demandz = demandz * 75;
}

ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel" , velCallback);     //create a subscriber for ROS cmd_vel topic

// ** Setup **
                        
void setup() {  

  nh.initNode();              // init ROS
  nh.subscribe(sub);          // subscribe to cmd_vel

  pinMode(4, OUTPUT);     // motor PWM pins
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);


  //Serial.begin(115200);
}

void loop() {

     nh.spinOnce();        // make sure we listen for ROS messages and activate the callback if there is one

     currentMillis = millis();  

     if (currentMillis - previousMillis >= loopTime) {  // start timed loop for everything else
         previousMillis = currentMillis;

        // work out the two values for differential drive of each wheel

        wheel1 = demandx - (demandz);
        wheel2 = demandx + (demandz);

        wheel1 = constrain(wheel1,-255,255);
        wheel2 = constrain(wheel2,-255,255);

      
        // drive motors


        if (wheel1 > 0) {
          wheel1a = abs(wheel1);
          analogWrite(6, wheel1a);
          analogWrite(7, 0);
        }
        else if (wheel1 < 0) {
          wheel1a = abs(wheel1);
          analogWrite(7, wheel1a);
          analogWrite(6, 0);
        }
        else {
          analogWrite(7,0);
          analogWrite(6, 0);
        }

        // other motor

        if (wheel2 > 0) {
          wheel2a = abs(wheel2);
          analogWrite(5, wheel2a);
          analogWrite(4, 0);
        }
        else if (wheel2 < -0) {
          wheel2a = abs(wheel2);
          analogWrite(4, wheel2a);
          analogWrite(5, 0);
        }
        else {
          analogWrite(4, 0);
          analogWrite(5, 0);
        }


     } // end of timed loop    
   
} // end of main loop




  
