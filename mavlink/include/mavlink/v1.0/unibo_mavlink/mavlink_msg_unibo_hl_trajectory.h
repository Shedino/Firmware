// MESSAGE UNIBO_HL_TRAJECTORY PACKING

#define MAVLINK_MSG_ID_UNIBO_HL_TRAJECTORY 202

typedef struct __mavlink_unibo_hl_trajectory_t
{
 uint64_t Tstamp; ///< 
 float p_refX; ///< 
 float p_refY; ///< 
 float p_refZ; ///< 
 float dot_p_refX; ///< 
 float dot_p_refY; ///< 
 float dot_p_refZ; ///< 
 float dot2_p_refX; ///< 
 float dot2_p_refY; ///< 
 float dot2_p_refZ; ///< 
 float dot3_p_refX; ///< 
 float dot3_p_refY; ///< 
 float dot3_p_refZ; ///< 
 float dot4_p_refX; ///< 
 float dot4_p_refY; ///< 
 float dot4_p_refZ; ///< 
 float psi_ref; ///< 
 float dot_psi_ref; ///< 
 float dot2_psi_ref; ///< 
} mavlink_unibo_hl_trajectory_t;

#define MAVLINK_MSG_ID_UNIBO_HL_TRAJECTORY_LEN 80
#define MAVLINK_MSG_ID_202_LEN 80

#define MAVLINK_MSG_ID_UNIBO_HL_TRAJECTORY_CRC 182
#define MAVLINK_MSG_ID_202_CRC 182



#define MAVLINK_MESSAGE_INFO_UNIBO_HL_TRAJECTORY { \
	"UNIBO_HL_TRAJECTORY", \
	19, \
	{  { "Tstamp", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_unibo_hl_trajectory_t, Tstamp) }, \
         { "p_refX", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_unibo_hl_trajectory_t, p_refX) }, \
         { "p_refY", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_unibo_hl_trajectory_t, p_refY) }, \
         { "p_refZ", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_unibo_hl_trajectory_t, p_refZ) }, \
         { "dot_p_refX", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_unibo_hl_trajectory_t, dot_p_refX) }, \
         { "dot_p_refY", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_unibo_hl_trajectory_t, dot_p_refY) }, \
         { "dot_p_refZ", NULL, MAVLINK_TYPE_FLOAT, 0, 28, offsetof(mavlink_unibo_hl_trajectory_t, dot_p_refZ) }, \
         { "dot2_p_refX", NULL, MAVLINK_TYPE_FLOAT, 0, 32, offsetof(mavlink_unibo_hl_trajectory_t, dot2_p_refX) }, \
         { "dot2_p_refY", NULL, MAVLINK_TYPE_FLOAT, 0, 36, offsetof(mavlink_unibo_hl_trajectory_t, dot2_p_refY) }, \
         { "dot2_p_refZ", NULL, MAVLINK_TYPE_FLOAT, 0, 40, offsetof(mavlink_unibo_hl_trajectory_t, dot2_p_refZ) }, \
         { "dot3_p_refX", NULL, MAVLINK_TYPE_FLOAT, 0, 44, offsetof(mavlink_unibo_hl_trajectory_t, dot3_p_refX) }, \
         { "dot3_p_refY", NULL, MAVLINK_TYPE_FLOAT, 0, 48, offsetof(mavlink_unibo_hl_trajectory_t, dot3_p_refY) }, \
         { "dot3_p_refZ", NULL, MAVLINK_TYPE_FLOAT, 0, 52, offsetof(mavlink_unibo_hl_trajectory_t, dot3_p_refZ) }, \
         { "dot4_p_refX", NULL, MAVLINK_TYPE_FLOAT, 0, 56, offsetof(mavlink_unibo_hl_trajectory_t, dot4_p_refX) }, \
         { "dot4_p_refY", NULL, MAVLINK_TYPE_FLOAT, 0, 60, offsetof(mavlink_unibo_hl_trajectory_t, dot4_p_refY) }, \
         { "dot4_p_refZ", NULL, MAVLINK_TYPE_FLOAT, 0, 64, offsetof(mavlink_unibo_hl_trajectory_t, dot4_p_refZ) }, \
         { "psi_ref", NULL, MAVLINK_TYPE_FLOAT, 0, 68, offsetof(mavlink_unibo_hl_trajectory_t, psi_ref) }, \
         { "dot_psi_ref", NULL, MAVLINK_TYPE_FLOAT, 0, 72, offsetof(mavlink_unibo_hl_trajectory_t, dot_psi_ref) }, \
         { "dot2_psi_ref", NULL, MAVLINK_TYPE_FLOAT, 0, 76, offsetof(mavlink_unibo_hl_trajectory_t, dot2_psi_ref) }, \
         } \
}


