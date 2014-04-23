// MESSAGE UNIBO_PARAMETERS PACKING

#define MAVLINK_MSG_ID_UNIBO_PARAMETERS 201

typedef struct __mavlink_unibo_parameters_t
{
 float Offset_T; ///< 
 float lat_mode; ///< 
 float delta; ///< 
 float K1; ///< 
 float L1; ///< 
 float Ixy; ///< 
 float K2; ///< 
 float L2; ///< 
 float Iz; ///< 
 float KpAttX; ///< 
 float KpAttY; ///< 
 float KpAttZ; ///< 
 float KdAttX; ///< 
 float KdAttY; ///< 
 float KdAttZ; ///< 
 float KiAttX; ///< 
 float KiAttY; ///< 
 float KiAttZ; ///< 
 float GE; ///< 
 float epsilon; ///< 
 float XY_Multiplier; ///< 
 float offset_x; ///< 
 float offset_y; ///< 
 float offset_z; ///< 
} mavlink_unibo_parameters_t;

#define MAVLINK_MSG_ID_UNIBO_PARAMETERS_LEN 96
#define MAVLINK_MSG_ID_201_LEN 96

#define MAVLINK_MSG_ID_UNIBO_PARAMETERS_CRC 2
#define MAVLINK_MSG_ID_201_CRC 2



#define MAVLINK_MESSAGE_INFO_UNIBO_PARAMETERS { \
	"UNIBO_PARAMETERS", \
	24, \
	{  { "Offset_T", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_unibo_parameters_t, Offset_T) }, \
         { "lat_mode", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_unibo_parameters_t, lat_mode) }, \
         { "delta", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_unibo_parameters_t, delta) }, \
         { "K1", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_unibo_parameters_t, K1) }, \
         { "L1", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_unibo_parameters_t, L1) }, \
         { "Ixy", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_unibo_parameters_t, Ixy) }, \
         { "K2", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_unibo_parameters_t, K2) }, \
         { "L2", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_unibo_parameters_t, L2) }, \
         { "Iz", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_unibo_parameters_t, Iz) }, \
         { "KpAttX", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_unibo_parameters_t, KpAttX) }, \
         { "KpAttY", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_unibo_parameters_t, KpAttY) }, \
         { "KpAttZ", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_unibo_parameters_t, KpAttZ) }, \
         { "KdAttX", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_unibo_parameters_t, KdAttX) }, \
         { "KdAttY", NULL, MAVLINK_TYPE_FLOAT, 0, 52, offsetof(mavlink_unibo_parameters_t, KdAttY) }, \
         { "KdAttZ", NULL, MAVLINK_TYPE_FLOAT, 0, 56, offsetof(mavlink_unibo_parameters_t, KdAttZ) }, \
         { "KiAttX", NULL, MAVLINK_TYPE_FLOAT, 0, 60, offsetof(mavlink_unibo_parameters_t, KiAttX) }, \
         { "KiAttY", NULL, MAVLINK_TYPE_FLOAT, 0, 64, offsetof(mavlink_unibo_parameters_t, KiAttY) }, \
         { "KiAttZ", NULL, MAVLINK_TYPE_FLOAT, 0, 68, offsetof(mavlink_unibo_parameters_t, KiAttZ) }, \
         { "GE", NULL, MAVLINK_TYPE_FLOAT, 0, 72, offsetof(mavlink_unibo_parameters_t, GE) }, \
         { "epsilon", NULL, MAVLINK_TYPE_FLOAT, 0, 76, offsetof(mavlink_unibo_parameters_t, epsilon) }, \
         { "XY_Multiplier", NULL, MAVLINK_TYPE_FLOAT, 0, 80, offsetof(mavlink_unibo_parameters_t, XY_Multiplier) }, \
         { "offset_x", NULL, MAVLINK_TYPE_FLOAT, 0, 84, offsetof(mavlink_unibo_parameters_t, offset_x) }, \
         { "offset_y", NULL, MAVLINK_TYPE_FLOAT, 0, 88, offsetof(mavlink_unibo_parameters_t, offset_y) }, \
         { "offset_z", NULL, MAVLINK_TYPE_FLOAT, 0, 92, offsetof(mavlink_unibo_parameters_t, offset_z) }, \
         } \
}


