#include "../headers/RPiForklift.hpp"

void RPiForklift::writePosition(LIFT_POSITION position)
{
    switch(position)
    {
        case FLOOR:
            write(FLOOR_POSITION);
        break;

        case UP:
            write(UP_POSITION);
        break;

        case DOWN2:
            write(DOWN_POSITION);
        break;

        case UP2:
            write(UP2_POSITION);
        break;
    }
}