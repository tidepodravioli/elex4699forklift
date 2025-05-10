#include "../headers/AutoPilotTest.hpp"

AutoPilotTest::AutoPilotTest()
{
    gpioInitialise();
    cout << "Gpio initialized" << endl;
    
}

void AutoPilotTest::start()
{
    RMotorDriver driver(MOTOR_L1, MOTOR_L2, MOTOR_R1, MOTOR_R2);
    
    RCoordinateHelper helper(1, true);
    helper.connect_socket(IP_ADDR, PORT);
    this_thread::sleep_for(chrono::milliseconds(100));
    helper.startFrameGetter();

    /* while(true)
    {
      helper.refreshRobot();
      cout << "Robot at : " << helper.getRobotCoords() << endl;
    } */
    
    RAutoPilot pilot(driver, helper);

    while(true)
    {
        helper.refreshRobot();
        cout << "Robot at : " << helper.getRobotCoords() << endl;

        cout << "Enter coordinates : ";
        string command;
        while(!raf_cin::get_data(&command, regex("^\\d{1,3} \\d{1,3}$")))
        {
            cout << "Enter valid coordinates : ";
        }

        vector<string> parts = delimitString(command, ' ');
        Point2i point(stoi(parts[0]), stoi(parts[1]));

        cout << "Heading to " << point << endl;
        cout << "In transit..." << endl;
        pilot.driveToPoint(point);
        cout << "At destination!" << endl;
    }
}

vector<string> AutoPilotTest::delimitString(std::string input, char delimiter)
{
    vector<string> parts;
    string builder = "";
    for(int charPosition = 0; charPosition < input.size(); charPosition++)
    {
      if(charPosition == input.size() - 1)
        builder += input.at(charPosition); 

      if(input.at(charPosition) == delimiter || charPosition == input.size() - 1) 
      {
        parts.push_back(builder);
        builder = "";
      }
      else builder += input.at(charPosition);
    }

    return parts;
}