/**
 * @brief Pack a unibo_hl_trajectory message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param p_refX 
 * @param p_refY 
 * @param p_refZ 
 * @param dot_p_refX 
 * @param dot_p_refY 
 * @param dot_p_refZ 
 * @param dot2_p_refX 
 * @param dot2_p_refY 
 * @param dot2_p_refZ 
 * @param dot3_p_refX 
 * @param dot3_p_refY 
 * @param dot3_p_refZ 
 * @param dot4_p_refX 
 * @param dot4_p_refY 
 * @param dot4_p_refZ 
 * @param psi_ref 
 * @param dot_psi_ref 
 * @param dot2_psi_ref 
 * @param Tstamp 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_unibo_hl_trajectory_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       float p_refX, float p_refY, float p_refZ, float dot_p_refX, float dot_p_refY, float dot_p_refZ, float dot2_p_refX, float dot2_p_refY, float dot2_p_refZ, float dot3_p_refX, float dot3_p_refY, float dot3_p_refZ, float dot4_p_refX, float dot4_p_refY, float dot4_p_refZ, float psi_ref, float dot_psi_ref, float dot2_psi_ref, uint64_t Tstamp)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_UNIBO_HL_TRAJECTORY_LEN];
	_mav_put_uint64_t(buf, 0, Tstamp);
	_mav_put_float(buf, 8, p_refX);
	_mav_put_float(buf, 12, p_refY);
	_mav_put_float(buf, 16, p_refZ);
	_mav_put_float(buf, 20, dot_p_refX);
	_mav_put_float(buf, 24, dot_p_refY);
	_mav_put_float(buf, 28, dot_p_refZ);
	_mav_put_float(buf, 32, dot2_p_refX);
	_mav_put_float(buf, 36, dot2_p_refY);
	_mav_put_float(buf, 40, dot2_p_refZ);
	_mav_put_float(buf, 44, dot3_p_refX);
	_mav_put_float(buf, 48, dot3_p_refY);
	_mav_put_float(buf, 52, dot3_p_refZ);
	_mav_put_float(buf, 56, dot4_p_refX);
	_mav_put_float(buf, 60, dot4_p_refY);
	_mav_put_float(buf, 64, dot4_p_refZ);
	_mav_put_float(buf, 68, psi_ref);
	_mav_put_float(buf, 72, dot_psi_ref);
	_mav_put_float(buf, 76, dot2_psi_ref);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_UNIBO_HL_TRAJECTORY_LEN);
#else
	mavlink_unibo_hl_trajectory_t packet;
	packet.Tstamp = Tstamp;
	packet.p_refX = p_refX;
	packet.p_refY = p_refY;
	packet.p_refZ = p_refZ;
	packet.dot_p_refX = dot_p_refX;
	packet.dot_p_refY = dot_p_refY;
	packet.dot_p_refZ = dot_p_refZ;
	packet.dot2_p_refX = dot2_p_refX;
	packet.dot2_p_refY = dot2_p_refY;
	packet.dot2_p_refZ = dot2_p_refZ;
	packet.dot3_p_refX = dot3_p_refX;
	packet.dot3_p_refY = dot3_p_refY;
	packet.dot3_p_refZ = dot3_p_refZ;
	packet.dot4_p_refX = dot4_p_refX;
	packet.dot4_p_refY = dot4_p_refY;
	packet.dot4_p_refZ = dot4_p_refZ;
	packet.psi_ref = psi_ref;
	packet.dot_psi_ref = dot_psi_ref;
	packet.dot2_psi_ref = dot2_psi_ref;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_UNIBO_HL_TRAJECTORY_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_UNIBO_HL_TRAJECTORY;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_UNIBO_HL_TRAJECTORY_LEN, MAVLINK_MSG_ID_UNIBO_HL_TRAJECTORY_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_UNIBO_HL_TRAJECTORY_LEN);
#endif
}

/**
 * @brief Pack a unibo_hl_trajectory message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param p_refX 
 * @param p_refY 
 * @param p_refZ 
 * @param dot_p_refX 
 * @param dot_p_refY 
 * @param dot_p_refZ 
 * @param dot2_p_refX 
 * @param dot2_p_refY 
 * @param dot2_p_refZ 
 * @param dot3_p_refX 
 * @param dot3_p_refY 
 * @param dot3_p_refZ 
 * @param dot4_p_refX 
 * @param dot4_p_refY 
 * @param dot4_p_refZ 
 * @param psi_ref 
 * @param dot_psi_ref 
 * @param dot2_psi_ref 
 * @param Tstamp 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_unibo_hl_trajectory_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           float p_refX,float p_refY,float p_refZ,float dot_p_refX,float dot_p_refY,float dot_p_refZ,float dot2_p_refX,float dot2_p_refY,float dot2_p_refZ,float dot3_p_refX,float dot3_p_refY,float dot3_p_refZ,float dot4_p_refX,float dot4_p_refY,float dot4_p_refZ,float psi_ref,float dot_psi_ref,float dot2_psi_ref,uint64_t Tstamp)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_UNIBO_HL_TRAJECTORY_LEN];
	_mav_put_uint64_t(buf, 0, Tstamp);
	_mav_put_float(buf, 8, p_refX);
	_mav_put_float(buf, 12, p_refY);
	_mav_put_float(buf, 16, p_refZ);
	_mav_put_float(buf, 20, dot_p_refX);
	_mav_put_float(buf, 24, dot_p_refY);
	_mav_put_float(buf, 28, dot_p_refZ);
	_mav_put_float(buf, 32, dot2_p_refX);
	_mav_put_float(buf, 36, dot2_p_refY);
	_mav_put_float(buf, 40, dot2_p_refZ);
	_mav_put_float(buf, 44, dot3_p_refX);
	_mav_put_float(buf, 48, dot3_p_refY);
	_mav_put_float(buf, 52, dot3_p_refZ);
	_mav_put_float(buf, 56, dot4_p_refX);
	_mav_put_float(buf, 60, dot4_p_refY);
	_mav_put_float(buf, 64, dot4_p_refZ);
	_mav_put_float(buf, 68, psi_ref);
	_mav_put_float(buf, 72, dot_psi_ref);
	_mav_put_float(buf, 76, dot2_psi_ref);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_UNIBO_HL_TRAJECTORY_LEN);
#else
	mavlink_unibo_hl_trajectory_t packet;
	packet.Tstamp = Tstamp;
	packet.p_refX = p_refX;
	packet.p_refY = p_refY;
	packet.p_refZ = p_refZ;
	packet.dot_p_refX = dot_p_refX;
	packet.dot_p_refY = dot_p_refY;
	packet.dot_p_refZ = dot_p_refZ;
	packet.dot2_p_refX = dot2_p_refX;
	packet.dot2_p_refY = dot2_p_refY;
	packet.dot2_p_refZ = dot2_p_refZ;
	packet.dot3_p_refX = dot3_p_refX;
	packet.dot3_p_refY = dot3_p_refY;
	packet.dot3_p_refZ = dot3_p_refZ;
	packet.dot4_p_refX = dot4_p_refX;
	packet.dot4_p_refY = dot4_p_refY;
	packet.dot4_p_refZ = dot4_p_refZ;
	packet.psi_ref = psi_ref;
	packet.dot_psi_ref = dot_psi_ref;
	packet.dot2_psi_ref = dot2_psi_ref;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_UNIBO_HL_TRAJECTORY_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_UNIBO_HL_TRAJECTORY;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_UNIBO_HL_TRAJECTORY_LEN, MAVLINK_MSG_ID_UNIBO_HL_TRAJECTORY_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_UNIBO_HL_TRAJECTORY_LEN);
#endif
}

/**
 * @brief Encode a unibo_hl_trajectory struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param unibo_hl_trajectory C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_unibo_hl_trajectory_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_unibo_hl_trajectory_t* unibo_hl_trajectory)
{
	return mavlink_msg_unibo_hl_trajectory_pack(system_id, component_id, msg, unibo_hl_trajectory->p_refX, unibo_hl_trajectory->p_refY, unibo_hl_trajectory->p_refZ, unibo_hl_trajectory->dot_p_refX, unibo_hl_trajectory->dot_p_refY, unibo_hl_trajectory->dot_p_refZ, unibo_hl_trajectory->dot2_p_refX, unibo_hl_trajectory->dot2_p_refY, unibo_hl_trajectory->dot2_p_refZ, unibo_hl_trajectory->dot3_p_refX, unibo_hl_trajectory->dot3_p_refY, unibo_hl_trajectory->dot3_p_refZ, unibo_hl_trajectory->dot4_p_refX, unibo_hl_trajectory->dot4_p_refY, unibo_hl_trajectory->dot4_p_refZ, unibo_hl_trajectory->psi_ref, unibo_hl_trajectory->dot_psi_ref, unibo_hl_trajectory->dot2_psi_ref, unibo_hl_trajectory->Tstamp);
}

/**
 * @brief Encode a unibo_hl_trajectory struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param unibo_hl_trajectory C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_unibo_hl_trajectory_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_unibo_hl_trajectory_t* unibo_hl_trajectory)
{
	return mavlink_msg_unibo_hl_trajectory_pack_chan(system_id, component_id, chan, msg, unibo_hl_trajectory->p_refX, unibo_hl_trajectory->p_refY, unibo_hl_trajectory->p_refZ, unibo_hl_trajectory->dot_p_refX, unibo_hl_trajectory->dot_p_refY, unibo_hl_trajectory->dot_p_refZ, unibo_hl_trajectory->dot2_p_refX, unibo_hl_trajectory->dot2_p_refY, unibo_hl_trajectory->dot2_p_refZ, unibo_hl_trajectory->dot3_p_refX, unibo_hl_trajectory->dot3_p_refY, unibo_hl_trajectory->dot3_p_refZ, unibo_hl_trajectory->dot4_p_refX, unibo_hl_trajectory->dot4_p_refY, unibo_hl_trajectory->dot4_p_refZ, unibo_hl_trajectory->psi_ref, unibo_hl_trajectory->dot_psi_ref, unibo_hl_trajectory->dot2_psi_ref, unibo_hl_trajectory->Tstamp);
}

/**
 * @brief Send a unibo_hl_trajectory message
 * @param chan MAVLink channel to send the message
 *
 * @param p_refX 
 * @param p_refY 
 * @param p_refZ 
 * @param dot_p_refX 
 * @param dot_p_refY 
 * @param dot_p_refZ 
 * @param dot2_p_refX 
 * @param dot2_p_refY 
 * @param dot2_p_refZ 
 * @param dot3_p_refX 
 * @param dot3_p_refY 
 * @param dot3_p_refZ 
 * @param dot4_p_refX 
 * @param dot4_p_refY 
 * @param dot4_p_refZ 
 * @param psi_ref 
 * @param dot_psi_ref 
 * @param dot2_psi_ref 
 * @param Tstamp 
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_unibo_hl_trajectory_send(mavlink_channel_t chan, float p_refX, float p_refY, float p_refZ, float dot_p_refX, float dot_p_refY, float dot_p_refZ, float dot2_p_refX, float dot2_p_refY, float dot2_p_refZ, float dot3_p_refX, float dot3_p_refY, float dot3_p_refZ, float dot4_p_refX, float dot4_p_refY, float dot4_p_refZ, float psi_ref, float dot_psi_ref, float dot2_psi_ref, uint64_t Tstamp)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_UNIBO_HL_TRAJECTORY_LEN];
	_mav_put_uint64_t(buf, 0, Tstamp);
	_mav_put_float(buf, 8, p_refX);
	_mav_put_float(buf, 12, p_refY);
	_mav_put_float(buf, 16, p_refZ);
	_mav_put_float(buf, 20, dot_p_refX);
	_mav_put_float(buf, 24, dot_p_refY);
	_mav_put_float(buf, 28, dot_p_refZ);
	_mav_put_float(buf, 32, dot2_p_refX);
	_mav_put_float(buf, 36, dot2_p_refY);
	_mav_put_float(buf, 40, dot2_p_refZ);
	_mav_put_float(buf, 44, dot3_p_refX);
	_mav_put_float(buf, 48, dot3_p_refY);
	_mav_put_float(buf, 52, dot3_p_refZ);
	_mav_put_float(buf, 56, dot4_p_refX);
	_mav_put_float(buf, 60, dot4_p_refY);
	_mav_put_float(buf, 64, dot4_p_refZ);
	_mav_put_float(buf, 68, psi_ref);
	_mav_put_float(buf, 72, dot_psi_ref);
	_mav_put_float(buf, 76, dot2_psi_ref);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UNIBO_HL_TRAJECTORY, buf, MAVLINK_MSG_ID_UNIBO_HL_TRAJECTORY_LEN, MAVLINK_MSG_ID_UNIBO_HL_TRAJECTORY_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UNIBO_HL_TRAJECTORY, buf, MAVLINK_MSG_ID_UNIBO_HL_TRAJECTORY_LEN);
#endif
#else
	mavlink_unibo_hl_trajectory_t packet;
	packet.Tstamp = Tstamp;
	packet.p_refX = p_refX;
	packet.p_refY = p_refY;
	packet.p_refZ = p_refZ;
	packet.dot_p_refX = dot_p_refX;
	packet.dot_p_refY = dot_p_refY;
	packet.dot_p_refZ = dot_p_refZ;
	packet.dot2_p_refX = dot2_p_refX;
	packet.dot2_p_refY = dot2_p_refY;
	packet.dot2_p_refZ = dot2_p_refZ;
	packet.dot3_p_refX = dot3_p_refX;
	packet.dot3_p_refY = dot3_p_refY;
	packet.dot3_p_refZ = dot3_p_refZ;
	packet.dot4_p_refX = dot4_p_refX;
	packet.dot4_p_refY = dot4_p_refY;
	packet.dot4_p_refZ = dot4_p_refZ;
	packet.psi_ref = psi_ref;
	packet.dot_psi_ref = dot_psi_ref;
	packet.dot2_psi_ref = dot2_psi_ref;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UNIBO_HL_TRAJECTORY, (const char *)&packet, MAVLINK_MSG_ID_UNIBO_HL_TRAJECTORY_LEN, MAVLINK_MSG_ID_UNIBO_HL_TRAJECTORY_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UNIBO_HL_TRAJECTORY, (const char *)&packet, MAVLINK_MSG_ID_UNIBO_HL_TRAJECTORY_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_UNIBO_HL_TRAJECTORY_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_unibo_hl_trajectory_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float p_refX, float p_refY, float p_refZ, float dot_p_refX, float dot_p_refY, float dot_p_refZ, float dot2_p_refX, float dot2_p_refY, float dot2_p_refZ, float dot3_p_refX, float dot3_p_refY, float dot3_p_refZ, float dot4_p_refX, float dot4_p_refY, float dot4_p_refZ, float psi_ref, float dot_psi_ref, float dot2_psi_ref, uint64_t Tstamp)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint64_t(buf, 0, Tstamp);
	_mav_put_float(buf, 8, p_refX);
	_mav_put_float(buf, 12, p_refY);
	_mav_put_float(buf, 16, p_refZ);
	_mav_put_float(buf, 20, dot_p_refX);
	_mav_put_float(buf, 24, dot_p_refY);
	_mav_put_float(buf, 28, dot_p_refZ);
	_mav_put_float(buf, 32, dot2_p_refX);
	_mav_put_float(buf, 36, dot2_p_refY);
	_mav_put_float(buf, 40, dot2_p_refZ);
	_mav_put_float(buf, 44, dot3_p_refX);
	_mav_put_float(buf, 48, dot3_p_refY);
	_mav_put_float(buf, 52, dot3_p_refZ);
	_mav_put_float(buf, 56, dot4_p_refX);
	_mav_put_float(buf, 60, dot4_p_refY);
	_mav_put_float(buf, 64, dot4_p_refZ);
	_mav_put_float(buf, 68, psi_ref);
	_mav_put_float(buf, 72, dot_psi_ref);
	_mav_put_float(buf, 76, dot2_psi_ref);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UNIBO_HL_TRAJECTORY, buf, MAVLINK_MSG_ID_UNIBO_HL_TRAJECTORY_LEN, MAVLINK_MSG_ID_UNIBO_HL_TRAJECTORY_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UNIBO_HL_TRAJECTORY, buf, MAVLINK_MSG_ID_UNIBO_HL_TRAJECTORY_LEN);
#endif
#else
	mavlink_unibo_hl_trajectory_t *packet = (mavlink_unibo_hl_trajectory_t *)msgbuf;
	packet->Tstamp = Tstamp;
	packet->p_refX = p_refX;
	packet->p_refY = p_refY;
	packet->p_refZ = p_refZ;
	packet->dot_p_refX = dot_p_refX;
	packet->dot_p_refY = dot_p_refY;
	packet->dot_p_refZ = dot_p_refZ;
	packet->dot2_p_refX = dot2_p_refX;
	packet->dot2_p_refY = dot2_p_refY;
	packet->dot2_p_refZ = dot2_p_refZ;
	packet->dot3_p_refX = dot3_p_refX;
	packet->dot3_p_refY = dot3_p_refY;
	packet->dot3_p_refZ = dot3_p_refZ;
	packet->dot4_p_refX = dot4_p_refX;
	packet->dot4_p_refY = dot4_p_refY;
	packet->dot4_p_refZ = dot4_p_refZ;
	packet->psi_ref = psi_ref;
	packet->dot_psi_ref = dot_psi_ref;
	packet->dot2_psi_ref = dot2_psi_ref;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UNIBO_HL_TRAJECTORY, (const char *)packet, MAVLINK_MSG_ID_UNIBO_HL_TRAJECTORY_LEN, MAVLINK_MSG_ID_UNIBO_HL_TRAJECTORY_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UNIBO_HL_TRAJECTORY, (const char *)packet, MAVLINK_MSG_ID_UNIBO_HL_TRAJECTORY_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE UNIBO_HL_TRAJECTORY UNPACKING


/**
 * @brief Get field p_refX from unibo_hl_trajectory message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_hl_trajectory_get_p_refX(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field p_refY from unibo_hl_trajectory message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_hl_trajectory_get_p_refY(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field p_refZ from unibo_hl_trajectory message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_hl_trajectory_get_p_refZ(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field dot_p_refX from unibo_hl_trajectory message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_hl_trajectory_get_dot_p_refX(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field dot_p_refY from unibo_hl_trajectory message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_hl_trajectory_get_dot_p_refY(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field dot_p_refZ from unibo_hl_trajectory message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_hl_trajectory_get_dot_p_refZ(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  28);
}

/**
 * @brief Get field dot2_p_refX from unibo_hl_trajectory message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_hl_trajectory_get_dot2_p_refX(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  32);
}

/**
 * @brief Get field dot2_p_refY from unibo_hl_trajectory message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_hl_trajectory_get_dot2_p_refY(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  36);
}

/**
 * @brief Get field dot2_p_refZ from unibo_hl_trajectory message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_hl_trajectory_get_dot2_p_refZ(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  40);
}

/**
 * @brief Get field dot3_p_refX from unibo_hl_trajectory message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_hl_trajectory_get_dot3_p_refX(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  44);
}

/**
 * @brief Get field dot3_p_refY from unibo_hl_trajectory message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_hl_trajectory_get_dot3_p_refY(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  48);
}

/**
 * @brief Get field dot3_p_refZ from unibo_hl_trajectory message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_hl_trajectory_get_dot3_p_refZ(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  52);
}

/**
 * @brief Get field dot4_p_refX from unibo_hl_trajectory message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_hl_trajectory_get_dot4_p_refX(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  56);
}

/**
 * @brief Get field dot4_p_refY from unibo_hl_trajectory message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_hl_trajectory_get_dot4_p_refY(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  60);
}

/**
 * @brief Get field dot4_p_refZ from unibo_hl_trajectory message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_hl_trajectory_get_dot4_p_refZ(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  64);
}

/**
 * @brief Get field psi_ref from unibo_hl_trajectory message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_hl_trajectory_get_psi_ref(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  68);
}

/**
 * @brief Get field dot_psi_ref from unibo_hl_trajectory message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_hl_trajectory_get_dot_psi_ref(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  72);
}

/**
 * @brief Get field dot2_psi_ref from unibo_hl_trajectory message
 *
 * @return 
 */
