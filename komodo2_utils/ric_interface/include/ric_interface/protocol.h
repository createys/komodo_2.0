#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>

namespace ric
{
    namespace protocol
    {
        enum class Type
        {
            KEEP_ALIVE = 100,
            LOGGER = 101,
            ULTRASONIC = 102,
            IMU = 103,
            GPS = 104,
            ERROR = 105
        };

        enum class ErrCode
        {
            INIT = 50,
            READ = 51,
            CALIB = 52
        };

        const uint16_t MAX_PKG_SIZE = 512;
        const uint8_t HEADER_CODE = 200;
        const uint8_t HEADER_INDX = 0;
        const uint8_t PKG_SIZE_INDX = 1;

        struct package
        {
            uint8_t type = 0;
            uint8_t id = 0;
        };

        struct keepalive : package
        {
            keepalive() { type = (uint8_t)Type::KEEP_ALIVE; }
        };

        struct logger : package
        {
            logger() { type = (uint8_t)Type::LOGGER; }
            char msg[30];
            int32_t value = 0;
        };

        struct error : package
        {
            uint8_t code = 0; //error code
            uint8_t comp_type = 0; //reporting component type
            uint8_t comp_id = 0; //reporting component id
            error() { type = (uint8_t)Type::ERROR; }
        };

        struct sensor : package
        {

        };

        struct actuator : package
        {
        };


        struct ultrasonic : sensor
        {
            ultrasonic() { type = (uint8_t)Type::ULTRASONIC; }
            uint16_t distance_mm = 0;

            const static uint8_t ID_RIGHT = 1;
            const static uint8_t ID_REAR = 2;
            const static uint8_t ID_LEFT = 3;
        };

        struct imu : sensor
        {
            imu() { type = (uint8_t)Type::IMU; }
            float roll_rad = 0,
                    pitch_rad = 0,
                    yaw_rad = 0,
                    accl_x_rad = 0,
                    accl_y_rad = 0,
                    accl_z_rad = 0,
                    gyro_x_rad = 0,
                    gyro_y_rad = 0,
                    gyro_z_rad = 0,
                    mag_x_rad = 0,
                    mag_y_rad = 0,
                    mag_z_rad = 0;
        };

        struct gps : sensor
        {
            gps() { type = (uint8_t)Type::GPS; }
            double lat = 0, lon = 0;
            float alt = 0;
            float speed = 0;
            float heading = 0;
            float satellites = 0;
            uint8_t date_time = 0; //UTC hundredths of a second
        };
    }
}



#endif //PROTOCOL_H