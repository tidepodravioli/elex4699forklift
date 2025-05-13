#include "../headers/AutoForkTest.hpp"

AutoForkTest::AutoForkTest()
{   

}

void AutoForkTest::start()
{
    RPiCamera m_camera(0, CAP_DSHOW);
    RCoordinateHelper m_helper(1, true);

    RAutoFork m_fork(m_camera, m_helper);
    while(true)
    {
        m_fork.dock();
    }
}