static inline float mavlink_msg_unibo_hl_trajectory_get_dot2_psi_ref(const mavlink_message_t* msg)
{
	return _MAV_RETURN_float(msg,  76);
}

/**
 * @brief Get field Tstamp from unibo_hl_trajectory message
 *
 * @return 
 */
static inline uint64_t mavlink_msg_unibo_hl_trajectory_get_Tstamp(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Decode a unibo_hl_trajectory message into a struct
 *
 * @param msg The message to decode
 * @param unibo_hl_trajectory C-struct to decode the message contents into
 */
static inline void mavlink_msg_unibo_hl_trajectory_decode(const mavlink_message_t* msg, mavlink_unibo_hl_trajectory_t* unibo_hl_trajectory)
{
#if MAVLINK_NEED_BYTE_SWAP
	unibo_hl_trajectory->Tstamp = mavlink_msg_unibo_hl_trajectory_get_Tstamp(msg);
	unibo_hl_trajectory->p_refX = mavlink_msg_unibo_hl_trajectory_get_p_refX(msg);
	unibo_hl_trajectory->p_refY = mavlink_msg_unibo_hl_trajectory_get_p_refY(msg);
	unibo_hl_trajectory->p_refZ = mavlink_msg_unibo_hl_trajectory_get_p_refZ(msg);
	unibo_hl_trajectory->dot_p_refX = mavlink_msg_unibo_hl_trajectory_get_dot_p_refX(msg);
	unibo_hl_trajectory->dot_p_refY = mavlink_msg_unibo_hl_trajectory_get_dot_p_refY(msg);
	unibo_hl_trajectory->dot_p_refZ = mavlink_msg_unibo_hl_trajectory_get_dot_p_refZ(msg);
	unibo_hl_trajectory->dot2_p_refX = mavlink_msg_unibo_hl_trajectory_get_dot2_p_refX(msg);
	unibo_hl_trajectory->dot2_p_refY = mavlink_msg_unibo_hl_trajectory_get_dot2_p_refY(msg);
	unibo_hl_trajectory->dot2_p_refZ = mavlink_msg_unibo_hl_trajectory_get_dot2_p_refZ(msg);
	unibo_hl_trajectory->dot3_p_refX = mavlink_msg_unibo_hl_trajectory_get_dot3_p_refX(msg);
	unibo_hl_trajectory->dot3_p_refY = mavlink_msg_unibo_hl_trajectory_get_dot3_p_refY(msg);
	unibo_hl_trajectory->dot3_p_refZ = mavlink_msg_unibo_hl_trajectory_get_dot3_p_refZ(msg);
	unibo_hl_trajectory->dot4_p_refX = mavlink_msg_unibo_hl_trajectory_get_dot4_p_refX(msg);
	unibo_hl_trajectory->dot4_p_refY = mavlink_msg_unibo_hl_trajectory_get_dot4_p_refY(msg);
	unibo_hl_trajectory->dot4_p_refZ = mavlink_msg_unibo_hl_trajectory_get_dot4_p_refZ(msg);
	unibo_hl_trajectory->psi_ref = mavlink_msg_unibo_hl_trajectory_get_psi_ref(msg);
	unibo_hl_trajectory->dot_psi_ref = mavlink_msg_unibo_hl_trajectory_get_dot_psi_ref(msg);
	unibo_hl_trajectory->dot2_psi_ref = mavlink_msg_unibo_hl_trajectory_get_dot2_psi_ref(msg);
#else
	memcpy(unibo_hl_trajectory, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_UNIBO_HL_TRAJECTORY_LEN);
#endif
}