/**
 * @brief Pack a unibo_parameters message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param Offset_T 
 * @param lat_mode 
 * @param delta 
 * @param K1 
 * @param L1 
 * @param Ixy 
 * @param K2 
 * @param L2 
 * @param Iz 
 * @param KpAttX 
 * @param KpAttY 
 * @param KpAttZ 
 * @param KdAttX 
 * @param KdAttY 
 * @param KdAttZ 
 * @param KiAttX 
 * @param KiAttY 
 * @param KiAttZ 
 * @param GE 
 * @param epsilon 
 * @param XY_Multiplier 
 * @param offset_x 
 * @param offset_y 
 * @param offset_z 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_unibo_parameters_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       float Offset_T, float lat_mode, float delta, float K1, float L1, float Ixy, float K2, float L2, float Iz, float KpAttX, float KpAttY, float KpAttZ, float KdAttX, float KdAttY, float KdAttZ, float KiAttX, float KiAttY, float KiAttZ, float GE, float epsilon, float XY_Multiplier, float offset_x, float offset_y, float offset_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_UNIBO_PARAMETERS_LEN];
	_mav_put_float(buf, 0, Offset_T);
	_mav_put_float(buf, 4, lat_mode);
	_mav_put_float(buf, 8, delta);
	_mav_put_float(buf, 12, K1);
	_mav_put_float(buf, 16, L1);
	_mav_put_float(buf, 20, Ixy);
	_mav_put_float(buf, 24, K2);
	_mav_put_float(buf, 28, L2);
	_mav_put_float(buf, 32, Iz);
	_mav_put_float(buf, 36, KpAttX);
	_mav_put_float(buf, 40, KpAttY);
	_mav_put_float(buf, 44, KpAttZ);
	_mav_put_float(buf, 48, KdAttX);
	_mav_put_float(buf, 52, KdAttY);
	_mav_put_float(buf, 56, KdAttZ);
	_mav_put_float(buf, 60, KiAttX);
	_mav_put_float(buf, 64, KiAttY);
	_mav_put_float(buf, 68, KiAttZ);
	_mav_put_float(buf, 72, GE);
	_mav_put_float(buf, 76, epsilon);
	_mav_put_float(buf, 80, XY_Multiplier);
	_mav_put_float(buf, 84, offset_x);
	_mav_put_float(buf, 88, offset_y);
	_mav_put_float(buf, 92, offset_z);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_UNIBO_PARAMETERS_LEN);
#else
	mavlink_unibo_parameters_t packet;
	packet.Offset_T = Offset_T;
	packet.lat_mode = lat_mode;
	packet.delta = delta;
	packet.K1 = K1;
	packet.L1 = L1;
	packet.Ixy = Ixy;
	packet.K2 = K2;
	packet.L2 = L2;
	packet.Iz = Iz;
	packet.KpAttX = KpAttX;
	packet.KpAttY = KpAttY;
	packet.KpAttZ = KpAttZ;
	packet.KdAttX = KdAttX;
	packet.KdAttY = KdAttY;
	packet.KdAttZ = KdAttZ;
	packet.KiAttX = KiAttX;
	packet.KiAttY = KiAttY;
	packet.KiAttZ = KiAttZ;
	packet.GE = GE;
	packet.epsilon = epsilon;
	packet.XY_Multiplier = XY_Multiplier;
	packet.offset_x = offset_x;
	packet.offset_y = offset_y;
	packet.offset_z = offset_z;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_UNIBO_PARAMETERS_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_UNIBO_PARAMETERS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_UNIBO_PARAMETERS_LEN, MAVLINK_MSG_ID_UNIBO_PARAMETERS_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_UNIBO_PARAMETERS_LEN);
#endif
}

/**
 * @brief Pack a unibo_parameters message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param Offset_T 
 * @param lat_mode 
 * @param delta 
 * @param K1 
 * @param L1 
 * @param Ixy 
 * @param K2 
 * @param L2 
 * @param Iz 
 * @param KpAttX 
 * @param KpAttY 
 * @param KpAttZ 
 * @param KdAttX 
 * @param KdAttY 
 * @param KdAttZ 
 * @param KiAttX 
 * @param KiAttY 
 * @param KiAttZ 
 * @param GE 
 * @param epsilon 
 * @param XY_Multiplier 
 * @param offset_x 
 * @param offset_y 
 * @param offset_z 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_unibo_parameters_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           float Offset_T,float lat_mode,float delta,float K1,float L1,float Ixy,float K2,float L2,float Iz,float KpAttX,float KpAttY,float KpAttZ,float KdAttX,float KdAttY,float KdAttZ,float KiAttX,float KiAttY,float KiAttZ,float GE,float epsilon,float XY_Multiplier,float offset_x,float offset_y,float offset_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_UNIBO_PARAMETERS_LEN];
	_mav_put_float(buf, 0, Offset_T);
	_mav_put_float(buf, 4, lat_mode);
	_mav_put_float(buf, 8, delta);
	_mav_put_float(buf, 12, K1);
	_mav_put_float(buf, 16, L1);
	_mav_put_float(buf, 20, Ixy);
	_mav_put_float(buf, 24, K2);
	_mav_put_float(buf, 28, L2);
	_mav_put_float(buf, 32, Iz);
	_mav_put_float(buf, 36, KpAttX);
	_mav_put_float(buf, 40, KpAttY);
	_mav_put_float(buf, 44, KpAttZ);
	_mav_put_float(buf, 48, KdAttX);
	_mav_put_float(buf, 52, KdAttY);
	_mav_put_float(buf, 56, KdAttZ);
	_mav_put_float(buf, 60, KiAttX);
	_mav_put_float(buf, 64, KiAttY);
	_mav_put_float(buf, 68, KiAttZ);
	_mav_put_float(buf, 72, GE);
	_mav_put_float(buf, 76, epsilon);
	_mav_put_float(buf, 80, XY_Multiplier);
	_mav_put_float(buf, 84, offset_x);
	_mav_put_float(buf, 88, offset_y);
	_mav_put_float(buf, 92, offset_z);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_UNIBO_PARAMETERS_LEN);
#else
	mavlink_unibo_parameters_t packet;
	packet.Offset_T = Offset_T;
	packet.lat_mode = lat_mode;
	packet.delta = delta;
	packet.K1 = K1;
	packet.L1 = L1;
	packet.Ixy = Ixy;
	packet.K2 = K2;
	packet.L2 = L2;
	packet.Iz = Iz;
	packet.KpAttX = KpAttX;
	packet.KpAttY = KpAttY;
	packet.KpAttZ = KpAttZ;
	packet.KdAttX = KdAttX;
	packet.KdAttY = KdAttY;
	packet.KdAttZ = KdAttZ;
	packet.KiAttX = KiAttX;
	packet.KiAttY = KiAttY;
	packet.KiAttZ = KiAttZ;
	packet.GE = GE;
	packet.epsilon = epsilon;
	packet.XY_Multiplier = XY_Multiplier;
	packet.offset_x = offset_x;
	packet.offset_y = offset_y;
	packet.offset_z = offset_z;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_UNIBO_PARAMETERS_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_UNIBO_PARAMETERS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_UNIBO_PARAMETERS_LEN, MAVLINK_MSG_ID_UNIBO_PARAMETERS_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_UNIBO_PARAMETERS_LEN);
#endif
}

/**
 * @brief Encode a unibo_parameters struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param unibo_parameters C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_unibo_parameters_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_unibo_parameters_t* unibo_parameters)
{
	return mavlink_msg_unibo_parameters_pack(system_id, component_id, msg, unibo_parameters->Offset_T, unibo_parameters->lat_mode, unibo_parameters->delta, unibo_parameters->K1, unibo_parameters->L1, unibo_parameters->Ixy, unibo_parameters->K2, unibo_parameters->L2, unibo_parameters->Iz, unibo_parameters->KpAttX, unibo_parameters->KpAttY, unibo_parameters->KpAttZ, unibo_parameters->KdAttX, unibo_parameters->KdAttY, unibo_parameters->KdAttZ, unibo_parameters->KiAttX, unibo_parameters->KiAttY, unibo_parameters->KiAttZ, unibo_parameters->GE, unibo_parameters->epsilon, unibo_parameters->XY_Multiplier, unibo_parameters->offset_x, unibo_parameters->offset_y, unibo_parameters->offset_z);
}

/**
 * @brief Encode a unibo_parameters struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param unibo_parameters C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_unibo_parameters_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_unibo_parameters_t* unibo_parameters)
{
	return mavlink_msg_unibo_parameters_pack_chan(system_id, component_id, chan, msg, unibo_parameters->Offset_T, unibo_parameters->lat_mode, unibo_parameters->delta, unibo_parameters->K1, unibo_parameters->L1, unibo_parameters->Ixy, unibo_parameters->K2, unibo_parameters->L2, unibo_parameters->Iz, unibo_parameters->KpAttX, unibo_parameters->KpAttY, unibo_parameters->KpAttZ, unibo_parameters->KdAttX, unibo_parameters->KdAttY, unibo_parameters->KdAttZ, unibo_parameters->KiAttX, unibo_parameters->KiAttY, unibo_parameters->KiAttZ, unibo_parameters->GE, unibo_parameters->epsilon, unibo_parameters->XY_Multiplier, unibo_parameters->offset_x, unibo_parameters->offset_y, unibo_parameters->offset_z);
}

/**
 * @brief Send a unibo_parameters message
 * @param chan MAVLink channel to send the message
 *
 * @param Offset_T 
 * @param lat_mode 
 * @param delta 
 * @param K1 
 * @param L1 
 * @param Ixy 
 * @param K2 
 * @param L2 
 * @param Iz 
 * @param KpAttX 
 * @param KpAttY 
 * @param KpAttZ 
 * @param KdAttX 
 * @param KdAttY 
 * @param KdAttZ 
 * @param KiAttX 
 * @param KiAttY 
 * @param KiAttZ 
 * @param GE 
 * @param epsilon 
 * @param XY_Multiplier 
 * @param offset_x 
 * @param offset_y 
 * @param offset_z 
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_unibo_parameters_send(mavlink_channel_t chan, float Offset_T, float lat_mode, float delta, float K1, float L1, float Ixy, float K2, float L2, float Iz, float KpAttX, float KpAttY, float KpAttZ, float KdAttX, float KdAttY, float KdAttZ, float KiAttX, float KiAttY, float KiAttZ, float GE, float epsilon, float XY_Multiplier, float offset_x, float offset_y, float offset_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_UNIBO_PARAMETERS_LEN];
	_mav_put_float(buf, 0, Offset_T);
	_mav_put_float(buf, 4, lat_mode);
	_mav_put_float(buf, 8, delta);
	_mav_put_float(buf, 12, K1);
	_mav_put_float(buf, 16, L1);
	_mav_put_float(buf, 20, Ixy);
	_mav_put_float(buf, 24, K2);
	_mav_put_float(buf, 28, L2);
	_mav_put_float(buf, 32, Iz);
	_mav_put_float(buf, 36, KpAttX);
	_mav_put_float(buf, 40, KpAttY);
	_mav_put_float(buf, 44, KpAttZ);
	_mav_put_float(buf, 48, KdAttX);
	_mav_put_float(buf, 52, KdAttY);
	_mav_put_float(buf, 56, KdAttZ);
	_mav_put_float(buf, 60, KiAttX);
	_mav_put_float(buf, 64, KiAttY);
	_mav_put_float(buf, 68, KiAttZ);
	_mav_put_float(buf, 72, GE);
	_mav_put_float(buf, 76, epsilon);
	_mav_put_float(buf, 80, XY_Multiplier);
	_mav_put_float(buf, 84, offset_x);
	_mav_put_float(buf, 88, offset_y);
	_mav_put_float(buf, 92, offset_z);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UNIBO_PARAMETERS, buf, MAVLINK_MSG_ID_UNIBO_PARAMETERS_LEN, MAVLINK_MSG_ID_UNIBO_PARAMETERS_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UNIBO_PARAMETERS, buf, MAVLINK_MSG_ID_UNIBO_PARAMETERS_LEN);
#endif
#else
	mavlink_unibo_parameters_t packet;
	packet.Offset_T = Offset_T;
	packet.lat_mode = lat_mode;
	packet.delta = delta;
	packet.K1 = K1;
	packet.L1 = L1;
	packet.Ixy = Ixy;
	packet.K2 = K2;
	packet.L2 = L2;
	packet.Iz = Iz;
	packet.KpAttX = KpAttX;
	packet.KpAttY = KpAttY;
	packet.KpAttZ = KpAttZ;
	packet.KdAttX = KdAttX;
	packet.KdAttY = KdAttY;
	packet.KdAttZ = KdAttZ;
	packet.KiAttX = KiAttX;
	packet.KiAttY = KiAttY;
	packet.KiAttZ = KiAttZ;
	packet.GE = GE;
	packet.epsilon = epsilon;
	packet.XY_Multiplier = XY_Multiplier;
	packet.offset_x = offset_x;
	packet.offset_y = offset_y;
	packet.offset_z = offset_z;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UNIBO_PARAMETERS, (const char *)&packet, MAVLINK_MSG_ID_UNIBO_PARAMETERS_LEN, MAVLINK_MSG_ID_UNIBO_PARAMETERS_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UNIBO_PARAMETERS, (const char *)&packet, MAVLINK_MSG_ID_UNIBO_PARAMETERS_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_UNIBO_PARAMETERS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_unibo_parameters_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float Offset_T, float lat_mode, float delta, float K1, float L1, float Ixy, float K2, float L2, float Iz, float KpAttX, float KpAttY, float KpAttZ, float KdAttX, float KdAttY, float KdAttZ, float KiAttX, float KiAttY, float KiAttZ, float GE, float epsilon, float XY_Multiplier, float offset_x, float offset_y, float offset_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_float(buf, 0, Offset_T);
	_mav_put_float(buf, 4, lat_mode);
	_mav_put_float(buf, 8, delta);
	_mav_put_float(buf, 12, K1);
	_mav_put_float(buf, 16, L1);
	_mav_put_float(buf, 20, Ixy);
	_mav_put_float(buf, 24, K2);
	_mav_put_float(buf, 28, L2);
	_mav_put_float(buf, 32, Iz);
	_mav_put_float(buf, 36, KpAttX);
	_mav_put_float(buf, 40, KpAttY);
	_mav_put_float(buf, 44, KpAttZ);
	_mav_put_float(buf, 48, KdAttX);
	_mav_put_float(buf, 52, KdAttY);
	_mav_put_float(buf, 56, KdAttZ);
	_mav_put_float(buf, 60, KiAttX);
	_mav_put_float(buf, 64, KiAttY);
	_mav_put_float(buf, 68, KiAttZ);
	_mav_put_float(buf, 72, GE);
	_mav_put_float(buf, 76, epsilon);
	_mav_put_float(buf, 80, XY_Multiplier);
	_mav_put_float(buf, 84, offset_x);
	_mav_put_float(buf, 88, offset_y);
	_mav_put_float(buf, 92, offset_z);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UNIBO_PARAMETERS, buf, MAVLINK_MSG_ID_UNIBO_PARAMETERS_LEN, MAVLINK_MSG_ID_UNIBO_PARAMETERS_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UNIBO_PARAMETERS, buf, MAVLINK_MSG_ID_UNIBO_PARAMETERS_LEN);
#endif
#else
	mavlink_unibo_parameters_t *packet = (mavlink_unibo_parameters_t *)msgbuf;
	packet->Offset_T = Offset_T;
	packet->lat_mode = lat_mode;
	packet->delta = delta;
	packet->K1 = K1;
	packet->L1 = L1;
	packet->Ixy = Ixy;
	packet->K2 = K2;
	packet->L2 = L2;
	packet->Iz = Iz;
	packet->KpAttX = KpAttX;
	packet->KpAttY = KpAttY;
	packet->KpAttZ = KpAttZ;
	packet->KdAttX = KdAttX;
	packet->KdAttY = KdAttY;
	packet->KdAttZ = KdAttZ;
	packet->KiAttX = KiAttX;
	packet->KiAttY = KiAttY;
	packet->KiAttZ = KiAttZ;
	packet->GE = GE;
	packet->epsilon = epsilon;
	packet->XY_Multiplier = XY_Multiplier;
	packet->offset_x = offset_x;
	packet->offset_y = offset_y;
	packet->offset_z = offset_z;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UNIBO_PARAMETERS, (const char *)packet, MAVLINK_MSG_ID_UNIBO_PARAMETERS_LEN, MAVLINK_MSG_ID_UNIBO_PARAMETERS_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UNIBO_PARAMETERS, (const char *)packet, MAVLINK_MSG_ID_UNIBO_PARAMETERS_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE UNIBO_PARAMETERS UNPACKING


/**
 * @brief Get field Offset_T from unibo_parameters message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_parameters_get_Offset_T(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field lat_mode from unibo_parameters message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_parameters_get_lat_mode(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field delta from unibo_parameters message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_parameters_get_delta(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field K1 from unibo_parameters message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_parameters_get_K1(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field L1 from unibo_parameters message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_parameters_get_L1(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field Ixy from unibo_parameters message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_parameters_get_Ixy(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field K2 from unibo_parameters message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_parameters_get_K2(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field L2 from unibo_parameters message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_parameters_get_L2(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Get field Iz from unibo_parameters message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_parameters_get_Iz(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  32);
}

/**
 * @brief Get field KpAttX from unibo_parameters message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_parameters_get_KpAttX(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  36);
}

/**
 * @brief Get field KpAttY from unibo_parameters message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_parameters_get_KpAttY(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  40);
}

/**
 * @brief Get field KpAttZ from unibo_parameters message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_parameters_get_KpAttZ(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  44);
}

/**
 * @brief Get field KdAttX from unibo_parameters message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_parameters_get_KdAttX(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  48);
}

/**
 * @brief Get field KdAttY from unibo_parameters message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_parameters_get_KdAttY(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  52);
}

/**
 * @brief Get field KdAttZ from unibo_parameters message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_parameters_get_KdAttZ(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  56);
}

/**
 * @brief Get field KiAttX from unibo_parameters message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_parameters_get_KiAttX(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  60);
}

/**
 * @brief Get field KiAttY from unibo_parameters message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_parameters_get_KiAttY(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  64);
}

/**
 * @brief Get field KiAttZ from unibo_parameters message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_parameters_get_KiAttZ(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  68);
}

/**
 * @brief Get field GE from unibo_parameters message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_parameters_get_GE(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  72);
}

/**
 * @brief Get field epsilon from unibo_parameters message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_parameters_get_epsilon(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  76);
}

/**
 * @brief Get field XY_Multiplier from unibo_parameters message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_parameters_get_XY_Multiplier(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  80);
}

/**
 * @brief Get field offset_x from unibo_parameters message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_parameters_get_offset_x(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  84);
}

/**
 * @brief Get field offset_y from unibo_parameters message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_parameters_get_offset_y(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  88);
}

/**
 * @brief Get field offset_z from unibo_parameters message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_parameters_get_offset_z(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  92);
}

/**
 * @brief Decode a unibo_parameters message into a struct
 *
 * @param msg The message to decode
 * @param unibo_parameters C-struct to decode the message contents into
 */
