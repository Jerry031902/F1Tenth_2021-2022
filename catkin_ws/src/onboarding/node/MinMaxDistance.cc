// Include the ros library
#include <ros/ros.h> 
#include <onboarding/PointDist.h>
#include <sensor_msgs/LaserScan.h>
// (todo) Include the LaserScan message header from the sensor_msgs library

class ScanDist
{
private:
    ros::NodeHandle n;
    ros::Subscriber scanSub;
    ros::Publisher minPub, maxPub;

    PointDist minPoint, maxPoint;

public:
    // Class constructor
    ScanDist()
    {
        n = ros::NodeHandle("~");
        scanSub = n.subscribe("/scan",1,scan_cb);
        // (todo) Initialize the scanSub and subscribe to 
        // the topic "/scan" with a buffer size of 1
        // using the callback scan_cb
        minPub = n.advertise<onboarding::PointerDist> ("/min_point",1);
        // (todo) Initialize the minPub publisher to publish on the "/min_point" 
        // topic and with the message type of onboarding::PointDist with a 
        // queue size of 1
        maxPub = n.advertise<onboarding::PointerDist> ("/max_point",1);
        // (todo) Initialize the maxPub publisher to publish on the "/max_point"
        // topic and with the message type of onboarding::PointDist with a 
        // queue size of 1
    }

    void scan_cb(const sensor_msgs::LaserScan &msg)
    {
        float minRange = msg->ranges[0];
        float maxRange = msg->ranges[0];
        float minAngle, maxAngle;
        int minCount = -1;
        int maxCount = -1;
        for(int i = 1; i < msg->ranges.size(); i++)
        {
            if(msg->ranges[i] < minRange)
            {
                minRange = msg->ranges[i];
            }
            if(msg->range[i] > maxRange)
            {
                maxRange = msg->ranges[i];
            }
        }
        for(int i = 1; i < msg->ranges.size(); i++)
        {
            if(minCount && maxCount != -1)
            {
                break;
            }
            if(msg->ranges[i] == minRange)
            {
                minCount = i;
            }
            if(msg->ranges[i] == maxRange)
            {
                maxCount = i;
            }
        }
        minAngle = minRange + minCount*msg->angle_increment;
        maxAngle = maxRange + maxCount*msg->angle_increment
        minPoint.distance = minRange;
        minPOint.angle = minAngle;
        // (todo) Find the min value and it's angle
        // Save it to the pre-declared minPoint variable.

        maxPoint.distance = maxRange;
        maxPoint.angle = maxAngle;
        // (todo) Find the max value and it's angle
        // Save it to the pre-declared maxPoint variable.
        minPub.publish(minPoint);
        maxPub.publish(maxPoint);
        //ROSINFO?
        // (todo) Publish those values to their respective
        // publishers

    }
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "MinMaxDistance_Node")
    // (todo) Initialized this file as a ros node (?)
    ScanDist sd;
    ros::spin();
    return 0;
}   