static inline void mavlink_msg_unibo_parameters_decode(const mavlink_message_t* msg, mavlink_unibo_parameters_t* unibo_parameters)
{
#if MAVLINK_NEED_BYTE_SWAP
	unibo_parameters->Offset_T = mavlink_msg_unibo_parameters_get_Offset_T(msg);
	unibo_parameters->lat_mode = mavlink_msg_unibo_parameters_get_lat_mode(msg);
	unibo_parameters->delta = mavlink_msg_unibo_parameters_get_delta(msg);
	unibo_parameters->K1 = mavlink_msg_unibo_parameters_get_K1(msg);
	unibo_parameters->L1 = mavlink_msg_unibo_parameters_get_L1(msg);
	unibo_parameters->Ixy = mavlink_msg_unibo_parameters_get_Ixy(msg);
	unibo_parameters->K2 = mavlink_msg_unibo_parameters_get_K2(msg);
	unibo_parameters->L2 = mavlink_msg_unibo_parameters_get_L2(msg);
	unibo_parameters->Iz = mavlink_msg_unibo_parameters_get_Iz(msg);
	unibo_parameters->KpAttX = mavlink_msg_unibo_parameters_get_KpAttX(msg);
	unibo_parameters->KpAttY = mavlink_msg_unibo_parameters_get_KpAttY(msg);
	unibo_parameters->KpAttZ = mavlink_msg_unibo_parameters_get_KpAttZ(msg);
	unibo_parameters->KdAttX = mavlink_msg_unibo_parameters_get_KdAttX(msg);
	unibo_parameters->KdAttY = mavlink_msg_unibo_parameters_get_KdAttY(msg);
	unibo_parameters->KdAttZ = mavlink_msg_unibo_parameters_get_KdAttZ(msg);
	unibo_parameters->KiAttX = mavlink_msg_unibo_parameters_get_KiAttX(msg);
	unibo_parameters->KiAttY = mavlink_msg_unibo_parameters_get_KiAttY(msg);
	unibo_parameters->KiAttZ = mavlink_msg_unibo_parameters_get_KiAttZ(msg);
	unibo_parameters->GE = mavlink_msg_unibo_parameters_get_GE(msg);
	unibo_parameters->epsilon = mavlink_msg_unibo_parameters_get_epsilon(msg);
	unibo_parameters->XY_Multiplier = mavlink_msg_unibo_parameters_get_XY_Multiplier(msg);
	unibo_parameters->offset_x = mavlink_msg_unibo_parameters_get_offset_x(msg);
	unibo_parameters->offset_y = mavlink_msg_unibo_parameters_get_offset_y(msg);
	unibo_parameters->offset_z = mavlink_msg_unibo_parameters_get_offset_z(msg);
#else
	memcpy(unibo_parameters, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_UNIBO_PARAMETERS_LEN);
#endif
}
